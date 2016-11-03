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

#include	"/home/fbs/go/src/test/ctest/tools/mytools.h"

pid_t task_pid;

    int
main ( int argc, char *argv[] )
{
    if (argc <= 0){
        printf("lose task_pid\n");
        exit(1);
    }

    task_pid = strtol(argv[0], NULL, 10);

    pid_t my_pid;
    int status;
    char *error;
    DWORD dlopen_entry, dlopen_offset, my_libc, t_libc;

    // my_pid entry addr
    my_pid = getpid();
    my_libc = procDLAddr(my_pid, "r-xp", "libc-");

    dlopen_entry = (unsigned long)dlsym(NULL, "__libc_dlopen_mode"); 
    if ((error = dlerror()) != NULL) { 
        printf("Unable to locate dlopen address.%s\n", error); 
        return -1; 
    } 
    dlopen_offset = dlopen_entry - my_libc; // _libc_dlopen_mode 函数在 libc 中的偏移量
    printf("dlopen_offset:%lu\n", dlopen_offset); 

    // task_pid entry addr
    t_libc = procDLAddr(task_pid, "r-xp", "libc-"); /* get from maps file of target T */ 
    if (!t_libc) { 
        printf("Unable to locate begin of target's libc.\n"); 
        return -1; 
    } 
    dlopen_entry = t_libc + dlopen_offset; 
    printf("dlopen_entry:%lu\n", dlopen_entry); 

    // attack目标进程

    char sbuf1[512], sbuf2[512];  // why 512(64*8)?
    struct my_user_regs regs, saved_regs, aregs;

    if (ptrace(PTRACE_ATTACH, task_pid, NULL, NULL) < 0) 
        return -1; 

    waitpid(task_pid, &status, 0); 
    ptrace(PTRACE_GETREGS, task_pid, NULL, &regs); 

    peekText(task_pid, regs.rsp + 512, sbuf1, sizeof(sbuf1));  // who can explain it , why add 512 ?
    peekText(task_pid, regs.rsp, sbuf2, sizeof(sbuf2));

    // 触发目标进程执行dlopen

    DWORD z=0;
    char filename_new_so[30]; 
    strcpy(filename_new_so,"./mylib/dynamicprint.so");

    pokeText(task_pid, regs.rsp, (char *)&z, sizeof(z));  // poke_text?
    pokeText(task_pid, regs.rsp + 512, filename_new_so, strlen(filename_new_so) + 1); // poke_text?

    memcpy(&saved_regs, &regs, sizeof(regs)); 

    regs.rdi = regs.rsp + 512; 
    regs.rsi = RTLD_NOW|RTLD_GLOBAL|RTLD_NODELETE; 
    regs.rip = dlopen_entry + 2; 

    ptrace(PTRACE_SETREGS, task_pid, NULL, &regs); 
    ptrace(PTRACE_CONT, task_pid, NULL, NULL); 

    waitpid(task_pid, &status, 0);

    // 恢复目标进程线程
    ptrace(PTRACE_SETREGS, task_pid, 0, &saved_regs); 

    pokeText(task_pid, saved_regs.rsp + 512, sbuf1, sizeof(sbuf1)); 
    pokeText(task_pid, saved_regs.rsp, sbuf2, sizeof(sbuf2)); 

    ptrace(PTRACE_DETACH, task_pid, NULL, NULL);

    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
