OBJS    := ${patsubst %.c, %.o, ${wildcard *.c}}
FILE_NAME := usb
obj-m   += ${FILE_NAME}.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

.PHONY: clean

clean:
	rm -rf *.o

insert:
	insmod ${FILE_NAME}.ko

remove:
	rmmod ${FILE_NAME}
