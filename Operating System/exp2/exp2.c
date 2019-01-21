#include<stdio.h>
#include<pthread.h>
#include<sys/types.h>
#include<linux/sem.h> 

int mutex1;
int mutex2;
int a=0;//线程共享变量

int semget(key_t key,int nsems,int semfig);
int semop(int semid,struct sembuf *sops,unsigned nsops);
int semctl(int semid,int semnum,int cmd,union semun arg);

void P(int semid,int index)
{
	struct sembuf sem;
	sem.sem_num=index;//要操作的信号灯的编号
	sem.sem_op=-1;//要执行的操作
	sem.sem_flg=0;//操作标志，一般设置为0
	semop(semid,&sem,(unsigned)1);
	return;
}
void V(int semid,int index)
{
	struct sembuf sem;	
	sem.sem_num = index;
	sem.sem_op =  1;
	sem.sem_flg = 0;	
	semop(semid,&sem,(unsigned)1);	
	return;
}
void *subp1()
{
	for(int i=1;i<=100;i++)
	{
		P(mutex1,0);
		a=a+i;
		V(mutex2,0);
	}
}
void *subp2()
{
	for(int i=1;i<=100;i++)
	{
		P(mutex2,0);
		printf("%d\n",a);
		V(mutex1,0);
	}
}
int main()
{
	//创建新信号量或获取一个已经存在的信号量的键值
	//IPC_CREAT表示不存在则创建
	mutex1=semget(IPC_PRIVATE,1,IPC_CREAT|0666);
  	mutex2=semget(IPC_PRIVATE,1,IPC_CREAT|0666);
	
    	//用于初始化信号量，在使用信号量前必须这样做
	//SETVAL用来把信号量初始化为一个已知的值
    	union semun sem_union;
	sem_union.val = 1;
  	semctl(mutex1,0,SETVAL,sem_union);
  	sem_union.val=0;
  	semctl(mutex2,0,SETVAL,sem_union);

	//创建两个线程
	pthread_t p1,p2;
	pthread_create(&p1,NULL,subp1,NULL);
	pthread_create(&p2,NULL,subp2,NULL);
	
	//等待两个线程运行结束
  	pthread_join(p1,NULL);
  	pthread_join(p2,NULL);	

	//删除两个信号灯
	//IPC_RMID用于删除一个已经无需继续使用的信号量标识符
  	semctl(mutex1,0,IPC_RMID,sem_union);
  	semctl(mutex2,0,IPC_RMID,sem_union);

	return 0;
}


