#include <cstring>
#include <algorithm>
#include <array>

#include <gtest/gtest.h>

#include "rnum_generator/generator.h"
#include "c_sort/bubble_sort.h"


TEST(c_bubble_sort, small_array_classic)
{
    std::array<int32_t, 5> a = getUnsortedArray();
    ASSERT_FALSE(std::is_sorted(a.begin(), a.end()));

    // Act
    c_bubble_sort(a.data(), a.size());

    // Assert
    ASSERT_TRUE(std::is_sorted(a.begin(), a.end()));
}


TEST(c_bubble_sort, large_array_classic)
{
    std::vector<int32_t> array = generateRandomArray(LARGE_SIZE);
    ASSERT_FALSE(std::is_sorted(array.begin(), array.end()));

    // Act
    c_bubble_sort(array.data(), array.size());

    // Assert
    ASSERT_TRUE(std::is_sorted(array.begin(), array.end()));
}


TEST(c_bubble_sort, rectangular_assemblyfied_small)
{
    std::array<int32_t, 5> a = getUnsortedArray();
    ASSERT_FALSE(std::is_sorted(a.begin(), a.end()));

    // Act
    c_bubble_sort_rect_assemblified(a.data(), a.size());

    // Assert
    ASSERT_TRUE(std::is_sorted(a.begin(), a.end()));
}

TEST(c_bubble_sort, rectangular_assemblyfied_large)
{
    std::vector<int32_t> array = generateRandomArray(LARGE_SIZE);
    ASSERT_FALSE(std::is_sorted(array.begin(), array.end()));

    // Act
    c_bubble_sort_rect_assemblified(array.data(), array.size());

    // Assert
    ASSERT_TRUE(std::is_sorted(array.begin(), array.end()));
}


TEST(c_bubble_sort, small_array_end)
{
    std::array<int32_t, 5> a = getUnsortedArray();
    ASSERT_FALSE(std::is_sorted(a.begin(), a.end()));

    // Act
    c_bubble_sort_end(a.data(), a.size());

    // Assert
    ASSERT_TRUE(std::is_sorted(a.begin(), a.end()));
}


TEST(c_bubble_sort, large_array_end)
{
    std::vector<int32_t> array = generateRandomArray(LARGE_SIZE);
    ASSERT_FALSE(std::is_sorted(array.begin(), array.end()));

    // Act
    c_bubble_sort_end(array.data(), array.size());

    // Assert
    ASSERT_TRUE(std::is_sorted(array.begin(), array.end()));
}


TEST(c_bubble_sort, small_array_swap)
{
    std::array<int32_t, 5> a = getUnsortedArray();
    ASSERT_FALSE(std::is_sorted(a.begin(), a.end()));

    // Act
    c_bubble_sort_swap(a.data(), a.size());

    // Assert
    ASSERT_TRUE(std::is_sorted(a.begin(), a.end()));
}


TEST(c_bubble_sort, large_array_swap)
{
    std::vector<int32_t> array = generateRandomArray(LARGE_SIZE);
    ASSERT_FALSE(std::is_sorted(array.begin(), array.end()));

    // Act
    c_bubble_sort_swap(array.data(), array.size());

    // Assert
    ASSERT_TRUE(std::is_sorted(array.begin(), array.end()));
}


TEST(c_bubble_sort, small_array_shaker)
{
    std::array<int32_t, 5> a = getUnsortedArray();
    ASSERT_FALSE(std::is_sorted(a.begin(), a.end()));

    // Act
    c_shaker_sort(a.data(), a.size());

    // Assert
    ASSERT_TRUE(std::is_sorted(a.begin(), a.end()));
}


TEST(c_bubble_sort, large_array_shaker)
{
    std::vector<int32_t> array = generateRandomArray(LARGE_SIZE);
    ASSERT_FALSE(std::is_sorted(array.begin(), array.end()));

    // Act
    c_shaker_sort(array.data(), array.size());

    // Assert
    ASSERT_TRUE(std::is_sorted(array.begin(), array.end()));
}
