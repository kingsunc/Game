#include "stdafx.h"
#include "texttool.h"

TEXTAREA::TEXTAREA()
{}

TEXTAREA::~TEXTAREA()
{}

void TEXTAREA::Init(char *p)
{
	ptext=p;
}

void TEXTAREA::SetDevice(HDC hdest,HDC hsrc,int wwin,int hwin)
{
	hdcdest=hdest;
	hdcsrc=hsrc;
	screenwidth=wwin;
	screenheight=hwin;	
}


void TEXTAREA::SetPos(int istyle,int x,int y)
{
	switch(istyle)
	{
	case TEXT_CENTER:
		xpos=(screenwidth-width)/2;
		ypos=y;
		break;
	case TEXT_USER:
		xpos=x;
		ypos=y;
		break;
	}
}

void TEXTAREA::SetColor(COLORREF cbk, COLORREF ctext)
{
	c1=cbk;
	c2=ctext;
}

void TEXTAREA::Draw()
{
	SetBkColor(hdcdest,c1);
	SetTextColor(hdcdest,c2);
	TextOut(hdcdest,xpos,ypos,ptext,strlen(ptext));
}

void TEXTAREA::Draw(char *p,int x,int y)
{
	SetBkColor(hdcdest,c1);
	SetTextColor(hdcdest,c2);
	TextOut(hdcdest,x,y,p,strlen(p));
}

void TEXTAREA::Stretch(int x,int y)
{
/*	TextOut(hdcdest,xpos,ypos,ptext[0],strlen(ptext[0]));
	
	StretchBlt(hdcdest,xpos,ypos,width*x,height*y,
		hdcdest,0,0,width,height,
		SRCCOPY);		
		*/
}
