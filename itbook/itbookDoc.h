// itbookDoc.h : CitbookDoc ��Ľӿ�
//


#pragma once


class CitbookDoc : public CRichEditDoc
{
protected: // �������л�����
	CitbookDoc();
	DECLARE_DYNCREATE(CitbookDoc)

// ����
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
	BOOL m_isSavetoDb;//�Ƿ�������ݿ�
	
// ����
public:
	//bool openFromData();
// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual CRichEditCntrItem* CreateClientItem(REOBJECT* preo) const;
	virtual BOOL DoSave(LPCTSTR lpszPathName, BOOL bReplace=TRUE );

// ʵ��
public:
	virtual ~CitbookDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	//afx_msg void OnFileOpen();
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual void DeleteContents();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
};


