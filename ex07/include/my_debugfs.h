#ifndef MY_DEBUGFS
# define MY_DEBUGFS
# include <linux/module.h>
# include <linux/kernel.h>
# include <linux/init.h>
# include <linux/hid.h>
# include <linux/miscdevice.h>
# include <linux/uaccess.h>
# include <linux/device.h>
# include <linux/kdev_t.h>
# include <linux/debugfs.h>

extern const struct file_operations fops_id;
extern const struct file_operations fops_jiffies;
extern const struct file_operations fops_foo;


#endif
