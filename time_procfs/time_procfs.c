#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/proc_fs.h> // proc_create
#include <linux/time64.h> 
#include <asm/uaccess.h> // copy_from_user

#define PROCNAME "driver/time_procfs"
#define MAXBUF 1024

MODULE_DESCRIPTION("time_procfs");
MODULE_LICENSE("GPL");

char modtest_buf[MAXBUF];

static long get_timestamp(void)  
{  
  long timestamp;  
  struct timespec64 ts;  

  ktime_get_real_ts64(&ts);  
  timestamp = ts.tv_sec*1000000000L + ts.tv_nsec;  

  return timestamp;  
}  

static ssize_t proc_read(struct file *file, char __user *buf, size_t count, loff_t *f_pos)
{
    if (*f_pos >= MAXBUF) {
        return 0;
    }

    if (snprintf(modtest_buf, MAXBUF, "%ld\n", get_timestamp()) < 0) {
        return -EFAULT;
    }

    if (copy_to_user(buf, modtest_buf, MAXBUF) > 0) {
        return -EFAULT;
    }
    *f_pos += MAXBUF;

    printk(KERN_INFO "proc_read len = %d\n", MAXBUF);

    return MAXBUF;
}

struct proc_ops proc_ops = {
    .proc_read = proc_read,
};

// モジュール初期化
static int __init modtest_module_init(void)
{
    struct proc_dir_entry *entry;

//  /proc/PROCNAME にインタフェース作成
    entry = proc_create(PROCNAME, 0666, NULL, &proc_ops);

    if (!entry) {
        printk(KERN_ERR "proc_create failed\n");
        return -EBUSY;
    }
    printk(KERN_INFO "modtest is loaded\n");
    return 0;
}

// モジュール解放
static void __exit modtest_module_exit(void)
{
//  インタフェース削除
    remove_proc_entry(PROCNAME, NULL);

    printk(KERN_INFO "modtest is removed\n");
}

module_init(modtest_module_init);
module_exit(modtest_module_exit);