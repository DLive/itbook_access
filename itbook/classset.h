#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// Cclassset �Ի���

class Cclassset : public CPropertyPage
{
	DECLARE_DYNAMIC(Cclassset)

public:
	Cclassset();
	virtual ~Cclassset();

// �Ի�������
	enum { IDD = IDD_CLASSSET };

	bool classinit();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ����
	virtual BOOL OnInitDialog();
	// ��ӷ���ĸ���
	CComboBox m_addFather;
	// ɾ������
	CComboBox m_delclass;
	// �޸ķ���
	CComboBox m_changeClassname;
	// �����޸�
	CComboBox m_fatherChangeName;
	CComboBox m_fatherFather;
	afx_msg void OnBnClickedAddclass();
	afx_msg void OnBnClickedChange();
	afx_msg void OnCbnSelchangeChangeclass();
	afx_msg void OnBnClickedDel();
	afx_msg void OnBnClickedChangefather();
	afx_msg void OnCbnSelchangeFatherchang();
};
