#include "edx-io.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    size_t id;
    double value;
} citizen_t;

int32_t citizen_comparer(citizen_t o1, citizen_t o2){
    if (o1.value < o2.value)
        return -1;
    else if (o1.value > o2.value)
        return 1;
    else return 0;
}

#define TYPE citizen_t

void insert_sort(TYPE in[], size_t len, int32_t (*comparer)(TYPE, TYPE)){
    for (int32_t i = 1; i < len; ++i){
        TYPE key = in[i];
        int32_t cur_idx = i - 1;

        for (; cur_idx >= 0 && comparer(key, in[cur_idx]) < 0; --cur_idx){
           in[cur_idx + 1] = in[cur_idx];
        }

        int32_t new_idx = cur_idx + 1;
        in[new_idx] = key;
   }
}

int main() {
    edx_open();
    size_t len = edx_next_i32();

    citizen_t * data = calloc(len, sizeof(citizen_t));

    if (data == NULL){
        return EXIT_FAILURE;
    }

    for (int32_t i = 0; i < len; ++i){
        data[i].id = i + 1;
        data[i].value = edx_next_double();
    }

    insert_sort(data, len, citizen_comparer);

    edx_print_ui64(data[0].id);
    edx_print_char(' ');
    edx_print_ui64(data[len/2].id);
    edx_print_char(' ');
    edx_println_ui64(data[len-1].id);
    edx_print_char('\n');

    free(data);
    edx_close();
    return EXIT_SUCCESS;
}
