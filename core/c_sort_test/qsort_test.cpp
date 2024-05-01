#include <cstring>
#include <algorithm>
#include <array>

#include <gtest/gtest.h>

#include "rnum_generator/generator.h"
#include "c_sort/quick_sort.h"


TEST(c_quick_sort, small_array)
{
    std::array<int32_t, 5> a = getUnsortedArray();
    ASSERT_FALSE(std::is_sorted(a.begin(), a.end()));

    // Act
    c_quick_sort(a.data(), a.size());

    // Assert
    ASSERT_TRUE(std::is_sorted(a.begin(), a.end()));
}


TEST(c_quick_sort, large_array)
{
    std::vector<int32_t> array = generateRandomArray(LARGE_SIZE);
    ASSERT_FALSE(std::is_sorted(array.begin(), array.end()));

    // Act
    c_quick_sort(array.data(), array.size());

    // Assert
    ASSERT_TRUE(std::is_sorted(array.begin(), array.end()));
}


TEST(c_quick_sort, small_array_assemblified)
{
    std::array<int32_t, 5> arr = getUnsortedArray();
    ASSERT_FALSE(std::is_sorted(arr.begin(), arr.end()));

    // Act
    c_quick_sort_assemblified(arr.data(), arr.size());

    // Assert
    ASSERT_TRUE(std::is_sorted(arr.begin(), arr.end()));
}

TEST(c_quick_sort, large_array_assemblified)
{
    std::vector<int32_t> arr = generateRandomArray(LARGE_SIZE);
    ASSERT_FALSE(std::is_sorted(arr.begin(), arr.end()));

    // Act
    c_quick_sort_assemblified(arr.data(), arr.size());

    // Assert
    ASSERT_TRUE(std::is_sorted(arr.begin(), arr.end()));
}