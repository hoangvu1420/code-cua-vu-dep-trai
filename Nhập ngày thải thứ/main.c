#include <stdio.h>
#include <conio.h>

int nhuan(int nam)
{
	int hc;
	if(nam%400==0||(nam%4==0 && nam%100!=0))
		hc=1;
	else
		hc=0;
	return hc;
}
int hople(int ngay,int thang,int nam)
{
	int hc,ch,sntt;
	hc=nhuan(nam);
	switch(thang)
	{
	case 1:case 3:case 5:case 7:case 8:case 10:case 12:sntt=31;break;
	case 4:case 6:case 9:case 11:sntt=30;break;
	case 2:sntt=(hc?29:28);break;
	}
	if(ngay<0||ngay>sntt||thang<0||thang>12||nam<0)
		ch=0;
	else
		ch=1;
	return ch;
}
int thu(int ngay,int thang,int nam)
{
	int t,t2,ret=ngay,s;
	for(int i=1;i<thang;i++)
	{
		if(i==1||i==3||i==5||i==7||i==8||i==10||i==12)
			ret=ret+31;
		else
		{
			if(i==2)
			{
				t2=(nhuan(nam)?29:28);
				ret=ret+t2;
			}
			else
				ret=ret+30;
		}
	}
	s=nam-1+((nam-1)/4)-((nam-1)/100)+((nam-1)/400)+ret;
	t=s%7;
	return t;
}
void main()
{
	int hc,t;
	int ngay,thang,nam;
	printf("Nhap ngay thang nam: ");scanf("%d%d%d",ngay,thang,nam);
	hc=hople(ngay,thang,nam);
	if(hc)
	{
		t=thu(ngay,thang,nam);
		switch(t)
		{
		case 0:printf("Chu nhat\n");break;
		case 1:printf("Thu hai\n");break;
		case 2:printf("Thu ba\n");break;
		case 3:printf("Thu tu\n");break;
		case 4:printf("Thu nam\n");break;
		case 5:printf("Thu sau\n");break;
		case 6:printf("Thu bay\n");break;
		}
	}
	else
		printf("ngay khong hop le\n");
	getch();
}
