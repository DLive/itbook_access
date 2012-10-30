#pragma once
#include <afxcmn.h>
#include <afxwin.h>
#include "Resource.h"


// ClocalSearchResult �Ի���

class ClocalSearchResult : public CDialogBar
{
	DECLARE_DYNAMIC(ClocalSearchResult)

public:
	ClocalSearchResult();   // ��׼���캯��
	virtual ~ClocalSearchResult();
	

// �Ի�������
	enum { IDD = IDD_LOCALRESULT };

	//BOOL Create();

protected:
	
	CDialogBar *m_pDialogBar;
	

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:


protected:
	
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg LONG OnInitDialog ( UINT, LONG );
public:
	//ͼ���б�
	CImageList Cil1;
	// ��������б�
	CListCtrl m_serResult;
	void getexeurl(CString* purl);
	// ����������
	bool searchArticle(CString &title);
	//����������
	bool searchClassId(int cid);
	//���������
	bool searchAndAdd(CString sqlcmd);
	afx_msg void OnNMDblclkResult(NMHDR *pNMHDR, LRESULT *pResult);
	// �ַ����ָ�
	void stringSplit(CString& source, CString& result, CString division);
	//�༭�����ʼֵ
	CString m_beginClassname;

	//��ҳ����
	int		m_pageCount;
	int		m_pageSize;
	int		m_pageIndex;
	CString m_sqlCondition;
	void setPageButtonInfo();

	BOOL m_treeIsInit;//�����Ƿ��ʼ��

	HTREEITEM FindItem(CTreeCtrl& tree, HTREEITEM item, DWORD strText,int* finLevel,int* curLevel);

	
	afx_msg void OnBnClickedLocalser();
	afx_msg void OnBnClickedDelete();

	// ɾ�������ļ���ť��ѡ��
	CButton m_deletLocalFile;
	BOOL ClassInit(void);
	afx_msg void OnTvnItemexpandingClasstree(NMHDR *pNMHDR, LRESULT *pResult); //��չ��
	afx_msg void OnNMRClickClasstree(NMHDR *pNMHDR, LRESULT *pResult);//���һ�
	afx_msg void OnTvnEndlabeleditClasstree(NMHDR *pNMHDR, LRESULT *pResult);//�༭��
	afx_msg void OnTvnBeginlabeleditClasstree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClose();
	afx_msg void OnTclassadd();
	afx_msg void OnTclassdel();
	afx_msg void OnNMDblclkResultclastree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnAddrootclass();
	afx_msg void OnBnClickedAfterpage();
	afx_msg void OnBnClickedPrepage();
	afx_msg void OnCbnSelchangeJmppage();
	afx_msg void OnClassReName();
	afx_msg void OnUpdateUIState(UINT /*nAction*/, UINT /*nUIElement*/);
	afx_msg void OnUpdateButtonPrepage(CCmdUI * pCmdUI);
	afx_msg void OnUpdateButtonAfterpage(CCmdUI * pCmdUI);
};
