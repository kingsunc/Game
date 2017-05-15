#ifndef __FILEREPORT
#define __FILEREPORT

class FILEREPORT
{
public:
	FILEREPORT();
	FILEREPORT(char *p);
	~FILEREPORT();
	
	void put(char *p);
	void put(char *p,int a,int b);
	void putnum(int i,char *p);
	
	//////////	
	void CheckDC(HDC h,char *p);

	//show
	void SetDevice(HDC h,int x,int y);
	void Output(char *p,int a,int b);
	void Show();


private:
	FILE *fp;

	//¼ÆÊýÆ÷×é
	int num[5];

	//show
	HDC hshow;
	int xpos;
	int ypos;
	char info[50];

};

#endif