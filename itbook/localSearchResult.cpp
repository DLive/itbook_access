// localSearchResult.cpp : 实现文件
//

#include "stdafx.h"
#include "itbook.h"
#include "localSearchResult.h"
#include "Conndb.h"
#include "itbookDoc.h"
//#include "itbookView.h"
#include "txtDoc.h"
#include "MainFrm.h"

#include "DLclassnamedlg.h" //分类名对话框

// ClocalSearchResult 对话框

IMPLEMENT_DYNAMIC(ClocalSearchResult, CDialogBar)

ClocalSearchResult::ClocalSearchResult()
{
	m_pDialogBar=NULL;
	m_treeIsInit=FALSE;
	m_pageSize=30;
}

ClocalSearchResult::~ClocalSearchResult()
{
}

void ClocalSearchResult::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RESULT, m_serResult);
	DDX_Control(pDX, IDC_DELLOCALFILE, m_deletLocalFile);
}


BEGIN_MESSAGE_MAP(ClocalSearchResult, CDialogBar)
	ON_MESSAGE(WM_INITDIALOG, OnInitDialog)
	ON_NOTIFY(NM_DBLCLK, IDC_RESULT, &ClocalSearchResult::OnNMDblclkResult)
	ON_BN_CLICKED(IDC_LOCALSER, &ClocalSearchResult::OnBnClickedLocalser)
	ON_BN_CLICKED(IDC_DELETE, &ClocalSearchResult::OnBnClickedDelete)
	ON_NOTIFY(TVN_ITEMEXPANDING, IDC_RESULTCLASTREE, &ClocalSearchResult::OnTvnItemexpandingClasstree)
	ON_NOTIFY(NM_RCLICK,IDC_RESULTCLASTREE, &ClocalSearchResult::OnNMRClickClasstree)
	ON_NOTIFY(TVN_ENDLABELEDIT,IDC_RESULTCLASTREE,&ClocalSearchResult::OnTvnEndlabeleditClasstree)
	ON_NOTIFY(TVN_BEGINLABELEDIT, IDC_RESULTCLASTREE, &ClocalSearchResult::OnTvnBeginlabeleditClasstree)
	ON_WM_CLOSE()
	ON_COMMAND(ID_TCLASSADD, &ClocalSearchResult::OnTclassadd)
	ON_COMMAND(ID_TCLASSDEL, &ClocalSearchResult::OnTclassdel)
	ON_NOTIFY(NM_DBLCLK, IDC_RESULTCLASTREE, &ClocalSearchResult::OnNMDblclkResultclastree)
	ON_COMMAND(ID_ADDROOTCLASS, &ClocalSearchResult::OnAddrootclass)
	ON_BN_CLICKED(IDC_AFTERPAGE, &ClocalSearchResult::OnBnClickedAfterpage)
	ON_BN_CLICKED(IDC_PREPAGE, &ClocalSearchResult::OnBnClickedPrepage)
	ON_CBN_SELCHANGE(IDC_JMPPAGE, &ClocalSearchResult::OnCbnSelchangeJmppage)
	ON_COMMAND(ID_CLASSRENAME, &ClocalSearchResult::OnClassReName)

	ON_UPDATE_COMMAND_UI(IDC_PREPAGE,OnUpdateButtonPrepage)
	ON_UPDATE_COMMAND_UI(IDC_AFTERPAGE,OnUpdateButtonAfterpage)
	ON_WM_UPDATEUISTATE()
END_MESSAGE_MAP()

//BOOL ClocalSearchResult::Create()
//{
//	//CDialogBar::Create(ClocalSearchResult::IDD);
//
//	return this->ShowWindow(true);
//}
void ClocalSearchResult::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	if (m_pDialogBar!=NULL) {
		// modeless case -- do not call base class OnCancel
		m_pDialogBar->PostMessage(WM_GOODBYELOCAL, IDCANCEL);
	}
	//else {
	//	CDialogBar::OnCancel(); // modal case
	//}
}

void ClocalSearchResult::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	
}

