#include <float.h>
#include <stdio.h>
#include <stdint.h>


void build_tiny_machine(long double size, int fx_call, int total_bytes_in_stack) {
    printf("Memory address of first variable in current stack frame is (%p)", &total_bytes_in_stack);
    fx_call++;
    // total_bytes_in_stack += sizeof(size) + sizeof(fx_call) + sizeof(total_bytes_in_stack);
    printf("In build_tiny_machine call %d current tiny machine size is %Lg meters\n", fx_call, size);
    printf("Size of parameters: %d bytes\n", total_bytes_in_stack);    
    build_tiny_machine(size/2, fx_call, total_bytes_in_stack);
    printf("built a tiny machine!");
}

int main(int argc, char *argv[]) {
    build_tiny_machine(LDBL_MAX, 0, 0);
}