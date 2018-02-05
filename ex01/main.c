#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

MODULE_AUTHOR("jcamhi");
MODULE_DESCRIPTION("my module\n");
MODULE_LICENSE("GPL");

int __init _ft_init(void)
{
	pr_debug("Hello world !\n");
	return 0;
}

void __exit _ft_exit(void)
{
	pr_debug("Cleaning up module.\n");
}

module_init(_ft_init);
module_exit(_ft_exit);
