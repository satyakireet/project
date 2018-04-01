#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>
int food[20],a=0;

int NumBowls,NumCats=0,NumMouse=0;
sem_t cat_wt_count,mouse_wt_count;
pthread_mutex_t mutex,cmutex,mmutex;
pthread_t t1,t2,t3,t4;

void * cat()
{
	pthread_mutex_lock(&mutex);
	NumCats=NumCats+1;
	a=a+1;
	printf("Cat %d has started execution \n",NumCats);
	printf("Cat is sleeping \n");
	sleep(2);
	printf("Cat wake up \n");
	pthread_cancel(t3);
	printf("Cat is sleeping again\n");
	sleep(2);
	
	pthread_cancel(t4);
	printf("Cat wake up and eating\n");
	food[a]=a;
	printf("Cat has executed \n");
	pthread_mutex_unlock(&mutex);
}

void * mouse()
{
	if(NumCats<1){
	
	NumMouse=NumMouse+1;
	printf("Mouse %d has started execution \n",NumMouse);
	printf("Mouse is sleeping \n");
	sleep(4);
	printf("Mouse wake  up and eating \n");
	sleep(3);
	printf("Mouse wake  up and eating \n");
	printf("Mouse has executed\n");
	a=a-1;
	}
	else
	printf("Cannot eat as cat is already eating \n");
}

int main()
{
	sem_init(&cat_wt_count,0,5);
	sem_init(&mouse_wt_count,0,5);
	
	int a=5;
	//pthread_create(&t1,NULL,cat,NULL);
	//pthread_create(&t2,NULL,cat,NULL);
	pthread_create(&t3,NULL,mouse,NULL);
	pthread_create(&t4,NULL,mouse,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	pthread_join(t3,NULL);
	pthread_join(t4,NULL);	
	
}
