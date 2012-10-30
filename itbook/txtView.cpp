// txtView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "itbook.h"
#include "txtView.h"
#include "txtDoc.h"

#include "MainFrm.h"
// CtxtView

IMPLEMENT_DYNCREATE(CtxtView, CEditView)

CtxtView::CtxtView()
{

}

CtxtView::~CtxtView()
{
}

BEGIN_MESSAGE_MAP(CtxtView, CEditView)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CtxtView ���

#ifdef _DEBUG
void CtxtView::AssertValid() const
{
	CEditView::AssertValid();
}

#ifndef _WIN32_WCE
void CtxtView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}
#endif
#endif //_DEBUG


// CtxtView ��Ϣ�������
CtxtDoc* CtxtView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CtxtDoc)));
	return (CtxtDoc*)m_pDocument;
}

void CtxtView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(bActivate)
	{
		
		CMainFrame* pMain=(CMainFrame*)AfxGetMainWnd();
		CpropertyDlg* pDlg=&pMain->m_propertyBar;
		pDlg->SendMessage(WM_MY_CHANGEINFO,(WPARAM)(CtxtView*)pActivateView,1);
		
	}
	CEditView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}


void CtxtView::OnInitialUpdate()
{
	CEditView::OnInitialUpdate();
	
	// TODO: �ڴ����ר�ô����/����û���
	//����Ĭ������
	LOGFONT lf;
	this->GetEditCtrl().GetFont()->GetLogFont(&lf);
	lf.lfWeight=400;
	wcscpy(lf.lfFaceName,_T("Tahoma"));
	lf.lfHeight=18;
	m_font.CreateFontIndirectW(&lf);
	if (m_font.m_hObject == NULL)
	{
		 m_font.CreatePointFont(120,L"Tahoma");
	}
	
	if (m_font.m_hObject != NULL)
		 SetFont (&m_font);
	SetTabStops(16);
	
	// ���ô�ӡ�߾�(720 � = 1/2 Ӣ��)
}

BOOL CtxtView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ����ר�ô����/����û���
	//cs.style &= ~(ES_AUTOVSCROLL|WS_VSCROLL);
	//return CEditView::PreCreateWindow(cs);
	BOOL   bPreCreated   =   CEditView::PreCreateWindow(cs); 
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// ���û���
	//cs.style   &=   ~(ES_AUTOHSCROLL);	//   Enable   word-wrapping 
	return   bPreCreated; 
}

int CtxtView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CEditView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������

	return 0;
}
