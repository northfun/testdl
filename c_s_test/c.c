/*
 * =====================================================================================
 *
 *       Filename:  c.c
 *
 *    Description:  client
 *
 *        Version:  1.0
 *        Created:  10/31/2016 03:33:57 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  north (n), fanbeishuang@126.com
 *        Company:  uyegame.com
 *
 * =====================================================================================
 */


#include	"../tools/mytools.h"
#include	"../tools/csapp.h"
#include <string.h>


    int
main ( int argc, char *argv[] )
{
    int clientfd, port, index, strlength;
    char *host;
    char *buf ="HelloThankYouThankYouVeryMuchHelloThankYouThankYouVeryMuchHowAreYouImFine";
    strlength = strlen(buf);

    rio_t rio;

    if (argc != 3){
        fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
        exit(0);
    }
    host = argv[1];
    port = atoi(argv[2]);

    clientfd = Open_clientfd(host, port);
    Rio_readinitb(&rio, clientfd);
    
    //while(Fgets(buf, MAXLINE, stdin) != NULL){
    while(index < strlength){
        Rio_writen(clientfd, buf+index, 1);
        //Rio_readlineb(&rio, buf, MAXLINE);
        //Fputs(buf+index, stdout);
        index++;
        Sleep(1);
    }
    printf("client say over\n");
    Close(clientfd);
    exit(0);
    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
