OBJS    := ${patsubst %.c, %.o, ${wildcard *.c}}
obj-m   += hello.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

.PHONY: clean

clean:
	rm -rf *.o

insert:
	insmod hello.ko

remove:
	rmmod hello
