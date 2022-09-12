//Generate output of ls in capitals

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include<ctype.h>
#define BS 30

int main()
{
    int fd[2];
    pid_t cpid;
    char wm[BS]="IIITDMKancheepuram";
    char buf[BS];
    int s=pipe(fd);

    if (s == -1) 
    {
        printf("error\n");
        exit(0);
    }

    cpid = fork();
    if (cpid == -1) 
    {
        printf("error\n");
        exit(0);
    }

    if (cpid == 0) 
    {    /* Child reads from pipe */
        close(fd[1]); /* Close unused write end */
        int nb;
        while((nb=read(fd[0],buf, BS))>0) //reads upto BS number of bytes from fd into buf
        {
		    for(int i=0;i<nb;i++)
		    {
                if(buf[i]>='a' && buf[i]<='z')
                {
                    buf[i]=toupper(buf[i]);
                }   
                else
                {
                    buf[i]=tolower(buf[i]);
                }
                printf("%c",buf[i]);
            }
        //nb=0;
        }
        close(fd[0]);
    } 
    else 
    { 
        close(fd[0]);//closing read end of pipe
        write(fd[1], wm, strlen(wm));
        close(fd[1]);
    }
    return(0);
}
