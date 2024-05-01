#include <array>
#include <algorithm>
#include <cstring>

#include <gtest/gtest.h>

#include "asm_sort/quick_sort.h"
#include "rnum_generator/generator.h"


#define asm_quick_sort asm_quick_sort_ludvig


TEST(asm_quick_sort, zero_elements)
{
  std::array<int32_t, 0> a;

  asm_quick_sort(a.data(), a.size());
  // It should not crash or anything
}

TEST(asm_quick_sort, one_element)
{
  std::array<int32_t, 1> a = {1};

  asm_quick_sort(a.data(), a.size());

  ASSERT_EQ(a[0], 1);
}


TEST(asm_quick_sort, two_element_equal)
{
  std::array<int32_t, 2> a = {1, 1};

  asm_quick_sort(a.data(), a.size());

  ASSERT_EQ(a[1], 1);
  ASSERT_EQ(a[0], 1);
}

TEST(asm_quick_sort, two_element_sorted)
{
  std::array<int32_t, 2> a = {1, 2};

  asm_quick_sort(a.data(), a.size());

  ASSERT_EQ(a[0], 1);
  ASSERT_EQ(a[1], 2);
}

TEST(asm_quick_sort, two_element_unsorted)
{
  std::array<int32_t, 2> a = {2, 1};

  asm_quick_sort(a.data(), a.size());

  ASSERT_EQ(a[0], 1);
  ASSERT_EQ(a[1], 2);
}


TEST(asm_quick_sort, three_element_unsorted)
{
  std::array<int32_t, 3> a = {2, -1, 1};

  asm_quick_sort(a.data(), a.size());

  ASSERT_EQ(a[0], -1);
  ASSERT_EQ(a[1], 1);
  ASSERT_EQ(a[2], 2);
}


// check that assembly implementation of quicksort is indeed sorting the array
TEST(asm_quick_sort, small_array)
{
  std::array<int32_t, 5> a = getUnsortedArray();
  ASSERT_FALSE(std::is_sorted(a.begin(), a.end()));

  // Act
  asm_quick_sort(a.data(), a.size());

  // Assert
  const std::array<int32_t, 5> g = getSortedArray();
  // Compare the sorted array to the golden one
  ASSERT_TRUE(std::equal(a.begin(), a.end(), g.begin()));

  ASSERT_TRUE(std::is_sorted(a.begin(), a.end()));
}


TEST(asm_quick_sort, large_array)
{
    std::vector<int32_t> array = generateRandomArray(LARGE_SIZE);
    ASSERT_FALSE(std::is_sorted(array.begin(), array.end()));

    // Act
    asm_quick_sort(array.data(), array.size());

    // Assert
    ASSERT_TRUE(std::is_sorted(array.begin(), array.end()));
}


TEST(asm_quick_sort, arrays_equal)
{
    std::vector<int32_t> array1 = generateRandomArray(LARGE_SIZE);
    std::vector<int32_t> array2 = generateRandomArray(LARGE_SIZE);

    ASSERT_TRUE(std::equal(array1.begin(), array1.end(), array2.begin()));
}
