#if !defined(AFX_SYMSET_H__06B3AF0D_57D7_4571_9D5A_1C333E07E969__INCLUDED_)
#define AFX_SYMSET_H__06B3AF0D_57D7_4571_9D5A_1C333E07E969__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// symset.h : header file
// ���ʷ�����𼯺��࣬���ڳ�������������ʱ���ж�



/////////////////////////////////////////////////////////////////////////////
// symset command target

class symset : public CCmdTarget
{
	DECLARE_DYNCREATE(symset)
public:
	symset();           // protected constructor used by dynamic creation
	symset(const symset &s){ //�������캯��
	  for(int i=0;i<50;i++)
		set[i]=s.set[i];
	}

	// Attributes
public:
	int InSet(int sym){  //�ж��Ƿ��ڵ�ǰ���ż�����
			return set[sym];
		}
		symset& operator=(const symset &ss);  //���ط��ż��������
		symset& operator+=(const symset &ss);
		symset& operator+=(const int sym){
			set[sym]=1;
			return *this;
		}
		symset& operator-=(const int sym){
			set[sym]=0;
			return *this;
		}
private:
		int set[50];  //������𼯺�

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(symset)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~symset();

	// Generated message map functions
	//{{AFX_MSG(symset)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYMSET_H__06B3AF0D_57D7_4571_9D5A_1C333E07E969__INCLUDED_)