LONG ClocalSearchResult::OnInitDialog(UINT wParam, LONG lParam)
{
	BOOL bRet = HandleInitDialog(wParam, lParam);

	if (!UpdateData(FALSE))

	{

		TRACE0("Warning: UpdateData failed during dialog init.\n");

	}

	// TODO:  在此添加额外的初始化
	m_serResult.SetExtendedStyle(LVS_EX_FLATSB|LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP|LVS_EX_ONECLICKACTIVATE|LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES);
	m_serResult.InsertColumn(0,_T("文章标题"),LVCFMT_LEFT,250,0);
	m_serResult.InsertColumn(1,_T("最后修改时间"),LVCFMT_LEFT,100,0);
	m_serResult.InsertColumn(2,_T("编号"),LVCFMT_LEFT,40,0);
	m_serResult.InsertColumn(3,_T("作者"),LVCFMT_LEFT,80,0);
	m_serResult.InsertColumn(4,_T("文章分类"),LVCFMT_LEFT,80,0);
	m_serResult.InsertColumn(5,_T("难度"),LVCFMT_LEFT,40,0);
	m_serResult.InsertColumn(6,_T("文件路径"),LVCFMT_LEFT,80,0);
	m_serResult.InsertColumn(7,_T("类型"),LVCFMT_LEFT,40,0);
	
	if(!m_treeIsInit)
	{
		ClassInit();
		m_treeIsInit=TRUE;
	}
	//setPageButtonInfo();

	return bRet;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

// 搜索文章
bool ClocalSearchResult::searchArticle(CString &title)
{
	CString keyword;
	this->stringSplit(title,keyword,_T(" "));
	m_sqlCondition=keyword;  //保存查询条件
	CString sqlcmd;
	
	CString pagesql;
	pagesql.Format(_T("select count(*) from articles as a where %s "),keyword);
	
	//设置跳转页
	CConndb page;
	m_pageCount=page.setPageInfo(pagesql,m_pageSize);
	if(m_pageCount>0)
	{
		CComboBox* pcb=(CComboBox*)GetDlgItem(IDC_JMPPAGE);
		pcb->ResetContent();
		wchar_t num[10];
		for(int i=0;i<m_pageCount;i++)
		{
			pcb->InsertString(i,(LPCTSTR)_itow(i+1,num,10));
		}
		pcb->SetCurSel(0);
	}

	//查询语句
	m_pageIndex=1;
	sqlcmd.Format(_T("SELECT TOP %d * FROM ( SELECT TOP %d a.title,a.id,a.classid,a.addtime,a.txtaddress,c.classname,a.author,a.difficulty,a.artitletype FROM articles AS a,class AS c where a.classid=c.id and (%s) ORDER BY a.id DESC )   ORDER BY a.id ASC ")
				,m_pageSize
				,m_pageSize*1
				,keyword);
	//setPageButtonInfo();
	//sqlcmd.Format(_T("SELECT a.title,a.id,a.classid,a.addtime,a.txtaddress,c.classname,a.author,a.difficulty,a.artitletype FROM articles AS a,class AS c where a.classid=c.id and (%s)"),keyword);
	if(searchAndAdd(sqlcmd))
		return true;
	else
		return false;
}
//按分类ID搜索
bool ClocalSearchResult::searchClassId(int cid)
{
	CString cmdtext;
	/*if(cid!=0)
	{
		cmdtext.Format(_T("SELECT a.title,a.id,a.classid,a.addtime,a.txtaddress,c.classname,a.author,a.difficulty,a.artitletype FROM articles AS a,class AS c where a.classid=c.id and a.classid in(select id from class where id=%d or parentid=%d)"),cid,cid);
	}
	else
	{*/
	CString keyword;
	keyword.Format(_T("a.classid=%d"),cid);
	m_sqlCondition=keyword;  //保存查询条件
	CString sqlcmd;
	
	CString pagesql;
	pagesql.Format(_T("select count(*) from articles as a where %s "),keyword);
	//设置跳转页
	CConndb page;
	m_pageCount=page.setPageInfo(pagesql,m_pageSize);
	if(m_pageCount>0)
	{
		CComboBox* pcb=(CComboBox*)GetDlgItem(IDC_JMPPAGE);
		pcb->ResetContent();
		wchar_t num[10];
		for(int i=0;i<m_pageCount;i++)
		{
			pcb->InsertString(i,(LPCTSTR)_itow(i+1,num,10));
		}
		pcb->SetCurSel(0);
	}

	//查询语句
	m_pageIndex=1;

	cmdtext.Format(_T("SELECT TOP %d * FROM ( SELECT TOP %d a.title,a.id,a.classid,a.addtime,a.txtaddress,c.classname,a.author,a.difficulty,a.artitletype FROM articles AS a,class AS c where a.classid=c.id and %s ORDER BY a.id DESC )   ORDER BY a.id ASC ")
				,m_pageSize
				,m_pageSize*1
				,keyword);
	//}
	//setPageButtonInfo();
	if(this->searchAndAdd(cmdtext))
		return true;
	else
		return false;

}
bool ClocalSearchResult::searchAndAdd(CString sqlcmd)  //sqlcmd为查询条件
{
	CConndb getarticle;

	getarticle.search(sqlcmd);
	CString titles,id,addtime,locaddress,classname,author,diffiNum,filetype;
	_variant_t var;
	try
	{
		if(!getarticle.m_pRecordset->BOF)
		{
			getarticle.m_pRecordset->MoveFirst();
			m_serResult.DeleteAllItems();
		}
		else
		{
			MessageBox(_T("没有相关文章，请重新搜索"));
			return false;
		}
		int i=0;
		while(!getarticle.m_pRecordset->adoEOF)
		{
			var=getarticle.m_pRecordset->GetCollect("title");
			if(var.vt!=VT_NULL)
				titles=(LPCSTR)_bstr_t(var);
			var=getarticle.m_pRecordset->GetCollect("id");
			if(var.vt!=VT_NULL)
				id=(LPCSTR)_bstr_t(var);
			var=getarticle.m_pRecordset->GetCollect("addtime");
			if(var.vt!=VT_NULL)
				addtime=(LPCSTR)_bstr_t(var);
			var=getarticle.m_pRecordset->GetCollect("txtaddress");
			if(var.vt!=VT_NULL)
				locaddress=(LPCSTR)_bstr_t(var);
			var=getarticle.m_pRecordset->GetCollect("classname");
			if(var.vt!=VT_NULL)
				classname=(LPCSTR)_bstr_t(var);
			var=getarticle.m_pRecordset->GetCollect("author");
			if(var.vt!=VT_NULL)
				author=(LPCSTR)_bstr_t(var);
			else
				author=_T("");
			var=getarticle.m_pRecordset->GetCollect("difficulty");
			if(var.vt!=VT_NULL)
				diffiNum=(LPCSTR)_bstr_t(var);
			else
				diffiNum=_T("");
			var=getarticle.m_pRecordset->GetCollect("artitletype");
			if(var.vt!=VT_NULL)
				filetype=(LPCSTR)_bstr_t(var);
			else
				filetype=_T("tit");
			//添加项
			m_serResult.InsertItem(i,_T(""));
			//添加数据
			m_serResult.SetItemText(i,0,titles);
			m_serResult.SetItemText(i,1,addtime);
			m_serResult.SetItemText(i,2,id);
			m_serResult.SetItemText(i,3,author);
			m_serResult.SetItemText(i,4,classname);
			m_serResult.SetItemText(i,5,diffiNum);
			m_serResult.SetItemText(i,6,locaddress);
			m_serResult.SetItemText(i,7,filetype);
			getarticle.m_pRecordset->MoveNext();
		}
		getarticle.m_pRecordset.Release();
	}
	catch(_com_error *e)
	{
		AfxMessageBox(e->ErrorMessage());
		return false;
	}
	return true;

}
void ClocalSearchResult::OnNMDblclkResult(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<NMITEMACTIVATE*>(pNMHDR);
	
	// TODO: 在此添加控件通知处理程序代码
	//得到文章内容
	CString pageno;
	for(int i=0;i<m_serResult.GetItemCount();i++)
	{
		if(m_serResult.GetItemState(i,LVIS_SELECTED)==LVIS_SELECTED)
		{
			pageno=m_serResult.GetItemText(i,2);
		}
	}
	CString cmdsql;
	cmdsql.Format(_T("select a.title,a.content,a.classid,a.id,a.addtime,a.txtaddress,a.author,a.artitletype,a.keyword,a.difficulty,c.classname from articles AS a,class AS c where a.id=%s and a.classid=c.id"),pageno);
	CConndb getarticle;
	getarticle.getarticle(cmdsql);
	
	CString title,classid,id,addtime,locaddress,classname,author,keyword,difficulty,type;
	CStringA content;
	difficulty=_T("0");
	_variant_t var;
	try
	{
		if(!getarticle.m_pRecordset->BOF)
		{
			getarticle.m_pRecordset->MoveFirst();
		}
		else
		{
			MessageBox(_T("该文章已不存在，请重新搜索"));
			return;
		}
		int i=0;
		while(!getarticle.m_pRecordset->adoEOF)
		{
			var=getarticle.m_pRecordset->GetCollect("title");
			if(var.vt!=VT_NULL)
				title=(LPCSTR)_bstr_t(var);
			var=getarticle.m_pRecordset->GetCollect("id");
			if(var.vt!=VT_NULL)
				id=(LPCSTR)_bstr_t(var);
			var=getarticle.m_pRecordset->GetCollect("addtime");
			if(var.vt!=VT_NULL)
				addtime=(LPCSTR)_bstr_t(var);
			var=getarticle.m_pRecordset->GetCollect("content");
			if(var.vt!=VT_NULL)
			{	
				content=(LPCSTR)_bstr_t(var);

			}
			var=getarticle.m_pRecordset->GetCollect("classid");
			if(var.vt!=VT_NULL)
				classid=(LPCSTR)_bstr_t(var);
			var=getarticle.m_pRecordset->GetCollect("txtaddress");
			if(var.vt!=VT_NULL)
				locaddress=(LPCSTR)_bstr_t(var);
			var=getarticle.m_pRecordset->GetCollect("classname");
			if(var.vt!=VT_NULL)
				classname=(LPCSTR)_bstr_t(var);
			var=getarticle.m_pRecordset->GetCollect("author");
			if(var.vt!=VT_NULL)
				author=(LPCSTR)_bstr_t(var);
			var=getarticle.m_pRecordset->GetCollect("artitletype");
			if(var.vt!=VT_NULL)
				type=(LPCSTR)_bstr_t(var);
			var=getarticle.m_pRecordset->GetCollect("difficulty");
			if(var.vt!=VT_NULL)
				difficulty=(LPCSTR)_bstr_t(var);
			var=getarticle.m_pRecordset->GetCollect("keyword");
			if(var.vt!=VT_NULL)
				keyword=(LPCSTR)_bstr_t(var);


			getarticle.m_pRecordset->MoveNext();
		}
		
		getarticle.m_pRecordset.Release();
	}
	catch(_com_error *e)
	{
		AfxMessageBox(e->ErrorMessage());
	
	}


	bool istemp=false;//是否缓存	
	if(GetFileAttributes(locaddress)==INVALID_FILE_ATTRIBUTES)
	{
		//文件是否存在
		CString filePath;
		getexeurl(&filePath);
		filePath+=_T("Temp\\");
		WIN32_FIND_DATA   wfd;
        HANDLE hFind = FindFirstFile(filePath, &wfd);
		//文件夹是否存在
        if (!((hFind != INVALID_HANDLE_VALUE) && (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)))
	    {
              SECURITY_ATTRIBUTES attrib;
			 attrib.bInheritHandle = FALSE;
			 attrib.lpSecurityDescriptor = NULL;
			 attrib.nLength =sizeof(SECURITY_ATTRIBUTES);
			 //上面定义的属性可以省略。 直接return ::CreateDirectory( path, NULL); 即可
			::CreateDirectory(filePath, &attrib);
        }
        FindClose(hFind);
		CFile aFile;
		if(type==_T("txt"))
		{
			locaddress.Format(_T("%s%s.txt"),filePath,title);
		}
		else
		{
			locaddress.Format(_T("%s%s.tit"),filePath,title);
		}
		if(!aFile.Open(locaddress,CFile::modeCreate|CFile::modeReadWrite,NULL))
		{
			AfxMessageBox(_T("文件打开失败"));
			return;
		}
		aFile.Write(content,content.GetLength());

		aFile.Close();
		istemp=true;
   
	 }
	 
	 //新建文档对象
	 CitbookApp *app=(CitbookApp*)AfxGetApp();
	 if(type==_T("txt"))
	 {
		 CtxtDoc* pdoc=(CtxtDoc*)( app->OpenDocumentFile(locaddress) );
		 
		 pdoc->m_isFromDb=true;
		 pdoc->m_aid=_ttoi(id);
		 pdoc->m_classid=classid;
		 pdoc->m_classname=classname;
		 pdoc->m_title=title;
		 pdoc->m_oldPath=locaddress;
		 pdoc->m_nowPath=locaddress;
		 pdoc->m_isTemp=istemp;
		 pdoc->m_author=author;
		 pdoc->m_artitletype=_T("txt");
		 pdoc->m_keyword=keyword;
		 pdoc->m_difficulty=difficulty;
		 pdoc->SetModifiedFlag(FALSE);

	 }
	 else
	 {
		 CitbookDoc* pdoc=(CitbookDoc*)( app->OpenDocumentFile(locaddress) );
		 
		 pdoc->m_isFromDb=true;
		 pdoc->m_aid=_ttoi(id);
		 pdoc->m_classid=classid;
		 pdoc->m_classname=classname;
		 pdoc->m_title=title;
		 pdoc->m_oldPath=locaddress;
		 pdoc->m_nowPath=locaddress;
		 pdoc->m_isTemp=istemp;
		 pdoc->m_author=author;
		 pdoc->m_artitletype=_T("tit");
		 pdoc->m_keyword=keyword;
		 pdoc->m_difficulty=difficulty;

		 pdoc->SetModifiedFlag(FALSE);
	 }
	 //ShowWindow(SW_MINIMIZE);
	 //::SetWindowPos(AfxGetMainWnd()->m_hWnd,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
	 //this->SetWindowPos(AfxGetMainWnd(),0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
	*pResult = 0;
}
//得到程序路径
void ClocalSearchResult::getexeurl(CString* purl)
{
	TCHAR exefileurl[MAX_PATH];
	GetModuleFileName(NULL,exefileurl,MAX_PATH);
	(_tcsrchr(exefileurl, _T('\\')))[1] = 0;
	*purl=exefileurl;
}
// 字符串分割
void ClocalSearchResult::stringSplit(CString& source, CString& result, CString division)
{
	source.TrimLeft();
	source.TrimRight();
	result.Empty();
    int pos = 0;
    int pre_pos = 0;
	bool isfirst=true;
	CString temp;
	CString tempresult;
	CString word;
    while( -1 != pos )
	{
        pre_pos = pos;
        pos = source.Find(division,(pos+1));
		
			
		if(pos!=-1)
		{
			word=source.Mid(pre_pos,(pos-pre_pos));
			word.TrimLeft();
			word.TrimRight();
			
		}
		else
		{
			word=source.Mid(pre_pos);
			word.TrimLeft();
			word.TrimRight();
		}
		if(word.IsEmpty())
			continue;

		temp.Format(_T("(a.title like '%c%s%c')"),0x25,word,0x25);

		if(isfirst)
		{
			tempresult=temp;
			isfirst=false;
		}
		else
		{
			tempresult+=_T(" OR ");
			tempresult+=temp;
			//tempresult.Format(_T("%s OR %s"),tempresult,temp);
		}
    }
	result=tempresult;
}

void ClocalSearchResult::OnBnClickedLocalser()
{
	// TODO: 在此添加控件通知处理程序代码
	 CString title;
	 GetDlgItem(IDC_TITLE)->GetWindowTextW(title);
	 if(title.IsEmpty())
	 {
		 MessageBox(_T("标题不能为空"));
		 
	 }
	 else
	 {		
		this->searchArticle(title);
	
	 }
}

void ClocalSearchResult::OnBnClickedDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	if(AfxMessageBox(_T("请确认是否删除？"),MB_OKCANCEL)==IDCANCEL)
		return;
	CConndb del;
	CString no;
	CString localpath;
	int count=0;
	bool isdellocal=false;
	if(m_deletLocalFile.GetCheck())
		isdellocal=true;
	CArray<int,int> arr;
	for(int i=0;i<m_serResult.GetItemCount();i++)
	{
		if(m_serResult.GetCheck(i))
		{
			no=m_serResult.GetItemText(i,2);
			del.deleteRecord(no);
			arr.SetAtGrow(count,i);
			if(isdellocal)
			{
				localpath=m_serResult.GetItemText(i,3);
				DeleteFile(localpath);
			}
			count++;
		}
		
	}
	if(count==0)
		AfxMessageBox(_T("您未选择内容"));

	for(int i=0;i<arr.GetSize();i++)
	{
		m_serResult.DeleteItem(arr.GetAt(arr.GetSize()-i-1));		
	}
	
}


