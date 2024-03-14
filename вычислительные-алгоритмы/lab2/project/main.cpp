#include <iostream>
#include <cmath>
#include <vector>
#include <chrono> // Include chrono library for timing

using namespace std;
using namespace std::chrono; // Namespace for chrono library

// Функция для проверки условия задачи и вывода пары чисел
void checkPairs(const vector<double>& sequence) {
    int n = sequence.size();
    auto start = high_resolution_clock::now(); // Start timing
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            double sum = sequence[i] + sequence[j];
            double squareSum = pow(sum, 2);
            double sumSquares = pow(sequence[i], 2) + pow(sequence[j], 2);
            if (squareSum == sumSquares) {
                auto stop = high_resolution_clock::now(); // Stop timing
                auto duration = duration_cast<microseconds>(stop - start); // Calculate duration
                cout << "Найдена пара чисел: (" << sequence[i] << ", " << sequence[j] << ")" << endl;
                cout << "Время выполнения: " << duration.count() << " микросекунд." << endl;
                return;
            }
        }
    }
    auto stop = high_resolution_clock::now(); // Stop timing
    auto duration = duration_cast<microseconds>(stop - start); // Calculate duration
    cout << "Такая пара чисел не найдена." << endl;
    cout << "Время выполнения: " << duration.count() << " микросекунд." << endl;
}

int main() {
    int n;
    cout << "Введите количество чисел в последовательности: ";
    cin >> n;

    if (n <= 1) {
        cout << "Последовательность должна содержать как минимум два числа." << endl;
        return 1;
    }

    vector<double> sequence(n);
    cout << "Введите элементы последовательности: ";
    for (int i = 0; i < n; ++i) {
        cin >> sequence[i];
    }

    checkPairs(sequence);

    return 0;
}

