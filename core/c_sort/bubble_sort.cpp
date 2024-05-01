#include "c_sort/bubble_sort.h"

/**
 * Classic bubble sort https://en.wikipedia.org/wiki/Bubble_sort
 *  while (unsorted) {
        loop (n = 0 .. N-1) {
            if (arr[n] > arr[n+1]) { swap(arr[n], arr[n+1]); }
        }
    }
 */
void c_bubble_sort(int32_t* array, size_t size)
{
    bool sorted;
    do {
        sorted = true;
        for (size_t i = 1; i < size; i++) {
            if (array[i - 1] > array[i]) {
                int32_t x = array[i];
                array[i] = array[i - 1];
                array[i - 1] = x;

                sorted = false;
            }
        }
    } while (!sorted);
}


/**
 * @desk bubble sort implemented in C without for/while loops.
    I wariable supposed needs allocation on stack, declare it
    at the beginning of function.
 */
void c_bubble_sort_rect_assemblified(int32_t* arr, size_t size)
{
    if (size == 0)
    {
        return;
    }

    const int32_t* tail = arr + size - 1;

    big_loop:
        bool sorted = true;
        
        int32_t* curr = arr;
        inner_loop:
            
            if (*curr > curr[1])
            {
                int32_t x = curr[1];
                curr[1] = *curr;
                *curr = x;

                sorted = false;
            }

            curr++;
            if (curr < tail)
            {
                goto inner_loop;
            }

        if (!sorted)
        {
            goto big_loop;
        }
}


/**
 *  1st optimisation : https://en.wikipedia.org/wiki/Bubble_sort#Optimizing_bubble_sort
 *  We know that each loop iteration promotes the max value element to the top
 *  of the array. Decrement(--) tail to exclude current highest element from
 *  participation in the next iteration of the loop.
 */
void c_bubble_sort_end(int32_t* arr, size_t size)
{
    bool sorted;
    size_t end = size;
    do {
        sorted = true;
        for (size_t i = 1; i < end; i++) {
            if (arr[i - 1] > arr[i]) {
                int32_t x = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1] = x;

                sorted = false;
            }
        }
        end--;
    } while (!sorted);
}


/**
 * 2nd optimisation : https://en.wikipedia.org/wiki/Bubble_sort#Optimizing_bubble_sort
 * Everythin higher than the last swap is sorted. Skip sorting everything above the last swap pos.
*/ 
void c_bubble_sort_swap(int32_t* array, size_t size)
{
    size_t end = size;
    do {
        size_t lastSwap = 0;
        for (size_t i = 1; i < end; i++) {
            if (array[i - 1] > array[i]) {
                int32_t x = array[i];
                array[i] = array[i - 1];
                array[i - 1] = x;

                lastSwap = i;
            }
        }
        end = lastSwap;
    } while (end > 1);
}


// Cocktail shaker sort
// https://en.wikipedia.org/wiki/Cocktail_shaker_sort
void c_shaker_sort(int32_t* array, size_t size)
{
    size_t begin = 0;
    size_t end = size;
    bool sorted;
    do {
        sorted = true;
        for (int i = 1; i < end; i++) {
            if (array[i - 1] > array[i]) {
                int x = array[i];
                array[i] = array[i - 1];
                array[i - 1] = x;
                sorted = false;
            }
        }

        if (sorted) {
            break;
        }

        end--;
        for (int i = end - 1; i > begin; i--) {
            if (array[i] > array[i + 1]) {
                int x = array[i + 1];
                array[i + 1] = array[i];
                array[i] = x;
                sorted = false;
            }
        }
        begin++;
    } while (!sorted);
}
