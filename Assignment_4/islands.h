#pragma once

#include "disjoint_set.h"

#include <vector>

// This class implemets boolean map of islands with computing the number of islands on the map.
// It uses disjoint sets for computing. The algorithm traverse a map only two times, thus
// the complexity is O(2 * N * M * complexity(disjoint_sets)) where N, M - size of the map.
// As it was said the complexity of operations on disjoint sets at most real cases are less
// then constant 4. So the total coplexity is O(2 * 4 * N * M) = O(N * M).
class MapOfIslands {
    int n_rows_ = 0;
    int n_columns_ = 0;

    // Boolean map of islands
    std::vector<std::vector<bool>> map_;
    // Disjoint sets on the map of islands
    std::vector<std::vector<DisjointSet*>> disjoint_sets_;

public:
    MapOfIslands() {}
    // When a map of islands is created every island's item on the map represents separate
    // disjoint set.
    MapOfIslands(int n_rows, int n_cols, const std::vector<std::vector<bool>>& map);

    ~MapOfIslands();

    // The method returns a number of islands on the map. Firstly it calls UnionAll() method
    // for uniting all islands, after it go through the given disjoint sets and couts a
    // number of sets.
    int NumberOfIslands();

private:
    // Helper function for NumberOfIslands() method. It walk only once through the map
    // from top to bottom, from left to right and on each step tries to unite current
    // island item with already visited islands which can be lefter or upper fromthe current.
    // It'sillustrated here:
    //
    //                 'island 2'
    //                     ^
    //                     |
    // 'island 1' <--- 'current'
    //
    void UnionAll();
};
