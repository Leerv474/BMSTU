#include <iostream>
#include <cstdlib>
#include <ctime>

void printArray(int** array, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << array[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void shellSort(int* arr, int size) {
    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; ++i) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

int main() {
    const int size = 5; // Size of the square matrix
    int** matrix = new int*[size];

    // Fill the matrix with random numbers in the range [30, 80]
    srand(time(nullptr));
    for (int i = 0; i < size; ++i) {
        matrix[i] = new int[size];
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = rand() % 51 + 30; // Random number between 30 and 80
        }
    }

    std::cout << "Original Matrix:" << std::endl;
    printArray(matrix, size);

    // Sort the secondary diagonal
    int* diagonal = new int[size];
    for (int i = 0; i < size; ++i) {
        diagonal[i] = matrix[i][size - 1 - i];
    }

    shellSort(diagonal, size);

    // Place the sorted diagonal back into the matrix
    for (int i = 0; i < size; ++i) {
        matrix[i][size - 1 - i] = diagonal[i];
    }

    std::cout << "\nMatrix with Sorted Secondary Diagonal:" << std::endl;
    printArray(matrix, size);

    // Deallocate memory
    for (int i = 0; i < size; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
    delete[] diagonal;

    return 0;
}

