Ок, сделаем по делу. У тебя лабораторная состоит из **3 частей**, и если просто “сдать”, нужно закрыть каждую:

---

# 1. Теория (кратко, но по сути)

### Confusion Matrix

* **TP** — правильно предсказали положительный класс
* **FP** — предсказали положительный, но он отрицательный
* **TN** — правильно предсказали отрицательный
* **FN** — пропустили положительный

---

### Метрики

* **Accuracy**
  [
  \frac{TP + TN}{TP + FP + TN + FN}
  ]
  → работает только при **сбалансированных данных**

* **Precision**
  [
  \frac{TP}{TP + FP}
  ]
  → насколько “чистые” положительные предсказания

* **Recall**
  [
  \frac{TP}{TP + FN}
  ]
  → сколько реальных положительных нашли

* **Specificity (TNR)**
  [
  \frac{TN}{TN + FP}
  ]

* **F1-score**
  [
  2 \cdot \frac{Precision \cdot Recall}{Precision + Recall}
  ]

---

### ROC и PR

* **ROC-кривая**: TPR vs FPR

* **ROC AUC**: вероятность, что модель ранжирует правильно

  * 0.5 = случайная модель

* **PR-кривая**: Precision vs Recall

* **PR AUC** — лучше при **дисбалансе**

---

# 2. Практика (пример на Python)

Если у тебя нет своего датасета — бери стандартный.

## Бинарная классификация

```python
from sklearn.datasets import make_classification
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report, roc_auc_score, average_precision_score
from sklearn.linear_model import LogisticRegression
from sklearn.ensemble import RandomForestClassifier

X, y = make_classification(n_samples=1000, weights=[0.7, 0.3], random_state=42)

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2)

models = {
    "LogReg": LogisticRegression(),
    "RF": RandomForestClassifier()
}

for name, model in models.items():
    model.fit(X_train, y_train)
    y_pred = model.predict(X_test)
    y_prob = model.predict_proba(X_test)[:, 1]

    print(name)
    print(classification_report(y_test, y_pred))
    print("ROC AUC:", roc_auc_score(y_test, y_prob))
    print("PR AUC:", average_precision_score(y_test, y_prob))
```

---

## Многоклассовая классификация

```python
from sklearn.datasets import load_iris
from sklearn.metrics import classification_report
from sklearn.linear_model import LogisticRegression

X, y = load_iris(return_X_y=True)

model = LogisticRegression(max_iter=200)
model.fit(X, y)

y_pred = model.predict(X)

print(classification_report(y, y_pred))
```

Смотри на:

* **macro avg**
* **micro avg**
* **weighted avg**

---

# 3. Итоговые выводы (это важно для оценки)

Вот готовый смысл, который можно вставить:

### 1. Метрики и баланс классов

* При **сбалансированных данных** подходит accuracy
* При **дисбалансе**:

  * precision — если важны ложные срабатывания
  * recall — если важно не пропустить
  * PR AUC — лучший выбор

---

### 2. ROC AUC vs PR AUC

* ROC AUC может выглядеть хорошо даже при дисбалансе
* PR AUC честнее отражает качество при редком классе

---

### 3. Multiclass averaging

* **micro** — учитывает все объекты (как accuracy)
* **macro** — равный вес классам
* **weighted** — учитывает дисбаланс

---

### 4. OvR vs OvO

* **OvR (one-vs-rest)** — один класс против всех
* **OvO (one-vs-one)** — попарное сравнение классов
* OvO точнее, но дороже по вычислениям

---

# 4. Контрольные вопросы (готовые ответы)

### 1

Классификация — задача предсказания класса.
Бинарная — 2 класса, многоклассовая — >2.

### 2

Confusion matrix — таблица ошибок классификации (TP, FP, TN, FN).

### 3

Accuracy — общая точность
Precision — точность положительных

### 4

* Recall важен: медицина (не пропустить болезнь)
* Precision важен: спам-фильтр

### 5

Specificity — доля правильно найденных отрицательных

### 6

F1 — баланс precision и recall одним числом

### 7

ROC — кривая TPR vs FPR
AUC = 0.5 → случайная модель

### 8

PR AUC лучше при дисбалансе, т.к. учитывает precision

### 9

* micro — общий результат
* macro — равные классы
* weighted — с учетом размера

### 10

* OvR — проще
* OvO — точнее, но тяжелее

---

# Важный момент

Ты не уточнил:
👉 нужно просто **отчёт** или **код + графики (ROC/PR)** тоже?

Если нужно — сделаю тебе:

* готовый **отчёт (Word/PDF)**
* или **код с построением графиков** (как требуют преподаватели)
