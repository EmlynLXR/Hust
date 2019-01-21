#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<time.h>
#include<pwd.h>
#include<grp.h>

int total;
int fstat(int,struct stat*);
int stat(const char*,struct stat*);
int lstat(const char*,struct stat*);

void printdir(char* dir,int depth);
void printfFILE(struct stat statbuf)
{
	mode_t mode=statbuf.st_mode;

	//文件类型
 	if     (S_ISREG(mode))  printf("-"); // 普通文件
 	else if(S_ISDIR(mode))    printf("d"); // 目录文件
        else if(S_ISCHR(mode))    printf("c"); // 字符设备文件
        else if(S_ISBLK(mode))    printf("b"); // 块设备文件
        else if(S_ISFIFO(mode))    printf("p"); // 管道文件
        else if(S_ISLNK(mode))  printf("l"); // 链接文件
        else                    printf("s"); // socket文件
	
	//文件权限 
        // 判断USR权限
        printf("%c", mode&S_IRUSR?'r':'-');
        printf("%c", mode&S_IWUSR?'w':'-');
        printf("%c", mode&S_IXUSR?'x':'-');
    
        // 判断GRP权限
        printf("%c", mode&S_IRGRP?'r':'-');
        printf("%c", mode&S_IWGRP?'w':'-');
        printf("%c", mode&S_IXGRP?'x':'-');
  
        // 判断OTH权限
        printf("%c", mode&S_IROTH?'r':'-');
        printf("%c", mode&S_IWOTH?'w':'-');
        printf("%c ", mode&S_IXOTH?'x':'-');	

	//硬连接数
	printf("%lu ", statbuf.st_nlink);

	//用户id和组id
	struct passwd* pwd=getpwuid(statbuf.st_uid);
	printf("%5s ",pwd->pw_name);
	struct group* grp = getgrgid(statbuf.st_gid);
	printf("%5s ",grp->gr_name);

	//文件大小
	printf("%10ld ", statbuf.st_size);

	//最后修改时间
	struct tm* t = localtime(&statbuf.st_mtime);
	printf("%4d-%2d-%2d %02d:%02d ", t->tm_year+1900, t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min);

	total++;
	return ;
}

void printdir(char* dir,int depth)
{
	DIR* dp;
	struct dirent* entry;
	struct stat statbuf;
	if((dp=opendir(dir))==NULL)
	{
		printf("opendir %s failed.\n",dir);
		return;
	}
	chdir(dir);
	while((entry=readdir(dp))!=NULL)
	{
		if(lstat(entry->d_name,&statbuf)==-1)
		{
			printf("lstat error.\n");
			return;
		}

		if(S_ISDIR(statbuf.st_mode))	
		{
			if((entry->d_name[0]=='.')||(entry->d_name[0]=='.'&&entry->d_name[1]=='.'))
				continue;
			printfFILE(statbuf);
			printf("%s depth=%d\n", entry->d_name,depth); 
			printdir(entry->d_name,depth+1);
		}
		else
		{
			printfFILE(statbuf);
			printf("%s depth=%d\n", entry->d_name,depth); 
		}					
	}	
	chdir("..");//返回父目录
	closedir(dp);
	return;		
}
int main(int argc,char**argv)
{
	total=0;
	int size=80;
	char* buffer=(char*)malloc(size);
	getcwd(buffer,size);
	if(argc==2)
	{
		if(strlen(argv[1])==1&&argv[1][0]=='.')
		{
			buffer=strcat(buffer,"/");
			buffer=strcat(buffer,argv[1]);
		}		
		else if(argv[1][0]=='.'&&argv[1][1]=='.')
		{
			buffer=strcat(buffer,"/");
			buffer=strcat(buffer,argv[1]);
		}
		else
			buffer=argv[1];
	}
	printdir(buffer,0);
	printf("\ntotal:%d\n",total);
	return 0;
}
