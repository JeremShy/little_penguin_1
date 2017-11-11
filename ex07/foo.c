#include "include/my_debugfs.h"

MODULE_LICENSE("GPL");

char buffer[PAGE_SIZE + 1];
int	locked;

static int my_open(struct inode *inode, struct file *file)
{
	return 0;
}

static int my_release(struct inode *inode, struct file *file)
{
	return 0;
}


static ssize_t my_read(struct file *_file, char __user *userbuff,
		       size_t len, loff_t *off)
{
	char *begin = buffer + *off;
	size_t buffer_size = strlen(buffer);
	char *end = (begin + len >= buffer + buffer_size ?
		     buffer + buffer_size : begin + len);
	int ret;

	if (locked)
		return -EIO;
	locked = 1;
	if (begin >= buffer + buffer_size) {
		locked = 0;
		return 0;
	}
	ret = copy_to_user(userbuff, begin, end - begin);
	if (ret == end - begin) {
		locked = 0;
		return -EIO;
	}
	*off += end - begin - ret;
	locked = 0;
	return (end - begin - ret);
}

static ssize_t my_write(struct file *_file,
			const char __user *userbuff, size_t len, loff_t *off)
{
	int ret;
	ssize_t rret;

	if (locked)
		return -EIO;
	locked = 1;
	if (len <= PAGE_SIZE) {
		ret = copy_from_user(buffer, userbuff, len);
		buffer[len] = '\0';
		rret = len;
	} else {
		ret = copy_from_user(buffer, userbuff, PAGE_SIZE);
		buffer[PAGE_SIZE] = '\0';
		rret = PAGE_SIZE;
	}
	locked = 0;
	if (ret != 0)
		return -EIO;
	return rret;
}

const struct file_operations fops_foo = {
	.owner = THIS_MODULE,
	.read = my_read,
	.open = my_open,
	.write = my_write,
	.release = my_release
};

