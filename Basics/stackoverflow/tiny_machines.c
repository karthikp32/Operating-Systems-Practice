#include <float.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

// Calculate the difference between two memory addresses in bytes
size_t get_address_diff_bytes(uintptr_t a1, uintptr_t a2) {
    // Return absolute difference between addresses in bytes
    return (a1 > a2) ? (a1 - a2) : (a2 - a1);
}

void build_tiny_machine(long double size, int fx_call, uintptr_t prev_stack_frame_addr, int total_bytes_in_stack) {
    uintptr_t current_stack_frame_addr = (uintptr_t) &total_bytes_in_stack;
    printf("current_stack_frame_addr: %ld\n",current_stack_frame_addr);
    fx_call++;
    if (prev_stack_frame_addr != (uintptr_t)NULL) {
        size_t size_of_last_stack_frame = get_address_diff_bytes(prev_stack_frame_addr, current_stack_frame_addr);
        total_bytes_in_stack += size_of_last_stack_frame;
        printf("total_bytes_in_stack: %d\n", total_bytes_in_stack);
    }

    // total_bytes_in_stack += sizeof(size) + sizeof(fx_call) + sizeof(total_bytes_in_stack);
    printf("\nIn build_tiny_machine call %d current tiny machine size is %Lg meters\n", fx_call, size);
    build_tiny_machine(size/2, fx_call, current_stack_frame_addr, total_bytes_in_stack);
    printf("built a tiny machine!");
}

int main(int argc, char *argv[]) {
    build_tiny_machine(LDBL_MAX, 0, (uintptr_t) NULL, 0);
}