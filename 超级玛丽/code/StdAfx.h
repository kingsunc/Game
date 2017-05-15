// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
#define AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers


// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// Local Header Files
#include <stdio.h>
#include <math.h>
#include <ctype.h>

// TODO: reference additional headers your program requires here
#define GAMEW 16
#define GAMEH 12

#define VIEWW GAMEW*32
#define VIEWH GAMEH*32

#define MAX_MAP_OBJECT 30
#define MAX_PAGE 5

//time
#define GAME_TIME_CLIP 40

#define TIME_GAME_IN 300
#define TIME_GAME_IN_PRE 2
#define TIME_GAME_END 3
#define TIME_GAME_WIN_WAIT 2
#define TIME_GAME_FAIL_WAIT 2


//game
#define MAX_MATCH 3

#define GAME_PRE 0
#define GAME_IN 1
#define GAME_WIN 2
#define GAME_OVER 3
#define GAME_IN_PRE 4
#define GAME_PASS 5
#define GAME_WIN_WAIT 6
#define GAME_FAIL_WAIT 7

//role
#define ROLE_STEP 4
#define JUMP_HEIGHT 3
#define FAIL_FRAME 2

//map
#define LOAD_MAP 1
#define LOAD_MAP_BK_OBJ 2
#define LOAD_MAP_ENEMY 3

#define PATH_MAP "map\\map1.txt"
#define PATH_MAP_BK_OBJ "map\\mapbk1.txt"
#define PATH_MAP_ENEMY "map\\mapenemy.txt"

//fire
#define FIREW 17
#define FIREH 17
#define FIRE_XOFF 32-FIREW

//bomb
#define BOMB_XOFF 20
#define BOMB_YOFF 23
#define COIN_XOFF 0
#define COIN_YOFF 32
//ani
#define ID_ANI_FIRE 1
#define ID_ANI_BOMB 2
#define ID_ANI_COIN 4


#define ID_BK_WATER 2


//view
#define STATE_VIEW_STOP 0

//speed
#define SPEED_DOWN 16
#define ENEMY_STEP_X 2

#define ENEMY_SPEED 2
#define WATER_SPEED 5

#define FIRE_SPEED 12
#define TIME_FIRE_BETWEEN 5

//WIN
#define X_WIN 73
#define Y_WIN 8
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
