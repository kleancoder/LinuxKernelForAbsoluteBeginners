#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/stat.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

#define __KERNEL__
#define LINUX
#define MODULE
//// end of macro define section

static short int shortInt = 1;
static int vInt = 111;
static long int longInt = 5555;
//// end of declaration of command line argument

MODULE_PARAM(shortInt, short);
MODULE_PARM_DESC(shortInt, "A short integer");
MODULE_PARAM(vInt, int);
MODULE_PARM_DESC(vInt, "An integer");
MODULE_PARAM(longInt, long);
MODULE_PARM_DESC(longInt, "A long integer");


static int entrance(void)
{
	int i;
	printk(KERN_INFO "Hello LKM =============\n");
	printk(KERN_INFO "myshort is a short integer: %hd\n", shortInt);
	printk(KERN_INFO "vInt is an integer: %d\n", vInt);
	printk(KERN_INFO "longInt is a long integer: %ld\n", longInt);

	return 0;
}
//// end of init section

static void out(void)
{
	printk(KERN_INFO "Goodbye LKM\n");
}
//// End of cleanup section

module __init (entrance);
module __exit(out);

MODULE_AUTHOR("Md Mahbubur Rahman");
MODULE_LICENSE (“BSD”);
//// End of module licensing section
