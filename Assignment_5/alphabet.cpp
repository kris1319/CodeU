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

bool Alphabet::operator==(const Alphabet& other) {
    if (number_of_letters_ != other.number_of_letters_) {
        return false;
    }

    for (unsigned i = 0; i < number_of_letters_; i++) {
        if (alphabet_[i] != other.alphabet_[i]) {
            return false;
        }
    }
    return true;
}

void Alphabet::AddLetterVertex(char v) {
    const auto in_alph = letter_graph_.find(v);
    if (in_alph == letter_graph_.end()) {
        letter_graph_[v] = std::unordered_set<char>();
    }
}

void Alphabet::BuildLetterGraph(const std::vector<std::string>& dictionary) {
    for (unsigned i = 0; i < dictionary.size(); i++) {
        if (!i) {
            for (char c : dictionary[i]) {
                AddLetterVertex(c);
            }
        } else {
            SetEdges(dictionary[i - 1], dictionary[i]);
        }
    }
}

void Alphabet::SetEdges(const std::string& first, const std::string& second) {
    unsigned skipped = 0;
    unsigned min_size = std::min(first.length(), second.length());
    while (skipped < min_size && second[skipped] == first[skipped]) {
        AddLetterVertex(second[skipped]);
        skipped++;
    }

    if (skipped < min_size) {
        AddLetterVertex(second[skipped]);
        AddLetterVertex(first[skipped]);

        const auto it = letter_graph_[second[skipped]].find(first[skipped]);
        if (it == letter_graph_[second[skipped]].end()) {
            letter_graph_[second[skipped]].insert(first[skipped]);
        }
        skipped++;
    }

    for (unsigned i = skipped; i < second.length(); i++) {
        AddLetterVertex(second[i]);
    }
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
