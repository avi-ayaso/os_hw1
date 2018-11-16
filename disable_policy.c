// this file is part of the kernel
#include "sys_calls_utils.h"






/* system call number 244

Description
Disable the enforcement of the policy for the process with PID=pid if the password is indeed the
administrator’s password. As mentioned before, after invoking this system call, the log of
process with PID=pid should be removed.
Note : the password is "234123" as mentioned above.

Return values
	● On success: return 0.
	● On failure: return -1
		o If pid<0 errno should contain ESRCH
		o If no such process exists errno should contain ESRCH
		o If the policy feature is already off for this process, errno should contain EINVAL .
		o If password is incorrect errno should contain EINVAL
		o On any other failure errno should contain EINVAL

\
*/
int sys_disable_policy (pid_t pid ,int password)
	_CHECK_PID(pid);  			// check if pid >= 0
	_PID_EXISTS(pid);		// check if pid exists in hash table
	task_t * p = find_task_by_pid(pid);
	if (p->entry_policy == false) {
		return _EINVAL;
	}
	_CHECK_PASSWORD(password); // check if password is 234123
	p->entry_policy = false;

	
	if (p->_log_list != NULL) {
		del_forbidden_activity_list(p->_log_list,p->num_of_violations);
		p->num_of_violations = 0;
		p->max_violations = 0;
		free(p->_log_list);
		p->_log_list = NULL;
	}

	return 0;
}


