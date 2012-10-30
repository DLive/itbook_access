#pragma once


// CtxtView ��ͼ
class CtxtDoc;

class CtxtView : public CEditView
{
	DECLARE_DYNCREATE(CtxtView)

protected:
	CtxtView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CtxtView();

public:
	CtxtDoc* GetDocument() const;
	
	//��������
	CFont m_font;

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
//	virtual void Serialize(CArchive& ar);
	virtual void OnInitialUpdate();
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


