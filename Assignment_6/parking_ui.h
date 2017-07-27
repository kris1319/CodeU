#pragma once

#include "arrangement.h"

// ParkingUI class provides UI.
class ParkingUI {
public:
    static void Run();

private:
    static void Rearrangings(int number_of_slots, CarParking& parking);
    static void GetUsersArrangement(int number_of_slots, std::vector<unsigned>& arrangement);
};
