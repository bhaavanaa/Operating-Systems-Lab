#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define BS 50

int main()
{
    int fd[2];
    int fd1[2];
    pid_t cpid;
    char wm[BS]="IIITDMKancheepuram";
    char wm1[BS]="IIITDMKancheepura ";
    char rm[BS];
    char rm1[BS];
    int s=pipe(fd);
    int s1=pipe(fd1);

    if (s == -1)
    {
        printf("error\n");
        exit(0);
    }

    if (s1 == -1)
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
        close(fd[1]);/* Close unused write end */
        close(fd1[1]);
        read(fd[0], rm, BS) ;//reading  from read end of fd into rm
        read(fd1[0], rm1, BS) ;
		if(strcmp(rm, rm1)==0)
            printf("the strings are same\n");
        else
            printf("the strings are different\n");
        close(fd[0]);
        close(fd1[0]);
    } 
    else 
    {  
        /* Parent writes to pipe */
        close(fd[0]);  /* Close unused read end */
        close(fd1[0]);
        write(fd[1], wm, strlen(wm)+1);//writes from wm into fd1    
        write(fd1[1], wm1, strlen(wm1)+1);
        close(fd[1]);//close write end of fd..fd[1]
        close(fd1[1]);
    }
    return(0);
}
