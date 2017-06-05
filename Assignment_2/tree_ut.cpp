#include "tree.h"

#include <gtest/gtest.h>
#include <iostream>
#include <queue>
#include <sstream>
#include <vector>

TEST(TBinaryTree, ConstructorOnlyKey) {
    int key = 1;
    TBinaryTree<int> tree(key);

    EXPECT_EQ(key, tree.GetKey());
    EXPECT_EQ(0, tree.GetDepth());
}

TBinaryTree<int>* GenerateSimpleTree(int rootVal, int leftVal, int rightVal) {
    TBinaryTree<int>* left = new TBinaryTree<int>(leftVal);
    TBinaryTree<int>* right = new TBinaryTree<int>(rightVal);

    return new TBinaryTree<int>(rootVal, left, right);
}

TEST(TBinaryTree, ConstructFromBottomToUp) {
    int rootVal = 1, leftVal = 2, rightVal = 3;
    auto tree = GenerateSimpleTree(rootVal, leftVal, rightVal);

    EXPECT_EQ(rootVal, tree->GetKey());
    EXPECT_EQ(0, tree->GetDepth());
    EXPECT_EQ(leftVal, tree->GetLeft()->GetKey());
    EXPECT_EQ(1, tree->GetLeft()->GetDepth());
    EXPECT_EQ(rightVal, tree->GetRight()->GetKey());
    EXPECT_EQ(1, tree->GetRight()->GetDepth());

    int newRoot = 0;
    TBinaryTree<int>* complexTree = new TBinaryTree<int>(newRoot, tree, nullptr);

    EXPECT_EQ(newRoot, complexTree->GetKey());
    EXPECT_EQ(0, complexTree->GetDepth());
    EXPECT_EQ(rootVal, complexTree->GetLeft()->GetKey());
    EXPECT_EQ(1, complexTree->GetLeft()->GetDepth());
}

TEST(TBinaryTree, TryConstructUsingAnotherTreeSubtree) {
    auto tree = GenerateSimpleTree(1, 2, 3);
    // Try to use the subtree in this way:
    //    1           0
    //  2  3  --> [3]   null
    EXPECT_THROW(new TBinaryTree<int>(0, tree->GetRight(), nullptr), std::invalid_argument);
    EXPECT_THROW(new TBinaryTree<int>(0, nullptr, tree->GetRight()), std::invalid_argument);
}

TEST(TBinaryTree, SetLeft) {
    int leftKey = 1, rootKey = 0;
    auto left = GenerateSimpleTree(leftKey, 2, 3);
    auto tree = new TBinaryTree<int>(rootKey);
    tree->SetLeft(nullptr);
    tree->SetLeft(left);

    EXPECT_EQ(leftKey, tree->GetLeft()->GetKey());
    EXPECT_EQ(1, tree->GetLeft()->GetDepth());

    // Reset the left child
    tree->SetLeft(nullptr);
    EXPECT_EQ(nullptr, tree->GetLeft());
}

TEST(TBinaryTree, SetRight) {
    int rightKey = 1, rootKey = 0;
    auto right = GenerateSimpleTree(rightKey, 2, 3);
    auto tree = new TBinaryTree<int>(rootKey);
    tree->SetRight(right);

    EXPECT_EQ(rightKey, tree->GetRight()->GetKey());
    EXPECT_EQ(1, tree->GetRight()->GetDepth());

    // Reset the right child
    tree->SetRight(nullptr);
    EXPECT_EQ(nullptr, tree->GetRight());
}

TEST(TBinaryTree, SetChildMultipleOwners) {
    // The tree is:
    //     0
    //   1   2
    // 3
    std::vector<int> values = {0, 1, 2, 3, 4};
    auto tree = TBinaryTree<int>::BuildFullBinaryTree(values);

    // Now we'll take pointer to node with key == 3 and will try to set it
    // to the right child of the node with key == 2:
    //     0
    //   1   2
    // 3 ----> [3]
    auto subtree = tree->GetLeft()->GetLeft();
    EXPECT_THROW(tree->GetRight()->SetRight(subtree), std::invalid_argument);
    // And to the left child:
    //       0
    //   1      2
    // 3 --> [3]
    EXPECT_THROW(tree->GetRight()->SetLeft(subtree), std::invalid_argument);
}

TEST(TBinaryTree, FindKey) {
    int rightKey = 2, leftKey = 1, rootKey = 0;
    auto tree = GenerateSimpleTree(rootKey, leftKey, rightKey);

    EXPECT_EQ(tree->FindKey(rightKey), tree->GetRight());
    EXPECT_EQ(tree->FindKey(leftKey), tree->GetLeft());
    EXPECT_EQ(tree->FindKey(rootKey), tree);
}

