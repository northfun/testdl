/*
 * =====================================================================================
 *
 *       Filename:  changeDlopen.c
 *
 *    Description:  升级程序 参考(linux进程热升级)
 *
 *        Version:  1.0
 *        Created:  10/11/2016 10:42:39 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  north (n), fanbeishuang@126.com
 *        Company:  uyegame.com
 *
 * =====================================================================================
 */

#include	"mytools.h"

pid_t task_pid;

    int
main ( int argc, char *argv[] )
{
    if (argc <= 0){
        exit(1);
    }

    task_pid = strtol(argv[0], NULL, 10);

    pid_t my_pid;
    int status;
    char *error;
    DWORD dlopen_entry, dlopen_offset, addr;

    my_pid = getpid();

    addr = procDLAddr(my_pid, "r-xp", "libc-");

    dlopen_entry = (unsigned long)dlsym(NULL, "__libc_dlopen_mode"); 
    if ((error = dlerror()) != NULL) { 
        printf("Unable to locate dlopen address.%s\n", error); 
        return -1; 
    } 
    dlopen_offset = dlopen_entry - addr; // _libc_dlopen_mode 函数在 libc 中的偏移量
    printf("dlopen_entry:%lu\n", dlopen_offset); 

    //t_libc = begin of libc of target process T; /* get from maps file of target T */ 
    //if (!t_libc) { 
    //    printf("Unable to locate begin of target's libc.\n"); 
    //    return -1; 
    //} 
    //dlopen_entry = t_libc + dlopen_offset; 

    char sbuf1[512], sbuf2[512]; 
    struct my_user_regs regs, saved_regs, aregs; 

    if (ptrace(PTRACE_ATTACH, task_pid, NULL, NULL) < 0) 
        return -1; 

    waitpid(task_pid, &status, 0); 
    ptrace(PTRACE_GETREGS, task_pid, NULL, &regs); 

    peekText(task_pid, regs.rsp + 512, sbuf1, sizeof(sbuf1)); 
    peekText(task_pid, regs.rsp, sbuf2, sizeof(sbuf2));

    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
