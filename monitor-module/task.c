#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/proc_fs.h>
#include <linux/slab.h>
#include <linux/mutex.h>
#include <linux/rcupdate.h>
#include <linux/sched/signal.h>
#include <linux/spinlock.h>
#include <linux/timer.h>

#define PROC_FILE_NAME "task_monitor"

struct task_info
{
    pid_t pid;
    char comm[TASK_COMM_LEN];
    long state;
    struct list_head list;
    struct rcu_head rcu;
};

static LIST_HEAD(task_list);
static DEFINE_SPINLOCK(task_list_lock);
static struct timer_list task_timer;

static void update_task_list(struct timer_list *t);

static void free_task_info(struct rcu_head *rcu)
{
    struct task_info *task = container_of(rcu, struct task_info, rcu);
    kfree(task);
}

static void update_task_list(struct timer_list *t)
{
    struct task_struct *task;
    struct task_info *entry, *tmp;
    struct list_head new_list;

    INIT_LIST_HEAD(&new_list);
    rcu_read_lock();
    for_each_process(task)
    {
        entry = kmalloc(sizeof(*entry), GFP_KERNEL);
        if (!entry)
            continue;
        entry->pid = task->pid;
        get_task_comm(entry->comm, task);
        entry->state = task->state;
        list_add_rcu(&entry->list, &new_list);
    }
    rcu_read_unlock();

    spin_lock(&task_list_lock);
    list_for_each_entry_safe(entry, tmp, &task_list, list)
    {
        list_del_rcu(&entry->list);
        call_rcu(&entry->rcu, free_task_info);
    }
    list_replace_rcu(&new_list, &task_list);
    spin_unlock(&task_list_lock);

    mod_timer(&task_timer, jiffies + msecs_to_jiffies(5000));
}

static int proc_show(struct seq_file *m, void *v)
{
    struct task_info *entry;
    rcu_read_lock();
    list_for_each_entry_rcu(entry, &task_list, list)
    {
        seq_printf(m, "PID: %d, Name: %s, State: %ld\n", entry->pid, entry->comm, entry->state);
    }
    rcu_read_unlock();
    return 0;
}

static int proc_open(struct inode *inode, struct file *file)
{
    return single_open(file, proc_show, NULL);
}

static const struct file_operations proc_fops = {
    .owner = THIS_MODULE,
    .open = proc_open,
    .read = seq_read,
    .llseek = seq_lseek,
    .release = single_release,
};

static int __init task_monitor_init(void)
{
    proc_create(PROC_FILE_NAME, 0, NULL, &proc_fops);
    timer_setup(&task_timer, update_task_list, 0);
    mod_timer(&task_timer, jiffies + msecs_to_jiffies(5000));
    printk(KERN_INFO "Task monitor module loaded\n");
    return 0;
}

static void __exit task_monitor_exit(void)
{
    struct task_info *entry, *tmp;
    remove_proc_entry(PROC_FILE_NAME, NULL);
    del_timer_sync(&task_timer);
    spin_lock(&task_list_lock);
    list_for_each_entry_safe(entry, tmp, &task_list, list)
    {
        list_del_rcu(&entry->list);
        kfree(entry);
    }
    spin_unlock(&task_list_lock);
    printk(KERN_INFO "Task monitor module unloaded\n");
}

module_init(task_monitor_init);
module_exit(task_monitor_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Task Monitoring Kernel Module");