BOOL ClocalSearchResult::ClassInit(void)
{
	CTreeCtrl* tc=(CTreeCtrl*)GetDlgItem(IDC_RESULTCLASTREE);
	tc->DeleteAllItems();
	DWORD dwStyle = GetWindowLong(tc->m_hWnd,GWL_STYLE);
	dwStyle |= WS_CHILD|TVS_HASLINES|TVS_LINESATROOT|TVS_HASBUTTONS|TVS_SHOWSELALWAYS;
    SetWindowLong(tc->m_hWnd,GWL_STYLE,dwStyle);
	
	//添加图示列表
	
	Cil1.Create(16,16,ILC_COLORDDB|ILC_MASK,0,2);
	Cil1.Add(AfxGetApp()->LoadIcon(IDI_FILES0));
	Cil1.Add(AfxGetApp()->LoadIcon(IDI_FILES1));
	tc->SetImageList(&Cil1,TVSIL_NORMAL);
	Cil1.SetBkColor(tc->GetBkColor());
	//tc->InsertItem(TVIF_TEXT|TVIF_PARAM|TVIF_IMAGE|TVIF_SELECTEDIMAGE,_T("所有分类"),0,1,0,0,0,NULL,NULL);
	//tc->SetExtendedStyle(0,TVS_HASLINES|TVS_LINESATROOT|TVS_HASBUTTONS|TVS_SHOWSELALWAYS|TVS_DISABLEDRAGDROP);

	CString cmdsql;
	cmdsql=_T("SELECT * from class order by lv ASC,parentid ASC,id ASC");
	CConndb getclass;
	getclass.search(cmdsql);
	HTREEITEM hItem,hSubItem;//树句柄
	if(!getclass.m_pRecordset->BOF)
	{
		getclass.m_pRecordset->MoveFirst();
		CString classname;
		int pid;
		int curlv=1;
		int curparentid=0;
		_variant_t var;
		DWORD cid;
		int i=0;
		while(!getclass.m_pRecordset->adoEOF)
		{
			var=getclass.m_pRecordset->GetCollect("id");
			if(var.vt!=VT_NULL)
				cid=var.ulVal;
			
			var=getclass.m_pRecordset->GetCollect("classname");
			if(var.vt!=VT_NULL)
				classname=(LPCSTR)_bstr_t(var);
			var=getclass.m_pRecordset->GetCollect("parentid");
			if(var.vt!=VT_NULL)
				pid=var.intVal;
			var=getclass.m_pRecordset->GetCollect("lv");
			if(var.vt!=VT_NULL)
				curlv=var.intVal;
			
			if(pid!=0)
			{
				curlv--;//得到该类的父节点深度
				if(pid!=curparentid)
				{
					int beginlv=1;
					hItem=FindItem(*tc,tc->GetRootItem(),pid,&curlv,&beginlv);
					curparentid=pid;
				}
				hSubItem = tc->InsertItem(TVIF_TEXT|TVIF_PARAM|TVIF_IMAGE|TVIF_SELECTEDIMAGE,classname,0,1,0,0,cid,hItem,TVI_LAST);
			}
			else
			{
				tc->InsertItem(TVIF_TEXT|TVIF_PARAM|TVIF_IMAGE|TVIF_SELECTEDIMAGE,classname,0,1,0,0,cid,TVI_ROOT,TVI_LAST);
			}

			
			i++;
			getclass.m_pRecordset->MoveNext();
		}

	}

	return 0;
}

