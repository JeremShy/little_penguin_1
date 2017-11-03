#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

int __init _ft_init(void) {
	printk(KERN_DEBUG "Hello world !\n");
	return (0);
}

void __exit _ft_exit(void) {
	printk(KERN_DEBUG "Cleaning up module.\n");
}

module_init(_ft_init);
module_exit(_ft_exit);
