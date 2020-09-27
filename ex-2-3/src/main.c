#include "edx-io.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(int32_t * o1, int32_t * o2){
    size_t size = sizeof(int32_t);

    if (memcmp(o1, o2, size) == 0){
        return;
    }

    uint8_t * o1_ptr = (uint8_t *)o1;
    uint8_t * o2_ptr = (uint8_t *)o2;

    for (int32_t i = 0; i < size; ++i){
        o1_ptr[i] ^= o2_ptr[i];
        o2_ptr[i] ^= o1_ptr[i];
        o1_ptr[i] ^= o2_ptr[i];
    }
}

int main() {
    edx_open();

    size_t sz = edx_next_i32();
    int32_t * dat = malloc(sizeof(int32_t) * sz);

    for (int32_t i = 0; i < sz; ++i){
        dat[i] = i + 1;
    }

    for (int32_t i = 2; i < sz; ++i){
        swap(&dat[i/2], &dat[i]);
    }

    for (int32_t i = 0; i < sz; ++i){
        edx_print_i32(dat[i]);
        edx_print_char(' ');
    }

    free(dat);
    edx_close();
    return EXIT_SUCCESS;
}
