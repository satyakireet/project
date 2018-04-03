#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>
int food[20] ,ss[20];
int NumBowls,NumCats=0,NumMouse=0;
sem_t cat_count,mouse_count;
pthread_mutex_t mutex,cmutex,mmutex;
pthread_t t1,t2,t3,t4;

void * cat()
{
	pthread_mutex_lock(&mutex);
	NumCats=NumCats+1;
	NumBowls=NumBowls+1;
	int b=NumBowls;
	int a=NumCats;
	pthread_mutex_unlock(&mutex);
	printf("Cat %d has started eating from bowl %d \n",a,b);
	printf("Cat %d is sleeping \n",a);

	sleep(2);
	
	printf("Cat %d wake up and started eating from bowl %d\n",a,b);
	while(NumMouse>0)
	{
	sem_destroy(&mouse_count);
	//printf("Mouse %d died by cat %d \n",NumMouse,a);
	ss[NumMouse]=-1;
	NumMouse=NumMouse-1;
	
	}
	//pthread_cancel(t3);
	printf("Cat %d is sleeping again\n",a);
	sleep(3);
	printf("Cat %d has completed eating from bowl %d\n",a,b);
	pthread_mutex_lock(&mutex);
	NumCats=NumCats-1;
	pthread_mutex_unlock(&mutex);
}

void * mouse()
{
	
	pthread_mutex_lock(&mmutex);
		NumMouse=NumMouse+1;
		int b=NumBowls;
		NumBowls=NumBowls-1;
		ss[NumMouse]=NumMouse;
		int rad=NumMouse;
		sleep(1);
		pthread_mutex_unlock(&mmutex);
	//if(NumCats<1){
	
	sem_wait(&mouse_count);
	//if(NumMouse==1){
	//			pthread_mutex_lock(&mmutex);
	//}
	printf("Mouse %d is eating from bowl %d \n",rad,b);
	printf("Mouse %d is sleeping \n",rad);
	sleep(2);
	printf("Mouse %d wake up and started eating from bowl %d\n",rad,b);
	if(rad!=ss[rad])
	{
		printf("Cat wake up and Mouse %d is dead\n",rad);
		return;
	}
	//printf("Mouse %d wake  up and eating \n",rad);
	sleep(1);
	if(rad!=ss[rad])
	{
		return;
	}printf("Mouse %d is sleeping  again \n",rad);
	printf("Mouse %d wake up and finished eating from bowl %d\n",rad,b);
	
	pthread_mutex_unlock(&mmutex);
}

int main()
{
	sem_init(&cat_count,0,5);
	sem_init(&mouse_count,0,5);
	
	int a=5,x;
	printf("Press 1 for  case 1:\n");
	printf("press 2 for case 2:\n");
	printf("press 3 for case 3:\n");
	printf("press 4 for case 4:\n");
	printf("press 5 for case 5:\n");
	scanf("%d",&x);
	switch(x)
	{
		case 1:
			printf("Case 1 : When single cat is eating  \n \n");
			pthread_create(&t1,NULL,cat,NULL);
			pthread_join(t1,NULL);
			break;
		case 2:
			printf("Case 2 : Whem single mouse is eating \n \n");
			pthread_create(&t1,NULL,mouse,NULL);
			pthread_join(t1,NULL);
			break;
		case 3:
			printf("case 3 : When  cat sees mouse is eating then mouse will die.\n \n");
			pthread_create(&t1,NULL,cat,NULL);
			pthread_create(&t2,NULL,mouse,NULL);
			pthread_join(t1,NULL);
			pthread_join(t2,NULL);
			
			break;
		case 4:
			printf("Case 4 : When mouse will eat after cat eats it \n \n");
			pthread_create(&t1,NULL,cat,NULL);
			sleep(8);
			pthread_create(&t2,NULL,mouse,NULL);
			pthread_join(t1,NULL);
			pthread_join(t2,NULL);
			break;
		case 5:
			printf("Case 5 : When two cats and two mouse eating simultaneously \n \n");
			pthread_create(&t1,NULL,cat,NULL);
			pthread_create(&t2,NULL,cat,NULL);
			sleep(5);
			pthread_create(&t3,NULL,mouse,NULL);
			pthread_create(&t4,NULL,mouse,NULL);
			pthread_join(t1,NULL);
			pthread_join(t2,NULL);
			pthread_join(t3,NULL);
			pthread_join(t4,NULL);
			break;
		default:
			printf("exiting \n");		
	}
}
