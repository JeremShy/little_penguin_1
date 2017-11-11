#include "include/my_debugfs.h"

MODULE_LICENSE("GPL");

char login[] = "jcamhi";
size_t login_size = sizeof(login) - 1;

static int my_open(struct inode *inode, struct file *file)
{
	return 0;
}

static int my_release(struct inode *inode, struct file *file)
{
	return 0;
}


static ssize_t my_read(struct file *_file, char __user *buff,
		       size_t len, loff_t *off)
{
	char *begin = login + *off;
	char *end = (begin + len >= login + login_size ?
		     login + login_size : begin + len);
	int ret;

	if (begin >= login + login_size)
		return 0;
	ret = copy_to_user(buff, begin, end - begin);
	if (ret == end - begin)
		return (-EIO);
	*off += end - begin - ret;
	return (end - begin - ret);
}

static ssize_t my_write(struct file *_file, const char __user *buff, size_t len,
		 loff_t *off)
{
	if (len == login_size) {
		char buffer[login_size];
		int retval = copy_from_user(buffer, buff, login_size);

		if (retval != 0)
			return (-EIO);
		if (len == login_size && !memcmp(buffer, login, login_size))
			return login_size;
	}
	return (-EINVAL);
}

const struct file_operations fops_id = {
	.owner = THIS_MODULE,
	.read = my_read,
	.open = my_open,
	.write = my_write,
	.release = my_release
};

