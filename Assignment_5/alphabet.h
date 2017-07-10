#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

// The class Alphabet implements an alphabet which can be costructed from an ordered
// set of words.
class Alphabet {
    // Number of letters in the alphabet
    unsigned number_of_letters_;
    std::vector<char> alphabet_;

    // Directed graph for letters from the given set of words
    std::unordered_map<char, std::unordered_set<char>> letter_graph_;

public:
    Alphabet(const std::vector<char>& alphabet)
        : number_of_letters_(alphabet.size())
        , alphabet_(alphabet)
    {}

    // Constructs an Alphabet object from the given ordered list of words. It uses graph
    // representation and topological sort for ordering letters.
    // It throws std::invalid_argument exception if the given dictionary contains cycles.
    //
    // The graph has all the letters as vertices and the orderings between some two.
    // letters as edges. For each neighboring pair of words it finds first indice i that
    //                   word_1[i] != word_2[i]
    // and sets directed edge [ word_2[i] ---> word_1[i] ]. After the graph is constructed
    // topological sort runs.
    //
    // Complexity. Each word is viewed twice: when it is 'word_i' and when it is 'word_i-1'.
    // Setting an edge and 2 vertices takes O(1). If L is the maximum word's legth, M - number
    // of words then it takes O(L * M) to construct a letter graph.
    // If N - number of letters in the alphabet and there is ordered pair for every two letters
    // from the alphabet in the given list of words then complexity of topological sort
    // (which usually is O(|V| + |E|)) is O(N * (N - 1) / 2) -> O(N^2)
    // Total complexity is O(L * M + N^2).
    Alphabet(const std::vector<std::string>& dictionary);

    ~Alphabet();

    unsigned GetNumberOfLetters() const;
    // Returns alphabet as a vector of letters
    std::vector<char> ToVectorOfLetters() const;

    bool operator==(const Alphabet& other);

private:
    // Adds new vertex to the letter graph.
    void AddLetterVertex(char v);
    // Sets directed edge between first not equal pair (second[i], firsrt[i]).
    void SetEdges(const std::string& first, const std::string& second);
    // Given an ordered list of words builds letter graph.
    void BuildLetterGraph(const std::vector<std::string>& dictionary);
    // Throws std::invalid_argument exception if the given dictionary contains cycles.
    void TopologicalSort(char v, std::unordered_map<char, int>& used);
};
