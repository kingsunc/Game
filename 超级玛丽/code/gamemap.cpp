#include "stdafx.h"
#include "gamemap.h"
#include "myclock.h"
#include "tool01.h"
#include "texttool.h"

//天空背景
extern MYBKSKY bmSky;

//角色
extern MYROLE rmain;

//计时器
extern MYCLOCK c1;

GAMEMAP::GAMEMAP()
{
	Init();
}

GAMEMAP::~GAMEMAP()
{
}

int GAMEMAP::LoadMap()
{
	FILE *fp;
	char temp[50]={0};
	int find=0;
	int i;
	
	
	memset(MapArray,0,sizeof(MapArray));
	iMapObjNum=0;
	
	memset(MapBkArray,0,sizeof(MapBkArray));
	iMapBkObjNum=0;
	
	memset(MapEnemyArray,0,sizeof(MapEnemyArray));
	iMapEnemyNum=0;
	
	memset(MapCoinArray,0,sizeof(MapCoinArray));
	iCoinNum=0;

	fp=fopen(PATH_MAP,"r");
	if(!fp)
	{
		return 0;
	}

	while(!find && !feof(fp))
	{
		FGetLine(temp,fp);
		if(temp[0]=='*' && temp[1]=='0'+iMatch)
		{
			find=1;
		}
	}
	if(!find)
	{
		return 0;
	}

	//找到了某一关的地图数据
	i=0;
	FGetLineJumpCom(temp,fp);	
	while(temp[0]!='#' && !feof(fp))
	{
		//map data
		sscanf(temp,"%d %d %d %d %d",
			&MapArray[i].x,
			&MapArray[i].y,
			&MapArray[i].w,
			&MapArray[i].h,
			&MapArray[i].id);			
		MapArray[i].show=0;
		iMapObjNum++;
		i++;
		FGetLineJumpCom(temp,fp);	
	}

	i=0;
	FGetLineJumpCom(temp,fp);	
	while(temp[0]!='#' && !feof(fp))
	{
		sscanf(temp,"%d %d %d %d %d",
			&MapBkArray[i].x,
			&MapBkArray[i].y,
			&MapBkArray[i].w,
			&MapBkArray[i].h,
			&MapBkArray[i].id);			
		MapBkArray[i].show=0;
		MapBkArray[i].iframe=0;
		iMapBkObjNum++;

		i++;
		FGetLineJumpCom(temp,fp);	
	}


	i=0;
	FGetLineJumpCom(temp,fp);	
	while(temp[0]!='#' && !feof(fp))
	{
		sscanf(temp,"%d %d %d %d %d %d %d",
			&MapEnemyArray[i].x,
			&MapEnemyArray[i].y,
			&MapEnemyArray[i].w,
			&MapEnemyArray[i].h,
			&MapEnemyArray[i].id,
			&MapEnemyArray[i].xleft,
			&MapEnemyArray[i].xright);			
		//动画元件，使用绝对坐标
		MapEnemyArray[i].x*=32;
		MapEnemyArray[i].y*=32;
		MapEnemyArray[i].xleft*=32;
		MapEnemyArray[i].xright*=32;
		MapEnemyArray[i].show=0;
		MapEnemyArray[i].movex=-ENEMY_STEP_X;
		iMapEnemyNum++;

		i++;
		FGetLineJumpCom(temp,fp);	
	}

	i=0;
	FGetLineJumpCom(temp,fp);	
	while(temp[0]!='#' && !feof(fp))
	{
		sscanf(temp,"%d %d %d %d %d",
			&MapCoinArray[i].x,
			&MapCoinArray[i].y,
			&MapCoinArray[i].w,
			&MapCoinArray[i].h,
			&MapCoinArray[i].id);			
		MapCoinArray[i].show=1;
		MapCoinArray[i].iframe=0;
		iCoinNum++;

		i++;
		FGetLineJumpCom(temp,fp);	
	}

	fclose(fp);
	return 1;
}

void GAMEMAP::Init()
{	
	iGameState=GAME_PRE;
	iMatch=0;
	iLife=3;
	iMoney=0;

	InitMatch();
}

