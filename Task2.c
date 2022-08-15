#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<pthread.h>
#include<semaphore.h>
#include<time.h>
#include<string.h>
#include<signal.h>
#include<fcntl.h>
#include<sys/stat.h>

int main(int argc, char **argv){
    pid_t pid;
    int fd[2];
    if(pipe(fd) == -1){
        perror("pipe");
        return EXIT_FAILURE;
    }
    
    for (int i = 1; i < argc; i++)
    {
        FILE *f = fopen(argv[i],"r");
        pid = fork();
        
        int num; 
        if(-1 == pid){
            perror("fork!\n");
            exit(-1);
        }
        if(!pid){
            //child
        close(fd[0]);
        int total = 0;
        
        while (fscanf(f,"%d",&num) != EOF)
        {   
         
            for (int i = 0; i < 32; i++)
            {
                if(!!(num & (1<<i))){
                    total++;
                }
            }
        
        
        }
        //printf("%d\n",total[m]);
        
        
        write(fd[1],&total,sizeof(int));
        //free(total);
        }
        else{
            //parent
        close(fd[1]);   
        int total;
        
        read(fd[0],&total,sizeof(int));

        printf("Total number of 1 bit in this file is: %d\n",total);
        
        close(fd[0]);
        
        }
        

    }

    for (int i = 1; i < argc; i++)
    {
        wait(NULL);
    }
    
    

    return 0;
}