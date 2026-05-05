/*Write a program to implement Parallel Merge sort using OpenMP. Use
existing algorithms and measure the performance of sequential and parallel algorithms.*/



#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

// Function to print array
void printArray(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++)
        cout << arr[i] << " ";
    cout << endl;
}

// Merge Function
void merge(vector<int>& arr, int l, int m, int r) {
    vector<int> temp(r - l + 1);
    int i = l, j = m + 1, k = 0;

    while (i <= m && j <= r) {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while (i <= m) temp[k++] = arr[i++];
    while (j <= r) temp[k++] = arr[j++];

    for (int i = l; i <= r; i++)
        arr[i] = temp[i - l];
}

// Sequential Merge Sort
void mergeSortSeq(vector<int>& arr, int l, int r) {
    if (l >= r) return;

    int m = (l + r) / 2;
    mergeSortSeq(arr, l, m);
    mergeSortSeq(arr, m + 1, r);
    merge(arr, l, m, r);
}

// Parallel Merge Sort
void mergeSortParallel(vector<int>& arr, int l, int r) {
    if (l >= r) return;

    int m = (l + r) / 2;

    #pragma omp parallel sections
    {
        #pragma omp section
        mergeSortParallel(arr, l, m);

        #pragma omp section
        mergeSortParallel(arr, m + 1, r);
    }

    merge(arr, l, m, r);
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
    start = omp_get_wtime();
    mergeSortSeq(arr1, 0, n - 1);
    end = omp_get_wtime();

    cout << "\nSorted Array (Sequential): ";
    printArray(arr1);

    cout << "Sequential Merge Sort Time: " << end - start << " sec\n";

    // Parallel
    start = omp_get_wtime();
    mergeSortParallel(arr2, 0, n - 1);
    end = omp_get_wtime();

    cout << "\nSorted Array (Parallel): ";
    printArray(arr2);

    cout << "Parallel Merge Sort Time: " << end - start << " sec\n";

    return 0;
}