#include "edx-io.h"
#include <inttypes.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void swap(int32_t *arg1, int32_t *arg2){
    if (*arg1 == *arg2)
        return;

    *arg1 = *arg1 ^ *arg2;
    *arg2 = *arg1 ^ *arg2;
    *arg1 = *arg1 ^ *arg2;
}

void quick_sort(int32_t * first, int32_t * last, int32_t step){

    if (first >= last){
        return;    
    }

    size_t items_cnt = (last - first + 1) / step;
    if ((last - first + 1) % step > 0){
        ++items_cnt;
    }
    size_t mid = items_cnt / 2;
    int32_t * pivot_ptr = first + (mid - 1) * step;

    int32_t pivot = *pivot_ptr;
    int32_t * l_ptr = first;
    int32_t * r_ptr = last;

    do {
        while (*l_ptr < pivot)
            l_ptr += step;
        while (*r_ptr > pivot)
            r_ptr -= step;

        if (l_ptr <= r_ptr){
            swap(l_ptr, r_ptr);
            l_ptr += step;
            r_ptr -= step;
        }
    } while (l_ptr <= r_ptr);

    quick_sort(first, r_ptr, step);
    quick_sort(l_ptr, last, step);
}

int main() {
  edx_open();

  size_t sz = edx_next_i32();
  size_t step = edx_next_i32();

  int32_t * dat = malloc(sizeof(int32_t) * sz);

  for (int32_t i = 0; i < sz; ++i) {
      dat[i] = edx_next_i32();
  }

  for (int32_t i = 0; i < step; ++i) {
    int32_t * first = dat + i;
    int32_t * last = first + ((sz - i) / step - 1) * step;

    if ((sz - i) % step > 0)
        last += step;

    quick_sort(first, last, step);
  }

  bool ok = true;

  for (int32_t i = 1; i < sz; ++i){
        if (dat[i - 1] > dat[i]){
            ok = false;
            break;
        }
  }

  if (ok){
      edx_print("YES");
  }
  else{
      edx_print("NO");
  }

  free(dat);
  edx_close();
  return EXIT_SUCCESS;
}
