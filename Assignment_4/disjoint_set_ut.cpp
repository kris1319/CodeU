#include "disjoint_set.h"

#include <gtest/gtest.h>
#include <vector>

TEST(DisjointSet, Single) {
    DisjointSet* single = new DisjointSet();
    EXPECT_TRUE(single->IsLeader());

    delete single;
}

TEST(DisjointSet, FindSetLeader) {
    DisjointSet* lead_first = new DisjointSet();
    DisjointSet* lead_second = new DisjointSet();

    const int numberOfItems = 5;
    std::vector<DisjointSet*> first_set;
    std::vector<DisjointSet*> second_set;
    for (int i = 0; i < numberOfItems; i++) {
        DisjointSet* item_first = new DisjointSet();
        first_set.push_back(item_first);
        DisjointSet::UnionSets(lead_first, item_first);
        EXPECT_EQ(lead_first->FindSetLeader(), item_first->FindSetLeader());

        DisjointSet* item_second = new DisjointSet();
        second_set.push_back(item_second);
        EXPECT_NE(lead_second->FindSetLeader(), item_second->FindSetLeader());

        DisjointSet::UnionSets(lead_second, item_second);
        EXPECT_EQ(lead_second->FindSetLeader(), item_second->FindSetLeader());
    }

    DisjointSet::UnionSets(lead_first, lead_second);
    EXPECT_EQ(lead_first->FindSetLeader(), lead_second->FindSetLeader());
    for (int i = 0; i < numberOfItems; i++) {
        EXPECT_EQ(first_set[i]->FindSetLeader(), second_set[i]->FindSetLeader());
    }

    for (int i = 0; i < numberOfItems; i++) {
        delete first_set[i];
        delete second_set[i];
    }

    delete lead_first;
    delete lead_second;
}

TEST(DisjointSet, UnionSets) {
    DisjointSet* first = new DisjointSet();
    DisjointSet* second = new DisjointSet();

    EXPECT_NE(first->FindSetLeader(), second->FindSetLeader());
    DisjointSet::UnionSets(first, second);
    EXPECT_EQ(first->FindSetLeader(), second->FindSetLeader());

    delete first;
    delete second;
}
