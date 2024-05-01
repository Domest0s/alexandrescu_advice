#pragma once

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void c_bubble_sort(int32_t* array, size_t size);
void c_bubble_sort_rect_assemblified(int32_t* array, size_t size);
void c_bubble_sort_end(int32_t* array, size_t size);
void c_bubble_sort_swap(int32_t* array, size_t size);

void c_shaker_sort(int32_t* array, size_t size);

#ifdef __cplusplus
}
#endif
