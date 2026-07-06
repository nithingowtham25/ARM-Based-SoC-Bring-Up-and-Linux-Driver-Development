/*  multiplier.c - Simple character device module
 *  
 *  Demonstrates module creation of character device for user
 *  interaction.  Also utilizes/demostrates kmalloc and write.
 *
 *  (Adapted from various example modules including those found in the
 *  Linux Kernel Programming Guide, Linux Device Drivers book and
 *  FSM's device driver tutorial)
 */

/* Moved all prototypes and includes into the headerfile */
#include "multiplier.h"
#include "xparameters.h"  /* needed for physical address of multiplier */

/* from xparameters.h */
#define PHY_ADDR XPAR_MULTIPLY_0_S00_AXI_BASEADDR /* physical address of multiplier */

/* size of physical address range for multiply */
#define MEMSIZE (XPAR_MULTIPLY_0_S00_AXI_HIGHADDR - XPAR_MULTIPLY_0_S00_AXI_BASEADDR + 1)

void *virt_addr; /* virtual address pointing to multiplier */

/* This structure defines the function pointers to our functions for
   opening, closing, reading and writing the device file.  There are
   lots of other pointers in this structure which we are not using,
   see the whole definition in linux/fs.h */
static struct file_operations fops = {
  .read = device_read,
  .write = device_write,
  .open = device_open,
  .release = device_close
};

/*
 * This function is called when the module is loaded and registers a
 * device for the driver to use.  We also allocate a little memory for
 * the driver to use as a backing store for data written to the device
 * file from userland, emulating a hardware device. Note: if there
 * were a real hardware device (with associated memory mapped io) we
 * wanted to read and write from we'd have to call ioremap to get a
 * kernel virtual memory address that maps to the physical address of
 * the device.
 */
int my_init(void)
{

  /* Linux kernel's version of printf */
  printk(KERN_INFO "Mapping virtual address...\n");

  /* map virtual address to multiplier physical address */
  /* use ioremap */
  virt_addr = ioremap(PHY_ADDR, MEMSIZE);

  if (!virt_addr) {
      printk(KERN_ALERT "ioremap failed!\n");
      return -ENOMEM;
  }

  /* print physical and virtual addresses */
  printk(KERN_INFO "Physical address = %#x\n", PHY_ADDR);
  printk(KERN_INFO "Virtual address = %p\n", virt_addr);


  /* This function call registers a device and returns a major number
     associated with it.  Be wary, the device file could be accessed
     as soon as you register it, make sure anything you need (ie
     buffers ect) are setup _BEFORE_ you register the device.*/
  Major = register_chrdev(0, DEVICE_NAME, &fops);

  
  /* Negative values indicate a problem */
  if (Major < 0) {		
    /* Make sure you release any other resources you've already
       grabbed if you get here so you don't leave the kernel in a
       broken state. */
    printk(KERN_ALERT "Registering char device failed with %d\n", Major);
    return Major;
  }

  printk(KERN_INFO "Registered a device with dynamic Major number of %d\n", Major);
  
  printk(KERN_INFO "Create a device file for this device with this command:\n'mknod /dev/%s c %d 0'.\n", DEVICE_NAME, Major);

  return 0;		/* success */
}

/*
 * This function is called when the module is unloaded, it releases
 * the device file.
 */
void my_exit(void)
{
  /* Unregister the device */
  unregister_chrdev(Major, DEVICE_NAME);

  /* Unmap virtual memory */
  printk(KERN_ALERT "unmapping virtual address space....\n");
  iounmap((void *)virt_addr);

}

/* 
 * Called when a process tries to open the device file, like "cat
 * /dev/multiplier".  Link to this function placed in file operations
 * structure for our device file.
 */
static int device_open(struct inode *inode, struct file *file)
{
  
  /* In these case we are only allowing one process to hold the device
     file open at a time. */
  if (Device_Open)		/* Device_Open is my flag for the usage of the device 
                         file (definied in multiplier.h)  */
    return -EBUSY;		/* Failure to open device is given
				                 back to the userland program. */
  Device_Open++;		  /* Keeping the count of the device opens. */


  try_module_get(THIS_MODULE);	/* increment the module use count
                                  (make sure this is accurate or you
                                  won't be able to remove the module
                                  later. */

  /* Print kernel message */
  printk(KERN_INFO "The multiplier device is opened successfully!!!\n");
  return 0;
}

