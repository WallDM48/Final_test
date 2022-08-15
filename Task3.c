#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<time.h>
#include<math.h>
#include<sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define THREAD_COUNT 5

pthread_mutex_t mux;

double **arr;
int n;
int m;

void* routine(void*arg){
        double result=0;
        pthread_mutex_lock(&mux);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; i < m; j++)
            {
                result += arr[i][j]*arr[i][j];
            }
            result = sqrt(result);
            printf("%lf",result);
            write(*(int*)arg,&result,sizeof(double));
        }
        
    pthread_mutex_unlock(&mux);
}


int main(){
    puts("Enter the size of array");
    scanf("%d %d",&n,&m);

    arr = (double **)malloc(n * sizeof(double *));
    for(int i=0;i<5;i++)
    {
        arr[i]=(double*)malloc(m*sizeof(double));
    }

    puts("Enter the elements of array");
    for (int i = 0; i < n; i++)
    {
        for(int j=0;j <m; j++){
            scanf("%lf",&arr[i][j]);
        }
    }

    puts("Enter the name of file");
    char *name;
    scanf("%s",name);
    
    pthread_t th1[THREAD_COUNT];
    pthread_mutex_init(&mux,NULL);

    int fd = open(name,O_WRONLY | O_TRUNC);
    if(fd < 0){
        perror("Error open the file!\n");
        exit(-1);
    }

    for(int i=1; i < THREAD_COUNT;i++ ){

    if(pthread_create(th1 +i,NULL,routine,NULL)){
        perror("thread creat\n");
        return -1;
        }
        
    }
   
    for (int i = 1; i < THREAD_COUNT; i++)
    {
        
         if(pthread_join(th1[i],NULL)){
        perror("join thread\n");
        return -1;

    }
    
    
    }

    for (int i = 0; i < n; i++)
    {
        free(arr[i]);
    }
    
    free(arr);
    return 0;
}