#if !defined(AFX_OUTPUT_H__87AC0620_10B7_4728_9BBE_59E5E509A7BA__INCLUDED_)
#define AFX_OUTPUT_H__87AC0620_10B7_4728_9BBE_59E5E509A7BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Resource.h"
// Output.h : header file
//�û��������������

/////////////////////////////////////////////////////////////////////////////
// COutput dialog
#include "datastructure.h"

class COutput : public CDialog
{
// Construction
public:

	CRect				m_rtIcon;				//����ͼ��λ��
	CRect				m_rtButtMax;			//��󻯰�ťλ��
	CRect				m_rtButtMin;			//��С����ťλ��
	CRect				m_rtButtExit;			//�رհ�ťλ��
    
	COutput(CWnd* pParent = NULL);   // standard constructor
 
// Dialog Data
	//{{AFX_DATA(COutput)
	enum { IDD = IDD_DIALOG2 };
	CListBox	m_DisplayList;    //��ʾdisplay��Ķ���
	CListBox	m_DataStack;      //��ʾ����ջ�Ķ���
	CEdit	m_stab;               //��ʾ�����ַ���
	CListBox	m_Rconst;         //��ʾʵ�����Ķ���
	CListCtrl	m_BtabList;       //��ʾ�ֳ���Ķ���
	CListCtrl	m_TabList;        //��ʾ���ű�Ķ���
	CListCtrl   m_ArrayList;          //������Ϣ������Ķ���
	CListBox	m_PcodeList;      //��ʾp����Ķ���
	CString	m_szOutput;           //�û������������Ϣ
	CToolTipCtrl m_ToolTip;       //������ʾ����
	CString	m_baseIndex;    //����ִ��ʱ����ջ��ǰ�Ļ���ַ
	CString	m_lineNum;              //��ǰԴ�����к�
	int		m_breakPoint;          //�ϵ��к�
	CString	m_lineContent;         //�������
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
