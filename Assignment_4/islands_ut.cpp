#include "disjoint_set.h"
#include "islands.h"

#include <cstdlib>
#include <ctime>
#include <gtest/gtest.h>
#include <iostream>
#include <random>
#include <tuple>
#include <vector>

TEST(MapOfIslands, NumberOfIslandsSimpleSingle) {
    std::vector<std::vector<bool>> map_values {
          {false, false, false}
        , {false,  true, false}
        , {false, false, false}
    };

    MapOfIslands map(3, 3, map_values);
    EXPECT_EQ(map.NumberOfIslands(), 1);
}

TEST(MapOfIslands, NumberOfIslandsSimple) {
    std::vector<std::vector<bool>> map_values {
          {false,  true, false, false}
        , { true,  true,  true, false}
        , {false,  true, false, false}
        , {false, false, false, false}
    };

    MapOfIslands map(4, 4, map_values);
    EXPECT_EQ(map.NumberOfIslands(), 1);
}

TEST(MapOfIslands, NumberOfIslandsThreeIslandsLight) {
    std::vector<std::vector<bool>> map_values {
          {false,  true, false, false}
        , { true,  true, false, false}
        , {false, false, false,  true}
        , {false, false,  true, false}
    };

    MapOfIslands map(4, 4, map_values);
    EXPECT_EQ(map.NumberOfIslands(), 3);
}

// Naive solution for computing the number of islands.
// Let's the map is a graph. So the number of islands will be equal to the number of
// the connected components. The solution uses dfs algorithm for selecting and counting
// the connected components.
class NaiveSolution {
    int n_rows_;
    int n_cols_;
    // The map of islands
    std::vector<std::vector<bool>> map_;
    // Colors of each connected component
    std::vector<std::vector<bool>> used_;

public:
    NaiveSolution(int n_rows, int n_cols, const std::vector<std::vector<bool>>& map)
        : n_rows_(n_rows)
        , n_cols_(n_cols)
        , map_(map)
        , used_(n_rows_, std::vector<bool>(n_cols_, false))
    {}

    ~NaiveSolution() {
        for (int row = 0; row < n_rows_; row++) {
            used_[row].clear();
            map_[row].clear();
        }

        map_.clear();
        used_.clear();
    }

    int GetSolution() {
        int color = 0;
        for (int row = 0; row < n_rows_; row++) {
            for (int col = 0; col < n_cols_; col++) {
                if (map_[row][col] && !used_[row][col]) {
                    color++;
                    dfs(row, col);
                }
            }
        }

        return color;
    }

private:
    void dfs(int row, int col) {
        used_[row][col] = true;

        for (int r : {-1, 0, 1}) {
            for (int c : {-1, 0, 1}) {
                if (r && c) {
                    continue;
                }

                if (row + r >= 0 && row + r < n_rows_ && col + c >= 0 && col + c < n_cols_) {
                    if (map_[row + r][col + c] && !used_[row + r][col + c]) {
                        dfs(row + r, col + c);
                    }
                }
            }
        }
    }
};

std::vector<std::vector<bool>> GenerateMap(int n_rows, int n_cols, float probability) {
    std::vector<std::vector<bool>> map(n_rows, std::vector<bool>(n_cols));

    int seed = std::time(0);
    std::mt19937 gen(seed);
    std::bernoulli_distribution distrib(probability);
    std::cout << "Run with n_rows=" << n_rows << ", n_cols=" << n_cols << ", probability=" << probability
              << ", seed=" << seed << std::endl;

    for (auto& row : map) {
        for (int col = 0; col < n_cols; col++) {
            row[col] = distrib(gen);
        }
    }

    return map;
}

TEST(MapOfIslands, RandomMaps) {
    for (int size : {20, 50, 100}) {
        for (float probability : {0.25, 0.5, 0.75}) {
            auto map = GenerateMap(size, size, probability);
            EXPECT_EQ(NaiveSolution(size, size, map).GetSolution(),
                        MapOfIslands(size, size, map).NumberOfIslands());
        }
    }
}

TEST(MapOfIslands, RandomLargeMaps) {
    for (int size : {1000, 2000}) {
        for (float probability : {0.25, 0.5}) {
            auto map = GenerateMap(size, size, probability);
            EXPECT_EQ(NaiveSolution(size, size, map).GetSolution(),
                        MapOfIslands(size, size, map).NumberOfIslands());
        }
    }
}

TEST(MapOfIslands, LargeMapOneIsland) {
    int size = 2000;
    std::vector<std::vector<bool>> map(size, std::vector<bool>(size, true));
    EXPECT_EQ(MapOfIslands(size, size, map).NumberOfIslands(), 1);
}
