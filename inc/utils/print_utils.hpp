
#pragma once

#include "libs/bitsets.hpp"

#include <string>
#include <vector>

/**
 * Prints a square matrix represented by a vector of Bitset objects.
 *
 * @param matrix The vector of Bitset objects representing the square matrix.
 * @param length The length of the square matrix.
 */
inline void print_bitset_square_matrix(
    const vector<Bitset> & matrix,
    uint lenght
) {
    std::cout << "[";
    std::cout << "[" << std::endl;
    for (uint i = 0; i < lenght; i++) {
        std::cout << "    [";
        for (uint j = 0; j < lenght; j++) {
            cout << (matrix[i].contains(j) ? '1' : '0');
            if (j < lenght-1) {
                std::cout << ", ";
            }
        }
        std::cout << "]," << std::endl;
    }
    std::cout << "]" << std::endl;
    cout << endl;
}

/**
 * @brief Prints a square matrix represented as a vector of bitsets as a list of lists.
 * 
 * @param matrix The square matrix represented as a vector of bitsets.
 * @param length The length of the matrix (number of rows/columns).
 */
inline void print_bitset_square_matrix_as_list_of_lists(
    const vector<Bitset> & matrix,
    uint lenght
) {
    bool has_values = false;
    for (uint i = 0; i < lenght - 1; i++) {
        for (uint j = i + 1; j < lenght; j++) {
            if (matrix[i].contains(j)) {
                if (!has_values) {
                    cout << "    ";
                    has_values = true;
                }
                cout << "[" << i+1 << ", " << j+1 << "], ";
            }
        }
        if (has_values) {
            cout << endl;
            has_values = false;
        }
    }
    cout << "]" << endl;
}

