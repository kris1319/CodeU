#pragma once

#include <iostream>
#include <vector>

// CarParking class implements N - 1 cars arrangement on the N slots. It provides interface
// for updating current parking state using simple actions kind of:
//                  [Move a car from the slot <i> to the slot <j>]
//
// The algorithm with the minimum possible actions of the last updating can be get using
// GetLastActions() method.
class CarParking {
public:
    // Action struct specifies one car relocation.
    struct Action {
        // Index of the slot from which the car will be moved.
        unsigned from = 0;
        // Index of the slot to which the car will be moved.
        unsigned to = 0;

        Action() = default;

        Action(unsigned afrom, unsigned ato)
            : from(afrom)
            , to(ato)
        {}

        operator bool () const;
    };

public:
    // Creates a class instance with the given arrangement state.
    CarParking(const std::vector<unsigned>& arrangement);

    ~CarParking() {}

    // Updates current state with the given ordering. It works in assumption that new_arrangement
    // vector is valid and it is possible to rearrange cars to get a new ordering.
    //
    // Algorithm. The main idea is to consider arrangements as the permutations.
    // Assume that we have two arrangements - current [a1, a2, ..., aN] and new [b1, b2, ..., bN], thus:
    //
    // * transition is a connection between 2 nodes (or 2 cars) v and u such are:
    //   current[v_new_idx] = u, where v_new_idx - index of the vth car in the new arrangement;
    //
    // * chain is a sequence of transitions [v1 -> v2 -> ... -> vK -> 0];
    //
    // * cycle is a sequence of jumps [v1 -> v2 -> ... -> vK -> v1];
    //
    // where v1, ..., vK - different nodes (i.e. cars), and 0 is an empty slot. For example:
    //
    // * if [1 2 0] - current, [0 1 2] - new then 1 -> 2 -> 0 is a chain
    //
    // * if [1 2 3 0] - current, [2 3 1 0] - new then 1 -> 2 -> 3 -> 1 is a cycle
    //
    // Also let's notice important facts: if we have
    // * a cycle with size K this cycle can be rearranged by K + 1 steps (simple actions),
    // * a chain with size K it needs K steps to rearrange the chain.
    // And these numbers of actions are the only possible minimums.
    // In this way the minimum possible number of steps for rearranging N cars is N.
    //
    // Also it is important that any possible arrangement can be factorized on the set of chains and
    // cycles even if the size of chain/cycle is 1.
    // The main idea of the method is to traverse two given arrangements (current and new) by chains and
    // cycles and recursively rearrange each chain and each cycle.
    //
    // Complexity.
    // On each chain/cycle the algorithm call itself recursively and after move current node (car) to
    // the empty slot where the car should be in the new arrangement.
    // One movement contains deleting busy slot and insert new one into the unordered_set of empty slots.
    // Thus the complexity of one movement is constant - O(1). Assume that the number of cycles is K.
    // Thus it takes O(N + K) to rearrange the cars. So K is less then N thus total complexity is O(N).
    void Rearrange(const std::vector<unsigned>& new_arrangement);

    // Returns current state of the class instance.
    std::vector<unsigned> GetCarArrangement() const;
    // Returns an ordered list of simple actions which represent the algorithm of the last
    // cars rearranging.
    // It returns an empty vector if there was no updating or if the last state was equal to
    // the previous one.
    std::vector<CarParking::Action> GetLastActions() const;
    // Prints into the given stream list of actions of the last cars rearranging.
    void PrintLastActions(std::ostream& out) const;

    bool operator==(const CarParking& other) const;

private:
    // Resets used_cars_ and clears last_actions_.
    void ResetLastActions();
    // Helper method which initializes helper data structures.
    void SetCarSlots(const std::vector<unsigned>& arrangement, std::vector<unsigned>& car_slots);

    // Implements one car movement.
    void ImplementAction(const CarParking::Action& action);
    // The method traverse the chain/cycle which starts from the 'car' node. It calls itself recursevely
    // with the next node of the current chain/cycle.
    void RearrangeChain(unsigned car, const std::vector<unsigned> &car_slots,
                        const std::vector<unsigned>& new_arrangement);

private:
    unsigned number_of_cars_ = 0;
    // Current arrangement.
    std::vector<unsigned> arrangement_;
    // The vector maps cars to its slots in the current arrangement. The size of the current_car_slots_ is N - 1.
    std::vector<unsigned> current_car_slots_;
    // The last used algorithm for rearranging cars.
    std::vector<CarParking::Action> last_actions_;

    // Possible empty slot.
    unsigned empty_slot_;
    // Helper field that allow to implement last movement for the cycles.
    CarParking::Action relocate_;
    // The vector contain marks for already traversed nodes.
    std::vector<bool> used_cars_;
};
