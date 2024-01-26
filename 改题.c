#include<stdio.h>
int main()
{
	int i,x[10],j,t;
	for(i=0;i<10;i++)
	{
		scanf("%d",&x[i]);
	}
	for(i=0;i<10;i++)
	{
		for(j=0;j<9-i;j++)
		{
			if(x[j]>x[j+1])
			{
				t=x[j];
				x[j]=x[j+1];
				x[j+1]=t;
			}
		}
	}
	for(i=0;i<10;i++)
	printf("%d",x[i]);
	return 0;
}

