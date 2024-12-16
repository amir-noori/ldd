#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Amir");
MODULE_DESCRIPTION("Fish Test Module");

ssize_t read_operation(struct file *proc_file, char *user_space_buffer, size_t read_size, loff_t *offset)
{
    char message[] = "all right!\n";
    int copy_result;
    size_t len = strlen(message);

    printk("fish read operation...");

    if (*offset >= len)
    {
        return 0;
    }

    copy_result = copy_to_user(user_space_buffer, message, len);
    *offset += len;

    return len;
}

static struct proc_dir_entry *proc_entry;
static struct file_operations driver_proc_ops = {
    .read = read_operation};

static int fish_module_init(void)
{
    printk("Hi, Im Fish\n");

    proc_entry = proc_create("fish",
                             0,
                             NULL,
                             &driver_proc_ops);

    return 0;
}

static void fish_module_exit(void)
{
    proc_remove(proc_entry);
    printk("Bye, from Fish\n");
}

module_init(fish_module_init);
module_exit(fish_module_exit);
