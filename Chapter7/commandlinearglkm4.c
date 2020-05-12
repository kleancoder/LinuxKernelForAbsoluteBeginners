#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/stat.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

#define __KERNEL__
#define LINUX
#define MODULE
//// end of macro define section

static int intArray[3] = { 1, 2, 3 };
static int arrayArgc = 0;
//// end of declaration of command line argument

MODULE_PARM_ARRAY(intArray, int, arrayArgc, 1111);
MODULE_PARM_DESC(intArray, "An array of integers");
//// end of adding module_param along with type to every variabble

static int entrance(void)
{
	int i;
	for (i = 0; i < (sizeof intArray / sizeof (int)); i++)
	{
		printk(KERN_INFO " intArray[%d] = %d\n", i, intArray[i]);
	}
	printk(KERN_INFO "got %d arguments for intArray.\n", arrayArgc);
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
