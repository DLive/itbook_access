// itbook.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "itbook.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "itbookDoc.h"
#include "itbookView.h"

#include "txtDoc.h"
#include "txtView.h"
#include "dlTxtView.h"

#include "Ccommon.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CitbookApp

BEGIN_MESSAGE_MAP(CitbookApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CitbookApp::OnAppAbout)
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CitbookApp::seltNewfile)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// ��׼��ӡ��������
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
	ON_COMMAND(ID_NEWTITFILE, &CitbookApp::OnNewtitfile)
	ON_COMMAND(ID_NEWTXTFILE, &CitbookApp::OnNewtxtfile)
END_MESSAGE_MAP()



//ɾ��temp�߳�������
UINT DeleteTemp(LPVOID lpParam)
{
	Ccommon getfile;
	CString tempPath;
	getfile.getExeUrl(&tempPath);
	tempPath+=_T("Temp\\");
	Ccommon deletefile;
	deletefile.DeleteDirectory(tempPath);
	
	return 0;
}

// CitbookApp ����
CitbookApp::CitbookApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CitbookApp ����

CitbookApp theApp;


// CitbookApp ��ʼ��

BOOL CitbookApp::InitInstance()
{
	//--------����ֻ����һ��ʵ��-------------------------

	HANDLE m_hMutex = ::CreateMutex(NULL, TRUE, _T("itbookone"));
    if (GetLastError() == ERROR_ALREADY_EXISTS) //�����Ѿ�����
    {
        HWND   oldHWnd = NULL;   
        oldHWnd = ::FindWindow(NULL, _T("ItBaby�ʼǹ���")); //�����Ѿ����еĳ���
        if (oldHWnd)   
        {   
			  AfxMessageBox(_T("����������"));
            ::ShowWindow(oldHWnd, SW_SHOWNORMAL); //������ʾ�ҵ��������еĳ���
            ::SetForegroundWindow(oldHWnd);       //�������еĳ�������Ϊ��ǰ����
        }  
        CloseHandle(m_hMutex);
        m_hMutex = NULL;
        return FALSE;
    }
	//-------------------------------------------------------------

	//����ɾ���߳�
	AfxBeginThread(DeleteTemp,(LPVOID)123);
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("ItBook�ʼǹ���"));
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)
	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_itbookTYPE,
		RUNTIME_CLASS(CitbookDoc),
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CitbookView));
	if (!pDocTemplate)
		return FALSE;
	pDocTemplate->SetContainerInfo(IDR_itbookTYPE_CNTR_IP);
	AddDocTemplate(pDocTemplate);
	
	pDocTemplate=new CMultiDocTemplate(IDR_txtTYPE,
			RUNTIME_CLASS(CtxtDoc),
			RUNTIME_CLASS(CChildFrame),
			RUNTIME_CLASS(CdlTxtView));
	pDocTemplate->SetContainerInfo(IDR_itbookTYPE_CNTR_IP);
	AddDocTemplate(pDocTemplate);

	// ������ MDI ��ܴ���
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;
	// �������к�׺ʱ�ŵ��� DragAcceptFiles
	//  �� MDI Ӧ�ó����У���Ӧ������ m_pMainWnd ֮����������
	// ������/��
	m_pMainWnd->DragAcceptFiles();

	// ���á�DDE ִ�С�
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// ������׼������DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	//if (!ProcessShellCommand(cmdInfo))
	//	return FALSE;


	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// �������ѳ�ʼ���������ʾ����������и���
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();


	return TRUE;
}


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CitbookApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}



// CitbookApp ��Ϣ�������


void CitbookApp::OnNewtitfile()
{
	CDocTemplate* pTemplate;
	// TODO: �ڴ���������������
	POSITION pz=m_pDocManager->GetFirstDocTemplatePosition();
	CString ext;
	while(pz)
	{
		pTemplate=m_pDocManager->GetNextDocTemplate(pz);
		pTemplate->GetDocString(ext,CDocTemplate::filterExt);
		if(ext==_T(".tit"))
			break;
	}
	ASSERT(pTemplate != NULL);
	ASSERT_KINDOF(CDocTemplate, pTemplate);
	
	pTemplate->OpenDocumentFile(NULL);
	
}

void CitbookApp::OnNewtxtfile()
{
	// TODO: �ڴ���������������
		CDocTemplate* pTemplate;
	// TODO: �ڴ���������������
	POSITION pz=m_pDocManager->GetFirstDocTemplatePosition();
	CString ext;
	while(pz)
	{
		pTemplate=m_pDocManager->GetNextDocTemplate(pz);
		pTemplate->GetDocString(ext,CDocTemplate::filterExt);
		if(ext==_T(".txt"))
			break;
	}
	ASSERT(pTemplate != NULL);
	ASSERT_KINDOF(CDocTemplate, pTemplate);
	
	pTemplate->OpenDocumentFile(NULL);
}
void CitbookApp::seltNewfile()
{

}