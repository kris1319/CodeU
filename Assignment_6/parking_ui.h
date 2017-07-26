#pragma once

#include "arrangement.h"

// ParkingUI class provides UI.
class ParkingUI {
public:
    void Run();
private:
    void Rearrangings(int NumberOfSlots, CarParking& parking);
};