#include "gtest/gtest.h"

#include <vector>

#include "sorter.h"
#include "rnum_generator.hpp"


TEST (One, Two)
{
    std::vector<int32_t> arr = generateRandomArray(10);
    EXPECT_FALSE(std::is_sorted(arr.begin(), arr.end()));

    // Act
    alex_sort(arr.data(), arr.size());

    // Assert
    EXPECT_TRUE(std::is_sorted(arr.begin(), arr.end()));
}
