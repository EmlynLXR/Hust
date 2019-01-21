#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<malloc.h>
#include<signal.h>

#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<linux/sem.h> 
#include<fcntl.h>


#define BufferSize 4000
#define BufferNum 10
#define writePath "/home/allen/桌面/test2.mkv"
#define readPath "/home/allen/桌面/exp3/forNEp03.mkv"

int pid1,pid2;
int semid1,semid2;

typedef struct sharebuff{
	char data[BufferSize];
	bool end;
	int len;
	struct sharebuff* next;
}ShareBuff;
ShareBuff* head=NULL,*tail=NULL;
int Buffers[BufferNum];

int semget(key_t,int,int);
int semop(int,struct sembuf*,unsigned);
int semctl(int,int,int,union semun);
int shmget(key_t,int,int);
void* shmat(int,char*,int);
int shmctl(int,int,ShareBuff*);

void killall()
{
	kill(pid1,SIGUSR1);
	kill(pid2,SIGUSR2);
}
void killp(int signal)
{
	exit(0);
}
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
void readbuf()
{
	signal(SIGINT,SIG_IGN);//设置忽略信号SIGINT
	signal(SIGUSR1,killp);//设置信号SIGUSR1
	ShareBuff* in=head;
	int fd;
	if((fd=open(readPath,O_RDONLY))==-1)
	{
		printf("Open failed in readBuf.\n");
		kill(pid2,SIGUSR2);
		close(fd);
		exit(0);
	}
	int n=0,len;	
	while(1)
	{
		P(semid1,n);
		len=read(fd,in->data,BufferSize);
		if(len!=BufferSize)
		{
			in->end=1;
			in->len=len;
			V(semid2,n);
			close(fd);
			exit(0);
		}
		in=in->next;
		V(semid2,n);	
		n=(n+1)%BufferNum;
	}
	exit(0);
}
void writebuf()
{
	signal(SIGINT,SIG_IGN);//设置忽略信号SIGINT
	signal(SIGUSR2,killp);//设置信号SIGUSR2
	ShareBuff* out=head;
	int fd;
	if((fd=open(writePath,O_WRONLY|O_TRUNC|O_CREAT,S_IRWXU))==-1)
	{
		printf("Open failed in writeBuf.\n");
		kill(pid1,SIGUSR1);
		close(fd);
		exit(0);
	}
	int n=0,len;	
	while(1)
	{
		P(semid2,n);
		
		if(out->end==1)
		{
			len=write(fd,out->data,out->len);
			V(semid1,n);
			close(fd);
			exit(0);
		}
		len=write(fd,out->data,BufferSize);
		out=out->next;
		V(semid1,n);
		n=(n+1)%BufferNum;	
	}
	exit(0);
}
int main()
{
	int size=sizeof(ShareBuff);
	void* shm=NULL;
	for(int i=0;i<BufferNum;i++)
	{
		ShareBuff* q=(ShareBuff*)malloc(size);
	
		Buffers[i]=shmget(IPC_PRIVATE,size,IPC_CREAT|0666);
		if(Buffers[i]==-1)
		{
			printf("shmget failed.\n");
			exit(0);
		}

		shm=shmat(Buffers[i],(void*)0,0);
		if(shm==(void*)-1)
		{
			printf("shmat failed.\n");
			exit(0);
		}

		q=(ShareBuff*)shm;
		q->next=NULL;
		if(i==0)
		{
			head=(ShareBuff*)malloc(sizeof(ShareBuff));
			head=q;
			tail=q;
		}
		else
		{
			tail->next=q;
			tail=q;
		}
	}
	tail->next=head;
	
	//创建新信号量或获取一个已经存在的信号量的键值
	//IPC_CREAT表示不存在则创建
	semid1=semget(IPC_PRIVATE,BufferNum,IPC_CREAT|0666);
	semid2=semget(IPC_PRIVATE,BufferNum,IPC_CREAT|0666);
	
    	//用于初始化信号量，在使用信号量前必须这样做
	//SETVAL用来把信号量初始化为一个已知的值
    	union semun sem_union;
	sem_union.val = 1;
	for(int i=0;i<BufferNum;i++)
  		semctl(semid1,i,SETVAL,sem_union);
	sem_union.val = 0;
	for(int i=0;i<BufferNum;i++)
  		semctl(semid2,i,SETVAL,sem_union);

	while((pid1=fork())==-1);
	if(pid1!=0)
	{
		while((pid2=fork())==-1);
	}

	if(pid1==0)
		readbuf();
	else if(pid2==0)
		writebuf();
	else
	{
		signal(SIGINT,killall);
		waitpid(pid1,NULL,0);
		waitpid(pid2,NULL,0);
		
		for(int i=0;i<BufferNum;i++)
	  		semctl(semid1,i,IPC_RMID,sem_union);
		for(int i=0;i<BufferNum;i++)
	  		semctl(semid2,i,IPC_RMID,sem_union);

		for(int i=0;i<BufferNum;i++)
		{
			if(shmctl(Buffers[i],IPC_RMID,0)==-1)
			{
				printf("shmctl failed.\n");
				exit(0);
			}
		}
	}

	return 0;
}
