#include "word_search.h"

WordSearch::~WordSearch() {
    for (auto& row : Grid) {
        row.clear();
    }
    Grid.clear();
}

std::vector<std::pair<int, int> > WordSearch::GetChildren(int row, int col) {
    std::vector<std::pair<int, int>> children;
    for (int r : {-1, 0, 1}) {
        for (int c : {-1, 0, 1}) {
            if (!r && !c) {
                continue;
            }
            children.push_back(std::pair<int, int>(row + r, col + c));
        }
    }

    return children;
}

void WordSearch::SearchFromPosition(int row, int col, std::string& current, std::vector<std::vector<bool>>& used,
                                    std::unordered_set<std::string>& valid, const Dictionary& dict) {
    used[row][col] = true;
    current.push_back(Grid[row][col]);

    if (dict.IsPrefix(current)) {
        if (dict.IsWord(current)) {
            valid.insert(current);
        }

        auto children = GetChildren(row, col);
        for (const auto& node : children) {
            if (node.first < 0 || node.first >= NRows ||
                node.second < 0 || node.second >= NColumns) {
                continue;
            }

            if (used[node.first][node.second]) {
                continue;
            }

            SearchFromPosition(node.first, node.second, current, used, valid, dict);
        }
    }

    used[row][col] = false;
    current.pop_back();
}

std::unordered_set<std::string> WordSearch::Search(const Dictionary& dict) {
    std::unordered_set<std::string> valid;
    for (int row = 0; row < NRows; row++) {
        for (int col = 0; col < NColumns; col++) {
            std::string word;
            std::vector<std::vector<bool>> used(NRows, std::vector<bool>(NColumns, false));
            SearchFromPosition(row, col, word, used, valid, dict);
        }
    }

    return valid;
}
