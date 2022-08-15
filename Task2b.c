#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<time.h>



#define COUNT 5

//int total = 0;
pthread_mutex_t mux;


void* routine(void*arg){
    int num;
    int total = 0;
    static int j =1;
     while(fscanf(arg,"%d",&num) !=EOF){
        pthread_mutex_lock(&mux);
        
        for (int  i = 0; i < 32; i++)
        {
            if(!!(num&(1<<i) )){
                total++;
            }
        }
         
        pthread_mutex_unlock(&mux);
        
     }
     printf("Total file%d = %d\n",j,total);
    j++;
    
    
}


int main(int argc,char **argv){
    pthread_t th1[argc-1];
    pthread_mutex_init(&mux,NULL);

    for(int i=1; i < argc;i++ ){
      FILE *f = fopen(argv[i],"r");
      if(!f){
        perror("fopen");
        return -1;
      }
    if(pthread_create(th1 +i,NULL,routine,f)){
        perror("thread creat\n");
        return -1;
        }
        
    }
   
    for (int i = 1; i < argc; i++)
    {
        
         if(pthread_join(th1[i],NULL)){
        perror("join thread\n");
        return -1;

    }
    
    
    }
   
    return 0;
}