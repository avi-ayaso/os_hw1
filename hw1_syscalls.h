

struct forbidden_activity_info {
	int syscall_req_level;	# the threshold of the sys call
	int proc_level;			# the process privilege level at the time
	int time;				# the time
}