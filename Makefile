# Makefile for atomic bug kernel module
obj-m += spin_lock_schedule.o
#obj-m += disable_irq_schedule.o
#obj-m += mutex_lock_schedule.o



all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

install:
	sudo insmod spin_lock_schedule.ko
	sudo insmod disable_irq_schedule.ko

uninstall:
	sudo rmmod spin_lock_schedule
	sudo rmmod disable_irq_schedule

.PHONY: all clean install uninstall
