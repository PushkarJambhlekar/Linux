OBJS    := ${patsubst %.c, %.o, ${wildcard *.c}}
DEVNAME := hello
obj-m   += ${DEVNAME}.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

.PHONY: clean

clean:
	rm -rf *.o
	rm -rf *.ko
	rm -rf *.symvers
	rm -rf *.order
	rm -rf *.mod.c

insert:
	sudo insmod ${DEVNAME}.ko

remove:
	sudo rmmod ${DEVNAME}
