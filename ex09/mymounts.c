#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/mount.h>
#include <linux/sched.h>
#include <linux/fs_struct.h>

MODULE_AUTHOR("jcamhi");
MODULE_DESCRIPTION("my module\n");
MODULE_LICENSE("GPL");

struct proc_dir_entry *entry;
char	buffer[1024];

int	get_mounted_max(void) {
	struct dentry *curdentry;
	int retval = 5;

	list_for_each_entry(curdentry, &current->fs->root.mnt->mnt_root->d_subdirs, d_child) {
		if (curdentry->d_flags & DCACHE_MANAGED_DENTRY)
			if (strlen(curdentry->d_name.name) + 1 > retval)
				retval = strlen(curdentry->d_name.name) + 1;
	}
	return (retval);
}

static int my_open(struct inode *inode, struct file *file)
{
	int max = get_mounted_max() + 5;
	struct dentry *curdentry;
	char path[201];

	curdentry = current->fs->root.dentry;
	snprintf(buffer, 1024, "%-*s%s\n", max, "root", curdentry->d_name.name);
	list_for_each_entry(curdentry, &current->fs->root.mnt->mnt_root->d_subdirs, d_child) {
		if (curdentry->d_flags & DCACHE_MANAGED_DENTRY) {
			char *ret = dentry_path_raw(curdentry, path, 200);
			snprintf(buffer, 1024, "%s%-*s%s\n", buffer, max, curdentry->d_name.name, ret);
		}
	}
	return 0;
}

static int my_release(struct inode *inode, struct file *file)
{
	return 0;
}


ssize_t my_read(struct file *f, char __user *buf, size_t c, loff_t *off) {

	return simple_read_from_buffer(buf, c, off, buffer, strlen(buffer));
}

static const struct file_operations file_ops = {
	.owner = THIS_MODULE,
	.read = &my_read,
	.open = &my_open,
	.release = &my_release
};

int __init _ft_init(void)
{
	pr_debug("DebugModule: Hello world !\n");
	entry = proc_create("mymounts", 0444, NULL, &file_ops); 
	if (!entry) {
		return -ENOMEM;
	}
	my_open(NULL, NULL);
	return 0;
}

void __exit _ft_exit(void)
{
	pr_debug("DebugModule: Cleaning up module.\n");
	remove_proc_entry("mymounts", NULL);
}

module_init(_ft_init);
module_exit(_ft_exit);
