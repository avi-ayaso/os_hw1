#ifndef _SYS_CALLS_H_
#define _SYS_CALLS_H_

#include <errno.h>
#include <sys/types.h>

struct forbidden_activity_info {
	int syscall_req_level;	// the threshold of the sys call
	int proc_level;			// the process privilege level at the time
	int time;				// the time						 
};

/*
=== system call number 243 ===
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
int enable_policy(pid_t pid , int size , int password) { 
	// wrapper
	int res = 0;
	errno = 0;
	__asm__ (
		"int $0x80;"
		: "=a" (res)		// output should be in eax -> res
		: "0" (243) , "b" (pid) , "c" (size), "d" (password)	// eax ; ebx ; ecx ; edx
		: "memory"
	);
	if (res < 0) {
		
		// #define ESRCH            3      /* No such process */
		// #define ENOMEM          12      /* Out of memory */
		// #define EINVAL          22      /* Invalid argument */
		errno= -res ;
		res= -1 ;
	}

	return res ;
}


/*
=== system call number 244 ===
Return values
	● On success: return 0.
	● On failure: return -1
		o If pid<0 errno should contain ESRCH
		o If no such process exists errno should contain ESRCH
		o If the policy feature is already off for this process, errno should contain EINVAL .
		o If password is incorrect errno should contain EINVAL
		o On any other failure errno should contain EINVAL
*/

int disable_policy(pid_t pid , int password) {
// wrapper
	int res = 0;
	errno = 0;
	__asm__ (
		"int $0x80;"
		: "=a" (res)		// output should be in eax -> res
		: "0" (244) , "b" (pid) , "c" (password)	// eax ; ebx ; ecx
		: "memory"
	);
	if (res < 0) {
		
		// #define ESRCH            3      /* No such process */
		// #define ENOMEM          12      /* Out of memory */
		// #define EINVAL          22      /* Invalid argument */
		errno= -res ;
		res= -1 ;
	}
	return res;
}

/*
=== system call number 245 ===
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
int set_process_capabilities(pid_t pid , int new_level , int password) {
	// wrapper
	int res = 0;
	errno = 0;
	__asm__ (
		"int $0x80;"
		: "=a" (res)		// output should be in eax -> res
		: "0" (245) , "b" (pid) , "c" (new_level), "d" (password)	// eax ; ebx ; ecx ; edx
		: "memory"
	);
	if (res < 0) {
		
		// #define ESRCH            3      /* No such process */
		// #define ENOMEM          12      /* Out of memory */
		// #define EINVAL          22      /* Invalid argument */
		errno= -res ;
		res= -1 ;
	}

	return res ;
}

/*
=== system call number 246 ===
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

int get_process_log(pid_t pid , int size , struct forbidden_activity_info * user_mem) { 
	int res = 0;
	errno = 0;
	__asm__ (
		"int $0x80;"
		: "=a" (res)		// output should be in eax -> res
		: "0" (246) , "b" (pid) , "c" (size), "d" (user_mem)	// eax ; ebx ; ecx ; edx
		: "memory"
	);
	if (res < 0) {
		
		// #define ESRCH            3      /* No such process */
		// #define ENOMEM          12      /* Out of memory */
		// #define EINVAL          22      /* Invalid argument */
		errno= -res ;
		res= -1 ;
	}

	return res ;
}

#endif /* _SYS_CALLS_H_ */
