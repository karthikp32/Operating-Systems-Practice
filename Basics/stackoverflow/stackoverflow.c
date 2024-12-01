#include <float.h>
#include <stdio.h>

void build_tiny_machine(long double size, int fx_call) {
    fx_call++;
    printf("In build_tiny_machine call %d current tiny machine size is %Lg meters\n", fx_call, size);
    build_tiny_machine(size/2, fx_call);
}

int main(int argc, char *argv[]) {
    build_tiny_machine(LDBL_MAX, 0);
}