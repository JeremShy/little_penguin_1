obj-m += main.o
MY_CFLAGS = -DDEBUG

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules EXTRA_CFLAGS=$(MY_CFLAGS)

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

re: clean all
