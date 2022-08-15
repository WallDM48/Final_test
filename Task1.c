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

#define LAPTOPS_COUNT 5


typedef struct Laptop{
    unsigned long serial_number;
    char model[100];
    double weight;
    double price;
}Laptop;

void rand_init_laptop(Laptop *l){
    static int i = 0;
    char buf[]="qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
    l->serial_number = i;
    l->model[0] = buf[26 +rand()%26];
    int len = (7 +rand()%4);
    for (int j = 1; j < len; j++)
    {   if(j%2 != 0){
        l->model[j] = ' ';
    }
        else{
        l->model[j] = buf[rand()%52];}
    }
    l->model[len] = '\0';
    l->weight = (25 + rand()%(10000 - 25))/1000.0;
    l->price = (1000 + rand()%(500000 - 1000))/100.0;  
    
    i++;
}

double totalLaptopWeight(Laptop* l){
    double total_weight = 0.0;
    if(!l){
        printf("Empty struct!\n");
        return -1;

    }
    for (int i = 0; i < LAPTOPS_COUNT; i++)
    {
        total_weight += l[i].weight;
    }
    if(total_weight < 0){
        return -1;
    }
    return total_weight;

}

 Laptop *minPriceItem(Laptop *l){
    Laptop *min_adrr = malloc(sizeof(Laptop));
     *min_adrr = *l;
    double min = l[0].price;
    for (int i = 1; i < LAPTOPS_COUNT; i++)
    {
        if(min > l[i].price)
        {   
            min = l[i].price;
            *min_adrr = l[i];
            
        }
    }

    return min_adrr;
    

 }

void print_struct(Laptop *l){
        printf("Serial number: %ld,  Model: %s,  Weight: %.3lf,  Price: %.2lf\n",l->serial_number,l->model,l->weight,l->price);
    
    
}

int main(){
    srand(time(0));
    Laptop *lap = malloc(LAPTOPS_COUNT*sizeof(Laptop));
    for (int i = 0; i < LAPTOPS_COUNT; i++)
    {
        rand_init_laptop(lap+i);
    }
    
    
    for (int i = 0; i < LAPTOPS_COUNT; i++)
    {
        print_struct(lap+i);
    }
    
    double total = totalLaptopWeight(lap);
    printf("Total weight is: %.3lf\n",total);

    Laptop *cheapest = malloc(sizeof(Laptop));

    cheapest = minPriceItem(lap);

    print_struct(cheapest);
  


    free(lap);
    free(cheapest);
    return 0;
}