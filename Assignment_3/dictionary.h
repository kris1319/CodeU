#pragma once

#include <iostream>
#include <map>
#include <string>
#include <unordered_set>
#include <vector>

// This class implements dictionary object. Inner structure of the class
// represents a trie (prefix-tree) which store all words in a dictionary.
// The tree has characters on its edges, so it allows to store and search
// large sets of strings.
//
// For example, for list of words "aba", "abc", "ac", "ba", the tree is:
//           *
//        a/  \b
//        *    *
//     b/  \c   \a
//     *    *^   *^
//  a/  \c
//  *^   *^
//
// Here * - nodes, / - edges, ^ - means that here the word ends.
class Dictionary {
    // Graph - a prefix-tree
    std::vector<std::map<char, int>> Tree;

public:
    Dictionary();
    // Construct Dictionary object with internal trie structure with words
    // from vocabulary.
    // Complexity of this method is O(L), where L - total length of all words.
    Dictionary(const std::vector<std::string> vocabulary);

    ~Dictionary();

    // Insert a word into the trie. Complexity - O(size(word)).
    void InsertWord(const std::string& word);

    // Checks if the given word is in the dictionary. Complexity - O(size(word)).
    bool IsWord(const std::string& word) const;
    // Checks if for the given prefix there is at least one word in the dictionary
    // which has such prefix. Complexity - O(size(prefix)).
    bool IsPrefix(const std::string& prefix) const;

    // Returns set of all words in the dictionary.
    std::unordered_set<std::string> GetAllWords() const;

    friend std::ostream& operator<< (std::ostream& stream, const Dictionary& dict);

private:
    // Helper function for IsWord() and IsPreix(), returns number of the node where
    // given prefix ends.
    int PrefixEndNode(const std::string& prefix) const;
    // Helper function for GetAllWords(), uses dfs for getting all words from the prefix-tree.
    void SearchTree(int node, std::string &word, std::unordered_set<std::string>& vocabulary) const;
};
