// this file is part of the kernel

#include <linux/slab.h>
#include <linux/sched.h>

/* 
system call number 245
int set_process_capabilities(pid_t pid,int new_level,int password)

Description
Set the privilege level of the process with PID=pid to new_level, if the password is correct. The
log of the process with PID=pid should not be affected at all.
Note : the password is "234123" as mentioned above.

Return values
	● On success: return 0.
	● On failure: return -1
		o If pid<0 errno should contain ESRCH
		o If no such process exists errno should contain ESRCH
		o If new_level is not 0,1,2 errno should contain EINVAL
		o If the password is incorrect errno should contain EINVAL
		o If the policy feature is off for this process, errno should contain EINVAL .
		o On memory allocation failure errno should contain ENOMEM
		o On any other failure errno should contain EINVAL
*/


int sys_set_process_capabilities (pid_t pid ,int new_level, int password) {
	if (pid < 0) {
		return -ESRCH;
	}
	if (find_task_by_pid(pid) == NULL ) {
		return -ESRCH;
	}
	if (new_level < 0 || new_level > 2 ) {
		return -EINVAL;
	}
	if (password != 234123) {
		return -EINVAL;
	}
	task_t * p = find_task_by_pid(pid);
	if (p->entry_policy == 0) {
		return -EINVAL;
	}
	p->priv_level = new_level;
	return 0;
}
