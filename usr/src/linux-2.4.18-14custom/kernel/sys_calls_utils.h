#ifndef _SYS_CALLS_UTILS_H_
#define _SYS_CALLS_UTILS_H_

#include <asm/uaccess.h>
#include <linux/slab.h>


// output will be in the given pointer
int copy_forbidden_activity_list_to_user(task_t * process , forbidden_activity_info * ret_val , int size) {
    unsigned long status = copy_to_user((void *)ret_val, (void *)(process->_log), sizeof(forbidden_activity_info)*size);
    if (status > 0) return -22;
    int index=0;
    int i=0;
    for (i=size;i<process->num_of_violations;++i,++index){
        process->_log[index] = process->_log[i];
    }
    process->num_of_violations = index;
    return 0;
}

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
