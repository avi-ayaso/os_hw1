system call number 244
int disable_policy (pid_t pid ,int password)

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