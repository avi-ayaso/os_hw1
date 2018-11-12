system call number 246
int get_process_log(pid_t pid,int size,struct forbidden_activity_info* user_mem)

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