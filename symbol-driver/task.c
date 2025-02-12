#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/proc_fs.h>
#include <linux/sysfs.h>
#include <linux/slab.h>
#include <linux/mutex.h>
#include <linux/cdev.h>
#include <linux/device.h>

#define DEVICE_NAME "custom_device"
#define PROC_FILE_NAME "custom_device_info"
#define SYSFS_CLASS_NAME "custom_device"
#define SYSFS_ATTR_NAME "custom_attr"
#define DEVICE_BUFFER_SIZE 1024

static dev_t dev_num;
static struct cdev custom_cdev;
static struct class *custom_class;
static struct device *custom_device;

static char *device_buffer;
static DEFINE_MUTEX(device_mutex);
static int device_state = 0;

#define CUSTOM_IOCTL_SET_STATE _IOW('c', 1, int)
#define CUSTOM_IOCTL_GET_STATE _IOR('c', 2, int)

static int device_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "Device opened\n");
    return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "Device released\n");
    return 0;
}

static ssize_t device_read(struct file *file, char __user *buffer, size_t length, loff_t *offset)
{
    ssize_t ret;
    mutex_lock(&device_mutex);
    if (*offset >= DEVICE_BUFFER_SIZE)
    {
        mutex_unlock(&device_mutex);
        return 0;
    }
    if (length > DEVICE_BUFFER_SIZE - *offset)
        length = DEVICE_BUFFER_SIZE - *offset;
    if (copy_to_user(buffer, device_buffer + *offset, length))
    {
        ret = -EFAULT;
    }
    else
    {
        *offset += length;
        ret = length;
    }
    mutex_unlock(&device_mutex);
    return ret;
}

static ssize_t device_write(struct file *file, const char __user *buffer, size_t length, loff_t *offset)
{
    ssize_t ret;
    mutex_lock(&device_mutex);
    if (*offset >= DEVICE_BUFFER_SIZE)
    {
        mutex_unlock(&device_mutex);
        return -ENOSPC;
    }
    if (length > DEVICE_BUFFER_SIZE - *offset)
        length = DEVICE_BUFFER_SIZE - *offset;
    if (copy_from_user(device_buffer + *offset, buffer, length))
    {
        ret = -EFAULT;
    }
    else
    {
        *offset += length;
        ret = length;
    }
    mutex_unlock(&device_mutex);
    return ret;
}

static long device_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    int ret = 0;
    mutex_lock(&device_mutex);
    switch (cmd)
    {
    case CUSTOM_IOCTL_SET_STATE:
        device_state = (int)arg;
        printk(KERN_INFO "Device state set to %d\n", device_state);
        break;
    case CUSTOM_IOCTL_GET_STATE:
        ret = put_user(device_state, (int __user *)arg);
        break;
    default:
        ret = -EINVAL;
    }
    mutex_unlock(&device_mutex);
    return ret;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = device_open,
    .release = device_release,
    .read = device_read,
    .write = device_write,
    .unlocked_ioctl = device_ioctl,
};

static int __init custom_device_init(void)
{
    int ret;

    device_buffer = kmalloc(DEVICE_BUFFER_SIZE, GFP_KERNEL);
    if (!device_buffer)
        return -ENOMEM;
    memset(device_buffer, 0, DEVICE_BUFFER_SIZE);

    ret = alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME);
    if (ret < 0)
        goto err_alloc;

    cdev_init(&custom_cdev, &fops);
    ret = cdev_add(&custom_cdev, dev_num, 1);
    if (ret < 0)
        goto err_cdev;

    custom_class = class_create(THIS_MODULE, SYSFS_CLASS_NAME);
    if (IS_ERR(custom_class))
    {
        ret = PTR_ERR(custom_class);
        goto err_class;
    }
    custom_device = device_create(custom_class, NULL, dev_num, NULL, DEVICE_NAME);
    if (IS_ERR(custom_device))
    {
        ret = PTR_ERR(custom_device);
        goto err_device;
    }

    printk(KERN_INFO "Custom device driver loaded\n");
    return 0;

err_device:
    class_destroy(custom_class);
err_class:
    cdev_del(&custom_cdev);
err_cdev:
    unregister_chrdev_region(dev_num, 1);
err_alloc:
    kfree(device_buffer);
    return ret;
}

static void __exit custom_device_exit(void)
{
    device_destroy(custom_class, dev_num);
    class_destroy(custom_class);
    cdev_del(&custom_cdev);
    unregister_chrdev_region(dev_num, 1);
    kfree(device_buffer);
    printk(KERN_INFO "Custom device driver unloaded\n");
}

module_init(custom_device_init);
module_exit(custom_device_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("shmblg4");
MODULE_DESCRIPTION("Custom Character Device Driver");
MODULE_VERSION("1.0");