void ClocalSearchResult::OnTvnItemexpandingClasstree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	HTREEITEM hItem=pNMTreeView->itemNew.hItem;

	CTreeCtrl* pTb=(CTreeCtrl*)GetDlgItem(IDC_RESULTCLASTREE);

	if(pNMTreeView->action==TVE_EXPAND)
	{
		pTb->SetItemImage(hItem,1,1);
	}
	else
	{
		pTb->SetItemImage(hItem,0,1);
	}
	*pResult = 0;

}
//树右击
void ClocalSearchResult::OnNMRClickClasstree(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	CTreeCtrl* pTb=(CTreeCtrl*)GetDlgItem(IDC_RESULTCLASTREE);

	CPoint   point; 
	TVHITTESTINFO   HitTestInfo; 
	GetCursorPos(&point); 
	pTb->ScreenToClient(&point); 
	HitTestInfo.pt   =   point; 
	//HTREEITEM   hItem   = pTb->HitTest(&HitTestInfo);
	
	UINT uFlags;
   HTREEITEM   hItem =pTb->HitTest(point, &uFlags);

    if ((hItem != NULL) && (TVHT_ONITEM & uFlags))
	{
		pTb->Select(hItem, TVGN_CARET);
		GetCursorPos(&point);
		this->SetForegroundWindow();
			
		CMenu m_menu;
		m_menu.LoadMenu(IDR_ICONMENU);
			
		CMenu *psub = (CMenu *)m_menu.GetSubMenu(1);  			
		DWORD dwID =psub->TrackPopupMenu(TPM_RIGHTBUTTON,point.x,point.y ,this);
		m_menu.DestroyMenu();
	}
	

	*pResult = 0;
}

