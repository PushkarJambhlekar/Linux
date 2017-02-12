#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/debugfs.h>
#include <linux/string.h>

#define READ_FILE(func_name)	\
static ssize_t func_name(struct file *fp, char __user *buffer, size_t count,\
			loff_t *ppos)
#define WRITE_FILE(func)	\
static ssize_t func(struct file *fp, const char __user *buffer,\
			size_t count, loff_t *ppos)
#define OPEN_FILE(func)		\
static int func(struct inode *inode, struct file *fp)
#define ID_READ_DATA		"57127be5f1c3\0"
#define ID_READ_DATA_SIZE	(strlen(ID_READ_DATA))
#define ROOT_DIR_NAME		"eudyptula"
#define ID_FILE_NAME		"id"
#define USERMOD_PERM		0666

struct dentry *eudyptula_dir = NULL;

OPEN_FILE(id_open)
{
	return 0;
}

READ_FILE(id_read)
{
	return simple_read_from_buffer(buffer, count, ppos, ID_READ_DATA,
					ID_READ_DATA_SIZE);
}

WRITE_FILE(id_write)
{
	char user_input[ID_READ_DATA_SIZE];
	ssize_t out = 0;

	out = simple_write_to_buffer(user_input, ID_READ_DATA_SIZE, ppos,
			buffer, count);
	if (out < 0)
		return out;

	if (!strncmp(user_input, ID_READ_DATA, ID_READ_DATA_SIZE) &&
			count - 1 == ID_READ_DATA_SIZE)
		return count;

	return -EINVAL;
}

static struct file_operations id_fop = {
	.owner = THIS_MODULE,
	.open  = id_open,
	.read  = id_read,
	.write = id_write,
};

static void delete_debugfs_root(void)
{
	pr_err("DEBUGFS: Deleting EUDYPTULA DIR");
	debugfs_remove_recursive(eudyptula_dir);
	eudyptula_dir = NULL;
}
static int debugfs_init(void)
{
	struct dentry *id_dentry;

	pr_info("Initializing debugfs\n");

	eudyptula_dir = debugfs_create_dir(ROOT_DIR_NAME, NULL);
	if (!eudyptula_dir) {
		pr_err("Failed to create root dir\n");
		return -ENOENT;
	}

	id_dentry = debugfs_create_file(ID_FILE_NAME, USERMOD_PERM,
					eudyptula_dir, NULL, &id_fop);
	if (!id_dentry) {
		pr_err("DEBUGFS: failed to create ID file\n");
		goto fail;
	}
	return 0;
fail:
	delete_debugfs_root();
	return -ENOENT;
}

static int __init debugfs_entry(void)
{
	if (debugfs_init()) {
		pr_err("DEBUGFS: Failed to load debugfs driver\n");
		return -ENOENT;
	}

	return 0;
}

static void __exit debugfs_exit(void)
{
	delete_debugfs_root();
}

module_init(debugfs_entry);
module_exit(debugfs_exit);


MODULE_LICENSE("GPL");

MODULE_DESCRIPTION("Eudyptula misc char device");
