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

DEFINE_MUTEX(lock);


static int __init atomic_bug_init(void)
{

    mutex_lock(&lock);
        schedule();
        msleep(100);
        udelay(100);

    mutex_unlock(&lock);


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