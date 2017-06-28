#include "islands.h"

MapOfIslands::~MapOfIslands() {
    for (int row = 0; row < n_rows_; row++) {
        for (auto item : disjoint_sets_[row]) {
            delete item;
        }

        map_[row].clear();
    }

    map_.clear();
    disjoint_sets_.clear();
}

MapOfIslands::MapOfIslands(int n_rows, int n_cols, const std::vector<std::vector<bool>>& map)
    : n_rows_(n_rows)
    , n_columns_(n_cols)
    , map_(map)
    , disjoint_sets_(n_rows_, std::vector<DisjointSet*>(n_columns_, nullptr))
{
    for (int row = 0; row < n_rows_; row++) {
        for (int col = 0; col < n_columns_; col++) {
            // For each island block a set is created
            if (map_[row][col]) {
                disjoint_sets_[row][col] = new DisjointSet();
            }
        }
    }
}

int MapOfIslands::NumberOfIslands() {
    UnionAll();

    int numberOfIslands = 0;
    for (const auto& row : disjoint_sets_) {
        for (const DisjointSet* item : row) {
            // The number of islands is equal to the number of sets' leaders.
            if (item && item->IsLeader()) {
                numberOfIslands++;
            }
        }
    }

    return numberOfIslands;
}

void MapOfIslands::UnionAll() {
    for (int row = 0; row < n_rows_; row++) {
        for (int col = 0; col < n_columns_; col++) {
            // Skip the water
            if (!map_[row][col]) {
                continue;
            }

            if (col > 0 && map_[row][col - 1]) {
                DisjointSet::UnionSets(disjoint_sets_[row][col], disjoint_sets_[row][col - 1]);
            }
            if (row > 0 && map_[row - 1][col]) {
                DisjointSet::UnionSets(disjoint_sets_[row][col], disjoint_sets_[row - 1][col]);
            }
        }
    }
}
