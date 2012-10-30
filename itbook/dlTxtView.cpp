// dlTxtView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "itbook.h"
#include "dlTxtView.h"

#include "txtDoc.h"
#include "MainFrm.h"

// CdlTxtView

IMPLEMENT_DYNCREATE(CdlTxtView, CRichEditView)

CdlTxtView::CdlTxtView()
{
	m_LineNumWidth=30;
}

CdlTxtView::~CdlTxtView()
{
}

BEGIN_MESSAGE_MAP(CdlTxtView, CRichEditView)
	ON_WM_MOUSEWHEEL()
	ON_WM_SIZE()
	ON_WM_VSCROLL()

	ON_NOTIFY(FN_SETFORMAT,ID_VIEW_TOOLBAR,&CdlTxtView::OnSetSize)
	ON_COMMAND(ID_EDIT_PASTE, &CdlTxtView::OnEditPaste)
END_MESSAGE_MAP()


// CdlTxtView ���

#ifdef _DEBUG
void CdlTxtView::AssertValid() const
{
	CRichEditView::AssertValid();
}

#ifndef _WIN32_WCE
void CdlTxtView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}
#endif
#endif //_DEBUG


// CdlTxtView ��Ϣ�������
CtxtDoc* CdlTxtView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CtxtDoc)));
	return (CtxtDoc*)m_pDocument;
}
void CdlTxtView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(bActivate)
	{
		
		CMainFrame* pMain=(CMainFrame*)AfxGetMainWnd();
		CpropertyDlg* pDlg=&pMain->m_propertyBar;
		pDlg->SendMessage(WM_MY_CHANGEINFO,(WPARAM)(CdlTxtView*)pActivateView,1); //**
		
	}
	CRichEditView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CdlTxtView::OnInitialUpdate()
{
	CRichEditView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	CRichEditCtrl& rCtrl = GetRichEditCtrl();
	CHARFORMAT2 cf;
	//CHARFORMAT cf;
	cf.cbSize=sizeof(CHARFORMAT2);
	rCtrl.GetSelectionCharFormat(cf);
	cf.dwMask|=CFM_BOLD;
	cf.dwEffects&=~CFE_BOLD;//���ô��壬ȡ����cf.dwEffects&=~CFE_BOLD;
	cf.dwMask|=CFM_ITALIC;
	cf.dwEffects&=~CFE_ITALIC;//����б�壬ȡ����cf.dwEffects&=~CFE_ITALIC;
	cf.dwMask|=CFM_UNDERLINE;
	cf.dwEffects&=~CFE_UNDERLINE;//����б�壬ȡ����cf.dwEffects&=~CFE_UNDERLINE;
	//cf.dwMask|=CFM_COLOR;
	//cf.crTextColor = RGB(255,0,0);//������ɫ
	cf.dwMask|=CFM_SIZE;
	cf.yHeight =200;//���ø߶�
	cf.dwMask|=CFM_FACE;
	cf.yOffset=0;
	cf.dwMask|=CFM_OFFSET;
	cf.sSpacing=0;
	cf.dwMask|=CFM_SPACING;
	cf.bPitchAndFamily=0;
	::lstrcpy(cf.szFaceName ,_T("������"));//��������
	//rich.SetSelectionCharFormat(cf);
	rCtrl.SetDefaultCharFormat(cf);

	//cfm.cbSize = sizeof(CHARFORMAT2);
	//cfm.dwMask = CFM_FACE | CFM_SIZE | CFM_BOLD |CFM_ITALIC | CFM_UNDERLINE | CFM_STRIKEOUT | CFM_PROTECTED|CFM_WEIGHT;
	//cfm.dwEffects =0;
	//cfm.yHeight = 240;
	//::lstrcpy(cfm.szFaceName, _T("Arial"));
	//rCtrl.SetDefaultCharFormat(cfm);
	PARAFORMAT2 pf2; 
	//this->GetRichEditCtrl().SetDefaultCharFormat
	pf2.cbSize = sizeof(PARAFORMAT2); 
	pf2.dyLineSpacing=220;
	pf2.dwMask = PFM_LINESPACING|PFM_SPACEAFTER|PFM_SPACEBEFORE|PFM_OFFSET; 
	pf2.bLineSpacingRule = 4; //1.5���о� 
	//pf2.dxOffset=100;
	pf2.dySpaceAfter=0;
	pf2.dySpaceBefore=0;
	pf2.bOutlineLevel=0;
	pf2.dxOffset=0;
	//bLineSpacingRule ��Ϊ3��4��5��dyLineSpacing����Ч
	this->GetRichEditCtrl().SetParaFormat(pf2);

	//CFont cfs;
	//
	//cfs.CreateFontW(12,                        // nHeight
	//				0,                         // nWidth
	//			  0,                         // nEscapement
	//			  0,                         // nOrientation
	//			  400,                 // nWeight
	//			  FALSE,                     // bItalic
	//			  FALSE,                     // bUnderline
	//			  0,                         // cStrikeOut
	//			  ANSI_CHARSET,              // nCharSet
	//			  OUT_DEFAULT_PRECIS,        // nOutPrecision
	//			  CLIP_DEFAULT_PRECIS,       // nClipPrecision
	//			  DEFAULT_QUALITY,           // nQuality
	//			  DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
	//			  _T("������"));
	//rCtrl.SetFont(&cfs);
}


