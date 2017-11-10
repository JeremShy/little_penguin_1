#include "include/my_debugfs.h"
#include <linux/syscalls.h>
#include <linux/unistd.h>
MODULE_AUTHOR("jcamhi");
MODULE_DESCRIPTION("my module\n");
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(sys_call_table);

struct dentry *fortytwo;
struct dentry *id;
struct dentry *gifi;
struct dentry *foo;

int __init _ft_init(void)
{
	char path[PATH_MAX + 1];
	pr_debug("DebugModule: Hello world !\n");
	fortytwo = debugfs_create_dir("fortytwo", NULL);
	if (!fortytwo) {
		pr_debug("DebugModule: Error while creating dir fortytwo\n");
		return (1);
	}
	id = debugfs_create_file("id", 0666, fortytwo, NULL, &fops_id);
	gifi = debugfs_create_file("jiffies", 0444, fortytwo, NULL, &fops_jiffies);
	foo = debugfs_create_file("foo", 0644, fortytwo, NULL, &fops_foo);
	dentry_path_raw(fortytwo, path, PATH_MAX);
	sys_chown(path, 99, 99);
	return 0;
}

void __exit _ft_exit(void)
{
	debugfs_remove_recursive(fortytwo);
	pr_debug("DebugModule: Cleaning up module.\n");
}

module_init(_ft_init);
module_exit(_ft_exit);
