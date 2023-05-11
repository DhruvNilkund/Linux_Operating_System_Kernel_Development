#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/sched.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Dhruv Nilkund");
MODULE_DESCRIPTION("This module lists all the current task from init");


static void listProcess(struct task_struct *task)
{
    struct task_struct *task_next;
    struct list_head *list;

    list_for_each(list,&task->children)
    {
        task_next=list_entry(list,struct task_struct,sibling);

        printk(KERN_INFO "\n----------------");
        printk(KERN_INFO "\nProcess Name : %s",task_next->comm);
        // printk(KERN_INFO "\nState : %ld",task_state(task->next));
        printk(KERN_INFO "\nProcess ID : %d",task_next->pid);

        listProcess(task_next);
        
    }
}


static int __init task_lister(void)
{
    printk(KERN_INFO "Loading the Module");

    listProcess(&init_task);

    printk(KERN_INFO "Module task completed");
    return 0;
}


static void __exit byebye(void)
{
    printk(KERN_INFO "Module Removed");
}

module_init(task_lister);
module_exit(byebye);