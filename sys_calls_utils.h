#ifndef _SYS_CALLS_UTILS_H_
#define _SYS_CALLS_UTILS_H_

    #include <linux/sched.h>
    #include <asm/uaccess.h>
    #include <linux/slab.h>

#include <errno.h>
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
                add_forbidden_activity_to_log(curr_p->_log,min_threshold,curr_p->priv_level); \
            } \
        } \
    }
	
//end


// for hw1 list functions
// used inside disable_policy and sys_calls
inline void del_forbidden_activity_list(log_list * _log_head, int counter)
{
    if (_log_head == NULL || list_empty(&(_log_head->_list_node))) return;
    int index = 0;
	struct list_head * iter; // blue part
    //forbidden_activity_info * tmp;
    log_list * tmp; // yellow part pointer
/**
    * list_for_each	-	iterate over a list
    * @pos:	the &struct list_head to use as a loop cursor.
    * @head:	the head for your list.
    #define list_for_each(pos, head)
 */
    list_for_each(iter,&(_log_head->_list_node))          //Traversing the list
    {
        if (index == counter) return;
/**
    * list_entry - get the struct for this entry
    * @ptr:	the &struct list_head pointer.
    * @type:	the type of the struct this is embedded in.
    * @member:	the name of the list_head within the struct.
    #define list_entry(ptr, type, member)
 */
            tmp = list_entry(iter,log_list,_list_node);  

/**
    * list_del - deletes entry from list.      
    * @entry: the element to delete from the list.
    * Note: list_empty() on entry does not return true after this, the entry is
    * in an undefined state.
     static inline void list_del(struct list_head *entry)
 */
            list_del(iter);	// remove my struct from list
            kfree(tmp);		// delete my struct
            
    }
    return;
}

// output will be in the given pointer
inline int copy_forbidden_activity_list_to_user(log_list * _log_head , forbidden_activity_info * ret_val , int size) {
	int index = 0;
	log_list * tmp;
	unsigned long status = 0;
    struct list_head * iter;
	list_for_each(iter,&(_log_head->_list_node)) {          //Traversing the list
		if (index == size) {
            break;
        }				// end of loop
		// 				address ,  		my struct_name		field_name
        tmp = list_entry(iter,log_list,_list_node);  
        forbidden_activity_info * _tmp2 = &(tmp->_forbidden_activity);
		status = copy_to_user((void *)ret_val + index*(sizeof(*_tmp2)), (void *)(_tmp2), sizeof(*_tmp2));
		if (status > 0) {
            kfree(ret_val);
            return _EINVAL; // number of bytes weren't copied
        }
		index++;
	}

    del_forbidden_activity_list(_log_head,size);

	return 0;	
}	


inline int add_forbidden_activity_to_log(log_list * _log_head , int _syscall_req_level , int _proc_level) {
    log_list * tmp = (log_list *) kmalloc (sizeof(log_list),GFP_KERNEL);
    if (tmp == NULL) return _ENOMEM;
    tmp->_forbidden_activity.syscall_req_level = _syscall_req_level;
    tmp->_forbidden_activity.proc_level = _proc_level;
    tmp->_forbidden_activity.time = jiffies ;
    list_add_tail(&(tmp->_list_node) , &(_log_head->_list_node));
    return _EINVAL;
}
#endif /* _SYS_CALLS_UTILS_H_ */
