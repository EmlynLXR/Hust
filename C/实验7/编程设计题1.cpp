#include<stdio.h>
void isr0(void);
void isr1(void);
void isr2(void);
void isr3(void);
void isr4(void);
void isr5(void);
void isr6(void);
void isr7(void);
struct ISR_BITS{
	unsigned int bit0:1;
	unsigned int bit1:1;
	unsigned int bit2:1;
	unsigned int bit3:1;
	unsigned int bit4:1;
	unsigned int bit5:1;
	unsigned int bit6:1;
	unsigned int bit7:1;
};
union ISR_RSG{
	unsigned short a;
	struct ISR_BITS b;
};
int main()
{
	int N;scanf("%d",&N);
	union ISR_RSG x[10];
	for(int i=0;i<N;i++)
	{scanf("%hu",&x[i].a);}
	void (*p_fun[8])(void)={isr0,isr1,isr2,isr3,isr4,isr5,isr6,isr7};
	for(int i=0;i<N;i++)
	{
		printf("%d:\n",x[i].a);
    	if(x[i].b.bit0==1) (*p_fun[0])();
    	if(x[i].b.bit1==1) (*p_fun[1])();
    	if(x[i].b.bit2==1) (*p_fun[2])();
    	if(x[i].b.bit3==1) (*p_fun[3])();
    	if(x[i].b.bit4==1) (*p_fun[4])();
    	if(x[i].b.bit5==1) (*p_fun[5])();
    	if(x[i].b.bit6==1) (*p_fun[6])();
    	if(x[i].b.bit7==1) (*p_fun[7])();
    	printf("\n");
    }
}
void isr0(void)
{
	printf("The Interrupt Service Routine isr0 is called!\n");
}
void isr1(void)
{
	printf("The Interrupt Service Routine isr1 is called!\n");
}
void isr2(void)
{
	printf("The Interrupt Service Routine isr2 is called!\n");
}
void isr3(void)
{
	printf("The Interrupt Service Routine isr3 is called!\n");
}
void isr4(void)
{
	printf("The Interrupt Service Routine isr4 is called!\n");
}
void isr5(void)
{
	printf("The Interrupt Service Routine isr5 is called!\n");
}
void isr6(void)
{
	printf("The Interrupt Service Routine isr6 is called!\n");
}
void isr7(void)
{
	printf("The Interrupt Service Routine isr7 is called!\n");
}
