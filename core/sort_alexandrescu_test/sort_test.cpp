#include "gtest/gtest.h"

#include <algorithm>
#include <vector>
#include <random>

#include "sorter.h"


std::vector<int32_t> generateRandomArray(size_t size)
{
    std::vector<int32_t> arr(size);
    
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<int32_t> uniform_dist(0, 1000);
    
    for (int i = 0; i < size; i++)
    {
        arr[i] = uniform_dist(engine);
    }

    return arr;
}

TEST (One, Two)
{
    std::vector<int32_t> arr = generateRandomArray(10);
    EXPECT_FALSE(std::is_sorted(arr.begin(), arr.end()));

    // Act
    alex_sort(arr.data(), arr.size());

    // Assert
    EXPECT_TRUE(std::is_sorted(arr.begin(), arr.end()));
}
