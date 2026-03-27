/*
 * hello.c - Hello World kernel module
 *
 * Demonstrates module initialization, module release, and printk.
 *
 * (Adapted from various example modules including those found in the
 * Linux Kernel Programming Guide, Linux Device Drivers book, and
 * FSM's device driver tutorial)
 */

#include <linux/module.h>   /* Needed by all modules */
#include <linux/kernel.h>   /* Needed for KERN_INFO */
#include <linux/init.h>     /* Needed for __init and __exit macros */

/* 
 * This function is run upon module load.
 * This is where you setup data structures and reserve resources.
 */
static int __init my_init(void)
{
    printk(KERN_INFO "Hello world!\n");
    return 0; /* Non-zero return means init failed */
}

/* 
 * This function is run just prior to module removal.
 * Release all resources here.
 */
static void __exit my_exit(void)
{
    printk(KERN_ALERT "Goodbye world!\n");
}

/* Module metadata */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("ECEN749 Student: Nithin Gowtham");
MODULE_DESCRIPTION("Simple Hello World Module");

/* Register init and exit functions */
module_init(my_init);
module_exit(my_exit);
