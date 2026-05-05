
// Implement HPC application for AI/ML domain.


#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>
using namespace std;

// Function to calculate distance
double distance(double x1, double y1, double x2, double y2) {
    return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

int main() {
    int n, k, iterations;

    cout << "Enter number of data points: ";
    cin >> n;

    vector<double> x(n), y(n);

    cout << "Enter (x y) points:\n";
    for (int i = 0; i < n; i++)
        cin >> x[i] >> y[i];

    cout << "Enter number of clusters (k): ";
    cin >> k;

    cout << "Enter number of iterations: ";
    cin >> iterations;

    vector<double> cx(k), cy(k); // centroids

    // Initialize centroids (first k points)
    for (int i = 0; i < k; i++) {
        cx[i] = x[i];
        cy[i] = y[i];
    }

    vector<int> cluster(n);

    for (int it = 0; it < iterations; it++) {

        // Assign clusters (Parallel)
        #pragma omp parallel for
        for (int i = 0; i < n; i++) {
            double min_dist = 1e9;
            int best = 0;

            for (int j = 0; j < k; j++) {
                double d = distance(x[i], y[i], cx[j], cy[j]);
                if (d < min_dist) {
                    min_dist = d;
                    best = j;
                }
            }
            cluster[i] = best;
        }

        // Recalculate centroids
        vector<double> sumx(k, 0), sumy(k, 0);
        vector<int> count(k, 0);

        for (int i = 0; i < n; i++) {
            int c = cluster[i];
            sumx[c] += x[i];
            sumy[c] += y[i];
            count[c]++;
        }

        for (int j = 0; j < k; j++) {
            if (count[j] != 0) {
                cx[j] = sumx[j] / count[j];
                cy[j] = sumy[j] / count[j];
            }
        }
    }

    cout << "\nFinal Clusters:\n";
    for (int i = 0; i < n; i++) {
        cout << "Point (" << x[i] << ", " << y[i] << ") -> Cluster " << cluster[i] << endl;
    }

    return 0;
}