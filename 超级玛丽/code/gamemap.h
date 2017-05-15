#ifndef __GAMEMAP
#define __GAMEMAP

#include "bitmaptool.h"

struct MapObject
{
	int x;
	int y;
	int w;
	int h;
	int id;
	int iframe;
	int show;	//是否显示
};

struct ROLE
{
	int x;
	int y;
	int w;
	int h;
	int id;
	int iframe;
	int xleft;
	int xright;
	int movex;

	int show;	//是否显示
};

class GAMEMAP
{
public:
	int LoadMap();
	
	void Init();
	void InitMatch();
	//入参,物体索引图
	void Show(MYBITMAPOBJ & bmobj);
	//入参,背景物体索引图
	void ShowBkObj(MYANIOBJ & bmobj);
	//入参,动画物体索引图
	void ShowAniObj(MYANIOBJ & bmobj);

	void ShowInfo(HDC h);
	void ShowOther(HDC h);

	//键盘处理
	int KeyProc(int iKey);
	void KeyUpProc(int iKey);

	void MoveView();
	void SetViewState(int i);
	void SetGameState(int i);
	//hittest
	int RoleCanMove(int xoff, int yoff);
	int CheckRole();
	int CheckAni(int itimeclip);//入参，时间片
	void ClearEnemy(int i);
	void ClearCoin(int i);
	//逻辑检测
	int IsWin();
	void Fail();
	void Fail_Wait();
	
	GAMEMAP();
	~GAMEMAP();
	
	//data
	int iMatch;
	int iLife;
	int iGameState;
	int iMoney;

	struct MapObject MapArray[MAX_MAP_OBJECT];
	int iMapObjNum;

	struct MapObject MapBkArray[MAX_MAP_OBJECT];
	int iMapBkObjNum;

	struct ROLE MapEnemyArray[MAX_MAP_OBJECT];
	int iMapEnemyNum;

	struct MapObject MapCoinArray[MAX_MAP_OBJECT];
	int iCoinNum;

	//view
	int viewx;
	int viewy;
	int iViewState;

	//frame control
	int ienemyframe;

	int ibkobjframe;

	int iCoinFrame;

	//FIRE
	struct ROLE FireArray[MAX_MAP_OBJECT];
	int iFireNum;
	int iTimeFire;//两个子弹的时间间隔
	int iBeginFire;
	int ifireframe;

	//bomb
	struct MapObject BombArray[MAX_MAP_OBJECT];
	int iBombNum;

};

#endif