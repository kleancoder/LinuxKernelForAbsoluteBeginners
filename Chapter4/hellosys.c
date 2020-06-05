#include <linux/kernel.h>


// asmlinkage tells compiler to look on the CPU stack for the function parameters, instead of registers.
asmlinkage long sys_hellosys(void) {

	printk("Hello New System Call !\n");
	return 0;
}
