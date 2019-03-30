#include <sys/types.h> 
#include <sys/stat.h> 
#include <string.h> 
#include <stdio.h> 
#include <fcntl.h> 
#include <unistd.h> 
 
int main(void) 
{ 
	//写入MyDeviceDriver设备的内容
	char w_str[1024]; memset(w_str, 0, sizeof(w_str)); 
	//
    	char r_str[1024]; memset(r_str, 0, sizeof(r_str));
 
   	int fd = open("/dev/mydev", O_RDWR, S_IRUSR|S_IWUSR);//打开设备 


	if(fd == -1)
	{ 
		printf("Cannot open file\n"); 
		return -1; 
	} 

	read(fd, &r_str, sizeof(r_str)); 
	printf("The message in mydriver now is: %s\n", r_str); 

	printf("input:"); 
	scanf("%s",&w_str); 

	//将输入写入设备 
	write(fd, &w_str, sizeof(w_str)); 
	//读出设备的信息并打印 
	read(fd, &r_str, sizeof(r_str)); 
	printf("The message changed to: %s\n", r_str);   

	close(fd);//释放设备 

	return 0; 
} 
