#ifndef __UIBASE_H__
#define __UIBASE_H__

#pragma once

namespace DuiLib {
/////////////////////////////////////////////////////////////////////////////////////
//

#define UI_WNDSTYLE_CONTAINER	(0)
#define UI_WNDSTYLE_FRAME		(WS_VISIBLE | WS_OVERLAPPEDWINDOW)
#define UI_WNDSTYLE_CHILD		(WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN)
#define UI_WNDSTYLE_DIALOG		(WS_VISIBLE | WS_POPUPWINDOW | WS_CAPTION | WS_DLGFRAME | WS_CLIPSIBLINGS | WS_CLIPCHILDREN)

#define UI_WNDSTYLE_EX_FRAME	(WS_EX_WINDOWEDGE)
#define UI_WNDSTYLE_EX_DIALOG	(WS_EX_TOOLWINDOW | WS_EX_DLGMODALFRAME)

#define UI_CLASSSTYLE_CONTAINER	(0)
#define UI_CLASSSTYLE_FRAME		(CS_VREDRAW | CS_HREDRAW)
#define UI_CLASSSTYLE_CHILD		(CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS | CS_SAVEBITS)
#define UI_CLASSSTYLE_DIALOG	(CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS | CS_SAVEBITS)


/////////////////////////////////////////////////////////////////////////////////////
//
#ifndef ASSERT
#define ASSERT(expr)	_ASSERTE(expr)
#endif

#ifdef _DEBUG
#ifndef TRACE
#define TRACE __Trace
#endif
#define TRACEMSG __TraceMsg
#else
#ifndef TRACE
#define TRACE
#endif
#define TRACEMSG _T("")
#endif

void UILIB_API __Trace(LPCTSTR pstrFormat, ...);
LPCTSTR UILIB_API __TraceMsg(UINT uMsg);

/////////////////////////////////////////////////////////////////////////////////////
//

class STRINGorID
{
public:
	STRINGorID(LPCTSTR lpString) : m_lpstr(lpString)
	{
	}
	STRINGorID(UINT nID) : m_lpstr(MAKEINTRESOURCE(nID))
	{
	}

	LPCTSTR m_lpstr;
};

/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CDuiPoint : public tagPOINT
{
public:
	CDuiPoint();
	CDuiPoint(const POINT& src);
	CDuiPoint(int x, int y);
	CDuiPoint(LPARAM lParam);
};


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CDuiSize : public tagSIZE
{
public:
	CDuiSize();
	CDuiSize(const SIZE& src);
	CDuiSize(const RECT rc);
	CDuiSize(int cx, int cy);
};


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CDuiRect : public tagRECT
{
public:
	CDuiRect();
	CDuiRect(const RECT& src);
	CDuiRect(int iLeft, int iTop, int iRight, int iBottom);

	int GetWidth() const;			// 获取宽度;
	int GetHeight() const;			// 获取高度;
	void Empty();					// 清空处理;
	bool IsNull() const;			// 判断为空;
	void Join(const RECT& rc);		// 保证this包含rc;
	void ResetOffset();				// 左上角移动至原点;
	void Normalize();				// 合理化处理;
	void Offset(int cx, int cy);	// 偏移操作;
	//void Inflate(int cx, int cy);	// 缩放操作;
	//void Deflate(int cx, int cy);	// ？？操作;
	//void Union(CDuiRect& rc);		// 联合操作,this与rc的并集;
};

/////////////////////////////////////////////////////////////////////////////////////
//

// 指针数组;
class UILIB_API CStdPtrArray
{
public:
	CStdPtrArray(int iPreallocSize = 0);
	CStdPtrArray(const CStdPtrArray& src);
	~CStdPtrArray();

	void Empty();								// 清空;
	void Resize(int iSize);						// 重置数值大小;并默认空值;	
	bool IsEmpty() const;						// 判断为空;
	int Find(LPVOID iIndex) const;				// 查找;
	bool Add(LPVOID pData);						// 添加;
	bool SetAt(int iIndex, LPVOID pData);		// 修改iIndex内容;
	bool InsertAt(int iIndex, LPVOID pData);	// 在iIndex添加内容，其余后移;
	bool Remove(int iIndex);					// 移除iIndex内容;
	int GetSize() const;						// 数组个数;
	LPVOID* GetData();							// 数据;

