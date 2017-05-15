// mario01.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"

#include "bitmaptool.h"
#include "texttool.h"
#include "gamemap.h"
#include "myclock.h"

#define MAX_LOADSTRING 100

char *pPreText[]={
	"制作: programking 2008年6月",
	"操作:    Z:子弹    X:跳    方向键:左右移动 ",
	"按 回车键 开始",
};

int mapani[3][5]={
{32,32,64,32,32},
{32,32,64,32,32},
{0,64,128,256,320},
};


int mapanibk[3][3]={
{96,96,96},
{64,64,64},
{0,128,256},
};

//FILEREPORT f1;
TEXTAREA t1,t2;

MYCLOCK c1;

GAMEMAP gamemap;

MYBITMAP bmPre;
MYBKSKY bmSky;

MYBITMAPOBJ bmMap;
MYANIOBJ bmMapBkObj;
MYANIOBJ bmAniObj;
MYROLE rmain;

HDC hwindow,hscreen,hmem;
HBITMAP hmapnull;

int wwin,hwin;


// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The title bar text

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MARIO01, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_MARIO01);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_MARIO01);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
//	wcex.lpszMenuName	= (LPCSTR)IDC_MARIO01;
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   wwin=GetSystemMetrics(SM_CXSCREEN);
   hwin=GetSystemMetrics(SM_CYSCREEN);
   //dc
   hwindow=GetDC(hWnd);
   hscreen=CreateCompatibleDC(hwindow);
   hmem=CreateCompatibleDC(hwindow);
   
   //bitmap
   hmapnull=CreateCompatibleBitmap(hwindow,GAMEW*32*5,GAMEH*32);
	SelectObject(hscreen,hmapnull);
	SelectObject(hmem,hmapnull);

   ReleaseDC(hWnd, hwindow);

   //text
   t1.Init(pPreText[0]);
   t1.SetDevice(hscreen,hmem,GAMEW*32,GAMEH*32);
   t1.SetPos(TEXT_USER,180,260);
   t1.SetColor(TC_BLACK, TC_BLUE);

   t2.Init(pPreText[2]);
   t2.SetDevice(hscreen,hmem,GAMEW*32,GAMEH*32);
   t2.SetPos(TEXT_USER,180,300);
   t2.SetColor(TC_BLACK, TC_WHITE);

   //pic
   bmPre.Init(hInstance,IDB_BITMAP_PRE1,1,4);
   bmPre.SetDevice(hscreen,hmem,GAMEW*32,GAMEH*32);
   bmPre.SetPos(BM_USER,0,0);

   bmSky.Init(hInstance,IDB_BITMAP_MAP_SKY,1,3);
   bmSky.SetDevice(hscreen,hmem,GAMEW*32*MAX_PAGE,GAMEH*32);
   bmSky.SetPos(BM_USER,0,0);

   bmMap.Init(hInstance,IDB_BITMAP_MAP,9,1);
   bmMap.SetDevice(hscreen,hmem,GAMEW*32*MAX_PAGE,GAMEH*32);

   bmMapBkObj.Init(hInstance,IDB_BITMAP_MAP_BK,1,1);
   bmMapBkObj.SetDevice(hscreen,hmem,GAMEW*32*MAX_PAGE,GAMEH*32);
   bmMapBkObj.InitAniList(mapanibk[0],mapanibk[1],mapanibk[2],3);

   bmAniObj.Init(hInstance,IDB_BITMAP_ANI,1,1);
   bmAniObj.SetDevice(hscreen,hmem,GAMEW*32*MAX_PAGE,GAMEH*32);
   bmAniObj.InitAniList(mapani[0],mapani[1],mapani[2],sizeof(mapani[0])/sizeof(int));

   rmain.Init(hInstance,IDB_BITMAP_ROLE,5,1);
   rmain.SetDevice(hscreen,hmem,GAMEW*32*MAX_PAGE,GAMEH*32);

   //map
   gamemap.Init();
   rmain.SetPos(BM_USER,3*32,8*32);
   rmain.InitRole(0,GAMEW*32*MAX_PAGE-32);
   gamemap.LoadMap();   
   
   c1.SetDevice(hscreen);
   c1.Begin(hWnd, GAME_TIME_CLIP ,-1);

   MoveWindow(hWnd, 
	   (wwin-GAMEW*32)/2,
	    (hwin-GAMEH*32)/2,
		GAMEW*32,
		GAMEH*32+32,
	  false);
   
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	TCHAR szHello[MAX_LOADSTRING];
	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);

	switch (message) 
	{
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
				case IDM_ABOUT:
				   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
				   break;
				case IDM_EXIT:
				   DestroyWindow(hWnd);
				   break;
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_PAINT:
			hwindow = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code here...
			SelectObject(hscreen,hmapnull);

			switch(gamemap.iGameState)
			{
			case GAME_PRE:
				bmPre.Stretch(2,2,0);	
				t1.Draw();
				t2.Draw(pPreText[1],150,290);
				t2.Draw(pPreText[2],150,320);
				//TextOut(hscreen,200,50,pPreText[0], strlen(pPreText[0]));
				BitBlt(hwindow,0,0,GAMEW*32,GAMEH*32,
					hscreen,0,0,SRCCOPY);
				break;

			case GAME_IN_PRE:
				bmPre.Stretch(2,2,2);	
				gamemap.ShowInfo(hscreen);
				BitBlt(hwindow,0,0,GAMEW*32,GAMEH*32,
					hscreen,0,0,SRCCOPY);
				break;

			case GAME_IN:
			case GAME_WIN:
			case GAME_FAIL_WAIT:
				bmSky.DrawRollStretch(2,2,gamemap.iMatch);
				gamemap.ShowBkObj(bmMapBkObj);
				gamemap.Show(bmMap);
				gamemap.ShowAniObj(bmAniObj);
				gamemap.ShowOther(hscreen);
				rmain.Draw();
				c1.Show(gamemap.viewx+VIEWW-100,20);
				BitBlt(hwindow,0,0,GAMEW*32,GAMEH*32,hscreen,gamemap.viewx,0,SRCCOPY);
				break;

			case GAME_OVER:
				//输出图片GAME OVER
				bmPre.Stretch(2,2,1);	
				BitBlt(hwindow,0,0,GAMEW*32,GAMEH*32,
					hscreen,0,0,SRCCOPY);
				break;
					
			case GAME_PASS:
				//输出图片GAME OVER
				bmPre.Stretch(2,2,3);	
				BitBlt(hwindow,0,0,GAMEW*32,GAMEH*32,
					hscreen,0,0,SRCCOPY);
				break;
			}

			EndPaint(hWnd, &ps);
			break;

		case WM_TIMER:
			switch(gamemap.iGameState)
			{
			case GAME_PRE:
				break;

			case GAME_IN_PRE:
				if(c1.DecCount())
				{
					gamemap.SetGameState(GAME_IN);
					c1.ReStart(TIME_GAME_IN);					
				}
				InvalidateRect(hWnd,NULL,false);
				break;
				
			case GAME_IN:
			case GAME_WIN:
				if(c1.DecCount())
				{
					gamemap.Fail();
				}
				if(0 == c1.iNum%5)
				{
					bmSky.MoveRoll(1);//云彩移动
				}
				rmain.Move();//人物移动
				gamemap.MoveView();//视图移动
				gamemap.CheckRole();
				gamemap.CheckAni(c1.iNum);
				gamemap.IsWin();
				InvalidateRect(hWnd,NULL,false);
				break;

			case GAME_WIN_WAIT:
				if(c1.DecCount())
				{
					gamemap.SetGameState(GAME_IN_PRE);					
					InvalidateRect(hWnd,NULL,false);
				}
				break;

			case GAME_FAIL_WAIT:
				if(c1.DecCount())
				{
					gamemap.Fail_Wait();
				}
				break;

			case GAME_PASS:
				if(c1.DecCount())
				{
					gamemap.SetGameState(GAME_PRE);					
				}
				InvalidateRect(hWnd,NULL,false);
				break;
					
			case GAME_OVER:
				if(c1.DecCount())
				{
					gamemap.SetGameState(GAME_PRE);					
				}
				InvalidateRect(hWnd,NULL,false);
				break;
			}
			break;

		case WM_KEYDOWN:
			if(gamemap.KeyProc(wParam))	
				InvalidateRect(hWnd,NULL,false);
			break;

		case WM_KEYUP:
			gamemap.KeyUpProc(wParam);						
			break;

		case WM_DESTROY:
			c1.Destroy();
			DeleteObject((HBITMAP)hmapnull);
			DeleteDC(hwindow);
			DeleteDC(hscreen);
			DeleteDC(hmem);

			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}

