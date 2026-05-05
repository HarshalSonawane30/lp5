
/* Write a program to implement Parallel Bubble Sort  using OpenMP. Use
existing algorithms and measure the performance of sequential and parallel algorithms.

*/


#include <iostream>
#include <vector>
#include <chrono>
#ifdef _OPENMP
#include <omp.h>
#endif
using namespace std;

double nowSeconds() {
#ifdef _OPENMP
    return omp_get_wtime();
#else
    using clock = chrono::high_resolution_clock;
    return chrono::duration<double>(clock::now().time_since_epoch()).count();
#endif
}

// Function to print array
void printArray(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++)
        cout << arr[i] << " ";
    cout << endl;
}

// Sequential Bubble Sort
void bubbleSortSeq(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }
}

// Parallel Bubble Sort (Odd-Even)
void bubbleSortParallel(vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n; i++) {

        // Even phase
        #pragma omp parallel for
        for (int j = 0; j < n - 1; j += 2) {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }

        // Odd phase
        #pragma omp parallel for
        for (int j = 1; j < n - 1; j += 2) {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n), arr1, arr2;

    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    arr1 = arr;
    arr2 = arr;

    double start, end;

    // Sequential
    start = nowSeconds();
    bubbleSortSeq(arr1);
    end = nowSeconds();

    cout << "\nSorted Array (Sequential): ";
    printArray(arr1);

    cout << "Sequential Bubble Sort Time: " << end - start << " sec\n";

    // Parallel
    start = nowSeconds();
    bubbleSortParallel(arr2);
    end = nowSeconds();

    cout << "\nSorted Array (Parallel): ";
    printArray(arr2);

    cout << "Parallel Bubble Sort Time: " << end - start << " sec\n";

    return 0;
}