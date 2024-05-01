#pragma once

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

    void c_selection_sort(int32_t* array, size_t size);
    void c_cocktail_sort(int32_t* array, size_t size);

#ifdef __cplusplus
}
#endif
