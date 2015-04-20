static struct file_operations fops = {
	.read = read_dev,
	.write = write_dev,
	.open = open_dev,
	.release = close_dev
};