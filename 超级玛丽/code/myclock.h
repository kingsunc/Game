//clock 1.0

#ifndef __MYCLOCK
#define __MYCLOCK

#include "stdio.h"

class MYCLOCK
{
public:
	MYCLOCK()
	{
		iNum=0;
		iIsActive=0;
		iNumShow=0;
		iElapse=100;
		ishow=0;
	}
	~MYCLOCK()
	{
		Destroy();
	}

	void Begin(HWND hw,int elapse,int timetotal)
	{
		if(iIsActive)
			return;//已经启动了，直接返回

		hWnd=hw;
		iElapse=elapse;

		SetTimer(hWnd,1,iElapse,NULL);
		iNum=1000/iElapse;//一秒钟的时间消息数量
		iNumShow=timetotal;
		iIsActive=1;
	}
	void Destroy()
	{
		if(iIsActive)
		{
			iIsActive=0;
			KillTimer(hWnd,1);
		}
	}

	//入参： 秒数
	void ReStart(int timetotal)
	{
		iNumShow=timetotal;	
		iNum=1000/iElapse;
		ishow=1;
	}

	//////////////////////////// 显示部分
	void SetDevice(HDC h)
	{
		hDC=h;
	}

	void Show(int x,int y)
	{
		char temp[20]={0};

		if(!ishow)
			return;

		sprintf(temp,"TIME: %d  ",iNumShow);
		TextOut(hDC,x, y, temp,strlen(temp));
	}

	//计数，但不销毁
	int DecCount()
	{
		iNum--;
		if(iNum==0)
		{
			//过了一秒
			iNum=1000/iElapse;
			iNumShow--;
			if(iNumShow<=0)
			{
				//不销毁
				return 1;
			}
		}
		return 0;
	}

	int Dec()
	{
		iNum--;
		if(iNum<=0)
		{
			//过了一秒
			iNum=1000/iElapse;
			iNumShow--;
			if(iNumShow<=0)
			{
				iNumShow=0;
				Destroy();
				return 1;
			}
		}
		return 0;
	}
	
	//
	void SetShow(int i)
	{
		ishow=i;
	}

public:
	HWND hWnd;
	HDC hDC;

	int iNum;
	int iNumShow;
	int iElapse;
	int iIsActive;

	int ishow;
};


#endif