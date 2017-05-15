#pragma once

#define	PNG_NONE				_T("")						// 无图;
#define	PNG_BLACK_NORMAL		_T("black_normal.png")		// 普通黑棋;
#define	PNG_WHITE_NORMAL		_T("white_normal.png")		// 普通白棋;
#define	PNG_BLACK_CLICKED		_T("black_click.png")		// 刚下的黑棋;
#define	PNG_WHITE_CLICKED		_T("white_click.png")		// 刚下的白棋;
#define	PNG_UNIT_HOVER			_T("unit_hover.png")		// 悬浮十字叉;

enum UnitType
{
	E_BLACK	= -1,		// 黑;
	E_NONE	= 0,		// 无;
	E_WHITE	= 1			// 白;
};

// 棋子单元格;
class CUnitLayout: public CLabelUI
{
public:
	CUnitLayout();
	~CUnitLayout();

	virtual void DoEvent(TEventUI& event);

public:
	void SetUnitIndex(int iUnitIndex);
	void Begin();		// 开始;
	//int Validate();		// 验证

	int GetUnitType();

private:
	int	m_iUnitIndex;	// 记录步数;
};

