#pragma once

// The class implement disjoint sets data structure. It uses two heuristics for implementation
// of FindSetLeader() and UnionSets() methods: rank heuristic and path compression.
// The complexity of the operations is O(a(n)), where n - the number of items and a(n) -
// Inverse Ackermann function which grows very slow and for the most possible values of n
// it is less then 4. The proof of the such complexity can be found in the book
// 'Introduction to Algorithms' Cormen, Leiserson, Rivest, Stein.
class DisjointSet {
    // Pointer to the parent set's item
    DisjointSet* parent_;
    // Upper bound of the set's depth
    int rank_ = 0;

public:
    DisjointSet()
        : parent_(this)
    {}

    ~DisjointSet() {}

    // Returns true if current item is a leader item in it's set and false otherwise.
    bool IsLeader() const;
    // Returns a pointer to the leader item of the set to which belongs current item.
    // If the item is a leader of it's set, the method returns pointer to this.
    DisjointSet* FindSetLeader();

    // The methodunites 2 sets. If the given items belong to the one set nothing will
    // be done.
    static void UnionSets(DisjointSet* first, DisjointSet* second);
};
