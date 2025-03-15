#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/sched.h>
#include <linux/interrupt.h>
#include <linux/spinlock_types.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple driver to reproduce 'scheduling while atomic' bug");


static int __init atomic_bug_init(void)
{
    printk(KERN_INFO "atomic_bug: Loading module\n");
	spinlock_t lock;

    // Start atomic segment:
    printk(KERN_INFO "atomic_bug: use spin_lock, entering atomic context\n");

	spin_lock(&lock);

        schedule(); // Ask kernel to preempt process- NOT ALLOWED too

        // Call a function that sleeps - this will trigger the 'scheduling while atomic' warning
        // It happens because Linux kernel will place this thread into a queue and schedule another thread however we are in atomic context
        // so it is strictly forbidden
        
        msleep(100);  // Sleep in atomic context - NOT ALLOWED


        udelay(100); // Busy wait, no preempt - ALLOWED

    spin_unlock(&lock);

    printk(KERN_INFO "atomic_bug: Exiting atomic context\n");

    return 0;
}

static void __exit atomic_bug_exit(void)
{
    printk(KERN_INFO "atomic_bug: Unloading module\n");
}

module_init(atomic_bug_init);
module_exit(atomic_bug_exit);


/*
* When use spin_lock or mutex ?
*
*
*
*/