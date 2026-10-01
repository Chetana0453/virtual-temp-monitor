#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/kernel.h>

static int temperature = 25;

static ssize_t vtemp_read(struct file *file,
                          char __user *buffer,
                          size_t count,
                          loff_t *position)
{
    char text[16];
    int length;

    length = scnprintf(text, sizeof(text), "%d\n", temperature);

    return simple_read_from_buffer(buffer, count, position,
                                   text, length);
}
static const struct file_operations vtemp_fops = {
    .owner = THIS_MODULE,
    .read = vtemp_read,

};

static struct miscdevice vtemp_device = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "vtemp",
    .fops = &vtemp_fops,
    .mode = 0600,
};

static int __init vtemp_init(void)
{
    int ret;

    ret = misc_register(&vtemp_device);
    if (ret) {
        pr_err("vtemp: device registration failed: %d\n", ret);
        return ret;
    }

    pr_info("vtemp: device registered\n");
    return 0;
}

static void __exit vtemp_exit(void)
{
    misc_deregister(&vtemp_device);
    pr_info("vtemp: device removed\n");
}

module_init(vtemp_init);
module_exit(vtemp_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Virtual temperature sensor driver");
