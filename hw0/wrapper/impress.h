
#include <errno.h>

int impress(int id) { 
	int res = 0;
	__asm__ (
		"int $0x80;"
		: "=a" (res)		// output should be in eax -> res
		: "0" (247) , "b" (id)	// eax ; ebx
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

