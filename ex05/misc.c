#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/hid.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <linux/device.h>
#include <linux/kdev_t.h>

MODULE_AUTHOR("jcamhi");
MODULE_DESCRIPTION("my module\n");
MODULE_LICENSE("GPL");

char login[] = "jcamhi";
size_t login_size = sizeof(login) - 1;

int my_open(struct inode *inode, struct file *file) {
	pr_debug("MiscModule: opening");	
	return (0);
}

int my_release(struct inode *inode, struct file *file) {
	pr_debug("MiscModule: Releasing");
	return (0);
}


ssize_t my_read(struct file *_file, char __user *buff, size_t len, loff_t *off) {
	char *begin = login + *off;
	char *end = (begin + len >= login + login_size ? login + login_size : begin + len);
	int ret;

	if (begin >= login + login_size) {
		return 0;
	}
	ret = copy_to_user(buff, begin, end - begin);
	if (ret == end - begin) {
		return (-EIO);
	} else { 
		*off += end - begin - ret;
		return (end - begin - ret);
	}
	pr_debug("MiscModule: Error while reading");
	return (-1);
}

ssize_t my_write (struct file *_file, const char __user *buff, size_t len, loff_t *off) {
	if (len == login_size) {
		char buffer[login_size];
		int retval = copy_from_user(buffer, buff, login_size);
		if (retval != 0) {
			return (-EIO);
		}
		if (len == login_size && memcmp(buffer, login, login_size) == 0) {
			pr_debug("MiscModule: Good login !\n");
			return login_size;
		}
	}
	return (-EINVAL);
}

struct file_operations fops = {
	.owner = THIS_MODULE,
	.read = my_read,
	.open = my_open,
	.write = my_write,
	.release = my_release
};

struct miscdevice my_dev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "fortytwo",
	.fops = &fops
};

int __init _ft_init(void)
{
	pr_debug("MiscModule: Hello world !\n");
	misc_register(&my_dev);
	return 0;
}

void __exit _ft_exit(void)
{
	pr_debug("MiscModule: Cleaning up module.\n");
	misc_deregister(&my_dev);
}

module_init(_ft_init);
module_exit(_ft_exit);
