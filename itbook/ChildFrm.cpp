// ChildFrm.cpp : CChildFrame ���ʵ��
//
#include "stdafx.h"
#include "itbook.h"

#include "ChildFrm.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_DSPLLINENUM, &CChildFrame::OnDspllinenum)
END_MESSAGE_MAP()


// CChildFrame ����/����

CChildFrame::CChildFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ��������ʽ
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}


// CChildFrame ���

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG


// CChildFrame ��Ϣ�������

int CChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
		//����ͼ��

	HICON m_hicon;
	m_hicon=AfxGetApp()->LoadIconW(IDR_itbookTYPE);
	SetIcon(m_hicon,TRUE);
	return 0;
}

void CChildFrame::OnDspllinenum()
{
	// TODO: �ڴ���������������
	CRect rc;
	
	int left=0;
	if(((CMainFrame*)AfxGetMainWnd())->m_isDspLineNum)
	{
		((CMainFrame*)AfxGetMainWnd())->m_isDspLineNum=FALSE;
		left=0;
	}
	else
	{
		((CMainFrame*)AfxGetMainWnd())->m_isDspLineNum=TRUE;
		left=30;
	}

	POSITION   posTemp=AfxGetApp()->m_pDocManager-> GetFirstDocTemplatePosition(); 
	while(posTemp) 
	{ 
		//�����ĵ�ģ�� 
		CMultiDocTemplate   *pDocTemp=(CMultiDocTemplate*)AfxGetApp()->m_pDocManager-> GetNextDocTemplate(posTemp); 
		if(pDocTemp) 
		{	
			POSITION   posDoc=pDocTemp-> GetFirstDocPosition(); 
			while(posDoc) 
			{	
				//�����ĵ�ģ���Ӧ���ĵ� 
				CDocument   *pDoc=pDocTemp-> GetNextDoc(posDoc); 
				if(pDoc) 
				{ 
					POSITION   posView=pDoc-> GetFirstViewPosition(); 
					while(posView) 
					{ 
					//�����ĵ���Ӧ����ͼ 
						CView   *pView=pDoc-> GetNextView(posView); 
						if(pView) 
						{ 
					    pView->GetParent()->GetClientRect(rc);
						rc.left+=left;
						pView->SetWindowPos(FromHandle(HWND_TOP),rc.left,rc.top,rc.Width(),rc.Height(),SWP_NOREDRAW);
						//�õ�view��Ӧ�ĸ�����childframe�� 
						//CWnd   *pFrame=pView-> GetParent(); 
						//if(pFrame) 
						//	pFrame-> SendMessage(WM_CLOSE);//�ر�childframe,Ҳ�͹ر���view 
						}	
					} 
				} 
			} 
		}
	}

	//::SetWindowPos(this->m_hWnd,HWND_TOP,rc.left,rc.top,rc.Width(),rc.Height(),SWP_NOREDRAW);
}
