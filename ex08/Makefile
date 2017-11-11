obj-m += main.o

MY_CFLAGS = -DDEBUG

all: modules

modules:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) $(CFLAGS) modules EXTRA_CFLAGS=$(MY_CFLAGS)

install:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules_install

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

test: modules install
	modprobe -r main
	modprobe main

re: clean all
