int fiboiter(int n)
{
	int x=1;
	int y=1;
	int z=1;
	if(n<1)
		return 0;
	else if(n<3)
		return 1;
	else
	{
		while(n>3)
		{
			z=x+y;
			x=y;
			y=z;
			n--;
			write(z);
		}
		return z;
	}
	
}
int main()
{
	int n=10;
	int ret;
	ret=fiboiter(n);
	return ret;
}