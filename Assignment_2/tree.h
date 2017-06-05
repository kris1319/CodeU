#pragma once

#include <iostream>
#include <vector>
#include <string>

// Implementation of a binary tree data structure.
template <class T>
class TBinaryTree {
    T Key;
    // Depth of the node in the BT. The root depth is 0.
    unsigned Depth = 0;

    TBinaryTree* Parent = nullptr;
    TBinaryTree* Left = nullptr;
    TBinaryTree* Right = nullptr;

public:
    // Creating a root tree
    TBinaryTree(T value) : Key(value) {}
    // For creating a tree "from bottom to up"
    //
    // Notice: because of the Depth field in each tree node to maintain a consistency of all depths
    // values, constructor calls ComputeDepths() method for the left and right subtrees to
    // recompute depths. So this works O(n) where n is number of items in the left and right subtrees both.
    TBinaryTree(const T& key, TBinaryTree<T>* left, TBinaryTree<T>* right);

    ~TBinaryTree();

    // Sets left or right subtrees. If there is already subtree it will be deleted
    // whether or not nullptr was given.
    //
    // Notice: these methods recompute depths too, so each of them works
    // O(n) where n is number of items in the left or right subtree.
    TBinaryTree<T>* SetLeft(TBinaryTree<T>* left);
    TBinaryTree<T>* SetRight(TBinaryTree<T>* right);

    // Just getters
    T GetKey();
    unsigned GetDepth();
    TBinaryTree<T>* GetLeft();
    TBinaryTree<T>* GetRight();

    // The method returns the first found node with the given key.
    // If the tree doesn't have any node with the given key the method returns nullptr.
    // It uses DFS for searching.
    TBinaryTree<T>* FindKey(const T& key);

    // Generates full BT by given vector of keys which is string representation of a full BT.
    // More formally for each i=1,2,..,n (where n - number of the tree nodes) node with the Key = values[i]
    // has two children: node with Key = values[2 * i + 1] and node with Key = values[2 * i + 2].
    //
    // For example:
    //      values = {0, 1, 2, 3, 4, 5}
    // The tree will be:
    //        0
    //      /  \
    //     1   2
    //    /\  /\
    //   3 4 5
    static TBinaryTree* BuildFullBinaryTree(const std::vector<T>& values);

    // Returns pointer for LCA of two nodes in a tree.
    // If nullptr was given as one of the arguments methods throws argument_invalid exception.
    // Also if two nodes don't have an ancestor (they are from different trees) it also throws
    // argument_invalid exception.
    static TBinaryTree* LeastCommonAncestor(TBinaryTree<T>* first, TBinaryTree<T>* second);

    // Prints all ancestors of a node with the given key except itself to the given stream
    // and returns true or false wether there is a such node in the tree.
    bool PrintAncestors(const T& key, std::ostream& out);
    // Prints tree.
    void Print(std::ostream& out, std::string level = "");

private:
    // Helper constructor for the BuildFullBinaryTree method. It doesn't recompute depths
    // so it works faster for another one.
    TBinaryTree(const T& key, unsigned depth, TBinaryTree<T>* left, TBinaryTree<T>* right);
    // Recompute depth starting from the given value.
    void ComputeDepths(unsigned depth);

    // Also helper method for BuildFullBinaryTree method.
    static TBinaryTree<T>* BuildTree(const std::vector<T>& values, int idxRoot, unsigned depth);
};

#include "tree-inl.h"
