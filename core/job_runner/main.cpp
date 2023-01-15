#include <iostream>
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

int main(int argc, char* argv[])
{
    std::vector<SortJobDescription> sortSeries{
        {"quick_sort", alex_sort},
        {"Alex_sort", alex_sort}
    };




    return 0;
}