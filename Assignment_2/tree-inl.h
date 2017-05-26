#include "tree.h"

#include <queue>

template <class T>
TBinaryTree<T>::TBinaryTree(const T& root) {
    Root = new TTreeNode(root);
}

template <class T>
TBinaryTree<T>::TBinaryTree(const T& root, const TBinaryTree<T>& left, const TBinaryTree<T>& right) {
    Root = new TTreeNode(root, left.Root, right.Root);
}

template <class T>
TBinaryTree<T>::TBinaryTree(const std::vector<T>& values) {
    Root = BuildTree(values, 0);
}

template <class T>
typename TBinaryTree<T>::TTreeNode* TBinaryTree<T>::BuildTree(const std::vector<T>& values, int idxRoot) {
    int idxLeft = 2 * idxRoot + 1;
    int idxRight = idxLeft + 1;
    if (idxLeft >= values.size()) {
        return new TTreeNode(values[idxRoot]);
    } else if (idxRight >= values.size()) {
        return new TTreeNode(values[idxRoot], BuildTree(values, idxLeft), nullptr);
    } else {
        return new TTreeNode(values[idxRoot], BuildTree(values, idxLeft), BuildTree(values, idxRight));
    }
}

template <class T>
void TBinaryTree<T>::Print(std::ostream &out) {
    out << "Binary tree:" << std::endl;

    std::queue<TTreeNode*> nodes;
    nodes.push(Root);

    while (!nodes.empty()) {
        TTreeNode* node = nodes.front();
        if (!node) {
            break;
        }

        out << node->Key << " ";

        nodes.push(node->Left);
        nodes.push(node->Right);
        nodes.pop();
    }

    out << std::endl;
}

template <class T>
TBinaryTree<T>::~TBinaryTree() {
    std::queue<TTreeNode*> nodes;
    nodes.push(Root);

    while (!nodes.empty()) {
        TTreeNode* node = nodes.front();
        if (!node) {
            break;
        }

        nodes.push(node->Left);
        nodes.push(node->Right);

        nodes.pop();
        delete node;
    }
}
