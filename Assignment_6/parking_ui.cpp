#include "parking_ui.h"

void ParkingUI::GetUsersArrangement(int number_of_slots, std::vector<unsigned>& arrangement) {
    if (number_of_slots == 0) {
        return;
    }

    std::cout << "Enter an arrangement of cars at the parking lot" << std::endl;
    unsigned car;
    for (int i = 0; i < number_of_slots; ++i) {
        std::cin >> car;
        arrangement.push_back(car);
    }
}

void ParkingUI::Run() {
    // variables
    unsigned number_of_slots;
    std::string user_answer;

    while (true) {
        std::cout << "New parking is ready. Set a number of places:" << std::endl;
        std::cin >> number_of_slots;

        std::vector<unsigned> arrangement;
        GetUsersArrangement(number_of_slots, arrangement);

        CarParking parking = CarParking(arrangement);
        Rearrangings(number_of_slots, parking);

        std::cout << std::endl;
        std::cout << "Do you want to enter another arrangement (yes/no)?" << std::endl;
        std::cin >> user_answer;
        while (user_answer != "no" && user_answer != "yes") {
            std::cout << "Please write 'yes' or 'no'" << std::endl;
            std::cin >> user_answer;
        }
        if (user_answer == "no") {
            break;
        }
    }
}

void ParkingUI::Rearrangings(int number_of_slots, CarParking& parking) {
    if (number_of_slots == 0) {
        return;
    }

    std::string user_answer;
    while (true) {
        std::cout << "Do you want to rearrange the cars (yes/no)?" << std::endl;
        std::cin >> user_answer;
        if (user_answer == "no") {
            break;
        }
        if (user_answer != "yes") {
            std::cout << "Please write 'yes' or 'no'" << std::endl;
            continue;
        }

        std::vector<unsigned> new_arrangement;
        GetUsersArrangement(number_of_slots, new_arrangement);

        std::cout << "Rearranging process:" << std::endl;

        parking.Rearrange(new_arrangement);
        parking.PrintLastActions(std::cout);

        std::cout << std::endl;
    }
}
