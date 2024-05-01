#include "c_sort/quick_sort.h"

#include <algorithm>
#include <vector>


static void swap(int32_t* a, int32_t* b) {
    int32_t t = *a;
    *a = *b;
    *b = t;
}

/**
 *  @desc partition part of an array [low, high].
 *  @return pivot position. Lefters are lower than righters.
 */
static size_t partition(int32_t* arr, size_t low, size_t high)
{
    // pick pivot
    const int32_t pivot = arr[high];

    // from the low up
    size_t i = low;
    for (size_t j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }

    swap(&arr[i], &arr[high]);
    return (i);
}


void quick_sort_body(int32_t* arr, size_t low, size_t high)
{
    if (low < high) {
        const size_t partion_pos = partition(arr, low, high);
        if (partion_pos >= 1) {
            quick_sort_body(arr, low, partion_pos - 1);
        }
        quick_sort_body(arr, partion_pos + 1, high);
    }
}


// Function to implement Quick Sort
void c_quick_sort(int32_t* arr, size_t size)
{
    quick_sort_body(arr, 0, size - 1);
}



int32_t* partition_assemblified(int32_t* low_mark, int32_t* high_mark)
{
    // pick pivot
    const int32_t pivot = *high_mark;

    // from the low up
    int32_t* it = low_mark;
    int32_t* jt = low_mark;

    loop:
    {
        if (*jt < pivot) {
            swap(it, jt);
            it++;
        }

        jt++;
        if (jt < high_mark)
        {
            goto loop;
        }
    }

    swap(it, high_mark);

    return it;
}

void quick_sort_body_assemblified(int32_t* low, int32_t* high)
{
    if (low > high) {
        return;
    }
    
    int32_t* pivot_pos = partition_assemblified(low, high);

    quick_sort_body_assemblified(pivot_pos + 1, high);
    if (pivot_pos > low)
    {
        quick_sort_body_assemblified(low, pivot_pos - 1);
    }
}


void c_quick_sort_assemblified(int32_t* arr, size_t size)
{
    quick_sort_body_assemblified(arr, &arr[size - 1]);
}



// Standard library implementation
// (which may be not quick sort as the name suggests)
void native_qsort(int32_t* array, size_t size)
{
    std::qsort(array, size, sizeof(int32_t), [](const void* x, const void* y)
        {
            const int32_t arg1 = *static_cast<const int32_t*>(x);
            const int32_t arg2 = *static_cast<const int32_t*>(y);
            return arg2 - arg1;
        });
}
