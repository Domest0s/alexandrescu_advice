#pragma once

#include <cstdint>
#include <cstddef>
#include <vector>
#include <array>

std::array<int32_t, 5> getUnsortedArray();
std::array<int32_t, 5> getSortedArray();


constexpr size_t LARGE_SIZE = 10000;

std::vector<int32_t> generateRandomArray(size_t N_CEILING);
