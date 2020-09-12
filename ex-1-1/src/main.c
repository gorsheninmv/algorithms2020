#include "edx-io.h"
#include <stdint.h>

int main() {
    edx_open();
    int32_t a = edx_next_i32();
    int32_t b = edx_next_i32();
    int32_t result = a + b;
    edx_print_i32(result);
    edx_close();
}