/* 
 * Called when a process closes the device file.
 */
static int device_close(struct inode *inode, struct file *file)
{
  Device_Open--;		/* We're now ready for our next caller */
  
  /* 
   * Decrement the usage count, or else once you opened the file,
   * you'll never get get rid of the module.
   */
  module_put(THIS_MODULE);

  /* Print kernel message */
  printk(KERN_INFO "The multiplier device is closed successfully!!!\n");
  return 0;
}

/* 
 * Called when a process, which already opened the dev file, attempts to
 * read from it.
 */
static ssize_t device_read(struct file *filp,	/* see include/linux/fs.h   */
			   char __user *buffer,	/* buffer to fill with data */
			   size_t length,	/* length of the buffer     */
			   loff_t * offset)
{
    int i;
    int bytes_read = 0;

    /* 
     * The user may request any number of bytes, but the multiplier
     * peripheral only supports addresses from byte 0 to byte 11.
     * So we compute a safe length that does not exceed 12 bytes.
     */
    size_t valid_len = (length <= 12) ? length : 12;

    /* Print how many bytes were requested vs how many will be served */
    printk(KERN_INFO "Multiplier: Read requested = %zu bytes, serving = %zu bytes\n",
           length, valid_len);

    /*
     * Loop through each valid byte in the peripheral address space.
     * For each byte:
     *  - Read from the hardware using ioread32()
     *  - Copy it to user space using put_user()
     */
    for (i = 0; i < valid_len; i++) {

        /* Read one byte from the memory-mapped peripheral */
        char data = ioread32(virt_addr + i);

        /* 
         * Copy the byte from kernel space to user space buffer.
         * 'buffer' is a user-space pointer, so put_user is required.
         */
        put_user(data, buffer + i);

        /* Increment count of successfully transferred bytes */
        bytes_read++;

        /* Debug print for each byte read */
        printk(KERN_INFO "Multiplier: Read byte[%d] = %d\n", i, data);
    }

    /*
     * Return the number of bytes actually transferred to user space.
     * This satisfies the requirement of the read() system call.
     */
    printk(KERN_INFO "Multiplier: Total bytes read = %d\n", bytes_read);

    return bytes_read;
}

/* 
 * This function is called when somebody tries to write into our
 * device file.
 */
static ssize_t device_write(struct file *file, const char __user * buffer, size_t length, loff_t * offset)
{
    int i;
    int bytes_written = 0;

    /*
     * The multiplier peripheral only supports writes to byte
     * addresses 0 through 7. So we compute a safe length that
     * does not exceed 8 bytes.
     */
    size_t valid_len = (length <= 8) ? length : 8;

    /* Print how many bytes were requested vs how many will be written */
    printk(KERN_INFO "Multiplier: Write requested = %zu bytes, writing = %zu bytes\n",
           length, valid_len);

    /*
     * Loop through each byte to be written:
     *  - Copy data from user space to kernel variable using get_user()
     *  - Write that byte to the memory-mapped peripheral using iowrite32()
     */
    for (i = 0; i < valid_len; i++) {

        char data;

        /*
         * Copy one byte from user space buffer to kernel space.
         * 'buffer' is a user-space pointer, so get_user is required.
         */
        get_user(data, buffer + i);

        /*
         * Write the byte to the corresponding offset in the
         * multiplier peripheral address space.
         */
        iowrite32(data, virt_addr + i);

        /* Increment count of successfully written bytes */
        bytes_written++;

        /* Debug print for each byte written */
        printk(KERN_INFO "Multiplier: Wrote byte[%d] = %d\n", i, data);
    }

    /*
     * Return the number of bytes successfully written to the device.
     * This satisfies the requirement of the write() system call.
     */
    printk(KERN_INFO "Multiplier: Total bytes written = %d\n", bytes_written);

    return bytes_written;
}

/* These define info that can be displayed by modinfo */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nithin Gowtham Saravanan");
MODULE_DESCRIPTION("Module which creates a multiplier character device and allows user interaction with it");

/* Here we define which functions we want to use for initialization
   and cleanup */
module_init(my_init);
module_exit(my_exit);
