/*
 * =====================================================================================
 *
 *       Filename:  s.c
 *
 *    Description:  use as server,to test some defferent between threads vs progresses
 *
 *        Version:  1.0
 *        Created:  10/31/2016 02:47:26 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  north (n), fanbeishuang@126.com
 *        Company:  uyegame.com
 *
 * =====================================================================================
 */

#include	"../tools/csapp.h"
#include	"../tools/mytools.h"

    int
main ( int argc, char *argv[] )
{
    int listenfd, connfd, port, countForkTimes;
    WORD clientlen;
    struct sockaddr_in clientaddr;
    struct hostent *hp;
    char *haddrp;
    if (argc != 2){
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }
    port = atoi(argv[1]);
    listenfd = Open_listenfd(port);
   
    while(1){
        clientlen = sizeof(clientaddr);
        connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
        if (Fork() == 0){
            hp = Gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr,
                    sizeof(clientaddr.sin_addr.s_addr), AF_INET);
            haddrp = inet_ntoa(clientaddr.sin_addr);
            printf("server connected to %s (%s)\n", hp->h_name, haddrp);
            
            echo(connfd);
            printf("%s broken pipe\n", hp->h_name);
            Close(connfd);
            exit(1);
        }else{
            countForkTimes++;
            printf("fork count:%d\n", countForkTimes);
        }
    }

    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
