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
	ss[NumMouse]=-1;
	NumMouse=NumMouse-1;
	}
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
		if(b==0)
		{
			printf("No bowls available as no cat has eaten \n");
			return;
		}
		NumBowls=NumBowls-1;
		ss[NumMouse]=NumMouse;
		int rad=NumMouse;
		sleep(1);
		pthread_mutex_unlock(&mmutex);
	sem_wait(&mouse_count);
	printf("Mouse %d is eating from bowl %d \n",rad,b);
	printf("Mouse %d is sleeping \n",rad);
	sleep(2);
	printf("Mouse %d wake up and started eating from bowl %d\n",rad,b);
	if(rad!=ss[rad])
	{
		printf("Cat wake up and Mouse %d is dead\n",rad);
		return;
	}
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
	printf("********************************\n");
	printf("   Press 1 for case 1:   \n");
	printf("   press 2 for case 2:   \n");
	printf("   press 3 for case 3:   \n");
	printf("   press 4 for case 4:   \n");
	printf("   press 5 for case 5:   \n");
	printf("********************************\n");
	scanf("%d",&x);
	switch(x)
	{
		case 1:
			printf("---------------------------------------\n");
			printf("Case 1 : WHEN SINGLE CAT IS EATING:- \n \n");
			pthread_create(&t1,NULL,cat,NULL);
			pthread_join(t1,NULL);
			printf("\n---------------------------------------\n");
			break;
		case 2:
			printf("---------------------------------------\n");
			printf("Case 2 : WHEN SINGLE MOUSE IS EATING:- \n \n");
			pthread_create(&t1,NULL,mouse,NULL);
			pthread_join(t1,NULL);
			printf("\n---------------------------------------\n");
			break;
		case 3:
			printf("---------------------------------------\n");
			printf("case 3 : WHEN CAT SEES MOUSE IS EATING THEN MOUSE WILL DIE:-\n \n");
			pthread_create(&t1,NULL,cat,NULL);
			pthread_create(&t2,NULL,mouse,NULL);
			pthread_join(t1,NULL);
			pthread_join(t2,NULL);
			printf("\n---------------------------------------\n");
			break;
		case 4:
			printf("---------------------------------------\n");
			printf("Case 4 : MOUSE EATS AFTER CAT EATS IT:- \n \n");
			pthread_create(&t1,NULL,cat,NULL);
			sleep(8);
			pthread_create(&t2,NULL,mouse,NULL);
			pthread_join(t1,NULL);
			pthread_join(t2,NULL);
			printf("\n---------------------------------------\n");
			break;
		case 5:
			printf("---------------------------------------\n");
			printf("Case 5 : WHEN TWO CATS AND TWO MOUSE EATS SIMULTANEOUSLY:-\n \n");
			pthread_create(&t1,NULL,cat,NULL);
			pthread_create(&t2,NULL,cat,NULL);
			sleep(5);
			pthread_create(&t3,NULL,mouse,NULL);
			pthread_create(&t4,NULL,mouse,NULL);
			pthread_join(t1,NULL);
			pthread_join(t2,NULL);
			pthread_join(t3,NULL);
			pthread_join(t4,NULL);
			printf("\n---------------------------------------\n");
			break;
		default:
			printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
			printf("Invalid entry program is going to exit........... \n");
			printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");		
	}
}
