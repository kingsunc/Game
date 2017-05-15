#pragma once
#include "DuiBaseWindow.h"
#include "UnitLayout.h"

// CFiveFrame 对话框
class CFiveFrame : public CDuiBaseWindow
{
public:
	CFiveFrame();
	~CFiveFrame();

	LPCTSTR GetWindowClassName() const;

	virtual CStdString GetSkinFolder();
	virtual CStdString GetSkinFile();

	virtual void Init();
	virtual void OnFinalMessage(HWND hWnd);

	// 键盘响应;
	virtual LRESULT ResponseDefaultKeyEvent(WPARAM wParam);

	virtual CControlUI* CreateControl(LPCTSTR pstrClass);

	virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	// Caption双击事件;
	virtual LRESULT OnNcLButtonDbClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

protected:	

	void Notify(TNotifyUI& msg);

public:
	void BeginGame();		// 开始游戏;
	void EndGame();			// 结束游戏;

	int ValidateGame();	//	验证游戏;

private:

	CUnitLayout*		m_pArrUnit[15][15];		// 此处存指针，而不是对象;因为对象二次析构导致挂机
};