#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>


pid_t p1,p2;
int pipefd[2];
void killall()
{
	kill(p1,SIGUSR1);
	kill(p2,SIGUSR2);
	printf("Kill all.\n");
}
void killp(int signal)
{
	if(signal==SIGUSR1)
	{
		close(pipefd[1]);//关闭写管道
		printf("Child Process 1 is Killed by Parent.\n");
		exit(0);	
	}
	else
	{
		close(pipefd[0]);//关闭读管道
		printf("Child Process 2 is Killed by Parent.\n");
		exit(0);
	}

}
int main(void) {
	
	if(pipe(pipefd)<0)//创建无名管道
	{
		printf("Pipe create error.\n");
		return -1;
	}
	char inpipe[100],outpipe[100];//pipefd[0]用于读操作、pipefd[1]用于写操作

	while((p1=fork())==-1);
	if(p1!=0)
	{
		while((p2=fork())==-1);//创建子进程1、2
	}

	if(p1==0)//p1进程
	{
		signal(SIGINT,SIG_IGN);//设置忽略信号SIGINT
		signal(SIGUSR1,killp);//设置信号SIGUSR1
		close(pipefd[0]);//关闭读管道
		int x=1;
		while(1)
		{
			sprintf(outpipe,"I send you %d times.\n",x++);
			write(pipefd[1],outpipe,100);//发送数据至管道数据
			printf("p1:%s",outpipe);
			sleep(1);//睡眠1s
		}
	}
	else if(p2==0)//p2进程
	{
		signal(SIGINT,SIG_IGN);//设置忽略信号SIGINT
		signal(SIGUSR2,killp);//设置信号SIGUSR2
		close(pipefd[1]);//关闭写管道
		while(1)
		{
			if((read(pipefd[0],inpipe,100))!=0)//接收管道数据并显示
				printf("p2:%s",inpipe);
		}
	}
	else//主进程
	{
		signal(SIGINT,killall);//如果收到来自键盘的中断信号则调用killall函数
		waitpid(p1,NULL,0);
		waitpid(p2,NULL,0);//等待子进程1、2退出
		close(pipefd[0]);
		close(pipefd[1]);//关闭管道
		printf("Parent process is killed.\n");
		return 0;
	}	
}
