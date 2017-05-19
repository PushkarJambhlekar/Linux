OBJS    := ${patsubst %.c, %.o, ${wildcard *.c}}
obj-m   += hello.o
CFLAGS_hello.o  := -DDEBUG

all: clean
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

.PHONY: clean

clean:
	@echo Clean objs
	@rm -rf *.o
	@rm -rf *.ko
	@rm -rf *.mod.c
	@rm -rf *.symvers
	@rm -rf *.order
	@rm -rf .hello*
	@rm -rf .tmp*


insert:
	sudo insmod hello.ko

remove:
	sudo rmmod hello
