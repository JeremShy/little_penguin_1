obj-m := debugfs.o
debugfs-objs := main_debugfs.o id.o jiffies.o foo.o

MY_CFLAGS := -DDEBUG

all: modules

modules:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) $(CFLAGS) modules EXTRA_CFLAGS=$(MY_CFLAGS)

install:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules_install

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

test: modules install
	modprobe -r debugfs
	modprobe debugfs

re: clean all
