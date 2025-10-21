if (!requireNamespace("tidyverse", quietly = TRUE)) install.packages("tidyverse")
if (!requireNamespace("caret", quietly = TRUE)) install.packages("caret")
if (!requireNamespace("class", quietly = TRUE)) install.packages("class")
if (!requireNamespace("kknn", quietly = TRUE)) install.packages("kknn")
if (!requireNamespace("pROC", quietly = TRUE)) install.packages("pROC")

library(tidyverse)
library(caret)
library(class)
library(kknn)
library(pROC)

set.seed(123)

df <- read_csv("~/Documents/BMSTU/llm/lab2/thyroid_data.csv")

stopifnot("Заполните df реальными данными: колонки Kl, Y3, Y5, Y7, Y9" = TRUE)


df <- df %>% filter(!is.na(Kl))

features <- c("Y3","Y5","Y7","Y9")

for (f in features) {
  if (any(is.na(df[[f]]))) {
    df[[f]][is.na(df[[f]])] <- median(df[[f]], na.rm = TRUE)
  }
}

df <- df %>% mutate(Kl = factor(Kl))

preProc <- preProcess(df %>% select(all_of(features)), method = c("center","scale"))
X_scaled <- predict(preProc, df %>% select(all_of(features)))
df_scaled <- bind_cols(df %>% select(Kl), X_scaled)

trainIndex <- createDataPartition(df_scaled$Kl, p = 0.7, list = FALSE)
train <- df_scaled[trainIndex, ]
test  <- df_scaled[-trainIndex, ]

x_train <- as.matrix(train %>% select(-Kl))
y_train <- train$Kl
x_test  <- as.matrix(test %>% select(-Kl))
y_test  <- test$Kl

K_val <- 37

K_use <- min(K_val, nrow(train) - 1)
if (K_use < 1) stop("Слишком мало наблюдений в train для KNN")

knn_pred <- knn(train = x_train, test = x_test, cl = y_train, k = K_use)
knn_cm <- confusionMatrix(knn_pred, y_test)
cat("=== K-NN (k =", K_use, ") ===\n")
print(knn_cm)

kernel_epanechnikov <- function(u) {
  w <- ifelse(u <= 1, (1 - u^2), 0)
  return(w)
}

kernel_eddy <- function(u) {
  exp(-(abs(u)^3))
}

parzen_density_class <- function(x, X_class, h, kernel_fun) {
  if (nrow(X_class) == 0) return(0)
  dists <- sqrt(rowSums((t(t(X_class) - x))^2))
  u <- dists / h
  vals <- kernel_fun(u)
  
  d <- ncol(X_class)
  density <- sum(vals) / (nrow(X_class) * (h^d))
  return(density)
}

parzen_predict <- function(x_test_matrix, x_train_matrix, y_train_factor, h, kernel_name = "epanechnikov") {
  kernel_fun <- switch(kernel_name,
                       "epanechnikov" = kernel_epanechnikov,
                       "eddy" = kernel_eddy,
                       stop("Unknown kernel"))
  classes <- levels(y_train_factor)
  n_test <- nrow(x_test_matrix)
  preds <- factor(rep(NA, n_test), levels = classes)

  X_by_class <- lapply(classes, function(cl) x_train_matrix[which(y_train_factor == cl), , drop = FALSE])
  names(X_by_class) <- classes
  
  for (i in seq_len(n_test)) {
    x <- x_test_matrix[i, ]
    dens <- sapply(classes, function(cl) parzen_density_class(x, X_by_class[[cl]], h, kernel_fun))
    priors <- sapply(classes, function(cl) nrow(X_by_class[[cl]]) / nrow(x_train_matrix))
    post <- dens * priors
    preds[i] <- classes[which.max(post)]
  }
  return(preds)
}

cv_error_for_h <- function(h, x_train, y_train, kernel_name, folds = 5) {
  if (h <= 0) return(1)
  folds_idx <- createFolds(y_train, k = folds)
  errs <- c()
  for (fold in folds_idx) {
    X_tr <- x_train[-fold, , drop = FALSE]
    y_tr <- y_train[-fold]
    X_val <- x_train[fold, , drop = FALSE]
    y_val <- y_train[fold]
    pred_val <- parzen_predict(X_val, X_tr, y_tr, h = as.numeric(h), kernel_name = kernel_name)
    errs <- c(errs, mean(pred_val != y_val))
  }
  mean(errs)
}

