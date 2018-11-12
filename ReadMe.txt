
adding a service routine to the kernel

1.	Add a service routine "my_system_call"
	to implement a new system call we first create its service routine "my_system_call.c".
	and then we save them in the next directory (inside the VM):
		/usr/src/linux-2.4.18-14custom/kernel

2.	Add the object "my_system_call.o" to the Makefile
	here:
		/usr/src/linux-2.4.18-14custom/kernel/Makefile
	under obj-y.
	
3.	Add the sys call to the interupt handler
	open:
		/arch/i386/kernel/entry.S
	and add the sys call to the first empty sys call in the sys call table at the end of the file
	the new sys calls.

4.	MAKE A SNAPSHOT!!!!

5.	compile the kernel
	
				cd /usr/src/linux-2.4.18-14custom
				make bzImage
				cd arch/i386/boot
				cp bzImage /boot/vmlinuz-2.4.18-14custom
				reboot
				
#### if the system is fucked up. use the snapshot!

adding the sys calls' wrappers

1.	implementing all of the wrappers in "hw1_syscalls.h" file.
	each wrapper is based on this template:

				#include <errno.h>

				int my_system_call(int p1, char * p2, int p3) {

					unsigned int res ;
					
					__asm__ volatile (
						"int $0x80;"
						: "=a" (res)
						: "0" ("insert_here_the_sys_call_number") , "b" (p1) , "c" (p2), "d" (p3)
						: "memory"
					);
					
					if (res < 0) {
						errno= -res ;
						res= -1 ;
					}
					
					return (int)res ;
				}
	
	then we save this file on the VM home folder (~).
	
	we can then compile the test (.c file which includes the above header) on the VM home folder.
	
2.	compile and run the test
	
	when we have hw1_syscalls.h and the test.c on the home folder,
	we can then compile our program using the next command:
				
				gcc test.c
				./a.out
