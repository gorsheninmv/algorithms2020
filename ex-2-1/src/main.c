#include "edx-io.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int32_t Type;

typedef struct {
    Type * dat;
    Type * buf;
    size_t len;
} arrays_t;

void log_merge(int32_t b_idx, size_t len, int32_t first_val, int32_t last_val){
    edx_print_i32(b_idx + 1);
    edx_print_char(' ');
    edx_print_i32(b_idx + len);
    edx_print_char(' ');
    edx_print_i32(first_val);
    edx_print_char(' ');
    edx_print_i32(last_val);
    edx_print_char('\n');
}

void log_array(Type dat[], size_t len){
    for(int32_t i = 0; i < len; ++i){
        edx_print_i32(dat[i]);
        edx_print_char(' ');
    }

    edx_print_char('\n');
}

void merge(Type in1[], size_t in1_len, Type in2[], size_t in2_len, Type out[]) {
    int32_t in1_idx = 0, in2_idx = in1_idx;

    while (in1_idx < in1_len && in2_idx < in2_len) {
        if (in1[in1_idx] < in2[in2_idx]) {
            out[in1_idx + in2_idx] = in1[in1_idx];
            ++in1_idx;
        }
        else {
            out[in1_idx + in2_idx] = in2[in2_idx];
            ++in2_idx;
        }
    }

    memcpy(&out[in1_idx + in2_idx], &in1[in1_idx], sizeof(Type) * (in1_len - in1_idx));
    memcpy(&out[in1_idx + in2_idx], &in2[in2_idx], sizeof(Type) * (in2_len - in2_idx));
}

/* 
   Инвариант: после завершения процедуры в to_sort->dat отсортированный массив.
*/
void merge_sort(arrays_t * to_sort, int32_t b_idx) {
    if (to_sort->len == 1) {
        return;
    }

    size_t wall = to_sort->len / 2;
    arrays_t left = {to_sort->dat, to_sort->buf, wall};
    arrays_t right = {to_sort->dat + wall, to_sort->buf + wall, to_sort->len - wall};
    merge_sort(&left, b_idx);
    merge_sort(&right, b_idx + wall);

    merge(left.dat, left.len, right.dat, right.len, left.buf);
    to_sort->dat = left.buf;
    to_sort->buf = left.dat;

    log_merge(b_idx, to_sort->len, to_sort->dat[0], to_sort->dat[to_sort->len - 1]);
}

int main() {
    edx_open();
    size_t sz = edx_next_i32();
    int32_t * dat = malloc(sizeof(int32_t) * sz * 2);

    for(int32_t i = 0; i < sz; ++i){
        dat[i] = edx_next_i32();
    }
    arrays_t arg = {dat, dat + sz, sz};

    merge_sort(&arg, 0);

    log_array(arg.dat, arg.len);

    free(dat);
    edx_close();
    return EXIT_SUCCESS;
}
