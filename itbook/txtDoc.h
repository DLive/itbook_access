#pragma once

// CtxtDoc �ĵ�

class CtxtDoc : public CRichEditDoc
{
	DECLARE_DYNCREATE(CtxtDoc)

public:
	CtxtDoc();
	virtual ~CtxtDoc();
//#ifndef _WIN32_WCE
	virtual void Serialize(CArchive& ar);   // Ϊ�ĵ� I/O ��д
	virtual CRichEditCntrItem* CreateClientItem(REOBJECT* preo) const;
//#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	bool m_isFromDb;//true Ϊ�Ǵ����ݿ�ȡ������
	int m_aid;  //ID��
	CString m_oldPath;//��֮ǰ�����·��
	CString m_nowPath;//���ڵ�·��
	CString m_classid; //�����
	CString m_title; //����
	CString m_classname; //��������
	bool m_isTemp;//true Ϊ����
	CString m_author;//����
	CString m_difficulty;//�����Ѷ�
	CString m_artitletype;//�ı�����
	CString m_keyword;//�ؼ���
	BOOL m_infoIsFi;//������Ϣ�Ƿ��Ѹ���
	BOOL m_isANSI;//ture is ansi;
	BOOL m_isSavetoDb;//�Ƿ�������ݿ�  Ĭ�ϴ���
protected:
	virtual BOOL OnNewDocument();

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);

	

	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	BOOL selfSaveFile(CString& content,CString path);
	BOOL SaveAsAnsi(LPCTSTR pathname);
	virtual void OnCloseDocument();
};
