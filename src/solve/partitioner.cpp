/**
 * Constrained Partitioning
 * 
 * Given a set of N elements, partition them into k subsets such that:
 *  - capacity constraint: each subset has at most q elements
 *  - incompatible pairs: I[i][j] = 1 means that elements i and j cannot be in the same subset
 */

#include "solve/partitioner.hpp"
#include "combinatorics/combinatorics.hpp"

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>

using namespace std;

void Partitioner::print_partition(
    const vector<set<uint>>& partition,
    uint k
) {
    nb_found_partitions_for_k[k]++;

    cout << "{";
    for (uint i = 0; i < partition.size(); ++i) {
        const auto& subset = partition[i];
        cout << "{";
        for (uint j = 0; j < subset.size(); ++j) {
            auto it = subset.begin();
            advance(it, j);
            cout << *it;
            if (j < subset.size() - 1) {
                cout << ", ";
            }
        }
        
        if (i < partition.size() - 1) {
            cout << "},";
        } else {
            cout << "}";
        }
    }
    cout << "}" << endl;
}

/**
 * Constrained Partitioning, using backtracking.
 */
void Partitioner::generatePartitions( 
    uint k,
    vector<set<uint>>& partition, 
    uint index
) {
    if (index == n) {
        if (partition.size() == k) {
            // Print or process the valid partition
            print_partition(partition, k);
        }
        return;
    }

    // Try to add index to each existing subset or create a new one
    for (uint i = 0; i < partition.size(); i++) {
        if (
            (isValid(index, partition[i])) &&
            (partition[i].size() < q) // NOTE: skip if this would create a partition whose length is greater than q
        ) {
            partition[i].insert(index);
            generatePartitions(k, partition, index + 1);
            partition[i].erase(index);
        }
    }

    // Create a new subset
    partition.push_back({index});
    generatePartitions(k, partition, index + 1);
    partition.pop_back();
}

bool Partitioner::isValid(int element, const set<uint>& subset) {
    for (int existingElement : subset) {
        if (I[element][existingElement]) {
            return false;
        }
    }
    return true;
}

size_t Partitioner::get_total_nb_found_partitions() {
    return accumulate(
        nb_found_partitions_for_k.begin(), 
        nb_found_partitions_for_k.end(), 
        0
    );
}

void Partitioner::partition() {

    for (uint k = min_nb_subset; k < n + 1; k++) {
        vector<set<uint>> partition;
        generatePartitions(k, partition, 0);

        size_t nb_partitions = nb_found_partitions_for_k[k];
        cout << "Nb found partitions = " 
        << nb_partitions << endl;
        unsigned long long stirling = stirlingSecondKind(n, k);
        cout << "Stirling 2nd Kind S(n = "
            << n << ", k = " << k << ") = "
            << stirling << endl;
        if (nb_partitions == stirling) {
            cout << "🟢 equal" << endl;
        } else if(nb_partitions < stirling) {
            cout << "🔵 less" << endl;
        } else {
            cout << "🔴 more" << endl;
        }
    }

    size_t total_nb_partitions = get_total_nb_found_partitions();
    cout << "Total nb found partitions = " 
        << total_nb_partitions << endl;
    unsigned long long bell = bell_number(n);
    cout << "Bell number B(n = " << n << ") = " << bell << endl;
    cout << "ℹ️ Percentage of found partitions = " 
        << (double)total_nb_partitions / bell * 100 << "%" << endl;
}