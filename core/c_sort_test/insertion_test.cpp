#include <cstring>
#include <algorithm>
#include <array>

#include <gtest/gtest.h>

#include "rnum_generator/generator.h"
#include "c_sort/insertion_sort.h"


TEST(insertion_sort, small_array1)
{
    std::array<int32_t, 5> a = getUnsortedArray();
    ASSERT_FALSE(std::is_sorted(a.begin(), a.end()));

    // Act
    c_insertion_sort1(a.data(), a.size());

    // Assert
    ASSERT_TRUE(std::is_sorted(a.begin(), a.end()));
}


TEST(insertion_sort, large_array1)
{
    std::vector<int32_t> array = generateRandomArray(LARGE_SIZE);
    ASSERT_FALSE(std::is_sorted(array.begin(), array.end()));

    // Act
    c_insertion_sort1(array.data(), array.size());

    // Assert
    ASSERT_TRUE(std::is_sorted(array.begin(), array.end()));
}


TEST(insertion_sort, small_array2)
{
    std::array<int32_t, 5> a = getUnsortedArray();
    ASSERT_FALSE(std::is_sorted(a.begin(), a.end()));

    // Act
    c_insertion_sort2(a.data(), a.size());

    // Assert
    ASSERT_TRUE(std::is_sorted(a.begin(), a.end()));
}


TEST(insertion_sort, large_array2)
{
    std::vector<int32_t> array = generateRandomArray(LARGE_SIZE);
    ASSERT_FALSE(std::is_sorted(array.begin(), array.end()));

    // Act
    c_insertion_sort2(array.data(), array.size());

    // Assert
    ASSERT_TRUE(std::is_sorted(array.begin(), array.end()));
}