//添加发类
void ClocalSearchResult::OnTclassadd()
{

	// TODO: 在此添加命令处理程序代码
	CTreeCtrl* pTb=(CTreeCtrl*)GetDlgItem(IDC_RESULTCLASTREE);
	HTREEITEM hItem=pTb->GetSelectedItem();
	int pid=pTb->GetItemData(hItem);

	CDLclassnamedlg getname;
	getname.DoModal();
	CString classname=getname.m_name;
	if(classname.IsEmpty())
	{
		MessageBox(_T("分类名不能为空"));
		return;
	}
	CString sqlget;
	sqlget.Format(_T("select lv from class where id=%d"),pid);
	CConndb addclass;
	addclass.search(sqlget);
	int lv=0;
	if(!addclass.m_pRecordset->BOF)
	{
		addclass.m_pRecordset->MoveFirst();
		_variant_t var;
		var=addclass.m_pRecordset->GetCollect("lv");
		if(var.vt!=VT_NULL)
			lv=var.intVal;		
	}
	//插入新分类
	sqlget.Format(_T("insert into class (classname,parentid,lv) values ('%s',%d,%d)"),classname,pid,lv+1);
	addclass.excuteSql(sqlget);

	//得到刚才入的ID
	DWORD cid;
	sqlget.Format(_T("select max(id) as maxid from class"));
	addclass.search(sqlget);
	if(!addclass.m_pRecordset->BOF)
	{
		addclass.m_pRecordset->MoveFirst();
		_variant_t var;
		var=addclass.m_pRecordset->GetCollect("maxid");
		if(var.vt!=VT_NULL)
			cid=var.ulVal;
	}

	pTb->InsertItem(TVIF_TEXT|TVIF_PARAM|TVIF_IMAGE|TVIF_SELECTEDIMAGE,classname,0,1,0,0,cid,hItem,TVI_LAST);
	pTb->Expand(hItem,TVE_EXPAND);

	//通知初始化工具栏分类
	CMainFrame* pMain=(CMainFrame*)AfxGetMainWnd();
	CpropertyDlg* pDlg=&pMain->m_propertyBar;
	pDlg->SendMessage(WM_MY_SETCLASSINIT,0,0);

}


