#pragma once

class CConndb
{
public:
	CConndb(void);
	~CConndb(void);
	
	//����
	int insert(CString &comText);
	//����
	_ConnectionPtr m_pConnection;
	_RecordsetPtr	m_pRecordset;//�����
	void search(CString &sqlcmd);
	void getarticle(CString &cmdsql);
	int m_geteffectnum(CString &cmdsql);
	_variant_t RecordsAffecteds; //Ӱ������
	BOOL excuteSql(CString &cmdsql);
	// ɾ����¼
	bool deleteRecord(CString no);


	//��ҳ����
	//int		m_recodeCount; //������
	//int		m_paperCoutn;	//��ҳ��
	//int		m_paperNum;		//ÿҳ����

	int		setPageInfo(CString &sqlcmd,int pageSize);
};
