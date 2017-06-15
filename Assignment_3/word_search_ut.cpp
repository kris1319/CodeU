#include "dictionary.h"
#include "word_search.h"

#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

TEST(WordSearch, SearchOneChar) {
    std::vector<std::vector<char>> grid {{'a'}};

    std::unordered_set<std::string> words {"abcd", "a", "ab", "cab"};

    Dictionary dict(words);

    WordSearch search(1, 1, grid);
    auto result = search.Search(dict);

    EXPECT_EQ(result.size(), 1);
    EXPECT_NE(result.find("a"), result.end());
}

void Validate(const std::unordered_set<std::string>& expected, const std::unordered_set<std::string>& result) {
    EXPECT_EQ(result.size(), expected.size());
    for (const auto& word : expected) {
        EXPECT_NE(result.find(word), result.end());
    }
}

TEST(WordSearch, SearchSimple) {
    std::vector<std::vector<char>> grid {{'a', 'b'}, {'c', 'd'}};

    std::unordered_set<std::string> valid {"abcd", "a", "ab", "cab"};
    std::unordered_set<std::string> invalid {"aba", "kat", "abcda"};

    Dictionary dict(valid);
    for (const auto& word : invalid) {
        dict.InsertWord(word);
    }

    WordSearch search(2, 2, grid);
    Validate(valid, search.Search(dict));
}

TEST(WordSearch, Search) {
    std::vector<std::vector<char>> grid {{'a', 'b', 'a'}, {'c', 'b', 'd'}};

    std::unordered_set<std::string> valid {"abca", "a", "abba", "cabd"};
    std::unordered_set<std::string> invalid {"aaba", "kat", "abcda"};

    Dictionary dict(valid);
    for (const auto& word : invalid) {
        dict.InsertWord(word);
    }

    WordSearch search(2, 3, grid);
    Validate(valid, search.Search(dict));
}
