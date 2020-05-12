#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>

int main() {
    long int syscallnumber = syscall(329);
    printf(“System call sys_hellosys returned %ld\n”, syscallnumber);
    return 0;
}
