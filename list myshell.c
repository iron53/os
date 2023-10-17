#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>

#define MAX_INPUT_SIZE 1024
#define MAX_TOKENS 100

void maketoks(char *s,char *tok[])
{
     int i=0;
     char *p;
     
     p = strtok(s," ");
     while (p!=NULL)
     {
           tok[i++]=p;
           p=strtok(NULL," ");
     }
     tok[i]=NULL;
}

void list_files(const char *dn,char op)
{
     DIR *dp;
     printf("dir is %s",dn);
     struct dirent*entry;
     int dc=0,fc=0;
     dp=opendir(dn);     
     if (dp == NULL)
     {
        perror("Error openeing directory");
        return;
     } 
     switch(op)
     {
           case 'f':while((entry=readdir(dp)))
                    {
                         if (entry->d_type==DT_REG)
                            printf("%s\n",entry->d_name);
                    }
                    break;
           case 'n':while(entry=readdir(dp))      
                    {
                         if (entry->d_type==DT_DIR)
                            dc++;
                         if (entry->d_type==DT_REG)
                            fc++;
                         
                    }   
                    
                    printf("\n%d Dir(s)\t%d File (s)\n",dc,fc);
                    break;
                 
           case 'i':while(entry=readdir(dp))
                   {
                         if(entry->d_type==DT_REG)
                           printf("%s\t%d\n",entry->d_name,entry->d_fileno);
                         
                            
                   }     
                   break;    
     }
        closedir(dp);
}

int main()
{
    char buff[80],*args[10];
    int pid;
    while(1)
    {
         //fgets(buff,20,stdin);
         printf("myshell$");
         fflush(stdin);
         fgets(buff,80,stdin);
         buff[strlen(buff)-1]='\0';
         maketoks(buff,args);
         if(strcmp(args[0],"list")==0)
           list_files(args[2],args[1][0]);
         else
         {
             pid=fork();
             if(pid>0)
                wait(NULL);
             else
             {
                if(execvp(args[0],args)==-1)
                  printf("bad command.\n");
             }   
         }  
    }
}  

/*
void list_num_entries(const char *dirname)
{
     DIR*dir =opendir(dirname);
     if (dir == NULL)
     {
        perror("Error openeing directory");
        return;
     } 
     int count=0;
     while(readdir(dir)!=NULL)
          count++;
     printf("no. of entries in %s:%d\n",dirname,count);
     closedir(dir);       
}


void list_inode(const char*dirname)
{
     DIR * dir = opendir(dirname);
     if (dir == NULL)
     {
        perror("Error openeing directory");
        return;
     }
     struct dirent *entry;
     while ((entry=readdir(dir))!=NULL)
     {
           struct stat file_stat;
           char file_path[MAX_INPUT_SIZE];
           snprintf(file_path,sizeof(file_path),"%s/%s",dirname,entry->d_name);
           
           if(stat(file_path,&file_stat)==0)
           {
              printf("%s(inode:%Id\n",entry->d_name,(long)file_stat.st_ino);
           }
     }
     closedir(dir);
}

*/
