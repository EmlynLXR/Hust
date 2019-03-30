#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h> 
#include <linux/uaccess.h>
#include <linux/fs.h>//file_operations
#include <linux/types.h> //size_t
#include <asm/uaccess.h> //copy_to_user, copy_from_user



int device_id;
int Device_open = 0;
char buff[1024];
int init_module(void);
void cleanup_module(void);
int device_open(struct inode *, struct file *);
int device_release(struct inode *, struct file *);
ssize_t device_read(struct file *, char *, size_t, loff_t *);
ssize_t device_write(struct file *, const char *, size_t, loff_t *);

struct file_operations fops = {
 .read = device_read,
 .write = device_write,
 .open = device_open,
 .release = device_release
};

//注册
int init_module(void)
{
	
	int ret = register_chrdev(0,"mydev",&fops);
printk("begin to init_module\n");	
	if(ret<0)
	{
		printk("Failed to init\n");
		return -1;
	}
	printk("ID:%d\n",ret);
	device_id = ret;
	return 0;
}
//卸载
void cleanup_module(void)
{
	printk("begin to cleanup_module\n");
	unregister_chrdev(device_id,"mydev");
	printk("cleanup success\n");
}
//打开
int device_open (struct inode *inode, struct file *file)
{
	printk("begin to device_open\n");
	if(Device_open)
		return -EBUSY;	
	Device_open++;
	printk("open success\n");
 	try_module_get(THIS_MODULE);
	return 0;
}
//关闭
int device_release(struct inode *inode, struct file *file)
{
	printk("begin to device_release\n");
	Device_open--;
        module_put(THIS_MODULE);
	return 0;
}
//读
ssize_t device_read(struct file *file, char *str, size_t len, loff_t * loff)
{
	
	int ret = copy_to_user(str,buff,len);
printk("begin to device_read\n");
	if(ret<0)
	{
		printk("Failed to device_read\n");
		return -1;
	}
	printk("device_read success\n");
	return ret;
}
//写
ssize_t device_write(struct file *file, const char *str, size_t len, loff_t *loff)
{
	
	int ret = copy_from_user(buff,str,len);
printk("begin to device_write\n");
	if(ret<0)
	{
		printk("Failed to device_write\n");
		return -1;
	}
	
	printk("device_write success\n");
	return ret;

}
MODULE_LICENSE("GPL");

