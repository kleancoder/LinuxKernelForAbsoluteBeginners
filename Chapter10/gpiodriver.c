
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/stat.h>

#include <linux/cdev.h>
#include <linux/device.h>

#include <linux/fs.h>
#include <linux/slab.h>
#include <asm/uaccess.h>

#include <linux/string.h>
// end of header include section 


#define DEVICE_MAJOR  200
#define DEVICE_MINOR  0
#define DEVICE_DEV_COUNT 2
// end of define defition section 

static int     gpio_open( struct inode *, struct file * );
static ssize_t gpio_read( struct file * ,        char *  , size_t, loff_t *);
static ssize_t gpio_write(struct file * , const  char *  , size_t, loff_t *);
static int     gpio_close(struct inode *, struct file * );

struct file_operations gpio_fops = {
        read    :       gpio_read,
        write   :       gpio_write,
        open    :       gpio_open,
        release :       gpio_close,
        owner   :       GPIO_MODULE
};
struct cdev gpio_cdev;
static char *dev_c_message = NULL;


static int entrance(void)
{
	// get device number
	// A device ID is represented using the type dev_t.
	dev_t devno;
	unsigned int count = DEVICE_DEV_COUNT;
	
	int err;
	// A device ID consists of two parts: a major ID, identifying the class
    // of the device, and a minor ID, identifying a specific instance of a
    // device in that class. Given major and minor device IDs, makedev() combines these to produce
    // a device ID, returned as the function result.
    // The major and minor number are how Linux identifies the underlying hardware device associated with a device file.
    // Most of the cases major number identifies the driver while the minor distinguishes the different devices the driver controls.
	devno = MKDEV(DEVICE_MAJOR, DEVICE_MINOR);
	// register_chrdev_region function — register a range of device numbers
	// parameters are (dev_t from, unsigned count, const char * name);
	// from - the first in the desired range of device numbers; must include the major number. 
	// count - the number of consecutive device numbers required 
	// name - the name of the device or driver. 
	register_chrdev_region(devno, count , "gpiodev");

	// cdev_init — initialize a cdev structure 
	cdev_init(&gpio_cdev, &gpio_fops);
	gpio_cdev.owner = GPIO_MODULE;
	
	// cdev_add registers a character device with the kernel. 
	// The kernel maintains a list of character devices under cdev_map
	err = cdev_add(&gpio_cdev, devno, count);
	if (err < 0)
	{
		printk("Error: While Adding Device\n");
		return -1;
	}

	printk("TINY GPIO Device Driver.\n");
	printk("'mknod /dev/gpiodev_0 c %d 0'.\n", DEVICE_MAJOR);
	printk("'mknod /dev/gpiodev_1 c %d 1'.\n", DEVICE_MAJOR);

	// kmalloc is the normal method of allocating memory for objects smaller than page size in the kernel.
	dev_c_message = (char *)kmalloc(32, GFP_KERNEL);
	if (dev_c_message !=NULL) {
		printk("kmalloc dev_c_message: 0x%p\n", dev_c_message);
	}

    return 0;
}
// end of init section


static void out(void)
{
	dev_t devno;
	printk("Bye TINY GPIO Driver\n");

	if (dev_c_message){
        // release relevant kernel memory 
        kfree(dev_c_message);
	}

	// release the tiny GPIO char device
	devno = MKDEV(DEVICE_MAJOR, DEVICE_MINOR);

	// unregister_chrdev_region — unregister a range of device numbers
	unregister_chrdev_region(devno, DEVICE_DEV_COUNT);
	// cdev_del - remove a cdev from the system
	cdev_del(&gpio_cdev);
}
// End of cleanup section


static int gpio_open(struct inode *inod, struct file *fil)
{
	int dev_major;
	int dev_minor;
	
	dev_major = imajor(inod);
	dev_minor = iminor(inod);
	
	printk("\n*****TINY GPIO DEVICE: OPEN :  major %d  minor %d*****\n",dev_major, dev_minor);
	return 0;
}

static int gpio_close(struct inode *inod, struct file *fil)
{	
	int dev_major;
	int dev_minor;
	
	dev_major = MAJOR(filp->f_dentry->d_inode->i_rdev);
	dev_minor = MINOR(filp->f_dentry->d_inode->i_rdev);
	
	printk("\n*****TINY GPIO DEVICE: CLOSE :  major %d  minor %d*****\n",dev_major, dev_minor);
	return 0;
}


static ssize_t gpio_read(struct file *filp, char *buff, size_t len, loff_t *off)
{
	int dev_major, dev_minor;
	short count;

	dev_major = MAJOR(filp->f_dentry->d_inode->i_rdev);
	dev_minor = MINOR(filp->f_dentry->d_inode->i_rdev);
	printk("FILE OPERATION READ:%d:%d\n", dev_major, dev_minor);

	switch(minor){
		case 0:
			strcpy(dev_c_message,"DATA FROM MOUDLE: minor : 0");
			break;
		case 1:
			strcpy(dev_c_message,"DATA FROM MOUDLE: minor : 1");
			break;
		default:
			len = 0;
	}
	// copy_to_user — Copy a block of data into user space.
	// Returns number of bytes that could not be copied. On success, this will be zero.
	count = copy_to_user( buff, dev_c_message, len);
	return 0;
}

static ssize_t gpio_write(struct file *filp, const char *buff, size_t len, loff_t *off)
{
	int dev_major, dev_minor;
	short count;

	memset(dev_c_message, 0, 32);
	dev_major = MAJOR(filp->f_dentry->d_inode->i_rdev);
	dev_minor = MINOR(filp->f_dentry->d_inode->i_rdev);
	count = copy_from_user( dev_c_message, buff, len );

	printk("FILE OPERATION WRITE:%d:%d\n",dev_major,dev_minor);
	printk("dev_c_message: %s", dev_c_message);

	return len;
}

module __init (entrance);
module __exit(out);

MODULE_LICENSE("BSD");
MODULE_DESCRIPTION("TINY GPIO Device Driver");

