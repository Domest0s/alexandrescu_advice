#include "rnum_generator/generator.h"

#include <cstdlib>
#include <vector>
#include <map>
#include <mutex>


std::array<int32_t, 5> getUnsortedArray() {
    return { 5, 1, 4, 2, 3 };
}

std::array<int32_t, 5> getSortedArray() {
    return { 1, 2, 3, 4, 5 };
}


std::vector<int32_t> generateRandomArray(size_t N_CEILING)
{
    static std::map<size_t, std::vector<int32_t>> arrays;
    static std::mutex map_mutex;

    // Guard access to the map from multiple threads
    std::lock_guard<std::mutex> guard(map_mutex);

    if (arrays.find(N_CEILING) == arrays.end())
    {
        std::vector<int32_t> array(N_CEILING, 0);
        //array.reserve(N);

        srand(0);
        for (size_t i = 0; i < N_CEILING; i++) {
            array[i] = rand();
        }

        arrays.insert({ N_CEILING, array });
    }

    return arrays.at(N_CEILING);    // return a copy (!) of array
}
