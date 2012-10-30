#include "StdAfx.h"
#include "Conndb.h"
#include "Ccommon.h"

CConndb::CConndb(void)
{
	m_pConnection.CreateInstance(__uuidof(Connection));
	try
	{
		CString dbUrl;
		Ccommon db;
		db.getExeUrl(&dbUrl);
		dbUrl+=_T("data\\notebook.mdb");
		//dbUrl=_T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=")+dbUrl;  MSDAORA
		dbUrl=_T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=")+dbUrl;
		m_pConnection->Open(dbUrl.AllocSysString(),"","",adModeUnknown);
	}
	catch(_com_error e)
	{
		AfxMessageBox(_T("���ݿ�����ʧ�ܣ���ȷ�����ݿ��Ƿ��ڵ�ǰ·����"));
	}


}

CConndb::~CConndb(void)
{
	if(m_pConnection->State)
	{
		/*if(m_pRecordset->State)
			m_pRecordset->Close();*/
		m_pConnection->Close();
		m_pConnection=NULL;
	

	}
}
//ִ��sql����
int CConndb::insert(CString &comText)
{
	_variant_t RecordsAffected;
	try{
		m_pConnection->Execute( (_bstr_t)comText,&RecordsAffected,adCmdText);
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
	TRACE("Ӱ������:%d",RecordsAffected);
	return (int)RecordsAffected;

	
}
int CConndb::m_geteffectnum(CString &cmdsql)
{
	_variant_t RecordsAffected;
	int num;
	try{
		m_pRecordset=m_pConnection->Execute( (_bstr_t)cmdsql,&RecordsAffected,adCmdText);
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
	if(!m_pRecordset->BOF)
	{
		_variant_t var;
		CString id;
		m_pRecordset->MoveFirst();
		var=m_pRecordset->GetCollect("id");
		if(var.vt!=VT_NULL)
			id=(LPCSTR)_bstr_t(var);
		num=_wtoi(id.GetBuffer());
		id.ReleaseBuffer();

	}
	else
	{
		num=-1;
	}
	TRACE("Ӱ������:%d",RecordsAffected);
	
	return num;
}

void CConndb::search(CString& sqlcmd)
{
	_variant_t RecordsAffected;
	//CString cmdsql;
	
	try
	{
		m_pRecordset=m_pConnection->Execute((_bstr_t)sqlcmd,&RecordsAffected,adCmdText);
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
}

void CConndb::getarticle(CString &cmdsql)
{
	_variant_t RecordsAffected;
	try
	{
		m_pRecordset=m_pConnection->Execute((_bstr_t)cmdsql,&RecordsAffected,adCmdText);
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
}
// ɾ����¼
bool CConndb::deleteRecord(CString no)
{
	_variant_t RecordsAffected;
	CString sqlcmd;
	sqlcmd.Format(_T("delete from articles where id=%s"),no);
	try
	{		
		m_pConnection->Execute((_bstr_t)sqlcmd,&RecordsAffected,adCmdText);
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
	if((int)RecordsAffected>=1)
		return true;
	else
		return false;
}
BOOL CConndb::excuteSql(CString &cmdsql)
{
	try
	{
		m_pRecordset=m_pConnection->Execute((_bstr_t)cmdsql,&RecordsAffecteds,adCmdText);
		return TRUE;
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
		return FALSE;
	}
}
int CConndb::setPageInfo(CString &sqlcmd,int pageSize)
{
		///*int begin=sqlcmd.Find(_T("from"));
		//if(begin==-1)
		//	AfxMessageBox(_T("��ѯ����"));
		//total.Format(_T("select count(*) %s"),sqlcmd.Mid(begin));*/
	_variant_t RecordsAffected;
	m_pRecordset=m_pConnection->Execute((_bstr_t)sqlcmd,&RecordsAffected,adCmdText);
	m_pRecordset->MoveFirst();
	int count;
	if(!m_pRecordset->adoEOF)
		count=m_pRecordset->GetCollect(_variant_t((long)0)).intVal;
	int m_paperCount=count/pageSize;
	if(count%pageSize!=0)
		m_paperCount++;
	m_pRecordset->Close();
	//m_pRecordset.Release();
	return m_paperCount;
	//return 0;

}