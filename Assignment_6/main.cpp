#include <iostream>
#include <vector>
#include "arrangement.h"


std::vector<unsigned> GetUsersArrangement(int NumberOfSlots) {
    std::vector<unsigned> arrangement;
    std::cout << "Enter an arrangement of cars at the parking lot" << std::endl;
    unsigned car;
    for (int i = 0; i < NumberOfSlots; ++i) {
        std::cin >> car;
        arrangement.push_back(car);
    }
    return (arrangement);
}


void Rearrangements(CarParking &parking, int NumberOfSlots) {
    std::string user_answer;
    while (1) {
        std::cout << "Do you want to rearrange the cars (yes/no)?" << std::endl;
        std::cin >> user_answer;
        if (user_answer != "yes") {
            break;
        }
        std::vector<unsigned> new_arrangement = GetUsersArrangement(NumberOfSlots);
        std::cout << "Rearranging process:" << std::endl;
        parking.Rearrange(new_arrangement);
        parking.PrintLastActions(std::cout);
        std::cout << std::endl;
    }
}


int main() {
    int NumberOfSlots;
    std::cout << "How many slots are there?" << std::endl;
    std::cin >> NumberOfSlots;
    std::vector<unsigned> arrangement = GetUsersArrangement(NumberOfSlots);
    CarParking parking = CarParking(arrangement);
    Rearrangements(parking, NumberOfSlots);
}