#include "arrangement.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <gtest/gtest.h>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

void ValidateActions(std::vector<unsigned> arr, const std::vector<unsigned>& new_arr,
                     const std::vector<CarParking::Action>& actions, int seed=0) {
    for (const auto& action : actions) {
        arr[action.to] = arr[action.from];
        arr[action.from] = 0;
    }
    EXPECT_EQ(arr, new_arr) << "Seed = " << seed;
}

TEST(CarParking, ConstructorTest) {
    CarParking park({1, 2, 3, 4, 5, 0});
    EXPECT_TRUE(park.GetLastActions().empty());
}

TEST(CarParking, EmptyParkingTest) {
    std::vector<unsigned> arr;
    CarParking park(arr);

    EXPECT_TRUE(park.GetCarArrangement().empty());
}

TEST(CarParking, WithoutCarsTest) {
    std::vector<unsigned> arr {0};
    CarParking park(arr);

    park.Rearrange(arr);
    EXPECT_TRUE(park.GetLastActions().empty());
    EXPECT_TRUE(park == CarParking(arr));

    ValidateActions(arr, arr, park.GetLastActions());
}

TEST(CarParking, TheSameArrangementsTest) {
    std::vector<unsigned> arr {1, 2, 3, 4, 5, 0};
    CarParking park(arr);

    park.Rearrange(arr);
    EXPECT_TRUE(park.GetLastActions().empty());
    EXPECT_TRUE(park == CarParking(arr));

    ValidateActions(arr, arr, park.GetLastActions());
}

TEST(CarParking, SmallSimpleOneStepTest) {
    std::vector<unsigned> arr {0, 1};
    std::vector<unsigned> new_arr {1, 0};
    CarParking park(arr);

    park.Rearrange(new_arr);
    EXPECT_EQ(park.GetLastActions().size(), 1);
    EXPECT_TRUE(park == CarParking(new_arr));

    ValidateActions(arr, new_arr, park.GetLastActions());
}

TEST(CarParking, SmallSimpleTest) {
    std::vector<unsigned> arr {2, 0, 1};
    std::vector<unsigned> new_arr {1, 2, 0};
    CarParking park(arr);

    park.Rearrange(new_arr);
    EXPECT_EQ(park.GetLastActions().size(), 2);
    EXPECT_TRUE(park == CarParking(new_arr));

    ValidateActions(arr, new_arr, park.GetLastActions());
}

TEST(CarParking, ExampleTest) {
    std::vector<unsigned> arr {3, 1, 2, 0};
    std::vector<unsigned> new_arr {1, 2, 0, 3};
    CarParking park(arr);

    park.Rearrange(new_arr);
    EXPECT_EQ(park.GetLastActions().size(), 3);
    EXPECT_TRUE(park == CarParking(new_arr));

    ValidateActions(arr, new_arr, park.GetLastActions());
}

TEST(CarParking, OneSimpleCycleTest) {
    std::vector<unsigned> arr {1, 2, 3, 4, 0};
    std::vector<unsigned> new_arr {3, 4, 2, 1, 0};
    CarParking park(arr);

    park.Rearrange(new_arr);
    EXPECT_EQ(park.GetLastActions().size(), 5);
    EXPECT_TRUE(park == CarParking(new_arr));

    ValidateActions(arr, new_arr, park.GetLastActions());
}

int RandomShuffle(std::vector<unsigned>& arr) {
    int seed = std::time(0);
    std::mt19937 g(seed);

    std::shuffle(arr.begin(), arr.end(), g);
    return seed;
}

std::string ArrangementToString(const std::vector<unsigned>& arr) {
    std::stringstream ss;
    for (auto i : arr) {
        ss << " " << i;
    }

    return ss.str();
}

TEST(CarParking, RandomTestSet) {
    unsigned repeats = 100;
    std::vector<unsigned> arr {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 0};
    std::cout << "Random test set for "<< 16 << " cars"
              << " and " << repeats << " shuffles has started" << std::endl;
    std::cout << "Init data:" << ArrangementToString(arr) << std::endl;
    std::vector<unsigned> new_arr(arr);

    for (unsigned i = 0; i < repeats; i++) {
        CarParking park(arr);

        std::cout << "Seed " << RandomShuffle(new_arr) << std::endl;
        std::cout << "Shuffled:" << ArrangementToString(new_arr) << std::endl;

        park.Rearrange(new_arr);
        EXPECT_TRUE(park == CarParking(new_arr));
        ValidateActions(arr, new_arr, park.GetLastActions());
    }
}

TEST(CarParking, LargeRandomTestSet) {
    unsigned number_of_slots = 1500;
    unsigned repeats = 500;
    std::vector<unsigned> arr;
    for (unsigned i = 0; i < number_of_slots; i++) {
        arr.push_back(i + 1);
    }
    arr.push_back(0);

    std::cout << "Large random test set for "<< number_of_slots << " cars"
              << " and " << repeats << " shuffles has started" << std::endl;
    std::vector<unsigned> new_arr(arr);

    for (unsigned i = 0; i < repeats; i++) {
        CarParking park(arr);

        int seed = RandomShuffle(new_arr);
        park.Rearrange(new_arr);
        EXPECT_TRUE(park == CarParking(new_arr));
        ValidateActions(arr, new_arr, park.GetLastActions(), seed);
    }
}
