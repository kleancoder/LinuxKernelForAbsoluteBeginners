#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/stat.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

#define __KERNEL__
#define LINUX
#define MODULE
//// end of macro define section

static int input = 5; // variable should have initial default value
MODULE_PARAM (input, int);
MODULE_PARM_DESC(input, "An integer");

static init entrance (void)
{
	int square_val = input * input;
	printk(KERN_DEBUG “Square value of input = %i\n”, square_val);
}
//// end of init section

static void out (void)
{
	printk(KERN_DEBUG “Goodbye LKM\n”);
}
//// End of cleanup section

module __init (entrance);
module __exit(out);


MODULE_LICENSE (“BSD”);
//// End of module licensing section