BOOL CdlTxtView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if(nFlags==0)
	{
		int FirstLine = ::SendMessage( m_hWnd, EM_GETFIRSTVISIBLELINE, 0, 0 );
		if(zDelta>0)
			FirstLine=-1;
		else
			FirstLine=1;	
		this->GetRichEditCtrl().LineScroll(FirstLine);
		//this->GetRichEditCtrl().LineIndex(FirstLine);
		 TRACE(_T("nFlags=%d zDelta=%d x=%d y=%d   line=%d\n"), nFlags, zDelta, pt.x, pt.y, FirstLine);
	}
	return TRUE;
	//return CRichEditView::OnMouseWheel(nFlags, zDelta, pt);
}

void CdlTxtView::OnSize(UINT nType, int cx, int cy)
{
	CRichEditView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if(((CMainFrame*)AfxGetMainWnd())->m_isDspLineNum && nType==SIZE_MAXIMIZED)
	{
		CRect rc;
		GetParent()->GetClientRect(rc);
		rc.left=m_LineNumWidth;
		
		::SetWindowPos(this->m_hWnd,HWND_TOP,rc.left,rc.top,rc.Width(),rc.Height(),SWP_NOREDRAW);
	}
}

LRESULT CdlTxtView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: �ڴ����ר�ô����/����û���
	
	if( message == WM_PAINT )
	{
		if(((CMainFrame*)AfxGetMainWnd())->m_isDspLineNum)
			ShowLineNum(this->GetParent()->m_hWnd); 
	}

	return CRichEditView::WindowProc(message, wParam, lParam);
}

