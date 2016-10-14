/*
 * =====================================================================================
 *
 *       Filename:  mytools.c
 *
 *    Description:  一些工具
 *
 *        Version:  1.0
 *        Created:  10/11/2016 02:17:38 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  north (n), fanbeishuang@126.com
 *        Company:  uyegame.com
 *
 * =====================================================================================
 */


#include	"mytools.h"

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  spliteTo2DWORDs
 *  Description:  分割字符串为两个DWORD
 * =====================================================================================
 */
    void
spliteTo2DWORDs ( char *str, char *spl, DWORD res[2] ) 
{
    char *pindex, resstr[20];
    int index, strlength;
    if (str == NULL || spl == NULL) {
        return ;         
    }

    if ((strlength = strlen(str) )> 32){
        return ;
    }
    if ((pindex = strstr(str, spl)) != NULL){
        index = pindex - str;
        if (index > 16 || strlength - index > 16){
            // 8字节限制
            return;
        }
        strncpy(resstr, str, index);
        res[0] = strtoll(resstr, NULL, 16);
        memset(resstr, 0, sizeof(resstr));
        strncpy( resstr, &str[index+1], strlength - index);
        res[1] = strtol(resstr, NULL, 16);
    }
    return ; 
}       /* -----  end of function spliteTo2DWORDs  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  procDLAddr
 *  Description:  得到dlopen地址
 * =====================================================================================
 */
    DWORD
procDLAddr (pid_t pid, const char *pstate, const char *name)
{
    char path[30], line[200], strAddr1[20], strAddr2[20];
    FILE *f; 
    DWORD addr[2] = {0, 0};
    char *pindex;
    int length;

    snprintf(path, sizeof(path), "/proc/%d/maps", pid); 

    if ((f = fopen(path, "r")) == NULL) 
        return 0;  

    while(fgets(line, sizeof(line), f) != NULL) {
        if (strstr(line, pstate) && strstr(line, name)){
            if ((pindex = strstr(line, " ")) != NULL){
                *pindex = '\0';
                spliteTo2DWORDs(line, "-", addr);
                //printf("==========%s,%lu,%lu\n", line, addr[0], addr[1]);
                break;
            }
        }   

        memset(line, 0, sizeof(line)); 
    }   

    fclose(f);
    // 暂时不管errno了 
    return addr[0];
}       /* -----  end of function procDLAddr ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  printSize
 *  Description:  打印类型字节
 * =====================================================================================
 */
    void
printSize (  )
{
    // 4   8   8   8
    printf("int:%d\nlong int:%d\nusigned long:%d\nlong long:%d\n", sizeof(int), sizeof(long int), 
            sizeof(unsigned long), sizeof(long long));
    return ;
}		/* -----  end of function printSize  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  peekText
 *  Description:  "对ptrace(PTRACE_PEEKTEXT...)做封装，支持多字节的数据块的读取"
 * =====================================================================================
 */
    void
peekText (pid_t pid, DWORD addr, char *to, size_t size)
{
    size_t index = 0;
    while(index < size){
        ptrace(PTRACE_PEEKTEXT, pid, &addr, &to[index]);
        ++index;
    }
    return ;
}		/* -----  end of function peekText  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  pokeText
 *  Description:  多字节数据块的写入
 * =====================================================================================
 */
    void
pokeText (pid_t pid, DWORD addr, char *to, size_t size)
{
    return ;
}		/* -----  end of function pokeText  ----- */
