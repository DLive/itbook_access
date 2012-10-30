// itPropertySheet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "itbook.h"
#include "itPropertySheet.h"



// CitPropertySheet

IMPLEMENT_DYNAMIC(CitPropertySheet, CPropertySheet)

CitPropertySheet::CitPropertySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	m_dfCaption=new TCHAR[256];
	m_dfListFont.CreatePointFont(30,_T("����"));
}

CitPropertySheet::CitPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	m_dfCaption=new TCHAR[256];
	m_dfListFont.CreatePointFont(30,_T("����"));
}

CitPropertySheet::~CitPropertySheet()
{
	delete [] m_dfCaption;
}


BEGIN_MESSAGE_MAP(CitPropertySheet, CPropertySheet)
END_MESSAGE_MAP()


// CitPropertySheet ��Ϣ�������

BOOL CitPropertySheet::OnInitDialog()
{
	BOOL bResult = CPropertySheet::OnInitDialog();

	// TODO:  �ڴ��������ר�ô���

	CRect rect, rectPage, rectTab;
	GetPage(0)->GetWindowRect(&rectPage);

	GetWindowRect(&rect);
	rect.right+=150;
	
	int nWidth=rectPage.Width();
	rectPage.right=rect.right-20;
	rectPage.left=rect.right-nWidth;
	ScreenToClient(&rectPage);
	m_rectPage=rectPage;
	GetPage(0)->MoveWindow(&rectPage);

	//��������ҳԭ����TabControl
	CTabCtrl* pTab=GetTabControl();
	pTab->GetWindowRect(&rectTab);
	ScreenToClient(&rectTab);
	if(!pTab->ShowWindow(SW_HIDE))
		return FALSE;

	//�����б�ؼ�
	if(!m_wndList.Create(WS_CHILD | WS_VISIBLE |  LVS_REPORT | LVS_NOCOLUMNHEADER , CRect(10 ,rectTab.top,150,rectPage.bottom ),this,35000))
		return FALSE;
	m_wndList.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	listinit();

	//�����и߶�
	CFont font;
	font.CreatePointFont(240,_T("����"));
	m_wndList.SetFont(&font);
	
	CString strCaption;
	GetPage(0)->GetWindowText(strCaption);
	_tcscpy(m_dfCaption, strCaption.GetBuffer(strCaption.GetLength()));	

	return bResult;
}
void CitPropertySheet::listinit()
{
	LVITEM lvi;
	::ZeroMemory(&lvi,sizeof(lvi));

	CHeaderCtrl* pHeader=m_wndList.GetHeaderCtrl();
	pHeader->ShowWindow(SW_HIDE);

	CRect rectList;
	m_wndList.GetWindowRect(&rectList);
	ScreenToClient(&rectList);
	//����б�ͷ��ǰ���Ѿ�����
	m_wndList.InsertColumn(0,_T("����"),LVCFMT_CENTER,rectList.Width(),0);
	CString str;
	CTabCtrl* pTab=GetTabControl();
	TCITEM tci;
	::ZeroMemory(&tci,sizeof(tci));
	tci.mask=TCIF_TEXT;
	tci.cchTextMax=256;
	TCHAR szBuf[256]={0};
	tci.pszText=szBuf;
	for(int idxPge=0;idxPge<GetPageCount();idxPge++)
	{
		if(pTab->GetItem(idxPge,&tci))
		{
			lvi.iItem=idxPge;
			lvi.iSubItem=0;
			//lvi.iImage=idxPge;
			lvi.mask=LVIF_TEXT; //LVIF_IMAGE;
			lvi.pszText=tci.pszText;
			m_wndList.InsertItem(&lvi);
		}
	}
}