#include "tree.h"

#include <iostream>
#include <vector>

int main() {
    std::vector<int> values = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    TBinaryTree<int> tree(values);
    tree.Print(std::cout);

    return 0;
}
