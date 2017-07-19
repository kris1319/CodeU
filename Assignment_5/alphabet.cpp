#include "alphabet.h"

Alphabet::Alphabet(const std::vector<std::string>& dictionary) {
    BuildLetterGraph(dictionary);

    std::unordered_map<char, int> used;
    for (auto it : letter_graph_) {
        if (used.find(it.first) == used.end()) {
            TopologicalSort(it.first, used);
        }
    }

    number_of_letters_ = alphabet_.size();
}

Alphabet::~Alphabet() {
    letter_graph_.clear();
    alphabet_.clear();
}

unsigned Alphabet::GetNumberOfLetters() const {
    return number_of_letters_;
}

std::vector<char> Alphabet::ToVectorOfLetters() const {
    return alphabet_;
}

std::vector<std::string> Alphabet::GetAllPossibleAlphabets() {
    std::unordered_map<char, int> source_edges_number;
    for (const auto& vertex : letter_graph_) {
        source_edges_number[vertex.first] = vertex.second.size();
    }

    return GeneratePermutations(source_edges_number);
}

bool Alphabet::operator==(const Alphabet& other) {
    if (number_of_letters_ != other.number_of_letters_) {
        return false;
    }
    return alphabet_ == other.alphabet_;
}

void Alphabet::AddLetterVertex(char v) {
    const auto in_alph = letter_graph_.find(v);
    if (in_alph == letter_graph_.end()) {
        letter_graph_[v] = std::unordered_set<char>();
        inversed_letter_graph_[v] = std::unordered_set<char>();
    }
}

void Alphabet::BuildLetterGraph(const std::vector<std::string>& dictionary) {
    for (unsigned i = 0; i < dictionary.size(); i++) {
        if (!i) {
            for (char c : dictionary[i]) {
                AddLetterVertex(c);
            }
        } else {
            const std::string& first = dictionary[i - 1];
            const std::string& second = dictionary[i];

            unsigned skipped = 0;
            unsigned min_size = std::min(first.length(), second.length());
            while (skipped < min_size && second[skipped] == first[skipped]) {
                AddLetterVertex(second[skipped]);
                skipped++;
            }

            if (skipped < min_size) {
                SetEdges(first[skipped], second[skipped]);
                skipped++;
            }

            for (unsigned i = skipped; i < second.length(); i++) {
                AddLetterVertex(second[i]);
            }
        }
    }
}

void Alphabet::SetEdges(char first, char second) {
    AddLetterVertex(second);
    AddLetterVertex(first);

    letter_graph_[second].insert(first);
    inversed_letter_graph_[first].insert(second);
}

void Alphabet::TopologicalSort(char v, std::unordered_map<char, int>& used) {
    used[v] = 1;
    for (char next : letter_graph_[v]) {
        if (used.find(next) == used.end()) {
            TopologicalSort(next, used);
        } else if (used[next] == 1) {
            throw std::invalid_argument("The given dictionary is invalid: it contains cycles.");
        }
    }

    alphabet_.push_back(v);
    used[v] = 2;
}

std::vector<std::string> Alphabet::GeneratePermutations(std::unordered_map<char, int>& source_edges_number) {
    std::vector<std::string> possible_alphs;
    for (auto vertex : source_edges_number) {
        if (vertex.second) {
            continue;
        }

        // Mark vertex as used
        source_edges_number[vertex.first] = -1;
        // Deleting all adges directed to current vertex
        for (char prev : inversed_letter_graph_[vertex.first]) {
            source_edges_number[prev]--;
        }

        auto sub_alphs = GeneratePermutations(source_edges_number);
        if (sub_alphs.empty()) {
            possible_alphs.push_back(std::string(1, vertex.first));
        } else {
            for (auto& alph : sub_alphs) {
                alph.push_back(vertex.first);
                possible_alphs.push_back(alph);
            }
        }

        source_edges_number[vertex.first] = 0;
        for (char prev : inversed_letter_graph_[vertex.first]) {
            source_edges_number[prev]++;
        }
    }

    return possible_alphs;
}
