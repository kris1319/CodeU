#include "dictionary.h"

#include <gtest/gtest.h>
#include <string>
#include <unordered_set>

TEST(Dictionary, EmptyDict) {
    Dictionary dict;
    EXPECT_EQ(dict.GetAllWords().size(), 0);
}

void ValidateSetOfWords(const std::unordered_set<std::string>& expected,
                        const std::unordered_set<std::string>& stored) {
    EXPECT_EQ(stored.size(), expected.size());
    for (const auto& word : expected) {
        EXPECT_NE(stored.find(word), stored.end());
    }
}

TEST(Dictionary, DictFromVector) {
    std::unordered_set<std::string> vocabulary {"aba", "abac", "acd", "bk"};
    Dictionary dict(vocabulary);

    auto stored = dict.GetAllWords();
    ValidateSetOfWords(vocabulary, stored);
}

TEST(Dictionary, InsertWord) {
    Dictionary dict;

    std::string word = "abacaba";
    EXPECT_FALSE(dict.IsWord(word));
    dict.InsertWord(word);
    EXPECT_TRUE(dict.IsWord(word));

    std::unordered_set<std::string> vocabulary {"aba", "abac", "acd", "bk"};
    for (const auto& newWord : vocabulary) {
        dict.InsertWord(newWord);
    }

    vocabulary.insert(word);
    auto stored = dict.GetAllWords();
    ValidateSetOfWords(vocabulary, stored);
}

TEST(Dictionary, IsPrefix) {
    std::unordered_set<std::string> vocabulary {"aba", "abac", "acd", "bk", "abacaba"};
    Dictionary dict(vocabulary);

    for (const auto& word : vocabulary) {
        std::string prefix;
        for (char c : word) {
            prefix.push_back(c);
            EXPECT_TRUE(dict.IsPrefix(prefix));
        }
    }

    for (const auto& prefix : {"c", "abak"}) {
        EXPECT_FALSE(dict.IsPrefix(prefix));
    }
}

TEST(Dictionary, IsWord) {
    std::unordered_set<std::string> vocabulary {"aba", "abac", "acd", "bk", "abacaba"};
    Dictionary dict(vocabulary);

    for (const auto& word : vocabulary) {
        EXPECT_TRUE(dict.IsWord(word));
    }

    for (const auto& word : {"c", "abak", "abaca"}) {
        EXPECT_FALSE(dict.IsWord(word));
    }
}
