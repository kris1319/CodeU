#include "word_search.h"

WordSearch::~WordSearch() {
    for (int i = 0; i < NRows; i++) {
        Grid[i].clear();
        UsedGrid[i].clear();
        BranchCash[i].clear();
    }
    Grid.clear();
    UsedGrid.clear();
    BranchCash.clear();
}

void WordSearch::SearchFromPosition(int row, int col, std::string& current,
                                    std::unordered_set<std::string>& valid, const Dictionary& dict) {
    UsedGrid[row][col] = true;
    current.push_back(Grid[row][col]);
    BranchCash[row][col].insert(current);

    if (dict.IsPrefix(current)) {
        if (dict.IsWord(current)) {
            valid.insert(current);
        }

        std::vector<std::pair<int, int>> children(8);
        for (int r : {-1, 0, 1}) {
            for (int c : {-1, 0, 1}) {
                if (!r && !c) {
                    continue;
                }
                children.push_back(std::pair<int, int>(row + r, col + c));
            }
        }

        for (const auto& node : children) {
            if (node.first < 0 || node.first >= NRows ||
                node.second < 0 || node.second >= NColumns) {
                continue;
            }

            if (UsedGrid[node.first][node.second]) {
                continue;
            }
            if (BranchCash[node.first][node.second].find(current) != BranchCash[node.first][node.second].end())  {
                continue;
            }

            SearchFromPosition(node.first, node.second, current, valid, dict);
        }
    }

    UsedGrid[row][col] = false;
    current.pop_back();
}

std::unordered_set<std::string> WordSearch::Search(const Dictionary& dict) {
    std::unordered_set<std::string> valid;
    for (int row = 0; row < NRows; row++) {
        for (int col = 0; col < NColumns; col++) {
            std::string word;
            // It's not necessary to reset UsedGrid values because after using some node (i, j)
            // in the Grid the UsedGrid[i][j] is set to false.
            SearchFromPosition(row, col, word, valid, dict);
        }
    }

    ResetBranchCash();

    return valid;
}

void WordSearch::ResetBranchCash() {
    for (auto& row : BranchCash) {
        for (auto& node : row) {
            node.clear();
        }
    }
}
