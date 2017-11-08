#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/usb.h>
#include <linux/usb/input.h>
#include <linux/hid.h>

MODULE_AUTHOR("jcamhi");
MODULE_DESCRIPTION("my module\n");
MODULE_LICENSE("GPL");

static int __init _ft_init(void)
{
	pr_debug("MiscModule: Hello world !\n");
	return 0;
}

static void __exit _ft_exit(void)
{
	pr_debug("MiscModule: Cleaning up module.\n");
}

module_init(_ft_init);
module_exit(_ft_exit);
