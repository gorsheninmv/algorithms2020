#include "edx-io.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    size_t idx;
    int32_t value;
} item_t;

int32_t item_comparer(item_t o1, item_t o2){
    if (o1.value < o2.value)
        return -1;
    else if (o1.value > o2.value)
        return 1;
    else return 0;
}

#define TYPE item_t

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

void swap(TYPE * o1, TYPE * o2){
    size_t size = sizeof(TYPE);

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

void write_info(int32_t first, int32_t second){
    static char buff[255];
    sprintf(buff, "Swap elements at indices %d and %d.", first + 1, second + 1);
    edx_println(buff);
}

int main() {
    edx_open();
    size_t len = edx_next_i32();

    item_t * data = calloc(len * 2, sizeof(item_t));
    item_t * origs = data;
    item_t * sorted = origs + len;

    if (data == NULL) {
      return EXIT_FAILURE;
    }

    for (int32_t i = 0; i < len; ++i){
      origs[i].idx = i;
      origs[i].value = edx_next_i32();
    }

    memcpy(sorted, origs, len * sizeof(item_t));
    insert_sort(sorted, len, item_comparer);

    for (int32_t i = 0; i < len; ++i){
        int32_t orig_idx = sorted[i].idx;

        while (orig_idx < i){
            orig_idx = sorted[orig_idx].idx;
        }

        /* На самом деле эта ветвь основная, а while второстепенная.
           Код написан таким образом, чтобы выглядел чище.
           Для разбора алгоритма рекомендуется поменять их местами и добавить
           write_info() после цикла while.
        */
        if (i < orig_idx){
            write_info(i, orig_idx);
        }
    }

    edx_println("No more swaps needed.");

    free(data);
    edx_close();
    return EXIT_SUCCESS;
}
