#pragma once

#include <cassert>
#include <cstdint>
#include <cstring>


#include <iostream>
#include <iomanip>
#include <vector>

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
        const std::vector<size_t>& n_runs);

    void draw() const;

    void set(const char* name, size_t n_run, size_t time);
    const uint64_t& get(const char* name, size_t n_run) const;
    uint64_t& get(const char* name, size_t n_run);

private:
    std::vector<const char*> m_row_names;
    std::vector<size_t> m_column_n_runs;
    std::vector<size_t> m_results;
};

