#include "c_sort/insertion_sort.h"

// Original Insertion sort algorithm
// https://en.wikipedia.org/wiki/Insertion_sort#Algorithm
void c_insertion_sort1(int32_t* array, size_t size)
{
    if (size <= 1) {
        return;
    }

    for (size_t i = 1; i < size; i++) {
        size_t j = i;
        while (j > 0 && array[j - 1] > array[j]) {
            int32_t t = array[j - 1];
            array[j - 1] = array[j];
            array[j] = t;
            j--;
        }
    }
}


// Insertion sort algorithm with expanded swap
// The new inner loop shifts elements to the right
// to clear a spot for curr = array[i]
void c_insertion_sort2(int32_t* array, size_t size)
{
    if (size <= 1) {
        return;
    }

    for (size_t i = 1; i < size; i++) {
        int32_t curr = array[i];
        size_t j = i;
        while (j > 0 && array[j - 1] > curr) {
            array[j] = array[j - 1];
            j--;
        }
        array[j] = curr;
    }
}
