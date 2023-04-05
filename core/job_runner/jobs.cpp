#include "jobs.hpp"

#include <cassert>
#include <cstring>

#include <iostream>
#include <iomanip>


SpeedTable::SpeedTable(const std::vector<const char*>& names,
    const std::vector<size_t>& n_runs)
    : m_row_names(names)
    , m_column_n_runs(n_runs)
    , m_results(names.size()* n_runs.size(), 0)
{}


void SpeedTable::draw() const
{
    const size_t max_name_len = strlen(*std::max_element(m_row_names.begin(), m_row_names.end(),
        [](const char* a, const char* b) {
            return strlen(b) > strlen(a);
        }));

    // draw top row with Ns
    std::cout << std::setw(max_name_len) << " ";
    for (const uint64_t& n : m_column_n_runs)
    {
        std::cout << std::setw(10) << n;
    }
    std::cout << "\n";

    // draw algo measurements
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


void SpeedTable::set(const char* name, size_t n_run, size_t time)
{
    this->get(name, n_run) = time;
}


const uint64_t& SpeedTable::get(const char* name, size_t n_run) const
{
    return const_cast<SpeedTable*>(this)->get(name, n_run);
}

uint64_t& SpeedTable::get(const char* name, size_t n_run)
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
