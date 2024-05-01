#pragma once

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void asm_quick_sort_ludvig(int32_t* array, size_t size);
void asm_quick_sort_alex(int32_t* array, size_t size);

#ifdef __cplusplus
}
#endif
