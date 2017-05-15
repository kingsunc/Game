#ifndef __BITMAPTOOL
#define __BITMAPTOOL

#include "filereport.h"


#define BM_BOTTOM_RIGHT 0
#define BM_BOTTOM_CENTER 1
#define BM_CENTER 2
#define BM_USER 3

//
class MYBITMAP
{
public:
	MYBITMAP();
	~MYBITMAP();
	//初始化
	void Init(HINSTANCE hInstance,int iResource,int row,int col);
	void SetDevice(HDC hdest,HDC hsrc,int wwin,int hwin);
	//
	void SetPos(int istyle,int x,int y);
	
	//显示	
	void Draw(DWORD dwRop);
	void Stretch(int x,int y);
	void Stretch(int x,int y,int id);
	void Show(int x,int y);
	void ShowCenter(int y);
	void ShowLoop(int left,int top,int right,int bottom,int iframe);
	void ShowNoBack(int x,int y,int iFrame);
	void ShowNoBackLoop(int x,int y,int iFrame,int iNum);
	
	//动画播放
	void ShowAni();
	void SetAni(int x,int y);
	
//	FILEREPORT f;
	HBITMAP hBm;
public:
	//按照行列平均分成几个
	int inum;
	int jnum;

	int width;
	int height;
	int screenwidth;
	int screenheight;
	HDC hdcdest;
	HDC hdcsrc;	

	//当前位置
	int xpos;
	int ypos;

	int iStartAni;
};


class MYBITMAPBTN:public MYBITMAP
{
public:
	MYBITMAPBTN();
	~MYBITMAPBTN();
	
	//show
	void Draw();
	//mouse detect
	int MouseOver(int x,int y);	
	int DetectMouseMove(int x,int y);

	int framenow;
};

class MYBITMAPOBJ:public MYBITMAP
{
public:
	MYBITMAPOBJ();
	~MYBITMAPOBJ();

	//show
	void DrawItem(int x,int y,int id);
};

class MYBITMAPOBJ_MASK:public MYBITMAP
{
public:
	MYBITMAPOBJ_MASK();
	~MYBITMAPOBJ_MASK();

	//show
	void DrawItem(int x,int y,int id);
};

class MYBKSKY:public MYBITMAP
{
public:
	MYBKSKY();
	~MYBKSKY();

	//show
	void DrawRoll(); //循环补空
	void DrawRollStretch(int x,int y);
	void DrawRollStretch(int x,int y,int id);
	void MoveTo(int x,int y);
	void MoveRoll(int x);

	//data
	int xseparate;
};

class MYANIOBJ:public MYBITMAP
{
public:
	MYANIOBJ();
	~MYANIOBJ();
	void InitAniList(int *pw,int *ph,int *py,int inum);

	//show
	void DrawItem(int x,int y,int id,int iframe);

	//
	int wlist[20];
	int hlist[20];
	int ylist[20];
};

class MYROLE:public MYBITMAP
{
public:
	MYROLE();
	~MYROLE();
	//init
	void InitRole(int xleft, int xright);
	void SetLimit(int xleft, int xright);
	//show
	void Draw();
	void Draw(int x,int y,int iframe);
	void ChangeFrame();
	void SetState(int i);
	void Move();
	void Jump();
	//ANI
	void MoveTo(int x,int y);
	void MoveOffset(int x,int y);
	void MoveStepTo(int x,int y);//向目的地移动单位距离
	


	//data
	int iState;
	int iFrame;
	int minx;
	int maxx;

	//move
	int movex;
	int movey;

	// jump
	int jumpheight;
	int jumpx;

	//方向
	int idirec;
};

#endif