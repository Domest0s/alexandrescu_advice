#include <cassert>
#include <cstdint>

#include <algorithm>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <ranges>
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


class SpeedTable
{
public:
    SpeedTable(const std::vector<const char*>& names,
        const std::vector<size_t>& n_runs)
        : m_row_names(names)
        , m_column_n_runs(n_runs)
        , m_results(names.size() * n_runs.size(), 0)
    {}

    void draw() const
    {
        const size_t max_name_len = strlen(*std::max_element(m_row_names.begin(), m_row_names.end(),
            [](const char* a, const char* b) {
                return strlen(b) > strlen(a);
            }));

        for (const char* name : m_row_names)
        {
            std::cout << std::setw(max_name_len) << name;

            for (const uint64_t& n : m_column_n_runs)
            {
                std::cout << std::setw(10) << get(name, n);
            }

            std::cout << "\n";
        }
    }

    void set(const char* name, size_t n_run, size_t time)
    {
        this->get(name, n_run) = time;
    }

    const uint64_t& get(const char* name, size_t n_run) const
    {
        return const_cast<SpeedTable*>(this)->get(name, n_run);
    }

    uint64_t& get(const char* name, size_t n_run)
    {
        // find vertical position in the table
        auto it_name = std::find(m_row_names.begin(), m_row_names.end(), name);
        assert(it_name != m_row_names.end());
        const size_t name_pos = it_name - m_row_names.begin();

        // find horizontal position in the table
        auto it_N = std::find(m_column_n_runs.begin(), m_column_n_runs.end(), n_run);
        assert(it_N != m_column_n_runs.end());
        const size_t n_pos = it_N - m_column_n_runs.begin();

        const size_t index = n_pos + m_column_n_runs.size() * name_pos;
        return m_results[index];
    }

private:
    std::vector<const char*> m_row_names;
    std::vector<size_t> m_column_n_runs;
    std::vector<size_t> m_results;
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
    