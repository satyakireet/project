#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>
int food[20],a=0 ,ss[20];

int NumBowls,NumCats=0,NumMouse=0;
sem_t cat_count,mouse_count;
pthread_mutex_t mutex,cmutex,mmutex;
pthread_t t1,t2,t3,t4;

void * cat()
{
	pthread_mutex_lock(&mutex);
	NumCats=NumCats+1;
	a=a+1;
	printf("Cat %d has started execution \n",NumCats);
	printf("Cat %d is sleeping \n",NumCats);
		printf("Mouse  %d sem \n",mouse_count);

	sleep(2);
	
	printf("Cat %d wake up \n",NumCats);
	while(NumMouse>0)
	{
	sem_destroy(&mouse_count);
	printf("Mouse %d died \n %d",NumMouse,mouse_count);
	ss[NumMouse]=-1;
	NumMouse=NumMouse-1;
	}
	//pthread_cancel(t3);
	printf("Cat %d is sleeping again\n",NumCats);
	sleep(2);
	
	//pthread_cancel(t4);
	printf("Cat %d wake up and eating\n",NumCats);
	food[a]=a;
	printf("Cat %d has executed \n",NumCats);
	pthread_mutex_unlock(&mutex);
}

void * mouse()
{
		NumMouse=NumMouse+1;
		ss[NumMouse]=NumMouse;
		int rad=NumMouse;
	//if(NumCats<1){
	
	sem_wait(&mouse_count);
			printf("Mouse  %d sem \n",mouse_count);

	if(NumMouse==1){
				pthread_mutex_lock(&mmutex);
	}
	printf("Mouse %d is eating from  \n",NumMouse);
	printf("Mouse %d is sleeping \n",NumMouse);
	sleep(4);
	if(rad!=ss[rad])
	{
		return;
	}
	printf("Mouse %d wake  up and eating \n",NumMouse);
	sleep(3);
	printf("Mouse %d wake  up and eating \n",NumMouse);
	printf("Mouse %d has executed\n",NumMouse);
	
	pthread_mutex_unlock(&mmutex);

	//}
	/*else
	{
		printf("Mouse %d Cannot eat as cat %d is already eating \n",NumMouse,NumCats);
		NumMouse=NumMouse-1;
	}*/
}

int main()
{
	sem_init(&cat_count,0,5);
	sem_init(&mouse_count,0,5);
	
	int a=5,x;
	printf("Press 1 for  case 1:\n");
	printf("press 2 for case 2:\n");
	printf("press 3 for case 3:\n");
	scanf("%d",&x);
	switch(x)
	{
		case 1:
			printf("In this as cat is running so mouse will not execute \n");
			pthread_create(&t1,NULL,cat,NULL);
			pthread_create(&t2,NULL,cat,NULL);
			pthread_create(&t3,NULL,mouse,NULL);
			pthread_create(&t4,NULL,mouse,NULL);
			pthread_join(t1,NULL);
			pthread_join(t2,NULL);
			pthread_join(t3,NULL);
			pthread_join(t4,NULL);
			break;
		case 2:
			printf("In multiple mouse will execute as there is no cat thread/n");
			pthread_create(&t3,NULL,mouse,NULL);
			pthread_create(&t4,NULL,mouse,NULL);
			pthread_join(t3,NULL);
			pthread_join(t4,NULL);
			break;
		case 3:
			
			break;
		case 4:
			
			break;
		default:
			printf("exit");
			
	}
		
	
}
