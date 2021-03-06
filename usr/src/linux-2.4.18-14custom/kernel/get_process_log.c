// this file is part of the kernel

#include <linux/slab.h>
#include <linux/sched.h>
#include <asm/uaccess.h>



// output will be in the given pointer
static int copy_forbidden_activity_list_to_user(task_t * process , forbidden_activity_info * ret_val , int size) {
    unsigned long status = copy_to_user((void *)ret_val, (void *)(process->_log), sizeof(forbidden_activity_info)*size);
    if (status > 0) return -EINVAL;
    int index=0;
    int i=0;
    for (i=size;i<process->num_of_violations;++i,++index){
        process->_log[index] = process->_log[i];
    }
    process->num_of_violations = index;
    return 0;
}


/*
system call number 246

Description
Returns in user_mem the first records of the forbidden activities size of the process with
PID=pid. In addition, those size records should be removed from the process's forbidden
activities log.

Note :
	● You can assume that user_mem have enough space to contain the answer.
	● Read about "copy_to_user" and use it to copy data from kernel memory to user memory.

Return values
	● On success: return 0
	● On failure: return -1
		o If pid<0 errno should contain ESRCH
		o If no such process exists errno should contain ESRCH
		o If size>number of records in the log, errno should contain EINVAL and the log shouldn't be affected at all.
		o If size<0 errno should contain EINVAL
		o If the policy feature is off for this process, errno should contain EINVAL .
		o On any other failure errno should contain EINVAL

*/

int sys_get_process_log(pid_t pid , int size , forbidden_activity_info* user_mem) {
	if (pid < 0) {
		return -ESRCH;
	}
	if (find_task_by_pid(pid) == NULL ) {
		return -ESRCH;
	}
	task_t * p = find_task_by_pid(pid);
	if (size > p->num_of_violations || p->entry_policy == 0) {
		return -EINVAL;
	}
	return copy_forbidden_activity_list_to_user(p , user_mem , size);
}
