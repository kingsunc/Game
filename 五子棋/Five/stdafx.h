// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <objbase.h>
#include "resource.h"

// TODO: 在此处引用程序需要的其他头文件;

#include "DuilibProInc.h"
#include "FiveFrame.h"

extern	int g_iUnitIndex;
extern	CFiveFrame* g_pFrame;