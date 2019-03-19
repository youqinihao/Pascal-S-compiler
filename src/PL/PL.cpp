// PL.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "PL.h"

#include "MainFrm.h"
#include "PLDoc.h"
#include "PLView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPLApp

BEGIN_MESSAGE_MAP(CPLApp, CWinApp)
	//{{AFX_MSG_MAP(CPLApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPLApp construction

CPLApp::CPLApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPLApp object

CPLApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CPLApp initialization

BOOL CPLApp::InitInstance()
{
	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
    

		//���������ݷ�ʽ
 	 char pBuf[MAX_PATH];                                               //���·���ı���
     GetCurrentDirectory(MAX_PATH,pBuf); //��ȡ����ĵ�ǰĿ¼
	 CString desktop=GetPtPath(CSIDL_DESKTOPDIRECTORY);
	 if(strcmp(pBuf,(LPCTSTR)desktop))   //�Ƿ��Ѿ�������ݷ�ʽ
	 {
	 CString lnk="\\PL0.lnk";
	 desktop=desktop+lnk;
	 char pDesktop[MAX_PATH];
	 strcpy(pDesktop,(LPCTSTR)desktop);
	 
     strcat(pBuf,"\\");
     strcat(pBuf,AfxGetApp()->m_pszExeName);   
     strcat(pBuf,".exe");   //��ȡ�����ȫ�ļ���
     CreatLink(pBuf,pDesktop);
	 }
	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("YOUQI"));
    
	//ͨ��дע���ķ�ʽ��.p��չ���ļ��������й���
    CString szKeyName="PL";
	CString szExePath=ExePath();
	HKEY hKey;
	CString szValue="plԴ����";
	::RegCreateKey(HKEY_CLASSES_ROOT,szKeyName, &hKey);

	::RegSetValue(hKey,"",REG_SZ,szValue,szValue.GetLength());
	szValue="\\PL.exe \"%1\"";
	szValue=szExePath+szValue;
    ::RegSetValue(hKey, "shell\\open\\command", REG_SZ, szValue, szValue.GetLength());
	szValue="\\PL.exe ,-163";
	szValue=szExePath+szValue;
	::RegSetValue(hKey,"DefaultIcon",REG_SZ,szValue,szValue.GetLength());
	
	szKeyName=".p";
	szValue="PL";
	::RegCreateKey(HKEY_CLASSES_ROOT,szKeyName,&hKey);
	::RegSetValue(hKey,"",REG_SZ,szValue,szValue.GetLength());
	//��.bpl�ļ���startinterpret����
	szKeyName="BPL";
    szValue="pl�м��ļ�";
	::RegCreateKey(HKEY_CLASSES_ROOT,szKeyName, &hKey);

	::RegSetValue(hKey,"",REG_SZ,szValue,szValue.GetLength());
	szValue="\\startinterpret.exe \"%1\"";
	szValue=szExePath+szValue;
    ::RegSetValue(hKey, "shell\\open\\command", REG_SZ, szValue, szValue.GetLength());
	szValue="\\PL.exe ,-162";
	szValue=szExePath+szValue;
	::RegSetValue(hKey,"DefaultIcon",REG_SZ,szValue,szValue.GetLength());
	
	szKeyName=".bpl";
	szValue="BPL";
	::RegCreateKey(HKEY_CLASSES_ROOT,szKeyName,&hKey);
	::RegSetValue(hKey,"",REG_SZ,szValue,szValue.GetLength());
	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CPLDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CPLView));
	pDocTemplate->SetContainerInfo(IDR_CNTR_INPLACE);
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);//SW_SHOWMAXIMIZED
	m_pMainWnd->UpdateWindow();


	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CPLApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CPLApp message handlers
void CPLApp::SetPLBkColor()//�������жԻ���ı���ɫ
{
    CColorDialog dlg;
	if(dlg.DoModal()==IDOK)
	{
		SetDialogBkColor(dlg.GetColor()); 
	}
}

bool CPLApp::CreatLink(LPSTR szPath, LPSTR szLink)
{
     HRESULT hres;   
     IShellLink *psl;   
     IPersistFile *ppf;   
     WORD wsz[MAX_PATH];   
     //����һ��IShellLinkʵ��   
	 CoInitialize(NULL);
     hres=CoCreateInstance(CLSID_ShellLink,NULL,   
                  CLSCTX_INPROC_SERVER,IID_IShellLink,   
                  (void **)&psl);   
     if(FAILED(hres))   
          return false;   
      //����Ŀ��Ӧ�ó���   
      psl->SetPath(szPath);   
      //���ÿ�ݼ�(�˴���ΪShift+Ctrl+'R')   
      psl->SetHotkey(MAKEWORD('R',HOTKEYF_SHIFT|HOTKEYF_CONTROL));   
      //��IShellLink��ȡ��IPersistFile�ӿ�   
      //���ڱ����ݷ�ʽ�������ļ�   (*.lnk)   
      hres=psl->QueryInterface(IID_IPersistFile,(void**)&ppf);   
      if(FAILED(hres))   
           return  false;   
       //  ȷ�������ļ���ΪANSI��ʽ   
      MultiByteToWideChar(CP_ACP,0,szLink,-1,wsz,MAX_PATH);   
       //����IPersistFile::Save   
       //�����ݷ�ʽ�������ļ�   (*.lnk)   
      hres= ppf->Save(wsz,STGM_READWRITE);   
       //�ͷ�IPersistFile��IShellLink�ӿ�   
      ppf->Release();   
      psl->Release();  
	  CoUninitialize();
	   return true;
  
}

CString CPLApp::ExePath()
{
   CString    sPath;   
   GetModuleFileName(NULL,sPath.GetBufferSetLength(MAX_PATH+1),MAX_PATH);   
   sPath.ReleaseBuffer();   
   int    nPos;   
   nPos=sPath.ReverseFind('\\');   
   sPath=sPath.Left(nPos);   
   return    sPath;  
   return sPath;
}
//parameter
//CSIDL_PROGRAMS         :������
//CSIDL_DESKTOPDIRECTORY :����
//CSIDL_STARTMENU        :��ʼ�˵�
CString CPLApp::GetPtPath(int CSIDL)
{
 //����ȡ�õ�·��
    LPMALLOC      ShellMalloc;
    LPITEMIDLIST  DesktopPidl;
    char DesktopDir[MAX_PATH];
    CString s;
    s="";
    if(FAILED(SHGetMalloc(&ShellMalloc)))
        return "error";
    if(FAILED(SHGetSpecialFolderLocation(NULL,CSIDL,&DesktopPidl)))
        return "error" ;
    if(!SHGetPathFromIDList(DesktopPidl, DesktopDir))
    {
        ShellMalloc->Free(DesktopPidl);
        ShellMalloc->Release();
        return "error" ;
    }
    ShellMalloc->Free(DesktopPidl);
    ShellMalloc->Release();
    s=DesktopDir;
    return s;
}

