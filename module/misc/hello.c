#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>

typedef struct inode inode;
typedef struct file  file;

// Module Meta
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Sample char device");

#define READ_DATA               100
#define SAMPLE_DATA             "This is what you get after reading a MISC device\0"
#define DEVICE_NAME             "hello"
                  
static char data[READ_DATA] = {0};


//
// Opening MISC device. this just returns sample data 
//
int get_data(void)
{
    sprintf(data, "%s: %s\n", DEVICE_NAME, SAMPLE_DATA);

    return 0;
}
static int open(inode *iNode, file *fp)
{
    pr_info("%s: Opening MISC data\n", DEVICE_NAME);
    return 0;    
}

//
// Writing to Device
//
static ssize_t write_data(file *fp, const char __user *buffer, size_t len, loff_t *ppos)
{
    pr_info("%s: Just returning data\n", DEVICE_NAME);
    return len;
}

static ssize_t read_device(file *fp, char __user * buf, size_t len, loff_t * ppos)
{
    if(*ppos)   
    {    
        pr_info("%s: len is :%lld\n",DEVICE_NAME, *ppos);
        return 0;
    }

    pr_info("%s: Reading from device\n", DEVICE_NAME);
    get_data();
    copy_to_user(buf, data, READ_DATA);
    *ppos += len;
    return len;
}
//
// Closing device
//
static int close(inode *iNode, file *fp)
{
    pr_info("%s: Done with device\n", DEVICE_NAME);
    return 0;
}


// File structure 
static const struct file_operations fops = {
        .owner      = THIS_MODULE,
        .write      = write_data,
        .read       = read_device,
        .open       = open,
        .release    = close,
        .llseek     = no_llseek,
};

struct miscdevice device_description = {
        .minor = MISC_DYNAMIC_MINOR,
        .name  = DEVICE_NAME,
        .fops  = &fops,
};

static int __init hello_init(void)
{
    misc_register(&device_description);
    return 0;
}

void __exit hello_exit(void)
{
    misc_deregister(&device_description);
    printk( "Goodbye world!\n");
}

module_init(hello_init);
module_exit(hello_exit);


