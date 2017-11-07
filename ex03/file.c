#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/slab.h>

int do_work(int *my_int, int retval)
{
	int i;
	int y = *my_int;
	int z;

	for (i = 0; i < *my_int; ++i)
		udelay(10);
	if (y < 10)
		/*
		 * That was a long sleep, tell userspace about it
		 */
		pr_info("We slept a long time!");
	z = i * y;
	return z;
}

int my_init(void)
{
	int x = 10;

	x = do_work(&x, x);
	return x;
}

void my_exit(void)
{
}

module_init(my_init);
module_exit(my_exit);
