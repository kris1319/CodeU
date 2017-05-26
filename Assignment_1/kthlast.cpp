#include <iostream>
#include <vector>
#include <stdexcept>
#include <sstream>

template <class T>
class TLinkedList {
    struct TListNode {
        T value;
        TListNode* next;

        TListNode(const T& val) : value(val), next(nullptr) {}
    };

    TListNode* root = nullptr;
    TListNode* tail = nullptr;
    int list_size = 0;

public:
    TLinkedList() {}

    // Makes list with values from the given vector values
    TLinkedList(const std::vector<T>& values) {
        for (const T& it : values) {
            Push(it);
        }
    }

    // We shoud free memory
    ~TLinkedList() {
        while (root != nullptr) {
            TListNode* next = root->next;
            delete root;
            root = next;
        }
    }

    int GetSize() {
        return list_size;
    }

    // Returns the kth from the last item in the list
    // Throws out_of_range exception if k < 0 or k >= list_size
    int GetLastK(int k) {
        // If k is greater than list size or less than 0 throw out_of_range exception.
        if (k > list_size - 1 || k < 0) {
            std::ostringstream errStream;
            errStream << "There are only " << list_size << " items in the list but k = " << k << " was given." << std::endl;

            throw std::out_of_range(errStream.str());
        }

        // Define 2 pointers:
        // * one will point to the item in the list
        // * another will point to kth from the last
        TListNode* lastK = root;
        TListNode* last = root;

        // Make gap between two pointers equal to k
        for (int gap = 0; gap != k; gap++)
            last = last->next;

        // Go to the end of the list. last pointer will point the last item
        // and lastK -- to the kth from the last
        while (last->next != nullptr) {
            last = last->next;
            lastK = lastK->next;
        }

        return lastK->value;
    }

    // Adds new item to the list
    int Push(T val) {
        TListNode* newIt = new TListNode(val);

        if (!tail) {
            root = newIt;
            tail = root;
        } else {
            tail->next = newIt;
            tail = tail->next;
        }

        list_size++;

        return list_size;
    }

    // Prints the list into the given stream
    void Print(std::ostream& out) {
        TListNode* list = root;
        while (list != nullptr) {
            out << list->value << " ";
            list = list->next;
        }

        out << std::endl << "Total size " << list_size << std::endl;
        out.flush();
    }
};

int main() {
    std::cout << "Checking empty list" << std::endl;
    TLinkedList<int> zeroList;
    zeroList.Print(std::cout);
    std::cout << std::endl;

    std::vector<int> values = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    TLinkedList<int> list(values);
    std::cout << "Checking constructor with vector {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}" << std::endl;
    list.Print(std::cout);
    std::cout << std::endl;

    std::cout << "Checking Push(10)" << std::endl;
    list.Push(10);
    list.Print(std::cout);
    std::cout << std::endl;

    std::cout << "Checking GetLastK(...)" << std::endl;
    std::cout << "last k = 0 : " << list.GetLastK(0) << std::endl;
    std::cout << "last k = list_size - 1 : " << list.GetLastK(list.GetSize() - 1) << std::endl;
    std::cout << "last k = 3 : " << list.GetLastK(3) << std::endl;
    std::cout << std::endl;

    std::cout << "Checking invalid k = -1" << std::endl;
    try {
        list.GetLastK(-1);
    } catch(std::out_of_range& ex) {
        std::cout << "Caught an out_of_range exception: " << ex.what();
    }
    std::cout << std::endl;

    std::cout << "Checking invalid k = list_size" << std::endl;
    try {
        list.GetLastK(list.GetSize());
    } catch(std::out_of_range& ex) {
        std::cout << "Caught an out_of_range exception: " << ex.what();
    }
    std::cout << std::endl;

    return 0;
}