	LPVOID GetAt(int iIndex) const;				// 索引内容;	
	LPVOID operator[] (int nIndex) const;

protected:
	LPVOID* m_ppVoid;
	int m_nCount;
	int m_nAllocated;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CStdValArray
{
public:
	CStdValArray(int iElementSize, int iPreallocSize = 0);
	~CStdValArray();

	void Empty();
	bool IsEmpty() const;
	bool Add(LPCVOID pData);
	bool Remove(int iIndex);
	int GetSize() const;
	LPVOID GetData();

	LPVOID GetAt(int iIndex) const;
	LPVOID operator[] (int nIndex) const;

protected:
	LPBYTE m_pVoid;
	int m_iElementSize;	// 由于int\char等占用字节不一致,需要额外存储;
	int m_nCount;
	int m_nAllocated;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CStdString
{
public:
	enum { MAX_LOCAL_STRING_LEN = 63 };

	CStdString();
	CStdString(const TCHAR ch);
	CStdString(const CStdString& src);
	CStdString(LPCTSTR lpsz, int nLen = -1);
	~CStdString();

	void Empty();
	int GetLength() const;
	bool IsEmpty() const;
	TCHAR GetAt(int nIndex) const;
	void Append(LPCTSTR pstr);
	void Assign(LPCTSTR pstr, int nLength = -1);
	LPCTSTR GetData();

	void SetAt(int nIndex, TCHAR ch);
	operator LPCTSTR() const;

	TCHAR operator[] (int nIndex) const;
	const CStdString& operator=(const CStdString& src);
	const CStdString& operator=(const TCHAR ch);
	const CStdString& operator=(LPCTSTR pstr);
#ifdef _UNICODE
	const CStdString& CStdString::operator=(LPCSTR lpStr);
	const CStdString& CStdString::operator+=(LPCSTR lpStr);
#else
	const CStdString& CStdString::operator=(LPCWSTR lpwStr);
	const CStdString& CStdString::operator+=(LPCWSTR lpwStr);
#endif
	CStdString operator+(const CStdString& src) const;
	CStdString operator+(LPCTSTR pstr) const;
	const CStdString& operator+=(const CStdString& src);
	const CStdString& operator+=(LPCTSTR pstr);
	const CStdString& operator+=(const TCHAR ch);

	bool operator == (LPCTSTR str) const;
	bool operator != (LPCTSTR str) const;
	bool operator <= (LPCTSTR str) const;
	bool operator <  (LPCTSTR str) const;
	bool operator >= (LPCTSTR str) const;
	bool operator >  (LPCTSTR str) const;

	int Compare(LPCTSTR pstr) const;			// 不区分大小写;
	int CompareNoCase(LPCTSTR pstr) const;		// 区分大小写, 完全一致，没有区别;

	void MakeUpper();	// 全部大写;
	void MakeLower();	// 全部小写;

	CStdString Left(int nLength) const;
	CStdString Mid(int iPos, int nLength = -1) const;
	CStdString Right(int nLength) const;

	int Find(TCHAR ch, int iPos = 0) const;
	int Find(LPCTSTR pstr, int iPos = 0) const;
	int ReverseFind(TCHAR ch) const;
	int Replace(LPCTSTR pstrFrom, LPCTSTR pstrTo);

	int __cdecl Format(LPCTSTR pstrFormat, ...);
	int __cdecl SmallFormat(LPCTSTR pstrFormat, ...);

protected:
	LPTSTR m_pstr;
	TCHAR m_szBuffer[MAX_LOCAL_STRING_LEN + 1];
};


/////////////////////////////////////////////////////////////////////////////////////
//

struct TITEM
{
	CStdString Key;
	LPVOID Data;
	struct TITEM* pNext;
};

class UILIB_API CStdStringPtrMap
{
public:
	CStdStringPtrMap(int nSize = 83);
	~CStdStringPtrMap();

	void Resize(int nSize = 83);
	LPVOID Find(LPCTSTR key) const;
	bool Insert(LPCTSTR key, LPVOID pData);
	LPVOID Set(LPCTSTR key, LPVOID pData);
	bool Remove(LPCTSTR key);
	int GetSize() const;
	LPCTSTR GetAt(int iIndex) const;
	LPCTSTR operator[] (int nIndex) const;

protected:
	TITEM** m_aT;
	int m_nBuckets;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CWindowWnd
{
public:
	CWindowWnd();

	HWND GetHWND() const;
	operator HWND() const;	// 运算符 *this相当于GetHWND();

	bool RegisterWindowClass();
	bool RegisterSuperclass();

	HWND Create(HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, const RECT rc, HMENU hMenu = NULL);
	HWND Create(HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int cx = CW_USEDEFAULT, int cy = CW_USEDEFAULT, HMENU hMenu = NULL);
	HWND Subclass(HWND hWnd);
	void Unsubclass();
	void ShowWindow(bool bShow = true, bool bTakeFocus = true);
	UINT ShowModal();
	void Close(UINT nRet = IDOK);
	void CenterWindow();
	void SetIcon(UINT nRes);

	LRESULT SendMessage(UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0L);
	LRESULT PostMessage(UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0L);
	void ResizeClient(int cx = -1, int cy = -1);

protected:
	virtual LPCTSTR GetWindowClassName() const = 0;
	virtual LPCTSTR GetSuperClassName() const;
	virtual UINT GetClassStyle() const;

	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual void OnFinalMessage(HWND hWnd);

	static LRESULT CALLBACK __WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK __ControlProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:
	HWND m_hWnd;
	WNDPROC m_OldWndProc;
	bool m_bSubclassed;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CDuiWaitCursor
{
public:
	CDuiWaitCursor();
	~CDuiWaitCursor();

protected:
	HCURSOR m_hOrigCursor;
};

} // namespace DuiLib

#endif // __UIBASE_H__
