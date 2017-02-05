OBJS    := ${patsubst %.c, %.o, ${wildcard *.c}}
obj-m   += kbintr.o

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
	insmod kbintr.ko

remove:
	rmmod kbintr
