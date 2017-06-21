#include "dictionary.h"

Dictionary::Dictionary() {
    Tree.push_back(std::unordered_map<char, int>());
}

Dictionary::Dictionary(const std::unordered_set<std::string> vocabulary)
    : Dictionary()
{
    for (const auto& word : vocabulary) {
        InsertWord(word);
    }
}

Dictionary::~Dictionary() {
    for (auto& edges : Tree) {
        edges.clear();
    }
    Tree.clear();
}

void Dictionary::InsertWord(const std::string &word) {
    int current = 0;
    for (const char& c : word) {
        if (Tree[current][c] != 0) {
            current = Tree[current][c];
            continue;
        }

        Tree.push_back(std::unordered_map<char, int>());
        int newNode = Tree.size() - 1;
        Tree[current][c] = newNode;
        current = newNode;
    }

    // If word ends in the node there should be empty edge from the node
    // to a fictitious SinkNode.
    Tree[current]['\0'] = SinkNode;
}

int Dictionary::PrefixEndNode(const std::string &prefix) const {
    int current = 0;
    for (const char& c : prefix) {
        const auto it = Tree[current].find(c);
        if (it == Tree[current].end()) {
            return NoSuchPrefixCode;
        }
        current = it->second;
    }

    return current;
}

bool Dictionary::IsPrefix(const std::string &prefix) const {
    int node = PrefixEndNode(prefix);
    if (node == NoSuchPrefixCode) {
        return false;
    }

    return true;
}

bool Dictionary::IsWord(const std::string &word) const {
    int node = PrefixEndNode(word);
    if (node == NoSuchPrefixCode || Tree[node].find('\0') == Tree[node].end())
        return false;

    return true;
}

void Dictionary::SearchTree(int node, std::string& word,
                            std::unordered_set<std::string> &vocabulary) const {
    for (auto const& edge : Tree[node]) {
        if (edge.first == '\0') {
            vocabulary.insert(word);
            continue;
        }

        word.push_back(edge.first);
        SearchTree(edge.second, word, vocabulary);
        word.pop_back();
    }
}

std::unordered_set<std::string> Dictionary::GetAllWords() const {
    std::unordered_set<std::string> vocabulary;
    std::string word;
    SearchTree(0, word, vocabulary);

    return vocabulary;
}

std::ostream& operator<< (std::ostream& stream, const Dictionary& dict) {
    auto words = dict.GetAllWords();
    for (const auto& word : words) {
        stream << word << " ";
    }
    stream << std::endl;

    return stream;
}
