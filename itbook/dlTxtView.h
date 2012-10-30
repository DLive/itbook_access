#pragma once


// CdlTxtView ��ͼ
class CtxtDoc;
class CdlTxtView : public CRichEditView
{
	DECLARE_DYNCREATE(CdlTxtView)

protected:
	CdlTxtView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CdlTxtView();

public:
	CtxtDoc* GetDocument() const;


	int			m_LineNumWidth;//�кſ��
	void ShowLineNum( HWND hEdit );//���к�
	afx_msg void OnSetSize(NMHDR* pNMHDR, LRESULT* pRes);

#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
public:
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual void OnInitialUpdate();
	afx_msg void OnEditPaste();
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
};


