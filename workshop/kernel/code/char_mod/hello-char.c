#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

MODULE_AUTHOR("Georgi");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A simple char device");

#define DEVICE_NAME "hello-char"

static int open_dev(struct inode *, struct file *);
static int close_dev(struct inode *, struct file *);
static ssize_t read_dev(struct file *, char *, size_t, loff_t *);
static ssize_t write_dev(struct file *, const char *, size_t, loff_t *);

static int major;
static const char *msg = "Hello CodepLOUsa!\n";
static unsigned long use_count = 0;

static struct file_operations fops = {
	.read = read_dev,
	.write = write_dev,
	.open = open_dev,
	.release = close_dev
};

int init_module(void)
{
    major = register_chrdev(0, DEVICE_NAME, &fops);

	if (major < 0) {
	  printk(KERN_ALERT "Registering char device failed with %d\n", major);
	  return major;
	}

	printk(KERN_INFO ">>> I was assigned major number %d. <<<\n", major);
	printk(KERN_INFO ">>> Run 'mknod /dev/%s c %d 0'. <<<\n", DEVICE_NAME, major);

	return 0;
}

void cleanup_module(void)
{
	unregister_chrdev(major, DEVICE_NAME);
}

/* 
 * Called when a process tries to open the device file, like
 * "cat /dev/mycharfile"
 */
static int open_dev(struct inode *inode, struct file *file)
{
	use_count++;
	try_module_get(THIS_MODULE);

	return 0;
}

/* 
 * Called when a process closes the device file.
 */
static int close_dev(struct inode *inode, struct file *file)
{
	use_count = 0;
	module_put(THIS_MODULE);

	return 0;
}

/* 
 * Called when a process, which already opened the dev file, attempts to
 * read from it.
 */
static ssize_t read_dev(struct file *filp,
			char *buffer,	/* buffer to fill with data */
			size_t length,	/* length of the buffer     */
			loff_t * offset)
{
	long failed_to_send;
	ssize_t msg_len = strlen(msg);
	ssize_t put_rc;

	if (use_count > 1) {
		return 0;
	}

	use_count++;

	/* Don't overrun the user's buffer */
	if (msg_len > length - 1) {
		msg_len = length - 1;
	}

	failed_to_send = copy_to_user(buffer, msg, msg_len);
	if (failed_to_send != 0) {
		printk(KERN_ALERT "Something went wrong!!\n");
		return -EIO;
	}

	put_rc = put_user('\0', buffer + msg_len);
	if (put_rc < 0) {
		printk(KERN_ALERT "Failed to put the last zero!\n");
		return put_rc;
	}

	return msg_len + 1;
}


/*  
 * Called when a process writes to dev file: echo "hi" > /dev/hello 
 */
static ssize_t
write_dev(struct file *filp, const char *buff, size_t len, loff_t * off)
{
	printk(KERN_ALERT "Sorry, this operation isn't supported.\n");
	return -EPERM;
}
