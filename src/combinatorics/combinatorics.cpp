#include "combinatorics/combinatorics.hpp"

/**
 * Compute the Bell number for n
 * 
 * @param n an integer
 * @return The Bell number for n, AKA the number of different 
 * partitioning of a set of n elements.
 */
unsigned long long bell_number(int n) {
    // Create a 2D array to store Bell triangle
    unsigned long long bell[n + 1][n + 1];

    // Initialize Bell triangle with zeros
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            bell[i][j] = 0;
        }
    }

    // The first Bell number is 1
    bell[0][0] = 1;

    // Fill the Bell triangle
    for (int i = 1; i <= n; i++) {
        // Explicitly put the last value of the previous row in the first position of the current row
        bell[i][0] = bell[i - 1][i - 1];

        // Fill the current row
        for (int j = 1; j <= i; j++) {
            bell[i][j] = bell[i - 1][j - 1] + bell[i][j - 1];
        }
    }

    // The Bell number for n is the first element in the nth row
    return bell[n][0];
}

// Function to compute Stirling numbers of the second kind S(n, k)
unsigned long long stirlingSecondKind(int n, int k) {
    // Create a 2D array to store the computed values
    unsigned long long S[n+1][k+1];

    // Initialize the base cases
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            if (j == 0 || j > i) {
                S[i][j] = 0;  // S(n, 0) = 0 for n > 0 and S(n, k) = 0 for k > n
            } else if (i == j) {
                S[i][j] = 1;  // S(n, n) = 1
            } else if (j == 1) {
                S[i][j] = 1;  // S(n, 1) = 1
            } else {
                // Recursive formula: S(n, k) = k * S(n-1, k) + S(n-1, k-1)
                S[i][j] = j * S[i-1][j] + S[i-1][j-1];
            }
        }
    }

    // Return the computed value S(n, k)
    return S[n][k];
}