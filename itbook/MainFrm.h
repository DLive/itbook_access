// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once

#include "toolDlg.h"
#include "editBar.h"
#include "propertyDlg.h"
#include "classset.h"
#include "baseSet.h"
#include "itbookView.h"
#include "localSearchResult.h"


class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// ����
public:
	CtoolDlg		m_tooldlg;
	CeditBar		m_editToolBar;
	CpropertyDlg	m_propertyBar;
	ClocalSearchResult m_searchBar;  //���ѷ��๤����
	NOTIFYICONDATA  d;//����ͼ��ṹ��
	BOOL			m_isDspLineNum;  //�Ƿ���ʾ�к�

	//����ѡ��
	Cclassset m_classset;
	CbaseSet m_baseSet;
// ����
public:
	BOOL TaskBarAddIcon(HWND hwnd, UINT uID, HICON hicon, LPTSTR lpszTip);
	BOOL TaskBarModifyIcon(HWND hwnd, UINT uID, HICON hicon, LPTSTR lpszTip);
	
// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
		// ͣ������������һ���Ա�
	void DockControlBarLeftOf(CToolBar* Bar, CToolBar* LeftOf);
	void DockControlBarBottomOf(CDialogBar* Bar, CDialogBar* LeftOf);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	
	//��������С���ߺ���

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnMyIconNotify(WPARAM wParam,LPARAM lParam);
	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnMainquit();
	afx_msg void OnMainshow();

	afx_msg void OnSetproperty();
	afx_msg void OnMproperty();
	afx_msg void OnUpdateMproperty(CCmdUI *pCmdUI);
	afx_msg void OnMsearch();
	afx_msg void OnUpdateMsearch(CCmdUI *pCmdUI);
	afx_msg void OnEditbar();
	afx_msg void OnUpdateEditbar(CCmdUI *pCmdUI);
	
	//afx_msg void OnDspllinenum();
	afx_msg void OnUpdateDspllinenum(CCmdUI *pCmdUI);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
};


