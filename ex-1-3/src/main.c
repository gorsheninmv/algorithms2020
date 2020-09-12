#include "edx-io.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

void insert_sort(int32_t in[], size_t len){
    if (len > 0){
        edx_print_i32(1);
    }

    for (int32_t i = 1; i < len; ++i){
        int32_t key = in[i];
        int32_t cur_idx = i - 1;

        for (; cur_idx >= 0 && key < in[cur_idx]; --cur_idx){
           in[cur_idx + 1] = in[cur_idx];
        }

        int32_t new_idx = cur_idx + 1;
        in[new_idx] = key;
        edx_print_char(' ');
        edx_print_i32(new_idx + 1);
   }
}

int main() {
    edx_open();
    size_t len = edx_next_i32();

    int32_t * data = calloc(len, sizeof(int32_t));

    if (data == NULL){
        return EXIT_FAILURE;
    }

    for (int32_t i = 0; i < len; ++i){
        data[i] = edx_next_i32();
    }

    insert_sort(data, len);
    edx_print_char('\n');

    for (int32_t i = 0; i < len; ++i){
        edx_print_i32(data[i]);
        edx_print_char(' ');
    }

    edx_print_char('\n');

    free(data);
    edx_close();
    return EXIT_SUCCESS;
}
