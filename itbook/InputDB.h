#pragma once


// CInputDB



class CInputDB : public CWnd
{
	DECLARE_DYNAMIC(CInputDB)

public:
	CInputDB();
	CInputDB(CDocument *pDoc);
	virtual ~CInputDB();

	bool getText(CString pathname,CString type);
	BOOL m_getinfo(CString pathname,CString type);
protected:
	CDocument *m_pDoc;//�ĵ�ָ��
	CString m_text;

	
	

protected:
	DECLARE_MESSAGE_MAP()
};


