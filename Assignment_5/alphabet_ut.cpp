#include "alphabet.h"

#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <vector>

TEST(Alphabet, SimpleCharsTest) {
    std::vector<char> alph_val {'a', 'b', 'c', 'd'};
    std::vector<std::string> dict {"a", "b", "c", "d"};
    Alphabet alph(dict);

    EXPECT_TRUE(alph == Alphabet(alph_val));
    EXPECT_EQ(alph.GetNumberOfLetters(), alph_val.size());
}

void PrintAlphabet(const Alphabet& alph) {
    for (char c : alph.ToVectorOfLetters()) {
        std::cout << c << " ";
    }
    std::cout << std::endl;
}

TEST(Alphabet, SimpleWordsTest) {
    std::vector<char> alph_val {'a', 'b', 'c', 'd'};
    std::vector<std::string> dict {
          "abc"
        , "abd"
        , "ca"
        , "cbbbbb"
        , "cc"
        , "daaaa"
    };
    Alphabet alph(dict);

    EXPECT_TRUE(alph == Alphabet(alph_val));
    EXPECT_EQ(alph.GetNumberOfLetters(), alph_val.size());
}

TEST(Alphabet, OneLetterAlphabetTest) {
    std::vector<char> alph_val {'a'};
    std::vector<std::string> dict {
          "a"
        , "aa"
        , "aa"
        , "aaaa"
        , "aaaaa"
        , "aaaaaa"
    };
    Alphabet alph(dict);

    EXPECT_TRUE(alph == Alphabet(alph_val));
    EXPECT_EQ(alph.GetNumberOfLetters(), alph_val.size());
}

TEST(Alphabet, InvalidDictionaryTest) {
    std::vector<std::string> dict {
          "absd"
        , "abbbbb"
        , "bbb"
        , "dasdh"
        , "ss"
    };
    EXPECT_THROW(new Alphabet(dict), std::invalid_argument);
}

TEST(Alphabet, EmptyDictionaryTest) {
    std::vector<std::string> dict;
    Alphabet alph(dict);

    EXPECT_EQ(alph.GetNumberOfLetters(), 0);
}

void Validate(const std::set<std::string>& expected, const std::vector<std::string>& result) {
    EXPECT_EQ(expected.size(), result.size());
    for (const auto& alph : result) {
        EXPECT_NE(expected.find(alph), expected.end());
    }
}

TEST(Alphabet, AllPermutationsSimple) {
    std::vector<std::string> dict {
          "aa"
        , "acc"
        , "acd"
        , "bb"
        , "bd"
    };
    std::set<std::string> expected {
          "dcba"
        , "dbca"
    };

    Alphabet alph(dict);
    Validate(expected, alph.GetAllPossibleAlphabets());
}

TEST(Alphabet, AllPermutations) {
    std::vector<std::string> dict {
          "aa"
        , "aga"
        , "agba"
        , "agbc"
        , "agbd"
        , "agd"
        , "e"
        , "c"
    };
    std::set<std::string> expected {
          "dcebga"
        , "dcbega"
        , "dbcega"
        , "dcegba"
        , "dcgeba"
        , "dgceba"
        , "gdceba"
        , "dcbgea"
        , "dbcgea"
        , "dcgbea"
        , "dgcbea"
        , "gdcbea"
        , "dbgcea"
        , "dgbcea"
        , "gdbcea"
    };

    Alphabet alph(dict);
    Validate(expected, alph.GetAllPossibleAlphabets());
}

TEST(Alphabet, AllPermutationsNFact) {
    std::vector<std::string> dict {
          "abcd"
    };
    std::set<std::string> expected {
          "dcba"
        , "cdba"
        , "dbca"
        , "bdca"
        , "cbda"
        , "bcda"
        , "dcab"
        , "cdab"
        , "dacb"
        , "adcb"
        , "cadb"
        , "acdb"
        , "dbac"
        , "bdac"
        , "dabc"
        , "adbc"
        , "badc"
        , "abdc"
        , "cbad"
        , "bcad"
        , "cabd"
        , "acbd"
        , "bacd"
        , "abcd"
    };

    Alphabet alph(dict);
    Validate(expected, alph.GetAllPossibleAlphabets());
}
