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
}

TEST(Alphabet, OneLetterAlphabetTest) {
    std::vector<char> alph_val {'a'};
    std::vector<std::string> dict {
          "aaaaaa"
        , "a"
        , "aaaa"
        , "aa"
        , "aa"
        , "aaaaa"
    };
    Alphabet alph(dict);

    EXPECT_TRUE(alph == Alphabet(alph_val));
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
