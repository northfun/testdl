/*
 * =====================================================================================
 *
 *       Filename:  handlertest.c
 *
 *    Description:  只是个验证
 *
 *        Version:  1.0
 *        Created:  10/10/2016 10:43:42 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  north (n), fanbeishuang@126.com
 *        Company:  uyegame.com
 *
 * =====================================================================================
 */


#include	"csapp.h"

    void
handler2 (int sig  )
{
    pid_t pid;

    printf("do handler2\n");
    while((pid = waitpid(-1, NULL, 0)) > 0){
        printf("waitpid ok %d\n", (int)pid);
    }
    if (errno != ECHILD)
        unix_error("waitpid error");

    Sleep(2);
    return ;
}		/* -----  end of function handler2  ----- */


    int
main ( int argc, char *argv[] )
{
    int i, n;
    char buf[MAXBUF];

    if (signal(SIGCHLD, handler2) == SIG_ERR)
        unix_error("signal error");

    for (i = 0; i < 3; i++){
        if (Fork() == 0){
            printf("Hello from child %d\n", (int)getpid());
            Sleep(1);
            exit(0);
        }
    }

    if ((n = read(STDIN_FILENO, buf, sizeof(buf))) < 0)
        unix_error("read error");

    printf("Parent processing input \n");
    while(1);
    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
