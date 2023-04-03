
#include <algorithm>
#include <chrono>
#include <ranges>
#include <vector>

#include "vt100.h"
#include "sorter.h"
#include "rnum_generator.hpp"

#include "jobs.hpp"



int main(int /*argc*/, char* /*argv*/[])
{
    std::vector<SortJobDescription> sortSeries{
        {"quick_sort", alex_sort},
        {"Alex_sort", alex_sort}
    };

    constexpr size_t N_MAX = 100000;
    constexpr size_t N_MIN = 100;

    // agregate names of the algorithms
    std::vector<const char*> algo_names;
    for (const SortJobDescription& desc : sortSeries)
    {
        algo_names.push_back(desc.name);
    }

    // generate the Ns
    std::vector<size_t> algo_Ns;
    for (uint64_t n = N_MIN; n <= N_MAX; n *= 10)
    {
        algo_Ns.push_back(n);
    }

    if (algo_Ns.back() != N_MAX)
    {
        algo_Ns.push_back(N_MAX);
    }

    SpeedTable table(algo_names, algo_Ns);

    // run alorithms
    for (const SortJobDescription& desc : sortSeries)
    {
        const SortJobDescription::Sorter theSort = desc.sorter;
        for (uint64_t n = N_MIN; n <= N_MAX; n *= 10)
        {
            // Prepare
            std::vector<int32_t> arrayToSort = generateRandomArray(n);

            // Act
            // start measure

            // returns elapsed time in nanoseconds
            using namespace std::chrono;
            uint64_t start = duration_cast<nanoseconds>
                (steady_clock::now().time_since_epoch()).count();

            theSort(arrayToSort.data(), arrayToSort.size());

            uint64_t end = duration_cast<nanoseconds>
                (steady_clock::now().time_since_epoch()).count();

            uint64_t timeNs = end - start;

            // record the results
            table.set(desc.name, n, timeNs);
        }
    }

    // present the results
    table.draw();

    return 0;
}


    // run something
