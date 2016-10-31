#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/usb/input.h>
#include <linux/usb.h>
#include <linux/hid.h>

#define USB_MODULE_PRINT(s)         printk("EudyptulaUSB: %s\n",s);

static struct usb_device_id usb_table [] =  {
                                                {
                                                    USB_INTERFACE_INFO(USB_INTERFACE_CLASS_HID,
                                                    USB_INTERFACE_SUBCLASS_BOOT,
                                                    USB_INTERFACE_PROTOCOL_KEYBOARD)
                                                },
                                                {}
                                            };

static int usb_probing( struct usb_interface *interface, const struct usb_device_id *id)
{
    USB_MODULE_PRINT("Probing for USB");
    return 0;
}

static void usb_disconnect(struct usb_interface *interface)
{
    USB_MODULE_PRINT("Disconnecting USB");
}

static struct usb_driver usbd = {
                                    .name       = "Eudyptula USB",
                                    .probe      = usb_probing,
                                    .disconnect = usb_disconnect,
                                    .id_table   = usb_table
                                };


static int __init usb_init(void)
{
    if(!usb_register(&usbd))
    {
        USB_MODULE_PRINT("USB registered");
    }

    return 0;
}

void __exit usb_exit(void)
{
    usb_deregister(&usbd);
    USB_MODULE_PRINT("usb deregistered");
}

module_init(usb_init);
module_exit(usb_exit);

MODULE_LICENSE("GPL");

