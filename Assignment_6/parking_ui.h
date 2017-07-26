#pragma once

#include "arrangement.h"

// ParkingUI class provides UI.
class ParkingUI {
public:
    static void Run();

private:
    static void Rearrangings(int NumberOfSlots, CarParking& parking);
    static void GetUsersArrangement(int NumberOfSlots, std::vector<unsigned>& arrangement);
};
