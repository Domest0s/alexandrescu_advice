#include <cstring>
#include <algorithm>
#include <array>

#include <gtest/gtest.h>

#include "rnum_generator/generator.h"
#include "c_sort/selection_sort.h"


TEST(selection_sort, small_array_selection)
{
    std::array<int32_t, 5> a = getUnsortedArray();
    ASSERT_FALSE(std::is_sorted(a.begin(), a.end()));

    // Act
    c_selection_sort(a.data(), a.size());

    // Assert
    ASSERT_TRUE(std::is_sorted(a.begin(), a.end()));
}

TEST(selection_sort, large_array_selection)
{
    std::vector<int32_t> array = generateRandomArray(LARGE_SIZE);
    ASSERT_FALSE(std::is_sorted(array.begin(), array.end()));

    // Act
    c_selection_sort(array.data(), array.size());

    // Assert
    ASSERT_TRUE(std::is_sorted(array.begin(), array.end()));
}


TEST(selection_sort, small_array_cocktail)
{
    std::array<int32_t, 5> a = getUnsortedArray();
    ASSERT_FALSE(std::is_sorted(a.begin(), a.end()));

    // Act
    c_cocktail_sort(a.data(), a.size());

    // Assert
    ASSERT_TRUE(std::is_sorted(a.begin(), a.end()));
}

TEST(selection_sort, large_array_cocktail)
{
    std::vector<int32_t> array = generateRandomArray(LARGE_SIZE);
    ASSERT_FALSE(std::is_sorted(array.begin(), array.end()));

    // Act
    c_cocktail_sort(array.data(), array.size());

    // Assert
    ASSERT_TRUE(std::is_sorted(array.begin(), array.end()));
}
