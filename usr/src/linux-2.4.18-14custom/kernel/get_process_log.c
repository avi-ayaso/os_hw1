// this file is part of the kernel

#include <linux/slab.h>
#include <linux/sched.h>

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
	if (pid < 0) return -3
	if (find_task_by_pid(pid) == NULL ) return -3;
	task_t * p = find_task_by_pid(pid);
	if (size > p->num_of_violations || p->entry_policy == 0) {
		return -22;
	}
	return copy_forbidden_activity_list_to_user(p , user_mem , size);
}