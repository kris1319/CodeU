#include "dictionary.h"

Dictionary::Dictionary() {
    Tree.push_back(std::map<char, int>());
}

Dictionary::Dictionary(const std::vector<std::string> vocabulary)
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

        Tree.push_back(std::map<char, int>());
        int newNode = Tree.size() - 1;
        Tree[current][c] = newNode;
        current = newNode;
    }

    Tree[current]['\0'] = -1;
}

int Dictionary::PrefixEndNode(const std::string &prefix) const {
    int current = 0;
    for (const char& c : prefix) {
        const auto it = Tree[current].find(c);
        if (it == Tree[current].end()) {
            return 0;
        }
        current = it->second;
    }

    return current;
}

bool Dictionary::IsPrefix(const std::string &prefix) const {
    return (bool)PrefixEndNode(prefix);
}

bool Dictionary::IsWord(const std::string &word) const {
    int node = PrefixEndNode(word);
    if (!node || Tree[node].find('\0') == Tree[node].end())
        return false;

    return true;
}

void Dictionary::SearchTree(int node, std::string& word,
                            std::unordered_set<std::string> &vocabulary) const {
    for (auto const& edge : Tree[node]) {
        if (edge.first == '\0') {
            vocabulary.insert(std::string(word.begin(), word.end()));
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
