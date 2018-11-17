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
	_CHECK_PID(pid);  		// check if pid >= 0
	_PID_EXISTS(pid);		// check if pid exists in hash table
	task_t * p = find_task_by_pid(pid);
	if (size > p->num_of_violations || p->entry_policy == 0) {
		return _EINVAL;
	}
	return copy_forbidden_activity_list_to_user(p , user_mem , size);
}