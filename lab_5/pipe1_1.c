//Generate output of ls in capitals

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include<ctype.h>
#define BS 20

int main()
{
    int fd[2];
    pid_t cpid;
    char wm[BS]="IIITDM";
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
            //	printf("\n%d\n",nb);
		    for(int i=0;i<nb;i++)
		    {
                buf[i]=toupper(buf[i]);
                printf("%c",buf[i]);
            }
        }
        close(fd[0]);
    } 
    else 
    { 
        close(fd[0]);//closing read end of pipe
        dup2(fd[1],1);//dup2(int oldfd,int newfd)...here 1=newfd which is file descriptor of stdout..duplicate oldfd into newfd
        //dup2 creates copy of 'oldfd' file descriptor into 'newfd'
        execlp("ls","ls",NULL);/* Parent writes to pipe */
    }
    return(0);
}
