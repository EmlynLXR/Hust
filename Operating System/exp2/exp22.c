#include<stdio.h>
#include<pthread.h>
#include<sys/types.h>
#include<linux/sem.h> 
#include<stdlib.h>
#include<time.h>

int semget(key_t key,int nsems,int semfig);
int semop(int semid,struct sembuf *sops,unsigned nsops);
int semctl(int semid,int semnum,int cmd,union semun arg);

int mutex;
int count=0;//已售票数量
int total=23;//总票数
int n=0;

void P(int semid,int index)
{
	struct sembuf sem;
	sem.sem_num=index;//要操作的信号灯的编号
	sem.sem_op=-1;//要执行的操作
	sem.sem_flg=0;//操作标志，一般设置为0
	semop(semid,&sem,1);
	return;
}
void V(int semid,int index)
{
	struct sembuf sem;	
	sem.sem_num = index;
	sem.sem_op =  1;
	sem.sem_flg = 0;	
	semop(semid,&sem,1);	
	return;
}
void *subp1()
{
	while(1)
	{
		P(mutex,0);
		if(count<total)
		{
			n=1 + (rand()%10);
			count=count+n;
			if(count>total)
			{
				printf("1:Need:%d,Ticket is not enough and sold out!\n",n);
				V(mutex,0);
				break;
			}
			else
				printf("1:Need:%d，Count:%d\n",n,count);
			V(mutex,0);
		}
		else
		{
			printf("1:Ticket is sold out!\n");
			V(mutex,0);
			break;				
		}	
	}
}
void *subp2()
{
	while(1)
	{
		P(mutex,0);
		if(count<total)
		{
			n=1 + (rand()%10);
			count=count+n;
			if(count>total)
			{
				printf("2:Need:%d,Ticket is not enough and sold out!\n",n);
				V(mutex,0);
				break;
			}			
			else
				printf("2:Need:%d，Count:%d\n",n,count);
			V(mutex,0);
		}
		else
		{
			printf("2:Ticket is sold out!\n");
			V(mutex,0);
			break;				
		}	
	}
}
void *subp3()
{
	while(1)
	{
		P(mutex,0);
		if(count<total)
		{
			n=1 + (rand()%10);
			count=count+n;
			if(count>total)
			{
				printf("3:Need:%d,Ticket is not enough and sold out!\n",n);
				V(mutex,0);
				break;
			}
			else	
				printf("3:Need:%d，Count:%d\n",n,count);
			V(mutex,0);
		}
		else
		{
			printf("3:Ticket is sold out!\n");
			V(mutex,0);
			break;				
		}	
	}
}
int main()
{
	srand(time( NULL )); 
	mutex=semget(IPC_PRIVATE,1,IPC_CREAT|0666);
	
    	union semun sem_union;
	sem_union.val = 1;
  	semctl(mutex,0,SETVAL,sem_union);

	pthread_t p1,p2,p3;
  	pthread_create(&p1,NULL,subp1,NULL);
  	pthread_create(&p2,NULL,subp2,NULL);
	pthread_create(&p3,NULL,subp3,NULL);
	
  	pthread_join(p1,NULL);
  	pthread_join(p2,NULL);
	pthread_join(p3,NULL);

  	semctl(mutex,0,IPC_RMID,sem_union);

	return 0;
}


