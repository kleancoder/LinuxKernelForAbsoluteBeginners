#include <linux/kernel.h>
#include <linux/module.h>
//// end of header include section

#define __KERNEL__
#define MODULE
#define LINUX
//// end of macro define section

int init_module(void)
{
	printk(KERN_DEBUG “Hello LKM!”);
	return 0;
}
//// end of init section

void cleanup_module (void)
{
	printk(KERN_DEBUG “Goodbye LKM”);
}
//// End of cleanup section

MODULE_LICENSE (“BSD”);
//// End of module licensing section
