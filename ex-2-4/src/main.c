#include "edx-io.h"
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(int32_t *arg1, int32_t *arg2) {
    if (*arg1 == *arg2)
        return;

    *arg1 = *arg1 ^ *arg2;
    *arg2 = *arg1 ^ *arg2;
    *arg1 = *arg1 ^ *arg2;
}

void quick_sort_to_find_interval(int32_t * first, int32_t * last, int32_t * k1, int32_t * k2) {

    if (first > last){
        return;    
    }

    int32_t pivot = first[(last - first) / 2];
    int32_t * l_ptr = first;
    int32_t * r_ptr = last;

    do {
        while (*l_ptr < pivot)
            ++l_ptr;
        while (*r_ptr > pivot)
            --r_ptr;

        if (l_ptr <= r_ptr){
            swap(l_ptr, r_ptr);
            ++l_ptr;
            --r_ptr;
        }
    } while (l_ptr <= r_ptr);

    if (k1 <= r_ptr)
        quick_sort_to_find_interval(first, r_ptr, k1, k2);
    if (k2 >= l_ptr)
        quick_sort_to_find_interval(l_ptr, last, k1, k2);
}

int main() {
  edx_open();

  size_t sz = edx_next_i32();
  size_t k1 = edx_next_i32() - 1;
  size_t k2 = edx_next_i32() - 1;
  int32_t A = edx_next_i32();
  int32_t B = edx_next_i32();
  int32_t C = edx_next_i32();
  int32_t a0 = edx_next_i32();
  int32_t a1 = edx_next_i32();

  int32_t *dat = malloc(sizeof(int32_t) * sz);
  dat[0] = a0;
  dat[1] = a1;

  for (int32_t i = 2; i < sz; ++i) {
    dat[i] = A * dat[i - 2] + B * dat[i - 1] + C;
  }

  quick_sort_to_find_interval(dat, dat + sz - 1, dat + k1, dat + k2);

  for (int32_t i = k1; i <= k2; ++i) {
    edx_print_i32(dat[i]);
    edx_print_char(' ');
  }

  free(dat);
  edx_close();
  return EXIT_SUCCESS;
}