optimize_parzen_h <- function(x_train, y_train, kernel_name, h_init = NULL) {
  if (is.null(h_init)) {
    pairwise <- as.matrix(dist(x_train))
    h0 <- median(pairwise[upper.tri(pairwise)], na.rm = TRUE)
    if (h0 == 0 || is.na(h0)) h0 <- 1
    h_init <- h0
  }
  obj <- function(logh) {
    h <- exp(logh)
    cv_error_for_h(h, x_train, y_train, kernel_name, folds = 5)
  }
  res <- optim(par = log(h_init), fn = obj, method = "Nelder-Mead",
               control = list(maxit = 200))
  h_opt <- exp(res$par)
  list(h_opt = as.numeric(h_opt), value = res$value, conv = res$convergence, optim_res = res)
}

kernels_to_try <- c("epanechnikov","eddy")
parzen_results <- list()

for (kname in kernels_to_try) {
  cat("Optimizing Parzen (kernel =", kname, ") ...\n")
  res <- optimize_parzen_h(x_train, y_train, kernel_name = kname)
  cat(sprintf("Kernel %s: h_opt = %.4f, CV error = %.4f, convergence = %d\n",
              kname, res$h_opt, res$value, res$conv))
  # Предсказание на тесте
  pred_test <- parzen_predict(x_test, x_train, y_train, h = res$h_opt, kernel_name = kname)
  cm <- confusionMatrix(pred_test, y_test)
  parzen_results[[kname]] <- list(opt = res, cm = cm, pred = pred_test)
  print(cm)
}

cat("\n=== Сравнение Accuracy на тестовой выборке ===\n")
knn_acc <- knn_cm$overall["Accuracy"]
parzen_summary <- tibble(
  kernel = names(parzen_results),
  accuracy = sapply(parzen_results, function(z) z$cm$overall["Accuracy"]),
  cv_error = sapply(parzen_results, function(z) z$opt$value),
  h_opt = sapply(parzen_results, function(z) z$opt$h_opt)
)
res_table <- bind_rows(
  tibble(method = "KNN", param = paste0("k=", K_use), Accuracy = unname(knn_acc)),
  parzen_summary %>% transmute(method = paste0("Parzen-", kernel),
                               param = paste0("h=", round(h_opt,4)),
                               Accuracy = unname(accuracy))
)
print(res_table)

library(ggplot2)
pca <- prcomp(rbind(x_train, x_test), center = FALSE, scale. = FALSE)
pcs <- as.data.frame(pca$x)
n_train <- nrow(x_train)
pcs_df <- tibble(PC1 = pcs[(n_train+1):nrow(pcs), 1],
                 PC2 = pcs[(n_train+1):nrow(pcs), 2],
                 True = y_test,
                 KNN = knn_pred,
                 Parzen_epanechnikov = parzen_results[["epanechnikov"]]$pred,
                 Parzen_eddy = parzen_results[["eddy"]]$pred)

plot_pred <- function(df_plot, pred_col, title) {
  ggplot(df_plot, aes_string(x = "PC1", y = "PC2", color = pred_col, shape = "True")) +
    geom_point(size = 3, alpha = 0.9) +
    labs(title = title, color = "Predicted", shape = "True class") +
    theme_minimal()
}

p1 <- plot_pred(pcs_df, "KNN", paste0("KNN (k=", K_use, ") — тестовая выборка"))
p2 <- plot_pred(pcs_df, "Parzen_epanechnikov", paste0("Parzen (epanechnikov), h=", round(parzen_results[["epanechnikov"]]$opt$h_opt,3)))
p3 <- plot_pred(pcs_df, "Parzen_eddy", paste0("Parzen (eddy), h=", round(parzen_results[["eddy"]]$opt$h_opt,3)))

print(p1)
print(p2)
print(p3)


cat("\n=== Лучшие параметры (минимум ошибки на CV) для Parzen ===\n")
for (kname in kernels_to_try) {
  r <- parzen_results[[kname]]$opt
  cat(sprintf("Kernel: %s | h_opt = %.6f | CV_error = %.6f | optim_conv = %d\n",
              kname, r$h_opt, r$value, r$conv))
}
cat(sprintf("KNN: k = %d (фиксировано в задании)\n", K_use)) 
