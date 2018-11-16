// this file is part of the kernel
#include "sys_calls_utils.h"

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

int sys_get_process_log(pid_t pid , int size , forbidden_activity_info * user_mem) {
	_CHECK_PID(pid);  		// check if pid >= 0
	_PID_EXISTS(pid);		// check if pid exists in hash table
	task_t * p = find_task_by_pid(pid);
	if (size > p->num_of_violations || p->entry_policy == false) {
		return _EINVAL;
	}

	if (copy_forbidden_activity_list_to_user(p->_log_list , user_mem , size) != 0) { 
		return _EINVAL;
	}
	p->num_of_violations -= size;
	return 0;
}