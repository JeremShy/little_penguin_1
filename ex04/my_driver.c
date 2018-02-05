#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/usb.h>
#include <linux/usb/input.h>
#include <linux/hid.h>

MODULE_AUTHOR("jcamhi");
MODULE_DESCRIPTION("my module\n");
MODULE_LICENSE("GPL");

static struct usb_device_id my_id_table[] = {
	{
		USB_INTERFACE_INFO(USB_INTERFACE_CLASS_HID,
				   USB_INTERFACE_SUBCLASS_BOOT,
				   USB_INTERFACE_PROTOCOL_KEYBOARD)
	},
	{ }
};

MODULE_DEVICE_TABLE(usb, my_id_table);

static int my_probe(struct usb_interface *intf, const struct usb_device_id *id)
{
	pr_debug("my_driver: probe called\n");
	printk(KERN_INFO "we are in probe function.\n");
	return 0;
}

static void my_disconnect(struct usb_interface *intf)
{
	pr_debug("my_driver: disconnect called");
}

static struct usb_driver my_driver = {
	.name = "my_driver",
	.probe = my_probe,
	.disconnect = my_disconnect,
	.id_table = my_id_table
};

static int __init _ft_init(void)
{
	int retval;

	pr_debug("my_driver: Hello world !\n");
	retval = usb_register(&my_driver);
	if (retval)
		pr_debug("my_driver: Error when trying to register the driver. retval = %d\n"
			 , retval);
	return retval;
}

static void __exit _ft_exit(void)
{
	pr_debug("my_driver: Cleaning up module.\n");
	usb_deregister(&my_driver);
}

module_init(_ft_init);
module_exit(_ft_exit);
