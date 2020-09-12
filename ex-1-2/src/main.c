#include "edx-io.h"
#include <stdint.h>

int main() {
    edx_open();
    int64_t a = edx_next_i64();
    int64_t b = edx_next_i64();
    int64_t result = a + b * b;
    edx_print_i64(result);
    edx_close();
}
