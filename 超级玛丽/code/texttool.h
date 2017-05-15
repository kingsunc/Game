#ifndef __TEXTTOOL
#define __TEXTTOOL

#define TEXT_BOTTOM_RIGHT 0
#define TEXT_BOTTOM_CENTER 1
#define TEXT_CENTER 2
#define TEXT_USER 3

#define TC_BLACK RGB(0,0,0)
#define TC_BLUE RGB(0,0,255)
#define TC_WHITE RGB(255,255,255)

class TEXTAREA
{
public:
	TEXTAREA();
	~TEXTAREA();

	void SetDevice(HDC hdest,HDC hsrc,int wwin,int hwin);
	void SetPos(int istyle,int x,int y);
	
	void Init(char *p);
	void SetColor(COLORREF cbk, COLORREF ctext);

	//显示	
	void Draw();
	void Draw(char *p,int x,int y);
	void Stretch(int x,int y);

	int width;
	int height;
	int screenwidth;
	int screenheight;
	HDC hdcdest;
	HDC hdcsrc;	

	//当前位置
	int xpos;
	int ypos;

	char *ptext;
	COLORREF c1;
	COLORREF c2;
};
#endif
