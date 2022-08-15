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
    
    
        
        pid = fork();
     
        int num; 
        if(-1 == pid){
            perror("fork!\n");
            exit(-1);
        }
        if(!pid){
            //child
            close(fd[0]);
            int t =0;
        for (int i = 1; i < argc; i++)
        {       
            
        
        
        FILE *f = fopen(argv[i],"r");
        while (fscanf(f,"%d",&num) != EOF)
        {   
         
            for (int j = 0; j < 32; j++)
            {
                if(!!(num & (1<<j))){
                    
                    t++;
                }
            }
        
        
        }
        
        
        write(fd[1],&t,sizeof(int));
        t=0;
        
        }
        
        close(fd[1]);
        
        }
        else{
            //parent
        close(fd[1]);   
    
        int t;
        for (int i = 0; i < argc -1; i++)
        {
            read(fd[0],&t,sizeof(int));
            printf("Total number of 1 bit in this file is: %d\n",t);
        }
        
        
        close(fd[0]);
        
        }
        

    

    for (int i = 1; i < argc; i++)
    {
        wait(NULL);
    }
    
    

    return 0;
}