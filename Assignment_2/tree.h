#pragma once

#include <iostream>
#include <vector>

template <class T>
class TBinaryTree {
    struct TTreeNode {
        T Key;
        TTreeNode* Left = nullptr;
        TTreeNode* Right = nullptr;

        TTreeNode(T value) : Key(value) {}
        TTreeNode(const T& key, TTreeNode* left, TTreeNode* right)
            : Key(key)
            , Left(left)
            , Right(right)
        {}
    };

    TTreeNode* Root = nullptr;

public:
    TBinaryTree() {}
    TBinaryTree(const T& root);
    TBinaryTree(const T& root, const TBinaryTree<T>& left, const TBinaryTree<T>& right);
    TBinaryTree(const std::vector<T>& values);

    ~TBinaryTree();

    void Print(std::ostream& out);

private:
    TTreeNode* BuildTree(const std::vector<T>& values, int idxRoot);
};

#include "tree-inl.h"