//���к�
void CdlTxtView::ShowLineNum( HWND hEdit )
{
	/*
	���ܣ���ʾ�ı���������
	������ 
	hEdit��Ҫ��ʾ�кŵ��ı�����ͨ��Edit�ؼ�û�в��Թ�������ֻ��RichEdit

	����ֵ��û�С�
	--------------------------------------------------------------------------------
	*/
	RECT     ClientRect;     //RichEdit�Ŀͻ�����С
	HDC      hdcEdit;         //RichEdit��Dc���豸������
	HDC      hdcCpb;          //��RichEdit���ݵ�Dc
	HBITMAP  hdcBmp;      //RichEdit���ݵ�λͼdc
	//int      CharHeight;      //�ַ��ĸ߶�
	int      chHeight;        //�ַ��ĸ߶ȣ����� 
	int      FirstLine;       //�ı����еĵ�һ���ɼ��е��кš�
	int      ClientHeight;    //RichEdit�Ŀͻ����߶� 
	int      LineCount;       //�ı��������� 
	int		 width=30;
	RECT	 numrc;
	wchar_t     countBuf[10];   //��ʾ�кŵĻ�����
	CHARFORMAT     CharFmt;  //RichEdit�е�һ���ṹ�����ڻ�ȡ�ַ���һϵ����Ϣ������ֻ��������ȡ�ַ��߶�
	
	//��ȡRichEdit��Dc
	hdcEdit = ::GetDC( hEdit);
	::GetClientRect( hEdit, &ClientRect);
	//��ȡRichEdit�Ŀͻ����߶�
	ClientHeight = ClientRect.bottom - ClientRect.top;
	//������RichEdit���ݵ�Dc
	numrc=ClientRect;
	hdcCpb = CreateCompatibleDC( hdcEdit );
	//������RichEdit���ݵ�λͼDc������������ʾ�к��õġ�
	hdcBmp = CreateCompatibleBitmap( hdcEdit, width, ClientHeight );
	//��λͼdcѡ��RichEdit������
	SelectObject( hdcCpb, hdcBmp );
	//�����ʾ�к�dc�ı�����ɫ����ҿ�������������ɫ
	FillRect( hdcCpb, &ClientRect, CreateSolidBrush(0xc8c8c8) );
	SetBkMode( hdcCpb, TRANSPARENT );
	//��ȡ��ǰRichEdit�ı��е�������
	LineCount = ::SendMessage( this->m_hWnd, EM_GETLINECOUNT, 0, 0 );

	RtlZeroMemory( &CharFmt, sizeof(CharFmt) );
	CharFmt.cbSize = sizeof( CharFmt );
	CharFmt=this->GetCharFormatSelection();
	//::SendMessage( GetRichEditCtrl().m_hWnd, EM_GETCHARFORMAT, TRUE, (long)&CharFmt );
	//��ȡ�ַ��߶ȣ���Ӣ��Ϊ��λ����ת��Ϊ����ֻҪ����20�͵õ����ߴ硣
	chHeight = abs(CharFmt.yHeight) / 20; 
	CFont *fn;
	fn=this->GetFont();
	//fn=this->GetRichEditCtrl().GetFont();
	LOGFONT lfn;
	if(fn)
	{
		fn->GetLogFont(&lfn);
	}
	TEXTMETRIC tm;
	//GetTextMetrics(::GetDC(this->GetRichEditCtrl().m_hWnd),&tm);
	//������ʾ�кŵ�ǰ��ɫ
	SetTextColor( hdcCpb, 0x000000 );
	//��ȡ�ı����е�һ���ɼ����е��кţ�û������кţ���ʾ��������ı��Ĺ�����������
	FirstLine = ::SendMessage( m_hWnd, EM_GETFIRSTVISIBLELINE, 0, 0 );
	FirstLine++;
	//��λͼdc��ѭ������к�
	numrc.top=2;
	numrc.bottom=numrc.top+chHeight+chHeight/2;
	//this->GetRichEditCtrl().LineScroll(FirstLine);
	//PARAFORMAT2 pf2;
	//pf2.cbSize = sizeof(PARAFORMAT2);
	//pf2.dwMask=PFM_LINESPACING|PFM_STYLE|PFM_SHADING;
	//this->GetRichEditCtrl().GetParaFormat(pf2);
	
	//TRACE(_T("tmWei=%d,tmItalic=%d tmdestcent=%d,tmshadowWei=%d chHeight=%d \n"),tm.tmWeight,tm.tmItalic,tm.tmDescent,pf2.wShadingWeight,chHeight);
	//TRACE(_T("charH=%d,charH=%d,tmHeitht=%d ,tmLeading=%d tmEleading=%d rcHeight=%d lineSpacing=%d linerule=%d \n"),CharFmt.yHeight,chHeight,tm.tmHeight,tm.tmInternalLeading,tm.tmExternalLeading,numrc.bottom-numrc.top,pf2.dyLineSpacing,pf2.bLineSpacingRule);
	//int color=40;
	//int col2=50;
	
	while( FirstLine <= LineCount )
	{
		//COLORREF col=RGB(100,col2,color);
		//color+=5;
		//col2+=7;
		//FillRect( hdcCpb, &numrc,CreateSolidBrush(col) );
		DrawText(hdcCpb,countBuf,wsprintf( countBuf, TEXT("%4u"), FirstLine++ ),&numrc,DT_VCENTER|DT_SINGLELINE);
		//TextOut( hdcCpb,0, CharHeight, countBuf, wsprintf( countBuf, TEXT("%4u"), FirstLine++ ));
		numrc.top+=chHeight+chHeight/2;
		numrc.bottom+=chHeight+chHeight/2;
		if(numrc.bottom > ClientRect.bottom ) break;
	}
	//����"����"��λͼ����"��"��RichEdit��
	BitBlt( hdcEdit, 0, 0, width, ClientHeight, hdcCpb, 0, 0, SRCCOPY );
	DeleteDC( hdcCpb );
	::ReleaseDC( hEdit, hdcEdit );
	DeleteObject( hdcBmp );

}
void CdlTxtView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//CRichEditView::OnVScroll(nSBCode, nPos, pScrollBar);

	SCROLLINFO si;
	this->GetScrollInfo(SB_VERT,&si);
	
	if(nPos!=si.nPos && nPos!=0)
	{
		int count=this->GetRichEditCtrl().GetLineCount();
		int lineAvg=si.nMax/count;

		TRACE(_T("npos=%d pbarpos=%d npage=%d mi=%d,mx=%d count=%d avg=%d \n"), nPos,si.nPos,si.nPage,si.nMin,si.nMax,count,(si.nMax)/count);
		int dir=nPos-si.nPos;
		if(dir>=lineAvg/2)
			this->GetRichEditCtrl().LineScroll(1);
		else if(dir<=-(lineAvg/2) && dir<0)
			this->GetRichEditCtrl().LineScroll(-1);
	}
}

