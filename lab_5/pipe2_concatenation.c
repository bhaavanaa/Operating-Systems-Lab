#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define BS 20

int main()
{
    int fd[2];
    pid_t cpid;
    char wm[BS]="IIITDMKancheepuram";
    char wm1[BS]="Students";
    char rm[BS+BS];
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
        close(fd[1]);/* Close unused write end */
        read(fd[0], rm, BS+BS) ;//reading  from read end of fd into rm
		printf("%s",rm);
        close(fd[0]);
    } 
    else 
    {  
        /* Parent writes to pipe */
        close(fd[0]);  /* Close unused read end */
        write(fd[1], wm, strlen(wm));//writes from wm into fd1
        write(fd[1], wm1, strlen(wm1)+1);
        close(fd[1]);//close write end of fd..fd[1]
    }
    return(0);
}