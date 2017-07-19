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
    std::unordered_map<char, std::unordered_set<char>> inversed_letter_graph_;

public:
    Alphabet(const std::vector<char>& alphabet)
        : number_of_letters_(alphabet.size())
        , alphabet_(alphabet)
    {}

    // Constructs an Alphabet object from the given ordered list of words. It uses graph
    // representation and topological sort for ordering letters.
    // It allows an empty list of words, size of the output alphabet will be 0.
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

    // Returns a list with all possible valid alphabets. Each alphabet is a string with letters
    // in right-to-left order.
    //
    // Algorithm. Let's consider a dictionary consisting only with N letters. On each iteration
    // it takes all vertices with no source edges and for each such node:
    //
    // * 'removes' all edges into current vertex
    //
    // * marks current node as used
    //
    // * calls recursively itself with N - 1 letters in the graph
    //
    // * if returned vector of alphabets with N - 1 letters is empty it means that current vertex
    //   is the last vertex without source edges and in this way it adds into result vector
    //   only one alphabet consisting with only one letter - itself.
    //
    // * else it appends to all alphabets from returned vector itself (current letter) and adds all
    //   new alphabets into result vector
    //
    // After searching all vertices with no source edges it returns result vector.
    //
    // Complexity. In the worst case it takes O(N!) where N is the number of letters because there
    // are N! different permutations.
    std::vector<std::string> GetAllPossibleAlphabets();

    bool operator==(const Alphabet& other);

private:
    // Adds new vertex to the letter graph.
    void AddLetterVertex(char v);
    // Sets directed edge between first not equal pair (second[i], firsrt[i]).
    void SetEdges(char first, char second);
    // Given an ordered list of words builds letter graph.
    void BuildLetterGraph(const std::vector<std::string>& dictionary);

    // Throws std::invalid_argument exception if the given dictionary contains cycles.
    void TopologicalSort(char v, std::unordered_map<char, int>& used);
    // Generate valid alphabets, it implements some sort of search with clipping
    std::vector<std::string> GeneratePermutations(std::unordered_map<char, int>& source_edges_number);
};
