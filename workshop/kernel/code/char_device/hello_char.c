#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
 
static dev_t first; /* Global variable for the first device number */
 
static int __init driver_entry(void) /* Constructor */
{
    printk(KERN_INFO "Namaskar: ofcd registered");
    if (alloc_chrdev_region(&first, 0, 3, "HelloChar") < 0)
    {
        return -1;
    }
    printk(KERN_INFO "HelloChar: <Major, Minor>: <%d, %d>\n", MAJOR(first), MINOR(first));
    return 0;
}
 
static void __exit driver_exit(void) /* Destructor */
{
    unregister_chrdev_region(first, 3);
    printk(KERN_INFO "HelloChar: unregistered");
}
 
module_init(driver_entry);
module_exit(driver_exit);
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Georgi K");
MODULE_DESCRIPTION("Hello World Character Driver");