//编辑分类名称
void ClocalSearchResult::OnTvnEndlabeleditClasstree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CString nowname;
	nowname=pTVDispInfo->item.pszText;
	if(nowname==this->m_beginClassname)
		return;
	CString sqltext;
	sqltext.Format(_T("update class set classname='%s' where id=%d"),nowname,pTVDispInfo->item.lParam);
	CConndb update;
	if(update.excuteSql(sqltext))
	{
		CTreeCtrl* pTb=(CTreeCtrl*)GetDlgItem(IDC_RESULTCLASTREE);
		TVITEMW tv;
		memset(&tv,0,sizeof(TVITEM));
		tv.mask=TVIF_TEXT|TVIF_PARAM|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
		tv.hItem=pTVDispInfo->item.hItem;
		pTb->GetItem(&tv);
		tv.pszText=(LPWSTR)(nowname.GetBuffer(nowname.GetLength()));
		nowname.ReleaseBuffer();
		pTb->SetItem(&tv);
	}
	
	//通知初始化工具栏分类
	CMainFrame* pMain=(CMainFrame*)AfxGetMainWnd();
	CpropertyDlg* pDlg=&pMain->m_propertyBar;
	pDlg->SendMessage(WM_MY_SETCLASSINIT,0,0);
	*pResult = 0;
}


