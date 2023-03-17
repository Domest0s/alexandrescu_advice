#include <iostream>
#include <iomanip>
#include <vector>

#include "vt100.h"
#include "sorter.h"
#include "rnum_generator.hpp"


struct SortJobDescription
{
    typedef void (*Sorter)(int32_t* arr, size_t size);

    const char* name;
    Sorter sorter;
};

struct RunSequenceScore
{
    struct RunScore{
        size_t N;
        size_t timeNs;

        RunScore(size_t n, size_t t)
            : N(n)
            , timeNs(t)
        {}
    };

    RunSequenceScore(const char* name_in,
        const std::vector<RunScore>& runs_in = {})
        : name(name_in)
        , runs(runs_in)
    {}

    const char* name;
    std::vector<RunScore> runs;
};


int main(int /*argc*/, char* /*argv*/[])
{
    std::cout << "Let the show begin..\n";

    std::vector<SortJobDescription> sortSeries{
        {"quick_sort", alex_sort},
        {"Alex_sort", alex_sort}
    };

    constexpr size_t N_MAX = 100000;
    
    std::vector<RunSequenceScore> resutls;
    
    // create
    //for (const SortJobDescription& desc : sortSeries)
    //{
    //    resutls.push_back({ desc.name });
    //    //std::vector<RunSequenceScore::RunScore>& sequence = resutls.back().runs;
    //}

    for (const SortJobDescription& desc : sortSeries)
    {
        resutls.emplace_back(desc.name);
        RunSequenceScore& sequence = resutls.back();

        const SortJobDescription::Sorter theSort = desc.sorter;
        for (size_t n = 10; n <= N_MAX; n *= 10)
        {
            // Prepare
            std::vector<int32_t> arrayToSort = generateRandomArray(n);
            
            // Act
            // start measure
            theSort(arrayToSort.data(), arrayToSort.size());

            size_t timeNs = 100;
            // end measure

            sequence.runs.emplace_back(n, timeNs);
        }
    }


    // present the results

    for (const RunSequenceScore& sequence : resutls)
    {
        std::cout << std::setw(10) << sequence.name;

        for (const auto& run : sequence.runs)
        {
            std::cout << std::setw(10) << run.timeNs;
            std::cout << "(" << run.N << ")";
        }

        std::cout << "\n";
    }

    return 0;
}
