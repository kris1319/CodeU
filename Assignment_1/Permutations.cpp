#include <iostream>
#include <map>
#include <string>
#include <ctype.h>

// This function takes references for 2 strings and returns:
// * false, if the strings are not permutations of each other
// * true, if the strings are permutations of each other
//
// Notice: function isn't case sensitive for English characters.
// It means that:
//    Listen | Silent -> true
//    tree | TEER -> true
//    й13 | 1Й3 -> false
// Compare with:
//    й13 | 1й3 -> true
bool CheckPermutations(const std::string& a, const std::string& b) {
    // simple case
    if (a.size() != b.size())
        return false;

    std::map<char, int> alph;
    // for each character in first string we'll increase the number of repetitions of this symbol
    // and for each character in the second string -- will decrease
    for (int i = 0; i < a.size(); i++) {
        // we use to_lower(...) because CheckPermutations(a, b) function isn't case-sensitive
        // for English alphabets
        char ai = tolower(a[i]);
        char bi = tolower(b[i]);
        alph[ai]++;
        alph[bi]--;
    }

    // the idea is that if we have 2 permutations all of alph's keys will be zeros
    // in other case there will be at least a one key which != 0
    for (const auto& it : alph)
        if (it.second != 0)
            return false;
    return true;
}

int main() {
    std::string a, b;
    std::cin >> a >> b;

    if (CheckPermutations(a, b))
        std::cout << "Yes" << std::endl;
    else
        std::cout << "No" << std::endl;

    return 0;
}
