obj-m += my_driver.o

all: modules

modules:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules EXTRA_CFLAGS=-DDEBUG

install:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules_install

uninstall:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules_uninstall
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

re: clean all
