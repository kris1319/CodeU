#include "disjoint_set.h"

#include <algorithm>

bool DisjointSet::IsLeader() const {
    return parent_ == this;
}

DisjointSet* DisjointSet::FindSetLeader() {
    if (IsLeader()) {
        return this;
    }

    parent_ = parent_->FindSetLeader();
    return parent_;
}

void DisjointSet::UnionSets(DisjointSet *first, DisjointSet *second) {
    DisjointSet* first_leader = first->FindSetLeader();
    DisjointSet* second_leader = second->FindSetLeader();
    if (first_leader == second_leader) {
        return;
    }

    if (first_leader->rank_ < second_leader->rank_) {
        std::swap(first_leader, second_leader);
    }
    second_leader->parent_ = first_leader;

    if (first_leader->rank_ == second_leader->rank_) {
        first_leader->rank_++;
    }
}
