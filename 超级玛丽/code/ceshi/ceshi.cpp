#include<stdio.h>
typedef struct
{
	int num;
	char name[10];
	char sex;
	float jump;
	float run;
	union
	{
		float shot;
		int lie;
	} km3;
} PHYSICAL;
Readin(PHYSICAL*,int*);
Output(PHYSICAL*,int);
main()
{
	PHYSICAL s[35];
	int n;
	Readin(s,&n);
	Output(s,n);
}
Readin(PHYSICAL *s,int *n)
{
   int i=0;
   PHYSICAL stu;
   printf("Enter num:");
   scanf("%d",&stu.num);
   while(stu.num>=0)
   {
	   printf("Enter name,sex,jump,run:");
	   scanf("%s %c %f %f",stu.name,&stu.sex,&stu.jump,&stu.run);
	   if(stu.sex=='M')
	   {
		   printf("Enter shot:");
		   scanf("%f",&stu.km3.shot);
	   }
	   else
	   {
		   printf("Enter lie:");
		   scanf("%d",&stu.km3.lie);
	   }
	   s[i]=stu;
	   i++;
	   printf("Enter num:");
	   scanf("%d",&stu.num);
   }
   *n=i;
}
Output(PHYSICAL s[],int n)
{
    int i;
	for(i=0;i<n;i++)
	{
		printf("%d,%s,%c,%5.2f,%5.2f,",s[i].num,s[i].name,s[i].sex,s[i].jump,s[i].run);
		if(s[i].sex=='M')
			printf("%5.2f\n",s[i].km3.shot);
		else
        	printf("%5.2f\n",s[i].km3.lie);
	}
}