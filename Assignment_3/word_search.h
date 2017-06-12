#pragma once

#include "dictionary.h"

#include <string>
#include <unordered_set>
#include <vector>

// The class impements search module for such words from dictionary
// which can be constructed from the Grid.
class WordSearch {
    int NRows;
    int NColumns;

    // Grid with characters
    std::vector<std::vector<char>> Grid;

public:
    WordSearch(int nRows, int nCols, const std::vector<std::vector<char>>& grid)
        : NRows(nRows)
        , NColumns(nCols)
        , Grid(grid)
    {}

    ~WordSearch();

    // The main idea of the Search() method is that it should to go through all possible strings
    // from the grid to find all valid (that may be constructed from the grid) words in the dictionary.
    //
    // Let's use the fact that if some prefix not in the dictionary then no words in the dictionary
    // with such prefix. Thus run dfs from each item in the grid and construct current string on each
    // iteration, then:
    //
    // * if current string is a prefix of the dictionary,
    //          go to this node and search further;
    // * else stop this branch of the grid-tree.
    //
    // It means that we iterate only through words from the dictionary.
    //
    // Complexity. Let's k - valid words in the dictionary, n * m - max size of the valid words from
    // the dictionary, where n, m - the grid's size. So it checks on each character in the string
    // is there such prefix, thus for the one largest word it takes O(nm(nm - 1) / 2) = O((nm)^2).
    // For all words it takes O(k(nm)^2) in the worst case of the largest possible strings.
    std::unordered_set<std::string> Search(const Dictionary& dict);

private:
    // Helper function for Search(), implements dfs on the grid.
    void SearchFromPosition(int row, int col, std::string& current, std::vector<std::vector<bool>>& used,
                            std::unordered_set<std::string>& valid, const Dictionary &dict);
    // Helper function, returns vector of children of the given node.
    std::vector<std::pair<int, int> > GetChildren(int row, int col);
};
