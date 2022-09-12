#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
#include<stdlib.h>

void  parse(char *line, char **argv);
void  execute(char **argv);

int main()
{
	int r=1;
	char comt[100];
    char com[100];
    char com_copy[100];
	char c[100][100];
	int t=0;
    char  line[1024]; 
    char  *argv[64];   
	while(r==1)
	{
		int f=vfork();
		if(f<0)
			printf("fork is not possible\n");
		else if(f>0)
		{
			wait(NULL);
		}
		else if(f==0)
		{
			printf("enter your command: ");
			scanf("%s", com);
            strcpy(com_copy, com);
            parse(com, argv);
			if(strcmp(com_copy, "history")!=0)
			{
				for(int j=0; j<strlen(com_copy); j++)
				{   
					
				    c[t][j]=com_copy[j];        
				}
				t++;
				execvp(argv[0], argv);   
			}
			else
			{
				for(int j=0; j<strlen(com_copy); j++)
				{   
				    c[t][j]=com_copy[j];        
				}
				t++;
				for(int i=0; i<t; i++)
				{
				    for(int g=0; g<strlen(c[i]); g++)
				    {
					    printf("%c",c[i][g]);
					}
					printf("\n");
				}
		    }
		    exit(0);
			
		}
		else
		{
			printf("failed fork\n");
		}
		//r='y';
		printf("Do you want to continue: ");
			scanf("%d", &r);
		
	}
	return(0);
}

void  parse(char *line, char **argv)
{
     while (*line != '\0') {       /* if not the end of line ....... */ 
          while (*line == ' ' || *line == '\t' || *line == '\n')
               *line++ = '\0';     /* replace white spaces with 0    */
          *argv++ = line;          /* save the argument position     */
          while (*line != '\0' && *line != ' ' && 
                 *line != '\t' && *line != '\n') 
               line++;             /* skip the argument until ...    */
     }
     *argv = '\0';                 /* mark the end of argument list  */
}

//void  execute(char **argv)
//{
  //   pid_t  pid;
  //   int    status;

    // if ((pid = fork()) < 0) {     /* fork a child process           */
    //      printf("*** ERROR: forking child process failed\n");
     //     exit(1);
     //}
     //else if (pid == 0) {          /* for the child process:         */
      //    if (execvp(*argv, argv) < 0) {     /* execute the command  */
        //       printf("*** ERROR: exec failed\n");
          //     exit(1);
          //}
     //}
     //else {                                  /* for the parent:      */
       //   while (wait(&status) != pid)       /* wait for completion  */
         //      ;
     //}
//}

//void  main(void)
//{
//     char  line[1024];             /* the input line                 */
  //   char  *argv[64];              /* the command line argument      */

//     while (1) {                   /* repeat until done ....         */
  //        printf("Shell -> ");     /*   display a prompt             */
   //       gets(line);              /*   read in the command line     */
    //      printf("\n");
     //     parse(line, argv);       /*   parse the line               */
      //    if (strcmp(argv[0], "exit") == 0)  /* is it an "exit"?     */
       //        exit(0);            /*   exit if it is                */
        //  execute(argv);           /* otherwise, execute the command */
     //}
//}*/

