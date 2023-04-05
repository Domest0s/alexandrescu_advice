#include <chrono>
#include <vector>

#include "vt100.h"
#include "sorter.h"
#include "rnum_generator.hpp"

#include "jobs.hpp"

std::vector<std::uint64_t> generate_n_list(std::uint64_t n_min, std::uint64_t n_max)
{
    std::vector<size_t> algo_Ns;
    for (uint64_t n = n_min; n <= n_max; n *= 10)
    {
        algo_Ns.push_back(n);
    }

    if (algo_Ns.back() != n_max)
    {
        algo_Ns.push_back(n_max);
    }
    return algo_Ns;
}

/**
 * @desc runs the functor and retuns elapsed time in misroseconds [us]
 */
template<typename TUnit = std::chrono::microseconds, typename F>
uint64_t measure(F functor)
{
    using namespace std::chrono;
    uint64_t start = duration_cast<TUnit>
        (steady_clock::now().time_since_epoch()).count();

    functor();

    uint64_t end = duration_cast<TUnit>
        (steady_clock::now().time_since_epoch()).count();

    return end - start;
}

int main(int /*argc*/, char* /*argv*/[])
{
    std::vector<SortJobDescription> sortSeries{
        {"quick_sort", alex_sort},
        {"Alex_sort", alex_sort}
    };

    constexpr size_t N_MIN = 100;
    constexpr size_t N_MAX = 1000000;

    // agregate names of the algorithms in a vector
    std::vector<const char*> algo_names;
    for (const SortJobDescription& desc : sortSeries)
    {
        algo_names.push_back(desc.name);
    }

    // generate the Ns. This will aslo match the top row of the table
    const std::vector<size_t> algo_Ns = generate_n_list(N_MIN, N_MAX);

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
            auto job = [&theSort, &arrayToSort]() {
                theSort(arrayToSort.data(), arrayToSort.size());
            };
            uint64_t elapsed = measure<std::chrono::microseconds>(job);

            table.set(desc.name, n, elapsed);
        }
    }

    // present the results
    table.draw();

    return 0;
}
