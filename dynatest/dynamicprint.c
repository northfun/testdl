/*
 * =====================================================================================
 *
 *       Filename:  testos.c
 *
 *    Description:  测试动态链接库
 *
 *        Version:  1.0
 *        Created:  10/09/2016 02:50:37 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  north (n), fanbeishuang@126.com
 *        Company:  uyegame.com
 *
 * =====================================================================================
 */


#include	<stdbool.h>
#include	<stdio.h>
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  dynamicPrint
 *  Description:  尝试修改它
 * =====================================================================================
 */

    bool
dynamicPrint (int argc, char *argv[]  )
{
    if( argc == 0){
        printf("I just do some print, cause no cmd to me(- -~). v1.3\n");
        return false;
    }else{
        int i;
        printf("I'm dynamicPrint func. v1.3\n");
        for(i=argc-1; i >= 0; i--){
            printf("argv[%d]=%s\n", i, argv[i]);
        }
        return true;
    }
}		/* -----  end of function dynamicPrint  ----- */
