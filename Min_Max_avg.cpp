// Implement Min, Max, Sum and Average operations using Parallel Reduction.

#include <iostream>
#include <vector>
#include <omp.h>
#include <climits>
using namespace std;

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    int sum = 0;
    int min_val = INT_MAX;
    int max_val = INT_MIN;

    double start = omp_get_wtime();

    #pragma omp parallel for reduction(+:sum) reduction(min:min_val) reduction(max:max_val)
    for (int i = 0; i < n; i++) {
        sum += arr[i];

        if (arr[i] < min_val)
            min_val = arr[i];

        if (arr[i] > max_val)
            max_val = arr[i];
    }

    double end = omp_get_wtime();

    double avg = (double)sum / n;

    cout << "\nSum = " << sum;
    cout << "\nMinimum = " << min_val;
    cout << "\nMaximum = " << max_val;
    cout << "\nAverage = " << avg;

    cout << "\nExecution Time = " << end - start << " sec";

    return 0;
}