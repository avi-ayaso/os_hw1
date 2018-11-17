#ifndef _SYS_CALLS_UTILS_H_
#define _SYS_CALLS_UTILS_H_

#include <asm/uaccess.h>
#include <linux/slab.h>



int add_forbidden_activity_to_log(task_t * _current , int _syscall_req_level) {
    int num_of_violations = _current->num_of_violations;
    int max_violations = _current->max_violations;
    if (num_of_violations == max_violations) return -22;
    _current->_log[num_of_violations].syscall_req_level = _syscall_req_level;
    _current->_log[num_of_violations].proc_level = _current->priv_level;
    _current->_log[num_of_violations].time = (int)jiffies;
    _current->num_of_violations++;
    return -22;
}


#endif /* _SYS_CALLS_UTILS_H_ */
