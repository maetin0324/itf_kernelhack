#include <linux/init.h>  
#include <linux/module.h>  
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/kthread.h>
#include <linux/time64.h>
  
MODULE_LICENSE("GPL v2");  
  
int drv_major = 0;  
int drv_minor = 0;  
int drv_nr_devs = 1;  
static struct task_struct *kthread_tsk;  
  
#define SKEL_DRV_NAME "skel_drv"  
  
static long get_timestamp(void)  
{  
  long timestamp;  
  struct timespec64 ts;  

  ktime_get_real_ts64(&ts);  
  timestamp = ts.tv_sec*1000000000L + ts.tv_nsec;  

  return timestamp;  
}  
  
static void my_kthread_main(void)  
{  
  set_current_state(TASK_INTERRUPTIBLE);  
  schedule_timeout(1 * HZ);  

  pr_info("my_kthread_main:%ld\n", get_timestamp());  
}  
  
static int my_kthread(void *arg)  
{  
  pr_info("%s:I %ld HZ-%d\n", __FUNCTION__, get_timestamp(), HZ);  

  while (!kthread_should_stop()) {  
    my_kthread_main();  
  }  

  pr_info("%s:O\n", __FUNCTION__);  
  return 0;  
}  
  
static int skel_init(void)  
{  
  dev_t dev = 0;  
  int ret;  

  pr_info("%s\n", __FUNCTION__);  

  if (drv_major) {  
    dev = MKDEV(drv_major, drv_minor);  
    ret = register_chrdev_region(dev, drv_nr_devs, SKEL_DRV_NAME);  
  }  
  else {  
    ret = alloc_chrdev_region(&dev, drv_minor, drv_nr_devs, SKEL_DRV_NAME);  
    drv_major = MAJOR(dev);  
  }  

  if (ret < 0) {  
    pr_err("SKEL_DRV: cant't get major %d\n", drv_major);  
  }  
  else {  
    pr_info("SKEL_DRV: char driver major number is %d\n", drv_major);  
  }  

  kthread_tsk = kthread_run(my_kthread, NULL, "skel kthread");  
  if (IS_ERR(kthread_tsk)) {  
    pr_err("SKEL_DRV: kthread_run failed\n");  
  }  
  else {  
    pr_info("kthread_main pid:%d\n", kthread_tsk->pid);  
  }  

  return 0;  
}  
  
static void skel_exit(void)  
{  
  dev_t dev = 0;  

  pr_info("%s\n", __FUNCTION__);  

  kthread_stop(kthread_tsk);  

  dev = MKDEV(drv_major, drv_minor);  
  unregister_chrdev_region(dev, drv_nr_devs);  
}  
  
module_init(skel_init);  
module_exit(skel_exit);  