void CdlTxtView::OnSetSize(NMHDR* pNMHDR, LRESULT* pRes)
{
	
	CFont cfont;
	cfont.CreateFontW(-((CHARNMHDR*)pNMHDR)->cf.yHeight/20,                        // nHeight
					0,                         // nWidth
				  0,                         // nEscapement
				  0,                         // nOrientation
				  400,                 // nWeight
				  FALSE,                     // bItalic
				  FALSE,                     // bUnderline
				  0,                         // cStrikeOut
				  ANSI_CHARSET,              // nCharSet
				  OUT_DEFAULT_PRECIS,        // nOutPrecision
				  CLIP_DEFAULT_PRECIS,       // nClipPrecision
				  DEFAULT_QUALITY,           // nQuality
				  DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
				  _T("Arial"));
	GetRichEditCtrl().SetFont(&cfont);

	*pRes =1;
}
void CdlTxtView::OnEditPaste()
{
	// TODO: �ڴ���������������
	CHARFORMAT cf; 
	memset(&cf,   0,   sizeof(CHARFORMAT)); 
	//�õ��趨������
	
	this->GetRichEditCtrl().GetDefaultCharFormat(cf); 
	this->GetRichEditCtrl().Paste(); 
	//�õ���ǰ�Ĺ���λ�� 
	LONG   iStart,iEnd; 
	this->GetRichEditCtrl().GetSel(iStart,iEnd); 
	//   Ϊѡ���������趨��ѡ���� 
	this->GetRichEditCtrl().SetSel(0,-1); 
	this->GetRichEditCtrl().SetSelectionCharFormat(cf); 
	//   �������ù��λ�� 
	this->GetRichEditCtrl().SetSel(iStart,iEnd);

	//CRichEditView::OnEditPaste();
}

BOOL CdlTxtView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ����ר�ô����/����û���

	return CRichEditView::PreCreateWindow(cs);
	 if (LoadLibraryA("RICHED20.DLL") == NULL)       
	 {          
		 AfxMessageBox(_T("Fail to load riched20.dll"),MB_OK | MB_ICONERROR);          
		 PostMessage(WM_QUIT,0,0);         
		 return FALSE; 
	}
}