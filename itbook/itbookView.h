// itbookView.h : CitbookView ��Ľӿ�
//


#pragma once
//������ͼ�ı���Ϣ
class CitbookDoc;
class CitbookCntrItem;

class CitbookView : public CRichEditView
{
protected: // �������л�����
	CitbookView();
	DECLARE_DYNCREATE(CitbookView)

// ����
public:
	CitbookDoc* GetDocument() const;
	//int			m_LineNumWidth;//�кſ��

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CitbookView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//void ShowLineNum( HWND hEdit );//���к�
// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnDestroy();
	afx_msg void OnSetCharFormat(NMHDR* pNMHDR, LRESULT* pRes);
	DECLARE_MESSAGE_MAP()
public:
//	virtual void Serialize(CArchive& ar);
	afx_msg void OnCharColor();
	
	afx_msg void OnCharbold();
	afx_msg void OnUpdateCharbold(CCmdUI *pCmdUI);
	// �õ�������Ϣ
	void onCharFormatgetEx(CHARFORMAT2& cf, DWORD dwMask,DWORD dwEffects);
	// ����������Ϣ
	void onCharFormatsetEx(CHARFORMAT2& cf);
	afx_msg void OnCharitalic();
	afx_msg void OnUpdateCharitalic(CCmdUI *pCmdUI);
	afx_msg void OnCharstrikeout();
	afx_msg void OnUpdateCharstrikeout(CCmdUI *pCmdUI);
	afx_msg void OnCharundeline();
	afx_msg void OnUpdateCharundeline(CCmdUI *pCmdUI);
	afx_msg void OnParaLeft();
	afx_msg void OnUpdateParaLeft(CCmdUI *pCmdUI);
	afx_msg void OnParaCenter();
	afx_msg void OnUpdateParaCenter(CCmdUI *pCmdUI);
	afx_msg void OnParaRight();
	afx_msg void OnUpdateParaRight(CCmdUI *pCmdUI);
	// ���ö�������
	void onParaFormatSetEx(PARAFORMAT2& pf);
	afx_msg void OnInsertNumbering();
	afx_msg void OnUpdateInsertNumbering(CCmdUI *pCmdUI);
	// �õ�������Ϣ
	void onParaFormatGetEx(PARAFORMAT2& pf);
	afx_msg void OnInsertBullet();
	afx_msg void OnUpdateInsertBullet(CCmdUI *pCmdUI);
	afx_msg void OnCharHighlight();
protected:
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
public:
	//afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
	//virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	//afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	//afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};

#ifndef _DEBUG  // itbookView.cpp �еĵ��԰汾
inline CitbookDoc* CitbookView::GetDocument() const
   { return reinterpret_cast<CitbookDoc*>(m_pDocument); }
#endif

