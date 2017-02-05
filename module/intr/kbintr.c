#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>

#define DEV_ID		(0x345ef2)
static irqreturn_t irq_handle (int irq, void *dev)
{
	printk(KERN_ERR "You have pressed %x\n",inb(0x60)&0xff);
	return IRQ_HANDLED;
}

static void mainmodule(void)
{	
	if(request_irq(1, irq_handle, IRQF_SHARED, "foo", (void*)irq_handle))
	{
		printk(KERN_ERR "FOO: failed to register IRQ\n");
	}
}
static int __init hello_init(void)
{
    	printk("Registering KB interrupt handler: FOO\n");
	mainmodule();
	return 0;
}

void __exit hello_exit(void)
{
	free_irq(1, (void*)irq_handle);
    	printk( "Deregistering FOO\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");

