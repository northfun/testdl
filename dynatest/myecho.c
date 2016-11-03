/*
 * =====================================================================================
 *
 *       Filename:  myecho.c
 *
 *    Description:  Just print envps
 *
 *        Version:  1.0
 *        Created:  10/09/2016 11:41:20 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  north (n), fanbeishuang@126.com
 *        Company:  uyegame.com
 *
 * =====================================================================================
 */

#include<stdio.h>
#include	<stdlib.h>
#include	<dlfcn.h>
#include	<unistd.h>
#include	"testos.h"
#include	"csapp.h"

//typedef void (*sighandler_t)(int);
//sighandler_t signal(int, sighandler_t);

void *handle;
bool (*dynprintFunc)(int, char *[]);
int g_argc;
char **g_argv;
char **g_envp;

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  loadFunc
 *  Description:  加载so函数
 * =====================================================================================
 */
    void
loadFunc ( int argc, char *argv[], char *envp[])
{
    // dynamicPrint(argc, argv);
    
    char *error;
    bool ok;

    if (handle != NULL && dlclose(handle) < 0){
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }

    handle = dlopen("./mylib/dynamicprint.so", RTLD_LAZY);
    if (!handle){
        fprintf(stderr, "%s\n", dlerror());
        printf("%s\n", dlerror());
        exit(1);
    }

    dynprintFunc = (bool (*)(int, char *[]))dlsym(handle, "dynamicPrint");
    if ((error = dlerror()) != NULL){
        fprintf(stderr, "%s\n", error);
        printf("%s\n", dlerror());
        exit(1);
    }

    ok = dynprintFunc(argc, argv);
    printf("func return %d\n", ok);

    return ;
}		/* -----  end of function loadFunc  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  signalHandler
 *  Description:  处理信号
 * =====================================================================================
 */
    void
signalHandler(int sig)
{
    switch (sig){
        case SIGINT:
            loadFunc(g_argc, g_argv, g_envp);
            break;
        case SIGHUP:
            dynprintFunc(0, NULL);
            break;
    }
    printf("get sig %d, INT:%d,HUP:%d\n", sig, SIGINT, SIGHUP);
    return ;
}		/* -----  end of function signalHandler(int sig)  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  nothing to say - -
 * =====================================================================================
 */
    int 
main(int argc, char *argv[], char *envp[])
{
    printf("1 current working directory: %s\n", getcwd(NULL, 0));
    chdir("/home/fbs/go/src/test/ctest");
    printf("2 current working directory: %s\n", getcwd(NULL, 0));

    g_argc = argc;
    g_argv = argv;
    g_envp = envp;

    if (signal(SIGINT, signalHandler) == SIG_ERR){
        unix_error("signal error");
    }
    if (signal(SIGHUP, signalHandler) == SIG_ERR){
        unix_error("signal error");
    }

    while(true){
    }

    return 0;
}