void GAMEMAP::InitMatch()
{
	memset(MapArray,0,sizeof(MapArray));
	memset(MapBkArray,0,sizeof(MapBkArray));
	memset(MapEnemyArray,0,sizeof(MapEnemyArray));
	memset(BombArray,0,sizeof(BombArray));
	memset(MapCoinArray,0,sizeof(MapCoinArray));

	iMapObjNum=0;
	iMapBkObjNum=0;
	iMapEnemyNum=0;
	iBombNum=0;
	iCoinNum=0;

	viewx=0;
	viewy=0;

	ienemyframe=0;

	iFireNum=0;
	ifireframe=0;

	iTimeFire=0;
	iBeginFire=0;
	
	ibkobjframe=0;

	iCoinFrame=0;
}
void GAMEMAP::Show(MYBITMAPOBJ & bmobj)
{
	int i;
	int xstart,ystart;
	int j,k;

	for(i=0;i<iMapObjNum;i++)
	{
		ystart=MapArray[i].y*32;
		for(j=0;j<MapArray[i].h;j++)
		{
			xstart=MapArray[i].x*32;
			for(k=0;k<MapArray[i].w;k++)
			{
				//最上层的地面做特殊处理
				if(j==0 && MapArray[i].id%3==0)
				{
					bmobj.DrawItem(xstart,ystart,MapArray[i].id+2);			
				}
				else
					bmobj.DrawItem(xstart,ystart,MapArray[i].id);			
				xstart+=32;
			}
			ystart+=32;
		
		}
		
	}
}

//根据人物与视图的位置关系决定是否移动视图
int GAMEMAP::KeyProc(int iKey)
{
	switch(iGameState)
	{
	case GAME_PRE:
		switch(iKey)
		{
		case 0xd:	//enter
			c1.ReStart(TIME_GAME_IN_PRE); //停顿两秒
			iGameState=GAME_IN_PRE;
			return 1;
		}
		break;
		
	case GAME_IN:
		switch(iKey)
		{
		case VK_RIGHT:	
			if(rmain.movey!=0)
			{
				rmain.jumpx=4;
			}
			rmain.movex=4;
			rmain.idirec=0;
			break;
			
		case VK_LEFT:
			if(rmain.movey!=0)
			{
				rmain.jumpx=-4;
			}
			rmain.movex=-4;
			rmain.idirec=1;//朝左
			break;
			
		case KEY_X: //跳
			if(rmain.movey!=0)
				break;
			rmain.movey=-8;
			rmain.jumpx=rmain.movex;//解决x键和方向键的响应问题
			break;
			
		case KEY_Z: //FIRE
			if(iBeginFire)
				break;
			iTimeFire=0;
			iBeginFire=1;		
			break;
		}
		break;
	}

	return 0;
}

void GAMEMAP::SetViewState(int i)
{
	iViewState=i;
}
void GAMEMAP::SetGameState(int i)
{
	iGameState=i;
}

void GAMEMAP::MoveView()
{
	
	if(rmain.xpos - viewx > 150)
	{
		viewx+=ROLE_STEP;	
		if(viewx>(MAX_PAGE-1)*GAMEW*32)
			viewx=(MAX_PAGE-1)*GAMEW*32;
		
		//设置人物向左移动的最大范围
		rmain.SetLimit(viewx, GAMEW*32*MAX_PAGE);
	}

	//视图不能往右移

	bmSky.SetPos(BM_USER,viewx,0);
	
}

void GAMEMAP::ShowBkObj(MYANIOBJ & bmobj)
{
	int i;
	int xstart,ystart;

	for(i=0;i<iMapBkObjNum;i++)
	{
		ystart=MapBkArray[i].y*32;
		xstart=MapBkArray[i].x*32;
		bmobj.DrawItem(xstart,ystart,MapBkArray[i].id,ibkobjframe);	
	}
}


void GAMEMAP::ShowInfo(HDC h)
{
	char temp[50]={0};

	SetTextColor(h, TC_WHITE);
	SetBkColor(h, TC_BLACK);

	sprintf(temp, "LIFE  : %d",iLife);
	TextOut(h, 220,100,temp,strlen(temp));

	sprintf(temp, "WORLD : %d",iMatch+1);
	TextOut(h, 220,130,temp,strlen(temp));
}

