#include <stdio.h>
#include <sched.h>

int main() {
    int cpu_id = sched_getcpu();
    if (cpu_id == -1) {
        perror("sched_getcpu failed");
        return 1;
    }
    printf("Current CPU ID: %d\n", cpu_id);
    return 0;
}

