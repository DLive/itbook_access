// itbookDoc.cpp : CitbookDoc ���ʵ��
//

#include "stdafx.h"
#include "itbook.h"

#include "itbookDoc.h"
#include "CntrItem.h"
#include "KSFileDialog.h"
#include "itbookView.h"
#include "InputDB.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CitbookDoc

IMPLEMENT_DYNCREATE(CitbookDoc, CRichEditDoc)


BEGIN_MESSAGE_MAP(CitbookDoc, CRichEditDoc)
	// ����Ĭ�ϵ� OLE ����ʵ��
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, &CRichEditDoc::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, &CRichEditDoc::OnEditLinks)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OLE_VERB_FIRST, ID_OLE_VERB_LAST, &CRichEditDoc::OnUpdateObjectVerbMenu)
	//ON_COMMAND(ID_FILE_OPEN, &CitbookDoc::OnFileOpen)
END_MESSAGE_MAP()


// CitbookDoc ����/����

CitbookDoc::CitbookDoc()
{
	// TODO: �ڴ����һ���Թ������
	m_isFromDb=false;
	m_isTemp=false;
	m_oldPath=_T("");
	m_nowPath=_T(" ");
	m_keyword=_T(" ");
	m_author=_T(" ");
	m_difficulty=_T("0");
	m_artitletype=_T("tit");
	m_isSavetoDb=TRUE;
	
}

CitbookDoc::~CitbookDoc()
{

}

BOOL CitbookDoc::OnNewDocument()
{
	if (!CRichEditDoc::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}

CRichEditCntrItem* CitbookDoc::CreateClientItem(REOBJECT* preo) const
{
	return new CitbookCntrItem(preo, const_cast<CitbookDoc*>(this));
}




// CitbookDoc ���л�

void CitbookDoc::Serialize(CArchive& ar)
{
	
	if (ar.IsStoring())
	{

	}
	else
	{		
		// TODO: �ڴ���Ӽ��ش���	
	}

	// ���û��� CRichEditDoc ������
	//  �����ĵ��� COleClientItem ��������л���
	// TODO: �����Ϊ�ı��������л��������� CRichEditDoc::m_bRTF = FALSE
	CRichEditDoc::Serialize(ar);		
}


// CitbookDoc ���

#ifdef _DEBUG
void CitbookDoc::AssertValid() const
{
	CRichEditDoc::AssertValid();
}

void CitbookDoc::Dump(CDumpContext& dc) const
{
	CRichEditDoc::Dump(dc);
}
#endif //_DEBUG


BOOL CitbookDoc::DoSave(LPCTSTR lpszPathName, BOOL bReplace)
{
	
	CKSFileDialog dlgFile(FALSE);
	dlgFile.SetDocumentPointer(this);
	dlgFile.SetAppPointer(AfxGetApp());
	dlgFile.SetMyParent(AfxGetMainWnd());
	return dlgFile.DoSave(lpszPathName,bReplace);

}


BOOL CitbookDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: �ڴ����ר�ô����/����û���

	 CRichEditDoc::OnSaveDocument(lpszPathName);
	 if(this->m_isSavetoDb)
	 {
		CInputDB insert(this);
		insert.getText(lpszPathName,_T("tit"));
		this->m_oldPath=lpszPathName;
		this->m_isFromDb=true;
	 }
	 
	return true;
}

void CitbookDoc::DeleteContents()
{
	// TODO: �ڴ����ר�ô����/����û���

	CRichEditDoc::DeleteContents();

}

BOOL CitbookDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CRichEditDoc::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO:  �ڴ������ר�õĴ�������
	this->SetModifiedFlag(FALSE);
	CInputDB setinfo(this);
	setinfo.m_getinfo(lpszPathName,_T("tit"));
	
	return TRUE;
}
void CitbookDoc::OnCloseDocument()
{
	// TODO: �ڴ����ר�ô����/����û���

	CRichEditDoc::OnCloseDocument();
	if(AfxGetApp()->m_pDocManager->GetOpenDocumentCount()<=0)
	{
		((CMainFrame*)AfxGetMainWnd())->m_propertyBar.m_pDoc=NULL;
	}
}