void GAMEMAP::ShowOther(HDC h)
{
	char temp[50]={0};

	//show money
	sprintf(temp,"MONEY: %d",iMoney);
	TextOut(h,viewx+20,20,temp,strlen(temp));
}
void GAMEMAP::ShowAniObj(MYANIOBJ & bmobj)
{
	int i;
	int xstart,ystart;

	//显示敌人
	for(i=0;i<iMapEnemyNum;i++)
	{
		if (!MapEnemyArray[i].show)
		{
			continue;
		}
		ystart=MapEnemyArray[i].y;
		xstart=MapEnemyArray[i].x;
		bmobj.DrawItem(xstart,ystart,MapEnemyArray[i].id,ienemyframe);	
	}

	//显示子弹
	for(i=0;i<MAX_MAP_OBJECT;i++)
	{
		if (FireArray[i].show)
		{
			ystart=FireArray[i].y;
			xstart=FireArray[i].x;
			bmobj.DrawItem(xstart,ystart,FireArray[i].id,ifireframe);
		}
	}

	for(i=0;i<iCoinNum;i++)
	{
		ystart=MapCoinArray[i].y*32;
		xstart=MapCoinArray[i].x*32;
		bmobj.DrawItem(xstart,ystart,MapCoinArray[i].id, iCoinFrame);	
	}

	//bomb
	for(i=0;i<MAX_MAP_OBJECT;i++)
	{
		if (BombArray[i].show)
		{
			ystart=BombArray[i].y;
			xstart=BombArray[i].x;
			bmobj.DrawItem(xstart,ystart,BombArray[i].id, BombArray[i].iframe);	
		}
	}
}

// 返回0，不能走；1，能走
int GAMEMAP::RoleCanMove(int xoff, int yoff)
{
	int i;
	
	if(xoff>0)
	{
		//右侧
		for(i=0;i<iMapObjNum;i++)
		{
			if( VLINE_IN_RECT(rmain.xpos+xoff+32,
				rmain.ypos+yoff,
				32,
				MapArray[i].x*32,
				MapArray[i].y*32,
				MapArray[i].w*32,
				MapArray[i].h*32)
				)
			{
				return 0;
			}
		}
		return 1;
	}
	else if(xoff<0)
	{
		//左侧
		for(i=0;i<iMapObjNum;i++)
		{
			if( VLINE_IN_RECT(rmain.xpos+xoff,
				rmain.ypos+yoff,
				32,
				MapArray[i].x*32,
				MapArray[i].y*32,
				MapArray[i].w*32,
				MapArray[i].h*32)
				)
			{
				return 0;
			}
		}
		return 1;
	}

	if(yoff>0)
	{
		//下方
		for(i=0;i<iMapObjNum;i++)
		{
			if( HLINE_IN_RECT(rmain.xpos+xoff,
				rmain.ypos+yoff+32,
				32,
				MapArray[i].x*32,
				MapArray[i].y*32,
				MapArray[i].w*32,
				MapArray[i].h*32)
				)
				return 0;
		}
		return 1;
	}
	else if(yoff<0)
	{
		//上方
		for(i=0;i<iMapObjNum;i++)
		{
			if( HLINE_IN_RECT(rmain.xpos+xoff,
				rmain.ypos+yoff,
				32,
				MapArray[i].x*32,
				MapArray[i].y*32,
				MapArray[i].w*32,
				MapArray[i].h*32)
				)
			{
				//碰撞后反向
				rmain.movey=4;
				return 0;
			}
		}
		return 1;
	}

	return 1;
}

int GAMEMAP::CheckRole()
{
	int i;
	
	//角色的检查
	if(rmain.movey == 0 )
	{
		//在水平移动，
		//检测角色是否站在某个物体上
		for(i=0;i<iMapObjNum;i++)
		{
			//下方线
			if( LINE_ON_LINE(rmain.xpos,
				rmain.ypos+32,
				32,
				MapArray[i].x*32,
				MapArray[i].y*32,
				MapArray[i].w*32)
				)
			{				
				return 1;
			}
		}
		//角色开始下落
		rmain.movey=SPEED_DOWN;	
		rmain.jumpx=0;//此时要清除跳跃速度，否则将变成跳跃，而不是落体
		return 0;
	}

	if(rmain.movey > 0 )
	{
		//down
		//检测角色是否站在某个物体上
		for(i=0;i<iMapObjNum;i++)
		{
			//下方线
			if( LINE_ON_LINE(rmain.xpos,
				rmain.ypos+32,
				32,
				MapArray[i].x*32,
				MapArray[i].y*32,
				MapArray[i].w*32)
				)
			{
				rmain.jumpheight=0;
				rmain.movey=0;
				return 1;
			}
		}
		return 0;
	}

	return 0;
}


