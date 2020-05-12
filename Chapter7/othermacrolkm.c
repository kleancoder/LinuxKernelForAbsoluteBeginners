#include <linux/kernel.h>
#include <linux/module.h>
//// end of header include section 

#define __KERNEL__
#define MODULE 
#define LINUX 
//// end of macro define section 


static int __init entrance (void) 
{
	printk(KERN_DEBUG “Hello LKM\n”);
	return 0;
} 
//// end of init section

static void __exit out (void)
{
	printk(KERN_DEBUG “Goodbye LKM\n”);
}
//// End of cleanup section

module __init (entrance);
module __exit(out);

MODULE_AUTHOR (“Md Mahbubur Rahman”);
MODULE_LICENSE (“BSD”);
//// End of module licensing section