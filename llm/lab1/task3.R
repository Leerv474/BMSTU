f <- function(x1, x2) {
  5*x1^2 + 5*x2^2 - 8*x1*x2
}

grad <- function(x) {
  x1 <- x[1]; x2 <- x[2]
  c(10*x1 - 8*x2,
    10*x2 - 8*x1)
}

gradient_descent <- function(start, lr = 0.1, epochs = 1000, tol = 1e-6) {
  x <- start
  for (i in 1:epochs) {
    g <- grad(x)
    new_x <- x - lr * g
    if (sqrt(sum((new_x - x)^2)) < tol) { # проверка сходимости
      cat("Сошлось за", i, "итераций\n")
      return(list(min_point = new_x, min_value = f(new_x[1], new_x[2])))
    }
    x <- new_x
  }
  cat("Достигнут лимит итераций\n")
  list(min_point = x, min_value = f(x[1], x[2]))
}

set.seed(42)
res <- gradient_descent(start = c(2, 2), lr = 0.05)
print(res)
