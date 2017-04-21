OBJS    := ${patsubst %.c, %.o, ${wildcard *.c}}
obj-m   += list.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

.PHONY: clean

clean:
	@echo Clean objs
	@rm -rf *.o
	@rm -rf *.ko
	@rm -rf *.mod.c
	@rm -rf *.symvers
	@rm -rf *.order

insert:
	insmod list.ko

remove:
	rmmod list
