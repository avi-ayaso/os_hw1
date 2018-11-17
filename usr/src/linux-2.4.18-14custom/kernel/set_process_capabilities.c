// this file is part of the kernel

#include <linux/slab.h>
#include <linux/sched.h>


#define _ESRCH            -3      /* No such process */
#define _ENOMEM          -12      /* Out of memory */
#define _EINVAL          -22      /* Invalid argument */


#define _PID_EXISTS(pid) { \
		if (find_task_by_pid(pid) == NULL ) {  \
            return _ESRCH; \
        } \
	}

#define _CHECK_PID(pid) { \
		if (pid < 0) { \
			return _ESRCH; \
		}  \
	}

#define _CHECK_PASSWORD(password) { \
		if (password != 234123) { \
            return _EINVAL; \
		} \
	}

// for hw1 when policy is on
#define _CHECK_LEVEL_THRESHOLD(curr_p,min_threshold) { \
        if (curr_p->entry_policy == 1) { \
            if (curr_p->priv_level < min_threshold) { \
                add_forbidden_activity_to_log(curr_p,min_threshold); \
            } \
        } \
    }

//end


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
	_CHECK_PID(pid);  		// check if pid >= 0
	_PID_EXISTS(pid);		// check if pid exists in hash table
	if (new_level < 0 || new_level > 2 ) {
		return _EINVAL;
	}
	_CHECK_PASSWORD(password); // check if password is 234123
	task_t * p = find_task_by_pid(pid);
	if (p->entry_policy == 0) {
		return _EINVAL;
	}
	p->priv_level = new_level;
	return 0;
}