TEST(TBinaryTree, BuildFullBinaryTree) {
    std::vector<int> values = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    auto tree = TBinaryTree<int>::BuildFullBinaryTree(values);

    std::queue<TBinaryTree<int>*> nodesQueue;
    nodesQueue.push(tree);
    for (auto key : values) {
        auto node = nodesQueue.front();
        nodesQueue.pop();

        EXPECT_EQ(key, node->GetKey());

        nodesQueue.push(node->GetLeft());
        nodesQueue.push(node->GetRight());
    }

    std::vector<int> empty;
    EXPECT_THROW(TBinaryTree<int>::BuildFullBinaryTree(empty), std::invalid_argument);
}

void PrintAncestorsTest(TBinaryTree<int>* tree, int key, const std::string& expected) {
    std::ostringstream ssResult;
    EXPECT_TRUE(tree->PrintAncestors(key, ssResult));
    EXPECT_EQ(expected, ssResult.str());
}

TEST(TBinaryTree, PrintAncestorsSimple) {
    // The tree is:
    //     0
    //   1   2
    // 3  4
    std::vector<int> values = {0, 1, 2, 3, 4};
    auto tree = TBinaryTree<int>::BuildFullBinaryTree(values);

    // Root doesn't have any ancestor
    {
        int key = 0;
        std::ostringstream ssExpected;
        ssExpected << "All ancestors of the node " << key << ":" << std::endl;
        PrintAncestorsTest(tree, key, ssExpected.str());
    }
    {
        int key = 2;
        std::ostringstream ssExpected;
        ssExpected << "All ancestors of the node " << key << ": 0" << std::endl;
        PrintAncestorsTest(tree, key, ssExpected.str());
    }
    {
        int key = 4;
        std::ostringstream ssExpected;
        ssExpected << "All ancestors of the node " << key << ": 1 0" << std::endl;
        PrintAncestorsTest(tree, key, ssExpected.str());
    }
}

TEST(TBinaryTree, PrintAncestors) {
    std::vector<int> values = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    auto tree = TBinaryTree<int>::BuildFullBinaryTree(values);

    for (int i = 0; i < values.size(); i++) {
        std::ostringstream ssExpected;
        ssExpected << "All ancestors of the node " << values[i] << ":";

        int j = (i - 1) / 2;
        while (j > 0) {
            ssExpected << " " << values[j];
            j = (j - 1) / 2;
        }
        if (i) {
            ssExpected << " " << values[0];
        }
        ssExpected << std::endl;

        PrintAncestorsTest(tree, values[i], ssExpected.str());
    }

    std::ostringstream ssFalse;
    EXPECT_FALSE(tree->PrintAncestors(17, ssFalse));
}

TEST(TBinaryTree, LeastCommonAncestor) {
    std::vector<int> values = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    auto tree = TBinaryTree<int>::BuildFullBinaryTree(values);

    EXPECT_EQ(tree->FindKey(3), TBinaryTree<int>::LeastCommonAncestor(tree->FindKey(15), tree->FindKey(8)));
    EXPECT_EQ(tree->FindKey(3), TBinaryTree<int>::LeastCommonAncestor(tree->FindKey(15), tree->FindKey(3)));
    EXPECT_EQ(tree->FindKey(3), TBinaryTree<int>::LeastCommonAncestor(tree->FindKey(3), tree->FindKey(3)));

    EXPECT_EQ(tree->FindKey(0), TBinaryTree<int>::LeastCommonAncestor(tree->FindKey(15), tree->FindKey(14)));
    EXPECT_EQ(tree->FindKey(0), TBinaryTree<int>::LeastCommonAncestor(tree->FindKey(1), tree->FindKey(2)));
    EXPECT_EQ(tree->FindKey(0), TBinaryTree<int>::LeastCommonAncestor(tree->FindKey(0), tree->FindKey(0)));

    EXPECT_EQ(tree->FindKey(1), TBinaryTree<int>::LeastCommonAncestor(tree->FindKey(4), tree->FindKey(15)));

    EXPECT_THROW(TBinaryTree<int>::LeastCommonAncestor(nullptr, tree->FindKey(8)), std::invalid_argument);
    EXPECT_THROW(TBinaryTree<int>::LeastCommonAncestor(tree->FindKey(8), nullptr), std::invalid_argument);
    EXPECT_THROW(TBinaryTree<int>::LeastCommonAncestor(GenerateSimpleTree(1, 2, 3), tree), std::invalid_argument);
}
