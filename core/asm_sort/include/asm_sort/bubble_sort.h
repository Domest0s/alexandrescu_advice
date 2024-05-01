#pragma once

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void asm_bubble_sort(int32_t* array, size_t size);
#if WIN32
void asm_bubble_sort_by_ivan(int32_t* array, size_t size);
#endif
void asm_bubble_sort_end(int32_t* array, size_t size);
void asm_bubble_sort_swap(int32_t* array, size_t size);


#ifdef __cplusplus
}
#endif
