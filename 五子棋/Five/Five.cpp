#include "stdafx.h"
#include "Five.h"
//#include "FiveFrame.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("Skin"));

	HRESULT Hr = ::CoInitialize(NULL);
	if( FAILED(Hr) )
	{
		return 0;
	}

	g_pFrame = new CFiveFrame();
	if( g_pFrame == NULL )
	{
		return 0;
	}
	g_pFrame->Create(NULL, _T(""), UI_WNDSTYLE_FRAME, 0L, 0, 0, 1024, 738);
	g_pFrame->CenterWindow();
	::ShowWindow(*g_pFrame, SW_SHOW);

	CPaintManagerUI::MessageLoop();
	::CoUninitialize();
	return 0;
}
