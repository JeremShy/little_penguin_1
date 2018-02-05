obj-m += my_driver.o

all: modules

modules:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules EXTRA_CFLAGS=-DDEBUG

install:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules_install

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

test: modules install
	modprobe -r my_driver
	modprobe my_driver

re: clean all
