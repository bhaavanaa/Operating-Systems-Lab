#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define BS 200

int main(int argc, char*argv[])
{
    int fd[2];
    pid_t cpid;
    char wm[BS];
    char rm[1];
    int s=pipe(fd);

    FILE *fptr1;
    char file_name[100];
    strcpy(file_name, argv[1]); 

    fptr1=fopen(file_name, "r");
    
    char c[1];  

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

    int characters=0;
    int words=0;
    int lines=0;
    int sentences=0;

    if (cpid == 0) 
    {    // Child reads from pipe 
        close(fd[1]); // Close unused write end 
        while(read(fd[0], rm, 1)>0 && rm[0]!=EOF) //reading  from read end of fd into rm
        {
            //printf("%s",rm);
            characters=characters+1;
            if(strcmp(rm," ")==0 || strcmp(rm,"\n")==0)
            {
                words=words+1;
            }
            if(strcmp(rm,"\n")==0)
            {
                lines=lines+1;
            }
            if(strcmp(rm,".")==0)
            {
                sentences=sentences+1;
            }
        }
        printf("sentences= %d\n", sentences);
        printf("lines= %d\n", lines);
        printf("words= %d\n", words);
        printf("characters= %d\n", characters);
        close(fd[0]);
    } 
    else 
    { 
        //Parent writes to pipe 
        close(fd[0]);  //Close unused read end 
        while(c[0]!=EOF)    
        {
            c[0]=fgetc(fptr1);
            write(fd[1], c,1);
            //printf("%c",c[0]);
            //c[0]=fgetc(fptr1);
        }
        //write(fd[1], wm, strlen(wm)+1);//writes from wm into fd1
        fclose(fptr1);
        close(fd[1]);//close write end of fd..fd[1]
    }
    return(0);
}
