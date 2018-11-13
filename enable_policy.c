// this file is part of the kernel
#include "sys_calls_utils.h"

/* system call number 243
Description
Enable the enforcement of the policy for process with PID=pid only if the password is indeed the
administrator’s password. The privileged level of this process should be set to the default level.
The forbidden activities log of the process will last up to size forbidden_activity_info objects. You
can assume that this process will not make more than size violations since the last time
get_process_log was invoked successfully with his pid as a parameter (get_process_log is a
system call that will be discussed below).
Note : the administrator’s password is 234123.

Return values
	● On success: return 0.
	● On failure: return -1
		o If pid<0 errno should contain ESRCH
		o If no such process exists errno should contain ESRCH
		o If password is incorrect errno should contain EINVAL
		o If the policy feature is already on for this process, errno should contain EINVAL .
		o If size<0 errno should contain EINVAL
		o On memory allocation failure errno should contain ENOMEM
		o On any other failure errno should contain EINVAL
*/

int sys_enable_policy (pid_t pid ,int size, int password) {
	_CHECK_PID(pid);  		// check if pid >= 0
	_PID_EXISTS(pid);		// check if pid exists in hash table
	_CHECK_PASSWORD(password); // check if password is 234123
	task_t * p = find_task_by_pid(pid);
	if (p->entry_policy == true || size < 0) {
		return _EINVAL;
	}
	p->entry_policy = true;
	p->num_of_violations = 0;
	p->max_violations = size;
	return 0;
}