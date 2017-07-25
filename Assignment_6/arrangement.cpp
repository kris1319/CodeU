#include "arrangement.h"

CarParking::Action::operator bool () const {
    return from || to;
}

CarParking::CarParking(const std::vector<unsigned>& arrangement)
        : number_of_cars_(arrangement.size() ? arrangement.size() - 1 : 0)
        , arrangement_(arrangement)
        , current_car_slots_(number_of_cars_)
{
    for (unsigned i = 0; i < arrangement_.size(); i++) {
        if (!arrangement_[i]) {
            empty_slot_ = i;
            break;
        }
    }

    used_cars_ = std::vector<bool>(number_of_cars_, false);
    SetCarSlots(arrangement_, current_car_slots_);
}

std::vector<unsigned> CarParking::GetCarArrangement() const {
    return arrangement_;
}

std::vector<CarParking::Action> CarParking::GetLastActions() const {
    return last_actions_;
}

void CarParking::PrintLastActions(std::ostream& out) const {
    int number_of_actions = last_actions_.size();
    if (number_of_actions == 0) {
        out << "There is nothing to move" << std::endl;
        return;
    }
    for (unsigned car : last_transitional_arrangements_[0]) {
        out << car << " ";
    }
    out << std::endl;
    for (int i = 0; i < number_of_actions; ++i) {
        out << "Step " << i + 1 << ": " << std::endl;
        out << "Move from " << last_actions_[i].from << " to " << last_actions_[i].to << std::endl;
        for (unsigned car : last_transitional_arrangements_[i + 1]) {
            out << car << " ";
        }
        out << std::endl;
    }
}

bool CarParking::operator==(const CarParking& other) const {
    return arrangement_ == other.arrangement_;
}

void CarParking::Rearrange(const std::vector<unsigned> &new_arrangement) {
    // Reinitialize data structures.
    ResetLastActions();

    std::vector<unsigned> car_slots(number_of_cars_);
    SetCarSlots(new_arrangement, car_slots);

    for (auto car : arrangement_) {
        if (!car) {     // The condition implements 'for each chain/cycle'.
            continue;
        }

        relocate_ = {0, 0};
        RearrangeChain(car, car_slots, new_arrangement);
        if (relocate_) {    // If it was a cycle.
            ImplementAction(relocate_);
        }
    }
}

void CarParking::RearrangeChain(unsigned car, const std::vector<unsigned> &car_slots,
                                const std::vector<unsigned> &new_arrangement)
{
    // Mark current node as used.
    used_cars_[car - 1] = true;

    unsigned slot = car_slots[car - 1];
    unsigned next_car = arrangement_[slot];
    if (next_car == car) {
        return;
    } else if (next_car && !used_cars_[next_car - 1]) {
        RearrangeChain(next_car, car_slots, new_arrangement);
    } else if (next_car) {      // It is a cycle.
        relocate_ = {empty_slot_, slot};
        slot = empty_slot_;
    }

    ImplementAction({current_car_slots_[car - 1], slot});
}

void CarParking::SetCarSlots(const std::vector<unsigned> &arrangement, std::vector<unsigned>& car_slots) {
    for (unsigned i = 0; i < arrangement.size(); i++) {
        if (arrangement[i]) {
            car_slots[arrangement[i] - 1] = i;
        }
    }
}

void CarParking::ImplementAction(const CarParking::Action &action) {
    unsigned car = arrangement_[action.from];
    arrangement_[action.to] = car;
    arrangement_[action.from] = 0;
    current_car_slots_[car - 1] = action.to;

    last_actions_.push_back(action);
    last_transitional_arrangements_.push_back(arrangement_);

    // 'From' slot is empty now.
    empty_slot_ = action.from;
}

void CarParking::ResetLastActions() {
    last_actions_.clear();
    last_transitional_arrangements_.clear();
    last_transitional_arrangements_.push_back(arrangement_);

    std::fill(used_cars_.begin(), used_cars_.end(), false);
}
