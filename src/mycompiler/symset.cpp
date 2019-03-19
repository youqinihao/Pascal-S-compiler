// symset.cpp : implementation file
//

#include "stdafx.h"
#include "symset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// symset

IMPLEMENT_DYNCREATE(symset, CCmdTarget)



symset::~symset()
{
}
 symset::symset()
{
	for(int i=0;i<50;i++)
		set[i]=0;
}
//

 symset& symset::operator=(const symset &ss)
{
	for (int i=0;i<50;i++)
		set[i]=ss.set[i];
	return *this;
}
//

 symset& symset::operator+=(const symset &ss)
{
	for (int i=0;i<50;i++)
		set[i]=set[i]||ss.set[i];
	return *this;
}

BEGIN_MESSAGE_MAP(symset, CCmdTarget)
	//{{AFX_MSG_MAP(symset)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// symset message handlers
