// this file is part of the kernel
#include <linux/slab.h>
#include <linux/sched.h>




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
int sys_disable_policy (pid_t pid ,int password) {
	if (pid < 0) return -ESRCH;
	if (find_task_by_pid(pid) == NULL ) return -ESRCH;
	task_t * p = find_task_by_pid(pid);
	if (p->entry_policy == 0) {
		return -EINVAL;
	}
	if (password != 234123) return -EINVAL;
	p->entry_policy = 0;

	
	if (p->_log != NULL) {
		p->num_of_violations = 0;
		p->max_violations = 0;
		kfree(p->_log);
		p->_log = NULL;
	}
	printk("\nDISABLE POLICY SUCCESS\n");
	return 0;
}


