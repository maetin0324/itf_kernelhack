#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/proc_fs.h> // proc_create
#include <asm/uaccess.h> // copy_from_user

// /proc/PROCNAMEにインタフェースを作る
#define PROCNAME "driver/modtest"
#define MAXBUF 1024

MODULE_DESCRIPTION("modtest");
MODULE_LICENSE("GPL");

static char modtest_buf[MAXBUF] = "Hello World!\n";
static int buflen = 1024;

// 読み込み
static ssize_t proc_read(struct file *file, char __user *buf, size_t count, loff_t *f_pos)
{
    if (*f_pos >= buflen) {
        return 0;
    }

    if (copy_to_user(buf, modtest_buf, buflen) > 0) {
        return -EFAULT;
    }
    *f_pos += buflen;

    printk(KERN_INFO "proc_read len = %d\n", buflen);

    return buflen;
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