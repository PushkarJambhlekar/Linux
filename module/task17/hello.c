#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/wait.h>

#define READ_DATA "57127be5f1c3\0"
#define READ_DATA_SIZE 13
#define DEVICE_NAME "eudyptula"
#define THREAD_NAME "eudyptula"

struct task_struct *thread;
DECLARE_WAIT_QUEUE_HEAD(wee_wait);

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

static const struct file_operations fops = {
	.owner   = THIS_MODULE,
	.write   = write_data,
	.llseek  = no_llseek
};

struct miscdevice device_description = {
	.minor = MISC_DYNAMIC_MINOR,
	.name  = DEVICE_NAME,
	.fops  = &fops,
	.mode  = 0222
};

int th_main(void *data)
{
	int status;

	pr_debug("in %s thread\n", THREAD_NAME);
	while (!kthread_should_stop()) {
		status = wait_event_interruptible(wee_wait,
						  kthread_should_stop());
		if (status) {
			pr_err("failed to wait for wee_wait\n");
			return status;
		}
	}
	return 0;
}
void init_thread(void)
{
	thread = kthread_run(&th_main, NULL, THREAD_NAME);
	pr_err("Kernel thread : %s\n", thread->comm);
}

static int __init hello_init(void)
{
	int error = 0;

	error = misc_register(&device_description);
	if (error)
		pr_err("Error in registering device: %d", error);

	init_thread();
	return error;
}

void __exit hello_exit(void)
{
	kthread_stop(thread);
	misc_deregister(&device_description);
}

module_init(hello_init);
module_exit(hello_exit);



MODULE_LICENSE("GPL");

MODULE_DESCRIPTION("Eudyptula misc char device");
