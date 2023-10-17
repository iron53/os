#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
void cp();
void pp();
int main()
{
    pid_t pid;
    pid=fork();
    if (pid == 0)
       cp();
    else
       pp();
    return 0;      
}
void cp()
{
     printf("\nI am Child Process: ");
     printf("My id : %d\n",getpid());
}
void pp()
{
     printf("I am parent process: ");
     printf("My id : %d\n",getppid());
}
