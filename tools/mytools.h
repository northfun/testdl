/*
 * =====================================================================================
 *
 *       Filename:  mytools.h
 *
 *    Description:  some define
 *
 *        Version:  1.0
 *        Created:  10/11/2016 02:20:15 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  north (n), fanbeishuang@126.com
 *        Company:  uyegame.com
 *
 * =====================================================================================
 */

#include	"csapp.h"
#include    <stdlib.h>
#include    <stdio.h>
#include    <stdarg.h>
#include    <dlfcn.h>
#include    <string.h>
#include    <sys/types.h>
#include    <sys/wait.h>
#include    <sys/ptrace.h>
//#include    <sys/user.h> // for GDB only
#include    <unistd.h>

typedef unsigned long  DWORD;
typedef unsigned int WORD;

struct my_user_regs { 
    DWORD r15; 
    DWORD r14; 
    DWORD r13; 
    DWORD r12; 
    DWORD rbp; 
    DWORD rbx; 
    DWORD r11; 
    DWORD r10; 
    DWORD r9; 
    DWORD r8;
    DWORD rax; 
    DWORD rcx; 
    DWORD rdx; 
    DWORD rsi; 
    DWORD rdi; 
    DWORD orig_rax; 
    DWORD rip; 
    DWORD cs; 
    DWORD eflags; 
    DWORD rsp; 
    DWORD ss; 
    DWORD fs_base; 
    DWORD gs_base; 
    DWORD ds; 
    DWORD es; 
    DWORD fs; 
    DWORD gs; 
};

DWORD procDLAddr (pid_t pid, const char *, const char*);
void spliteTo2DWORDs (char *str, char *spl, DWORD res[2]);
void peekText(pid_t, DWORD, char *, size_t);
void pokeText(pid_t, DWORD, char *, size_t);
void printSize();
void echo(int connfd);