void ClocalSearchResult::OnTvnBeginlabeleditClasstree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	this->m_beginClassname=pTVDispInfo->item.pszText;
	*pResult = 0;
}
//删除分类
void ClocalSearchResult::OnTclassdel()
{
	// TODO: 在此添加命令处理程序代码
	CTreeCtrl* pTb=(CTreeCtrl*)GetDlgItem(IDC_RESULTCLASTREE);
	HTREEITEM hItem=pTb->GetSelectedItem();
	if(pTb->ItemHasChildren(hItem))
	{
		AfxMessageBox(_T("该类含有子类,请先删除子类"));
		return;
	}
	CString sqlcmd;
	CConndb del;
	sqlcmd.Format(_T("select count(id) as num from articles where classid=%d"),pTb->GetItemData(hItem));
	del.search(sqlcmd);
	int count=0;
	if(!del.m_pRecordset->BOF)
	{
		del.m_pRecordset->MoveFirst();
		_variant_t var;
		var=del.m_pRecordset->GetCollect("num");
		if(var.vt!=VT_NULL)
			count=var.ulVal;
	}
	CString info;
	info.Format(_T("此次操作将删除%d篇文章"),count);
	if(AfxMessageBox(info,MB_OKCANCEL)!=IDOK)
		return;
	sqlcmd.Format(_T("delete from articles where classid=%d"),pTb->GetItemData(hItem));
	del.excuteSql(sqlcmd);
	sqlcmd.Format(_T("delete from class where id=%d"),pTb->GetItemData(hItem));
	
	if(del.excuteSql(sqlcmd))
	{
		pTb->DeleteItem(hItem);
	}
	
	//通知初始化工具栏分类
	CMainFrame* pMain=(CMainFrame*)AfxGetMainWnd();
	CpropertyDlg* pDlg=&pMain->m_propertyBar;
	pDlg->SendMessage(WM_MY_SETCLASSINIT,0,0);
}

void ClocalSearchResult::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	this->ShowWindow(FALSE);
	//CDialog::OnClose();
}



HTREEITEM ClocalSearchResult::FindItem(CTreeCtrl& tree, HTREEITEM item, DWORD strText,int* findLevel,int* curLevel)
{
	HTREEITEM hFind;	
	if(item == NULL)
		return NULL;
	
	while(item != NULL)
	{
		if(*findLevel==*curLevel)
		{
			//只有在到达指定深度时,才比较
			DWORD cc=tree.GetItemData(item);
			if(cc == strText)
				return item;
		}
		
		if(tree.ItemHasChildren(item))
		{
			(*curLevel)++;//深度加一
			item = tree.GetChildItem(item);
			hFind = FindItem(tree, item, strText,findLevel,curLevel);		
			if(hFind)
			{
				return hFind;		
			}
			else
			{
				item= tree.GetNextSiblingItem(tree.GetParentItem(item));
				(*curLevel)--;//深度减一
			}
		}
		else
		{
			item = tree.GetNextSiblingItem(item);
			if(item == NULL)
				return NULL;
		}		
	}

	return item;
}
void ClocalSearchResult::OnNMDblclkResultclastree(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	CTreeCtrl* pTb=(CTreeCtrl*)GetDlgItem(IDC_RESULTCLASTREE);
	int data;
	data=pTb->GetItemData(pTb->GetSelectedItem());
	searchClassId(data);
	*pResult = 0;
}

void ClocalSearchResult::OnAddrootclass()
{
	// TODO: 在此添加命令处理程序代码
	CDLclassnamedlg getname;
	//getname.SetWindowTextW(_T("添加分类"));
	getname.DoModal();
	CString classname=getname.m_name;
	//getname.Create(CDLclassnamedlg::IDD);
	//getname.ShowWindow(TRUE);
	if(classname.IsEmpty())
	{
		MessageBox(_T("分类名不能为空"));
		return;
	}
	CTreeCtrl* pTb=(CTreeCtrl*)GetDlgItem(IDC_RESULTCLASTREE);
	//CString classname=_T("新建分类,双击修改名字");
	CConndb addclass;
	//插入新分类
	CString sqlget;//=_T("insert into class (classname,parentid,lv) values ('新建分类,双击修改名字',0,1)");
	sqlget.Format(_T("insert into class (classname,parentid,lv) values ('%s',0,1)"),classname);
	addclass.excuteSql(sqlget);

	//得到刚才入的ID
	DWORD cid;
	sqlget.Format(_T("select max(id) as maxid from class"));
	addclass.search(sqlget);
	if(!addclass.m_pRecordset->BOF)
	{
		addclass.m_pRecordset->MoveFirst();
		_variant_t var;
		var=addclass.m_pRecordset->GetCollect("maxid");
		if(var.vt!=VT_NULL)
			cid=var.ulVal;
	}
	pTb->InsertItem(TVIF_TEXT|TVIF_PARAM|TVIF_IMAGE|TVIF_SELECTEDIMAGE,classname,0,1,0,0,cid,TVI_ROOT,TVI_LAST);
	//pTb->Expand(hItem,TVE_EXPAND);
	//通知初始化工具栏分类
	CMainFrame* pMain=(CMainFrame*)AfxGetMainWnd();
	CpropertyDlg* pDlg=&pMain->m_propertyBar;
	pDlg->SendMessage(WM_MY_SETCLASSINIT,0,0);
}

