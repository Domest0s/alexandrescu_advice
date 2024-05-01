#include "c_sort/selection_sort.h"

// Selection sort
// https://en.wikipedia.org/wiki/Selection_sort
void c_selection_sort(int32_t* array, size_t size)
{
    for (size_t i = 0; i < size; i++) {
        size_t index = i;
        int32_t min = array[index];
        for (size_t j = i + 1; j < size; j++) {
            if (array[j] < min) {
                index = j;
                min = array[j];
            }
        }
        if (index != i) {
            array[index] = array[i];
            array[i] = min;
        }
    }
}


// Like Selection sort which finds both min and max
// elements at each scan
// https://en.wikipedia.org/wiki/Selection_sort#Variants
void c_cocktail_sort(int32_t* array, size_t size)
{
    size_t end = size - 1;
    for (size_t i = 0; i < end; i++, end--) {
        size_t minIndex = i;
        int32_t min = array[minIndex];
        size_t maxIndex = end;
        int32_t max = array[maxIndex];
        if (min > max) {
            array[minIndex] = max;
            max = min;
            array[maxIndex] = min;
            min = array[minIndex];
        }
        for (size_t j = i + 1; j < end; j++) {
            const int32_t elem = array[j];
            if (elem < min) {
                minIndex = j;
                min = array[j];
            } else if (elem > max) {
                maxIndex = j;
                max = array[j];
            }
        }

        if (minIndex != i) {
            array[minIndex] = array[i];
            array[i] = min;
        }
        if (maxIndex != end) {
            array[maxIndex] = array[end];
            array[end] = max;
        }
    }
}
