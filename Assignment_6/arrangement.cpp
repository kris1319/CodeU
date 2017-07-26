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

void CarParking::PrintLastActions(std::ostream &out) const {
    std::vector<unsigned> arrangement = last_arrangement_;
    for (unsigned i : arrangement) {
        out << i << " ";
    }
    out << std::endl;
    unsigned step_counter = 0;
    for (const auto& action : last_actions_) {
        out << "Step " << ++step_counter << ":" << std::endl;
        out << "Move from " << action.from << " to " << action.to << std::endl;
        std::swap(arrangement[action.from], arrangement[action.to]);
        for (unsigned i : arrangement) {
            out << i << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "Rearranged by " << step_counter << " steps" << std::endl;
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
    last_actions_.push_back(action);

    unsigned car = arrangement_[action.from];
    arrangement_[action.to] = car;
    arrangement_[action.from] = 0;
    current_car_slots_[car - 1] = action.to;

    // 'From' slot is empty now.
    empty_slot_ = action.from;
}

void CarParking::ResetLastActions() {
    last_actions_.clear();
    last_arrangement_ = arrangement_;
    std::fill(used_cars_.begin(), used_cars_.end(), false);
}
