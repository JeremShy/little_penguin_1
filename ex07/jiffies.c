#include "include/my_debugfs.h"
#include <linux/jiffies.h>

MODULE_LICENSE("GPL");

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
	char buf[255];
	int ret;
	int jif_len;
	char *begin;
	char *end;

	snprintf(buf, 255, "%ld", jiffies);
	jif_len = strlen(buf);
	begin = buf + *off;
	end = (begin + len >= begin + jif_len ? begin + jif_len : begin + len);

	if (begin >= buf + jif_len)
		return (0);
	ret = copy_to_user(userbuff, begin, end - begin);
	if (ret == end - begin)
		return (-EIO);
	*off += end - begin - ret;
	return (end - begin - ret);

}

const struct file_operations fops_jiffies = {
	.owner = THIS_MODULE,
	.read = my_read,
	.open = my_open,
	.release = my_release
};