int GAMEMAP::CheckAni(int itimeclip)
{
	int i,j;
	int tempx,tempy;

	//发子弹
	if(iBeginFire)
	{
		if(0 == iTimeFire )
		{
			FireArray[iFireNum].show=1;
			FireArray[iFireNum].x=rmain.xpos;
			FireArray[iFireNum].y=rmain.ypos;
			FireArray[iFireNum].id=ID_ANI_FIRE;
			if(0==rmain.idirec)
			{
				FireArray[iFireNum].movex=FIRE_SPEED;
			}
			else
			{
				FireArray[iFireNum].movex=-FIRE_SPEED;
			}
			iFireNum=(iFireNum+1)%MAX_MAP_OBJECT;
			iTimeFire=1;
		}
		iTimeFire=(iTimeFire+1)%TIME_FIRE_BETWEEN;
	}


	//检查敌人，动画元件
	for(i=0;i<iMapEnemyNum;i++)
	{
		if ( IN_AREA(MapEnemyArray[i].x, viewx, VIEWW) )
		{
			MapEnemyArray[i].show=1;			
		}
		else
		{
			MapEnemyArray[i].show=0;
		}		
	}

	//子弹移动
	for(i=0;i<MAX_MAP_OBJECT;i++)
	{
		if (FireArray[i].show)
		{
			FireArray[i].x+=FireArray[i].movex;
			if( FireArray[i].x > viewx+VIEWW || FireArray[i].x<viewx)
			{
				FireArray[i].show = 0;
			}
		}
	}
		
	//检测子弹和敌人的碰撞
	for(i=0;i<iMapEnemyNum;i++)
	{
		if(MapEnemyArray[i].show)
		{
			for(j=0;j<MAX_MAP_OBJECT;j++)
			{
				if (FireArray[j].show)
				{
					if(RECT_HIT_RECT(FireArray[j].x,
						FireArray[j].y+FIRE_XOFF,
						FIREW,
						FIREH,
						MapEnemyArray[i].x,
						MapEnemyArray[i].y,
						MapEnemyArray[i].w*32,
						MapEnemyArray[i].h*32)
						)
					{
						ClearEnemy(i);
						FireArray[j].show=0;
						return 0;
					}
				}
			}
		}
	}

	//检测角色和金币的碰撞
	for(i=0;i<iCoinNum;i++)
	{
		tempx=MapCoinArray[i].x*32;
		tempy=MapCoinArray[i].y*32;
		
		if ( IN_AREA(tempx, viewx, VIEWW) )
		{
			if(	RECT_HIT_RECT(rmain.xpos,
				rmain.ypos,
				32,32,
				tempx,
				tempy,
				32,32)
				)
			{
				iMoney+=10;
				ClearCoin(i);
				return 0;
			}		
		}
	}


	///////////// 帧控制 ////////////////
	if(0 == itimeclip% ENEMY_SPEED)
	{
		//帧控制
		ienemyframe=1-ienemyframe;
		//敌人移动
		for(i=0;i<iMapEnemyNum;i++)
		{
			if(MapEnemyArray[i].show)
			{
				MapEnemyArray[i].x+=MapEnemyArray[i].movex;

				//控制敌人移动
				if(MapEnemyArray[i].movex<0)
				{
					if(MapEnemyArray[i].x<=MapEnemyArray[i].xleft)
					{
						MapEnemyArray[i].movex=ENEMY_STEP_X;
					}
				}
				else 
				{
					if(MapEnemyArray[i].x>=MapEnemyArray[i].xright)
					{
						MapEnemyArray[i].movex=-ENEMY_STEP_X;				
					}
				}
			}	
		}

	}

	if(0 == itimeclip% WATER_SPEED)
	{
		ibkobjframe=1-ibkobjframe;
		iCoinFrame=(iCoinFrame+1)%4;
	}

	//子弹
	ifireframe=1-ifireframe;

	//bomb frame control
	for(i=0;i<MAX_MAP_OBJECT;i++)
	{
		if(BombArray[i].show)
		{
			BombArray[i].iframe++;
			if(BombArray[i].iframe>3)
			{
				BombArray[i].show=0;
			}
		}	
	}
	return 0;
}

