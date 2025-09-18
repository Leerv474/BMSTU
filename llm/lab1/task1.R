Name <- c(
    "Aluminum",
    "Copper",
    "Zinc",
    "Nickel",
    "Iron",
    "Tin",
    "Lead",
    "Silver",
    "Gold",
    "Platinum",
    "Chromium",
    "Cobalt",
    "Manganese",
    "Titanium",
    "Magnesium",
    "Cadmium",
    "Mercury",
    "Tungsten",
    "Lithium",
    "Sodium",
    "Potassium",
    "Calcium",
    "Barium",
    "Strontium",
    "Vanadium",
    "Molybdenum",
    "Palladium"
)
set.seed(123) # reproducibility

N <- length(Name)

# Generate BirthYear first
BirthYear <- sample(1970:1994, N, replace = TRUE)

Cost <- ifelse(
    BirthYear < 1977,
    runif(
        N,
        min = 0.9 * (log(2009 - BirthYear) + 1) * 59000,
        max = 1.1 * (log(2009 - BirthYear) + 1) * 59000
    ),
    runif(
        N,
        min = 0.9 * (log2(2009 - BirthYear) + 1) * 69000,
        max = 1.1 * (log2(2009 - BirthYear) + 1) * 69000
    )
)

Salary <- runif(
    N,
    min = 0.9 * (log2(2007 + BirthYear) + 1) * 79000,
    max = 1.1 * (log2(2007 + BirthYear) + 1) * 79000
)

df <- data.frame(
    Nrow = 1:N,
    Name = Name,
    BirthYear = BirthYear,
    Count = sample(100:1000, N, replace = TRUE),
    Salary = round(Salary),
    Cost = round(Cost),
    PowerIOn = runif(N, 5, 15),
    Electro = runif(N, 0.7, 3.5),
    Radius = runif(N, 100, 250)
)

social_deduction <- numeric(N)

for (i in 1:N) {
    years <- df$BirthYear[i]:2009 + 1
    if (df$BirthYear[i] < 1977) {
        yearly_cost <- (log(years - df$BirthYear[i]) + 1) * 59000
    } else {
        yearly_cost <- (log2(years - df$BirthYear[i]) + 1) * 69000
    }
    social_deduction[i] <- sum(yearly_cost) * 0.1
}

df$SocialDeduction <- round(social_deduction)

df$Rank <- rank(df$Salary)

df_ranked <- df[order(df$Rank), ]

options(width = 200)
print(df_ranked)
# print(df_ranked[, setdiff(names(df), "Rank")])
plot(df)
