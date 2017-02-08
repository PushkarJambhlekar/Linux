#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>

#define READ_DATA "iiew2v3240f11\0"
#define READ_DATA_SIZE 13
#define DEVICE_NAME "eudyptula"

static ssize_t write_data(struct file *fp, const char __user *buffer,
			  size_t len, loff_t *ppos)
{

	char user_input[READ_DATA_SIZE];
	ssize_t out = 0;

	out = simple_write_to_buffer(user_input, READ_DATA_SIZE, ppos,
			buffer, len);
	if (out < 0)
		return out;

	if (!strncmp(user_input, READ_DATA, strlen(READ_DATA)) &&
			len - 1 == strlen(READ_DATA))
		return len;

	return -EINVAL;
}

static ssize_t read_data(struct file *file, char __user *buf, size_t len,
			 loff_t *ppos)
{
	return simple_read_from_buffer(buf, len, ppos, READ_DATA,
			strlen(READ_DATA));
}

static const struct file_operations fops = {
	.owner   = THIS_MODULE,
	.write   = write_data,
	.read    = read_data,
	.llseek  = no_llseek
};

struct miscdevice device_description = {
	.minor = MISC_DYNAMIC_MINOR,
	.name  = DEVICE_NAME,
	.fops  = &fops
};

static int __init hello_init(void)
{
	int error = 0;

	error = misc_register(&device_description);
	if (error)
		pr_err("Error in registering device: %d", error);

	return error;
}



void __exit hello_exit(void)
{
	misc_deregister(&device_description);
}

module_init(hello_init);
module_exit(hello_exit);



MODULE_LICENSE("GPL");

MODULE_DESCRIPTION("Eudyptula misc char device");