void GAMEMAP::ClearEnemy(int i)
{
	if(i<0 || i>=iMapEnemyNum)
		return;

	//create bomb
	BombArray[iBombNum].show=1;
	BombArray[iBombNum].id=ID_ANI_BOMB;
	BombArray[iBombNum].iframe=0;
	BombArray[iBombNum].x=MapEnemyArray[i].x-BOMB_XOFF;
	BombArray[iBombNum].y=MapEnemyArray[i].y-BOMB_YOFF;
	iBombNum=(iBombNum+1)%MAX_MAP_OBJECT;


	for(;i<iMapEnemyNum;i++)
	{
		MapEnemyArray[i]=MapEnemyArray[i+1];
	}
	iMapEnemyNum--;
}
void GAMEMAP::ClearCoin(int i)
{
	if(i<0 || i>=iCoinNum)
		return;

	BombArray[iBombNum].show=1;
	BombArray[iBombNum].id=ID_ANI_COIN;
	BombArray[iBombNum].iframe=0;
	BombArray[iBombNum].x=MapCoinArray[i].x*32-COIN_XOFF;
	BombArray[iBombNum].y=MapCoinArray[i].y*32-COIN_YOFF;
	iBombNum=(iBombNum+1)%MAX_MAP_OBJECT;

	//create bomb
/*	BombArray[iBombNum].show=1;
	BombArray[iBombNum].id=ID_ANI_COIN;
	BombArray[iBombNum].iframe=0;
	BombArray[iBombNum].x=MapCoinArray[i].x*32-COIN_XOFF;
	BombArray[iBombNum].y=MapCoinArray[i].y*32-COIN_YOFF;
	iBombNum=(iBombNum+1)%MAX_MAP_OBJECT;
*/
	//create bomb
	for(;i<iCoinNum;i++)
	{
		MapCoinArray[i]=MapCoinArray[i+1];
	}
	iCoinNum--;
}

int GAMEMAP::IsWin()
{
	int i;

	//检测角色和敌人的碰撞
	for(i=0;i<iMapEnemyNum;i++)
	{
		if(MapEnemyArray[i].show)
		{
			if(HLINE_ON_RECT(rmain.xpos, rmain.ypos+32,32,
				MapEnemyArray[i].x,
				MapEnemyArray[i].y,
				MapEnemyArray[i].w*32,
				MapEnemyArray[i].h*32))
			{
				if(0 == rmain.movey)
				{
					Fail();
				}
				else
				{
					//踩到敌人上
					ClearEnemy(i);
				}
				return 0;
			}
		}
	}

	if(rmain.ypos > GAMEH*32)
	{
	
		Fail();
		return 0;
	}

	//到达目的地后，自动走到屏幕右侧
	if(rmain.xpos > X_WIN*32 )
	{
		iGameState=GAME_WIN;

		//到达目的地
		rmain.MoveStepTo(MAX_PAGE*GAMEW*32, Y_WIN*32);
	}

	if(rmain.xpos >= MAX_PAGE*GAMEW*32 )
	{
		iGameState=GAME_WIN_WAIT;
		c1.ReStart(TIME_GAME_WIN_WAIT);

		InitMatch();
		
		rmain.SetPos(BM_USER,3*32,8*32);
		rmain.InitRole(0,GAMEW*32*MAX_PAGE-32);
		
		iMatch++;
		if(iMatch>=MAX_MATCH)
		{
			//全部通过
			Init();
			iGameState=GAME_PASS;			
		}
		LoadMap();   
		
		return 1;
	}

	return 1;
}

void GAMEMAP::Fail_Wait()
{
	InitMatch();

	if(	iLife <=0)
	{
		Init();
		iGameState=GAME_OVER;
		c1.ReStart(TIME_GAME_END);	
	}
	else
	{
		iGameState=GAME_IN_PRE;
		c1.ReStart(TIME_GAME_IN_PRE);	
	}
	
	rmain.SetPos(BM_USER,3*32,8*32);
	rmain.InitRole(0,GAMEW*32*MAX_PAGE-32);

	LoadMap();   
	
}

void GAMEMAP::Fail()
{
	rmain.movex=0;
	rmain.movey=0;

	iLife--;
	rmain.iFrame=FAIL_FRAME;
	
	iGameState=GAME_FAIL_WAIT;
	c1.ReStart(TIME_GAME_FAIL_WAIT);
	c1.SetShow(0);
}


void GAMEMAP::KeyUpProc(int iKey)
{
	switch(iKey)
	{
	case VK_RIGHT:	
		rmain.movex=0;
		break;

	case VK_LEFT:
		rmain.movex=0;
		break;

	case KEY_X: //跳
		break;

	case KEY_Z: //FIRE
		iBeginFire=0;
		break;
	}
	SetViewState(STATE_VIEW_STOP);
}