#include "disjoint_set.h"
#include "islands.h"

#include <cstdlib>
#include <gtest/gtest.h>
#include <vector>

TEST(MapOfIslands, NumberOfIslandsSimpleSingle) {
    std::vector<std::vector<bool>> map_values {
          {false, false, false}
        , {false,  true, false}
        , {false, false, false}
    };

    MapOfIslands map(3, 3, map_values);
    EXPECT_TRUE(map.NumberOfIslands() == 1);
}

TEST(MapOfIslands, NumberOfIslandsSimple) {
    std::vector<std::vector<bool>> map_values {
          {false,  true, false, false}
        , { true,  true,  true, false}
        , {false,  true, false, false}
        , {false, false, false, false}
    };

    MapOfIslands map(4, 4, map_values);
    EXPECT_TRUE(map.NumberOfIslands() == 1);
}

TEST(MapOfIslands, NumberOfIslandsThreeIslandsLight) {
    std::vector<std::vector<bool>> map_values {
          {false,  true, false, false}
        , { true,  true, false, false}
        , {false, false, false,  true}
        , {false, false,  true, false}
    };

    MapOfIslands map(4, 4, map_values);
    EXPECT_TRUE(map.NumberOfIslands() == 3);
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
    std::vector<std::vector<int>> colors_;

public:
    NaiveSolution(int n_rows, int n_cols, const std::vector<std::vector<bool>>& map)
        : n_rows_(n_rows)
        , n_cols_(n_cols)
        , map_(map)
        , colors_(n_rows_, std::vector<int>(n_cols_, 0))
    {}

    ~NaiveSolution() {
        for (int row = 0; row < n_rows_; row++) {
            colors_[row].clear();
            map_[row].clear();
        }

        map_.clear();
        colors_.clear();
    }

    int GetSolution() {
        int color = 0;
        for (int row = 0; row < n_rows_; row++) {
            for (int col = 0; col < n_cols_; col++) {
                if (map_[row][col] && !colors_[row][col]) {
                    color++;
                    dfs(row, col, color);
                }
            }
        }

        return color;
    }

private:
    void dfs(int row, int col, int color) {
        colors_[row][col] = color;

        for (int r : {-1, 0, 1}) {
            for (int c : {-1, 0, 1}) {
                if (r && c) {
                    continue;
                }

                if (row + r >= 0 && row + r < n_rows_ && col + c >= 0 && col + c < n_cols_) {
                    if (map_[row + r][col + c] && !colors_[row + r][col + c]) {
                        dfs(row + r, col + c, color);
                    }
                }
            }
        }
    }
};

bool GetRandomBool() {
    return std::rand() % 2;
}

TEST(MapOfIslands, RandomMap) {
    int n_rows = 1000, n_cols = 1000;
    std::vector<std::vector<bool>> map_values(n_rows, std::vector<bool>(n_cols));
    for (auto& row : map_values) {
        for (int col = 0; col < n_cols; col++) {
            row[col] = GetRandomBool();
        }
    }

    EXPECT_TRUE(NaiveSolution(n_rows, n_cols, map_values).GetSolution() ==
                MapOfIslands(n_rows, n_cols, map_values).NumberOfIslands());
}
