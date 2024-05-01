#pragma once

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void c_quick_sort(int32_t* array, size_t size);
void c_quick_sort_assemblified(int32_t* array, size_t size);
void native_qsort(int32_t* array, size_t size);

#ifdef __cplusplus
}
#endif
