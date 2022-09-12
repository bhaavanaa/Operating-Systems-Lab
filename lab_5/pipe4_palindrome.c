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
    char wm[BS]="malayalam";
    char rm[BS];
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
        read(fd[0], rm, BS); //reading  from read end of fd into rm
        int n=strlen(rm);
        //printf("%d\n", n);
        char rev[n];
        int j=n-1;
        int i;
		for(i=0; i<n; i++)
        {
            rev[i]=rm[j];
            printf("%c %c\n", rev[i], rm[j]);
            j--;
        }
        rev[i]='\0';
        printf("The reversed string: %s\n", rev);
        if(strcmp(rev, rm)==0)
            printf("the string is a palindrome\n");
        else        
            printf("the string is not a palindrome\n");
        close(fd[0]);
    }
    else
    {
        /* Parent writes to pipe */
        close(fd[0]);  /* Close unused read end */
        write(fd[1],wm, strlen(wm)+1);//writes from wm into fd1
        close(fd[1]);//close write end of fd..fd[1]
    }
    return(0);
}
