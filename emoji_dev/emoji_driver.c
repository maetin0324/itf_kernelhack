#include "emoji_driver.h"

#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/sched.h>
#include <linux/device.h>
#include <linux/string.h>
#include <asm/current.h>
#include <asm/uaccess.h>

MODULE_LICENSE("Dual BSD/GPL");

#define DRIVER_NAME "DevEmoji"
#define NUM_BUFFER 256

static const unsigned int MINOR_BASE = 0;
static const unsigned int MINOR_NUM = 1;

static unsigned int emoji_device_major;

static struct cdev emoji_device_cdev;

struct _emoji_data {
	unsigned char buffer[NUM_BUFFER];
};

struct _emoji_dict {
	unsigned char emoji_name[NUM_BUFFER];
	unsigned long  emoji_code;
};

typedef struct _emoji_dict edict_t;

static edict_t person_bowing = { ":bow:", 0xf09f99870a };

// 0: emoji -> binary
// other: stop
int emoji_state = 0;

static int emoji_device_open(struct inode *inode, struct file *file)
{
	printk("mydevice_open");
	
	struct _emoji_data *p = kmalloc(sizeof(struct _emoji_data), GFP_KERNEL);
	if (p == NULL) {
		printk(KERN_ERR "kmalloc\n");
		return -ENOMEM;
	}

	strlcat(p->buffer, "dummy", 5);

	file->private_data = p;

	return 0;
}

static int emoji_device_close(struct inode *inode , struct file *file)
{
	printk("mydevice_close");
	if (file->private_data) {
		kfree(file->private_data);
		file->private_data = NULL;
	}

	return 0;
}

static ssize_t emoji_device_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
	printk("mydevice_read");

	struct _emoji_data *p = filp->private_data;
	char cnv_buffer[NUM_BUFFER];

	if (count > NUM_BUFFER ) count = NUM_BUFFER;

	if (emoji_state == 0) {
		if (strcmp(person_bowing.emoji_name, p->buffer) == 0) {
			snprintf(cnv_buffer, NUM_BUFFER, "%lx", person_bowing.emoji_code);
		} else {

			strcpy(cnv_buffer, p->buffer);
		}
	} else {
		strcpy(cnv_buffer, "stopped");
	}

	if (copy_to_user(buf, cnv_buffer, count) != 0){
		return -EFAULT;
	}
	
	return count;
}

static ssize_t emoji_device_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{
	printk("mydevice_write");

	struct _emoji_data *p = filp->private_data;

	if (count > NUM_BUFFER) count = NUM_BUFFER;


	if (copy_from_user(p->buffer, buf, count) != 0){
		return -EFAULT;
	}
	return count;
}

static long emoji_device_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	printk("mydevice_ioctl");

	struct _emoji_data *p = filp->private_data;

	switch (cmd) {
	case EMOJI_DEVICE_SET_VALUES:
		printk("EMOJI_DEVICE_SET_VALUES");
		if (copy_from_user(&emoji_state, (void __user *)arg, sizeof(int))){
			return -EFAULT;
		}
		break;
	case EMOJI_DEVICE_GET_VALUES:
		printk("EMOJI_DEVICE_GET_VALUES");
		if (copy_to_user((void __user *)arg, &emoji_state, sizeof(int))) {
			return -EFAULT;
		}
		break;
	case EMOJI_DEVICE_CLEAR_VALUES:
		printk("EMOJI_DEVICE_CLEAR_VALUES");
		p->buffer[0] = '\0';
		emoji_state = 0;
		break;
	default:
		printk(KERN_WARNING "unsupported command %d", cmd);
		return -EFAULT;
	}

	return 0;
}


struct file_operations s_emoji_device_fops = {
	.open    = emoji_device_open,
	.release = emoji_device_close,
	.read    = emoji_device_read,
	.write   = emoji_device_write,
	.unlocked_ioctl = emoji_device_ioctl,
	.compat_ioctl   = emoji_device_ioctl,
};

static struct class *emoji_device_class = NULL;

static int emoji_device_init(void)
{
	printk("mydevice_init\n");

	int alloc_ret = 0;
	int cdev_err = 0;
	dev_t dev;


	alloc_ret = alloc_chrdev_region(&dev, MINOR_BASE, MINOR_NUM, DRIVER_NAME);
	if (alloc_ret != 0) {
		printk(KERN_ERR "alloc_chrdev_region = %d\n", alloc_ret);
		return -1;
	}

	emoji_device_major = MAJOR(dev);
	dev = MKDEV(emoji_device_major, MINOR_BASE);

	cdev_init(&emoji_device_cdev, &s_emoji_device_fops);
	emoji_device_cdev.owner = THIS_MODULE;

	cdev_err = cdev_add(&emoji_device_cdev, dev, MINOR_NUM);
	if (cdev_err != 0) {
		printk(KERN_ERR "cdev_add = %d\n", cdev_err);
		unregister_chrdev_region(dev, MINOR_NUM);
		return -1;
	}

	return 0;
}

static void emoji_device_exit(void)
{
	printk("mydevice_exit\n");

	dev_t dev = MKDEV(emoji_device_major, MINOR_BASE);

	cdev_del(&emoji_device_cdev);

	unregister_chrdev_region(dev, MINOR_NUM);
}

module_init(emoji_device_init);
module_exit(emoji_device_exit);

