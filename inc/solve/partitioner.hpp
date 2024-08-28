#pragma once

#include "libs/bitsets.hpp"
#include "data/model.hpp"

#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>


class Partitioner {
public:
    Partitioner(
        const int n, 
        const uint q,
        const vector<Bitset> &I
    ):
        n(n),
        q(q),
        min_nb_subset(std::ceil(n / q)),
        I(I),
        // vector of size N + 1, initialized to 0
        nb_found_partitions_for_k(vector<size_t>(n + 1, 0))
    {}

    void partition();
    size_t get_total_nb_found_partitions();

private:
    const uint n; // nb of elements
    const uint q; // max subset size (capacity)
    const uint min_nb_subset; // min nb of subsets
    const vector<Bitset> &I; // incompatible pairs

    vector<size_t> nb_found_partitions_for_k;

    void print_partition(
        const std::vector<std::set<uint>>& partition,
        uint k
    );
    void generatePartitions(
        uint k, 
        std::vector<std::set<uint>>& partition, 
        uint index
    );
    bool isValid(
        int element, 
        const std::set<uint>& subset
    );
    
};