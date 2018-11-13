#ifndef _SYS_CALLS_UTILS_H_
#define _SYS_CALLS_UTILS_H_

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



#endif /* _SYS_CALLS_UTILS_H_ */