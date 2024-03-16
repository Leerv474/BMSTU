#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

void findDivisors(int n) {
    int sum = 0;
    int count = 0;
    cout << "Делители числа " << n << ": ";
    auto start = high_resolution_clock::now();
    for (int i = 1; i <= n; ++i) {
        if (n % i == 0) {
            sum += i;
            cout << i << " ";
            count++;
        }
    }
    cout << "\nКоличество делителей: " << count << endl;
    cout << "Сумма делителей: " << sum << endl;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Время выполнения: " << duration.count() << " микросекунд." << endl;
}

int main() {
    int number;
    cout << "Введите натуральное число: ";
    cin >> number;

    if (number <= 0) {
        cout << "Число должно быть натуральным." << endl;
        return 1;
    }

    findDivisors(number);

    return 0;
}