void ClocalSearchResult::OnBnClickedAfterpage()
{
	// TODO: 在此添加控件通知处理程序代码
	m_pageIndex++;
	if(m_pageIndex>m_pageCount)
	{
		m_pageIndex--;
		return;
	}
	//setPageButtonInfo();
	
	CString sqlcmd;
	sqlcmd.Format(_T("SELECT TOP %d * FROM ( SELECT TOP %d a.title,a.id,a.classid,a.addtime,a.txtaddress,c.classname,a.author,a.difficulty,a.artitletype FROM articles AS a,class AS c where a.classid=c.id and %s ORDER BY a.id DESC )   ORDER BY a.id ASC ")
				,m_pageSize
				,m_pageSize*m_pageIndex
				,m_sqlCondition);

	searchAndAdd(sqlcmd);
	
}

void ClocalSearchResult::OnBnClickedPrepage()
{
	// TODO: 在此添加控件通知处理程序代码
	m_pageIndex--;
	if(m_pageIndex<1)
	{
		m_pageIndex++;
		return;
	}
	//setPageButtonInfo();

	CString sqlcmd;
	sqlcmd.Format(_T("SELECT TOP %d * FROM ( SELECT TOP %d a.title,a.id,a.classid,a.addtime,a.txtaddress,c.classname,a.author,a.difficulty,a.artitletype FROM articles AS a,class AS c where a.classid=c.id and %s ORDER BY a.id DESC )   ORDER BY a.id ASC ")
				,m_pageSize
				,m_pageSize*m_pageIndex
				,m_sqlCondition);

	searchAndAdd(sqlcmd);

}

void ClocalSearchResult::OnCbnSelchangeJmppage()
{
	// TODO: 在此添加控件通知处理程序代码
	int index=((CComboBox*)GetDlgItem(IDC_JMPPAGE))->GetCurSel();
	index++;
	m_pageIndex=index;
	if(m_pageIndex<0 || m_pageIndex>m_pageCount)
		return;
	//setPageButtonInfo();
	
	CString sqlcmd;
	sqlcmd.Format(_T("SELECT TOP %d * FROM ( SELECT TOP %d a.title,a.id,a.classid,a.addtime,a.txtaddress,c.classname,a.author,a.difficulty,a.artitletype FROM articles AS a,class AS c where a.classid=c.id and %s ORDER BY a.id DESC )   ORDER BY a.id ASC ")
				,m_pageSize
				,m_pageSize*m_pageIndex
				,m_sqlCondition);


	searchAndAdd(sqlcmd);
}

void ClocalSearchResult::setPageButtonInfo()
{
	//向前
	//if(m_pageIndex<=1)
	//	((CButton*)GetDlgItem(IDC_PREPAGE))->EnableWindow(FALSE);
	//else
	//	((CButton*)GetDlgItem(IDC_PREPAGE))->EnableWindow(TRUE);

	////向后
	//if(m_pageIndex>=m_pageCount)
	//	((CButton*)GetDlgItem(IDC_AFTERPAGE))->EnableWindow(FALSE);
	//else
	//	((CButton*)GetDlgItem(IDC_AFTERPAGE))->EnableWindow(TRUE);
}
void ClocalSearchResult::OnUpdateButtonPrepage(CCmdUI * pCmdUI){
	pCmdUI ->Enable(m_pageIndex<=1?FALSE:TRUE);
}
void ClocalSearchResult::OnUpdateButtonAfterpage(CCmdUI * pCmdUI){
	pCmdUI ->Enable(m_pageIndex>=m_pageCount?FALSE:TRUE);
}


void ClocalSearchResult::OnClassReName()
{
	// TODO: 在此添加命令处理程序代

	CDLclassnamedlg getname;
	getname.DoModal();
	CString classname=getname.m_name;
	if(classname.IsEmpty())
	{
		MessageBox(_T("分类名不能为空"));
		return;
	}

	CTreeCtrl* pTb=(CTreeCtrl*)GetDlgItem(IDC_RESULTCLASTREE);
	HTREEITEM hItem=pTb->GetSelectedItem();
	int pid=pTb->GetItemData(hItem);
	
	
	CString sqltext;
	sqltext.Format(_T("update class set classname='%s' where id=%d"),classname,pid);
	CConndb update;
	if(update.excuteSql(sqltext))
	{
		pTb->SetItemText(hItem,classname);
	}

	//通知初始化工具栏分类
	CMainFrame* pMain=(CMainFrame*)AfxGetMainWnd();
	CpropertyDlg* pDlg=&pMain->m_propertyBar;
	pDlg->SendMessage(WM_MY_SETCLASSINIT,0,0);
}

void ClocalSearchResult::OnUpdateUIState(UINT /*nAction*/, UINT /*nUIElement*/)
{
	// 该功能要求使用 Windows 2000 或更高版本。
	// 符号 _WIN32_WINNT 和 WINVER 必须 >= 0x0500。
	// TODO: 在此处添加消息处理程序代码
}
