#if !defined(AFX_OUTPUT_H__87AC0620_10B7_4728_9BBE_59E5E509A7BA__INCLUDED_)
#define AFX_OUTPUT_H__87AC0620_10B7_4728_9BBE_59E5E509A7BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Resource.h"
// Output.h : header file
//用户程序输出窗口类

/////////////////////////////////////////////////////////////////////////////
// COutput dialog
#include "datastructure.h"

class COutput : public CDialog
{
// Construction
public:

	CRect				m_rtIcon;				//程序图标位置
	CRect				m_rtButtMax;			//最大化按钮位置
	CRect				m_rtButtMin;			//最小化按钮位置
	CRect				m_rtButtExit;			//关闭按钮位置
    
	COutput(CWnd* pParent = NULL);   // standard constructor
 
// Dialog Data
	//{{AFX_DATA(COutput)
	enum { IDD = IDD_DIALOG2 };
	CListBox	m_DisplayList;    //显示display表的对象
	CListBox	m_DataStack;      //显示运行栈的对象
	CEdit	m_stab;               //显示常量字符串
	CListBox	m_Rconst;         //显示实常数的对象
	CListCtrl	m_BtabList;       //显示分程序的对象
	CListCtrl	m_TabList;        //显示符号表的对象
	CListCtrl   m_ArrayList;          //数组信息向量表的对象
	CListBox	m_PcodeList;      //显示p代码的对象
	CString	m_szOutput;           //用户程序输出的信息
	CToolTipCtrl m_ToolTip;       //弹出提示对象
	CString	m_baseIndex;    //解释执行时运行栈当前的基地址
	CString	m_lineNum;              //当前源程序行号
	int		m_breakPoint;          //断点行号
	CString	m_lineContent;         //输出内容
	//}}AFX_DATA
	


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutput)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COutput)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnDblclkList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkList3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkList7(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	
	//}}AFX_MSG

public:
	void DrawTitleBar(CDC *pDC);
	void outputs(char *s,int start,int len);
	void outputarray(int a);
	void ShowLine(int line);
	bool isFinish();
	void ShowTables();
	conrec inputdata(int kind);
    void outputTab(int t);
    void outputBtab(int b);
    void outputRconst(int c2);
    void ouptputStab(int sx);
    void outputi(int i);
    void outputf(double f);
    void outputc(char c);
    void outputPcode(int pc);
    void outputDataStack(int t,int b);
    void outputDisplay(int *display,int h2,bool flag);
    void interpretInit(char *file);
    void interpretStep(int &t,int &b);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTPUT_H__87AC0620_10B7_4728_9BBE_59E5E509A7BA__INCLUDED_)
