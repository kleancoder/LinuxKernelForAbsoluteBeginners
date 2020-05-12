#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/stat.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

#define __KERNEL__
#define LINUX
#define MODULE
//// end of macro define section

static char *stringVar = "hello";
//// end of declaration of command line argument


MODULE_PARAM(stringVar, charp);
MODULE_PARM_DESC(stringVar, "A character string");
//// end of adding module_param along with type to every variabble

static int entrance(void)
{
	int i;
	printk(KERN_INFO "mystring is a string: %s\n", stringVar);
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
