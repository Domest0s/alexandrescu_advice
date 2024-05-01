#include <array>
#include <algorithm>
#include <cstring>

#include <gtest/gtest.h>

#include "asm_sort/bubble_sort.h"
#include "rnum_generator/generator.h"

// check that assembly implementation of bubble sort is indeed sorting an array
TEST(asm_bubble_sort, asm_small_array_classic)
{
  std::array<int32_t, 5> a = getUnsortedArray();
  ASSERT_FALSE(std::is_sorted(a.begin(), a.end()));

  // Act
  asm_bubble_sort(a.data(), a.size());

  // Assert
  std::array<int32_t, 5> g = getSortedArray();
  // Compare the sorted array to the golden one
  ASSERT_TRUE(std::equal(a.begin(), a.end(), g.begin()));

  ASSERT_TRUE(std::is_sorted(a.begin(), a.end()));
}

TEST(asm_bubble_sort, asm_large_array_classic)
{
  std::vector<int32_t> array = generateRandomArray(LARGE_SIZE);
  ASSERT_FALSE(std::is_sorted(array.begin(), array.end()));

  // Act
  asm_bubble_sort(array.data(), array.size());

  // Assert
  ASSERT_TRUE(std::is_sorted(array.begin(), array.end()));
}

#ifdef WIN32

TEST(asm_bubble_sort, classic_ivan_small)
{
    std::array<int32_t, 5> arr = getUnsortedArray();
    ASSERT_FALSE(std::is_sorted(arr.begin(), arr.end()));

    // Act
    asm_bubble_sort_by_ivan(arr.data(), arr.size());

    // Assert
    std::array<int32_t, 5> g = getSortedArray();
    ASSERT_TRUE(std::is_sorted(arr.begin(), arr.end()));
}

TEST(asm_bubble_sort, classic_ivan_large)
{
    std::vector<int32_t> arr = generateRandomArray(LARGE_SIZE);
    ASSERT_FALSE(std::is_sorted(arr.begin(), arr.end()));

    // Act
    asm_bubble_sort_by_ivan(arr.data(), arr.size());

    // Assert
    ASSERT_TRUE(std::is_sorted(arr.begin(), arr.end()));
}

#endif // WIN32

TEST(asm_bubble_sort, asm_small_array_end)
{
  std::array<int32_t, 5> a = getUnsortedArray();
  ASSERT_FALSE(std::is_sorted(a.begin(), a.end()));

  // Act
  asm_bubble_sort_end(a.data(), a.size());

  // Assert
  std::array<int32_t, 5> g = getSortedArray();
  // Compare the sorted array to the golden one
  ASSERT_TRUE(std::equal(a.begin(), a.end(), g.begin()));

  ASSERT_TRUE(std::is_sorted(a.begin(), a.end()));
}

TEST(asm_bubble_sort, asm_large_array_end)
{
  std::vector<int32_t> array = generateRandomArray(LARGE_SIZE);
  ASSERT_FALSE(std::is_sorted(array.begin(), array.end()));

  // Act
  asm_bubble_sort_end(array.data(), array.size());

  // Assert
  ASSERT_TRUE(std::is_sorted(array.begin(), array.end()));
}


TEST(asm_bubble_sort, asm_small_array_swap)
{
  std::array<int32_t, 5> a = getUnsortedArray();
  ASSERT_FALSE(std::is_sorted(a.begin(), a.end()));

  // Act
  asm_bubble_sort_swap(a.data(), a.size());

  // Assert
  std::array<int32_t, 5> g = getSortedArray();
  // Compare the sorted array to the golden one
  ASSERT_TRUE(std::equal(a.begin(), a.end(), g.begin()));

  ASSERT_TRUE(std::is_sorted(a.begin(), a.end()));
}

TEST(asm_bubble_sort, asm_large_array_swap)
{
  std::vector<int32_t> array = generateRandomArray(LARGE_SIZE);
  ASSERT_FALSE(std::is_sorted(array.begin(), array.end()));

  // Act
  asm_bubble_sort_swap(array.data(), array.size());

  // Assert
  ASSERT_TRUE(std::is_sorted(array.begin(), array.end()));
}
