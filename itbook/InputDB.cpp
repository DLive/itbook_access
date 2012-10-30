// InputDB.cpp : 实现文件
//

#include "stdafx.h"
#include "itbook.h"
#include "InputDB.h"
#include "itbookView.h"
#include "Conndb.h"
#include <string.h>
#include <AtlConv.h>

#include "itbookDoc.h"
#include "txtDoc.h"
// CInputDB

IMPLEMENT_DYNAMIC(CInputDB, CWnd)

CInputDB::CInputDB()
{

}
CInputDB::CInputDB(CDocument *pDoc)
{
	m_pDoc=pDoc;
}

CInputDB::~CInputDB()
{
}


BEGIN_MESSAGE_MAP(CInputDB, CWnd)
END_MESSAGE_MAP()



// CInputDB 消息处理程序
bool CInputDB::getText(CString pathname,CString type)
{
	CString contenttext;

	 CFile bb;
	 if(!bb.Open(pathname,CFile::modeRead,NULL))
	 {
		AfxMessageBox(_T("error,file is not find"));
	 }
	byte head[2];
    bb.Read(head,2);
	
	if(((head[0]==0xff&&head[1]==0xfe)||(head[0]==0xfe&&head[1]==0xff)))
    {
		CString contemp;
		bb.Seek(2,CFile::begin);
		wchar_t* pbuf;
		ULONGLONG l=bb.GetLength();
		pbuf=new wchar_t[l];
		memset(pbuf,'\0',l);
		bb.Read(pbuf,l);
		pbuf[(l/2)]='\0';
		contenttext.Format(_T("%s"),pbuf);
		//this->GB2312ToUTF8(contemp,contenttext);
		delete []pbuf;
	}
	else
	{
		bb.SeekToBegin();
		 LPSTR pbuf;
		 ULONGLONG l=bb.GetLength();
		 pbuf=new char[l+1];
		 memset(pbuf,'\0',l+1);
		 bb.Read(pbuf,l);
		 //ansi to unicode
		 //size_t len=strlen(pbuf)+1;
		 int wlen=MultiByteToWideChar(CP_ACP,NULL,pbuf,-1,NULL,NULL);
		 
		 wchar_t *pwText=new wchar_t[wlen];
		 if(!pwText)
		{
			delete []pwText;
		}

		 MultiByteToWideChar(CP_ACP,0,pbuf,-1,pwText,wlen);
		 contenttext.Format(_T("%s"),pwText);
		 delete []pwText;
		 delete []pbuf;
	}
	bb.Close();
	 
	

	 BOOL m_isFromDb;
	 CString m_classid,m_oldPath,m_author,m_keyword,artype,difficulty;
	 int m_aid;
	 bool m_isTemp;
	 if(type==_T("tit"))
	 {
		CitbookDoc *pitbook=(CitbookDoc*)m_pDoc;
		m_isFromDb=pitbook->m_isFromDb;
		m_classid=pitbook->m_classid;
		m_aid=pitbook->m_aid;
		m_isTemp=pitbook->m_isTemp;
		m_oldPath=pitbook->m_oldPath;
		m_author=pitbook->m_author;
		m_keyword=pitbook->m_keyword;
		difficulty=pitbook->m_difficulty;
	 }
	 else
	 {
		CtxtDoc *pitbook=(CtxtDoc*)m_pDoc;
		m_isFromDb=pitbook->m_isFromDb;
		m_classid=pitbook->m_classid;
		m_aid=pitbook->m_aid;
		m_isTemp=pitbook->m_isTemp;
		m_oldPath=pitbook->m_oldPath;
		m_author=pitbook->m_author;
		m_keyword=pitbook->m_keyword;
		difficulty=pitbook->m_difficulty;
	 }

	//判断是保存，还是另存为
	bool isSave;//true is save. false is save as
	if(pathname.CompareNoCase(m_oldPath)==0)
		isSave=true;
	else
		isSave=false;
	//取得文件名
	int p=pathname.ReverseFind('\\');
	CString titlename;
	titlename=pathname.Right(pathname.GetLength()-p-1); 
	p=titlename.ReverseFind('.');
	titlename=titlename.Left(p);
	//得到时间
	CTime time=CTime::GetCurrentTime();
	CString data=time.Format("%Y-%m-%d");
	//取得路径
	pathname.Replace(_T("'"),_T("''"));

	
	contenttext.Replace(_T("'"),_T("''"));
	CString addText;
	
	CConndb add;//sql链接对象

	if(m_isFromDb && isSave==true)
	{
		CString updatasql;
		//如何缓存在temp 则不更新txtaddress
		if(m_isTemp)
			updatasql.Format(_T("update articles set title='%s',content='%s',classid=%s,addtime=#%s#,artitletype='%s',author='%s',keyword='%s',difficulty=%s where id=%d"),titlename,contenttext,m_classid,data,type,m_author,m_keyword,difficulty,m_aid);
		else
			updatasql.Format(_T("update articles set title='%s',content='%s',classid=%s,addtime=#%s#,txtaddress='%s',artitletype='%s',author='%s',keyword='%s',difficulty=%s where id=%d"),titlename,contenttext,m_classid,data,pathname,type,m_author,m_keyword,difficulty,m_aid);
		if(add.insert(updatasql)>=1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
 		addText.Format(_T("insert into articles (title,content,classid,addtime,txtaddress,artitletype,author,keyword,difficulty) values('%s','%s',%s,#%s#,'%s','%s','%s','%s',%s)"),titlename,contenttext,m_classid,data,pathname,type,m_author,m_keyword,difficulty);
		//得到插入ID

		
		if(add.insert(addText)>=1)
		{
			CString sqlget;
			int insertid;
			sqlget.Format(_T("select max(id) as maxid from articles"));
			add.search(sqlget);
			if(!add.m_pRecordset->BOF)
			{
				add.m_pRecordset->MoveFirst();
				_variant_t var;
				var=add.m_pRecordset->GetCollect("maxid");
				if(var.vt!=VT_NULL)
				insertid=var.ulVal;
			}
			if(type==_T("tit"))
			{
				CitbookDoc *pitbook=(CitbookDoc*)m_pDoc;
				pitbook->m_aid=insertid;
			}
			else
			{
				CtxtDoc *pitbook=(CtxtDoc*)m_pDoc;
				pitbook->m_aid=insertid;
			}
			return true;
		}
		else
		{
			return false;
		}
	}
	
}

BOOL CInputDB::m_getinfo(CString pathname,CString type)
{
	CString text;
	text.Format(_T("SELECT a.id, a.title,a.classid,a.author,a.keyword,a.difficulty,a.artitletype,c.classname FROM articles AS a, class AS c WHERE a.classid=c.id AND a.txtaddress='%s'"),pathname);
	CConndb setinfo;
	setinfo.getarticle(text);
	
	
	CString title,cid,author,classname,keyword,difficulty;
	difficulty=_T("0");
	int aid;
	if(!setinfo.m_pRecordset->BOF)
	{
		setinfo.m_pRecordset->MoveFirst();
		_variant_t var;
		CString value;
		while(!setinfo.m_pRecordset->adoEOF)
		{
			var=setinfo.m_pRecordset->GetCollect("title");
			if(var.vt!=VT_NULL)
				title=(LPCSTR)_bstr_t(var);
			var=setinfo.m_pRecordset->GetCollect("id");
			if(var.vt!=VT_NULL)
				aid=var.intVal;
			var=setinfo.m_pRecordset->GetCollect("classid");
			if(var.vt!=VT_NULL)
				cid=(LPCSTR)_bstr_t(var);
			var=setinfo.m_pRecordset->GetCollect("classname");
			if(var.vt!=VT_NULL)
				classname=(LPCSTR)_bstr_t(var);
			var=setinfo.m_pRecordset->GetCollect("keyword");
			if(var.vt!=VT_NULL)
				keyword=(LPCSTR)_bstr_t(var);
			var=setinfo.m_pRecordset->GetCollect("author");
			if(var.vt!=VT_NULL)
				author=(LPCSTR)_bstr_t(var);
			var=setinfo.m_pRecordset->GetCollect("difficulty");
			if(var.vt!=VT_NULL)
				difficulty=(LPCSTR)_bstr_t(var);

			setinfo.m_pRecordset->MoveNext();
		}
		if(type==_T("tit"))
		{
			CitbookDoc *pitbook=(CitbookDoc*)m_pDoc;
			pitbook->m_nowPath=pathname;
			pitbook->m_isFromDb=true;
			pitbook->m_aid=aid;
			pitbook->m_classid=cid;
			pitbook->m_classname=classname;
			pitbook->m_keyword=keyword;
			pitbook->m_author=author;
			pitbook->m_difficulty=difficulty;
			pitbook->SetModifiedFlag(FALSE);
		}
		else
		{
			CtxtDoc *pitbook=(CtxtDoc*)m_pDoc;
			pitbook->m_nowPath=pathname;
			pitbook->m_isFromDb=true;
			pitbook->m_aid=aid;
			pitbook->m_classid=cid;
			pitbook->m_classname=classname;
			pitbook->m_keyword=keyword;
			pitbook->m_author=author;
			pitbook->m_difficulty=difficulty;
			pitbook->SetModifiedFlag(FALSE);
		}
		
	}

	return TRUE;
}
