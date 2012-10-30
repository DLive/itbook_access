// classset.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "itbook.h"
#include "classset.h"
#include "Conndb.h"


// Cclassset �Ի���

IMPLEMENT_DYNAMIC(Cclassset, CPropertyPage)

Cclassset::Cclassset()
	: CPropertyPage(Cclassset::IDD)
{

}

Cclassset::~Cclassset()
{
}

void Cclassset::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);


	DDX_Control(pDX, IDC_ADDFCLASS, m_addFather);
	DDX_Control(pDX, IDC_DELCLASS, m_delclass);
	DDX_Control(pDX, IDC_CHANGECLASS, m_changeClassname);
	DDX_Control(pDX, IDC_FATHERCHANG, m_fatherChangeName);
	DDX_Control(pDX, IDC_FATHER, m_fatherFather);
}
BEGIN_MESSAGE_MAP(Cclassset, CPropertyPage)
	ON_BN_CLICKED(IDC_ADDCLASS, &Cclassset::OnBnClickedAddclass)
	ON_BN_CLICKED(IDC_CHANGE, &Cclassset::OnBnClickedChange)
	ON_CBN_SELCHANGE(IDC_CHANGECLASS, &Cclassset::OnCbnSelchangeChangeclass)
	ON_BN_CLICKED(IDC_DEL, &Cclassset::OnBnClickedDel)
	ON_BN_CLICKED(IDC_CHANGEFATHER, &Cclassset::OnBnClickedChangefather)
	ON_CBN_SELCHANGE(IDC_FATHERCHANG, &Cclassset::OnCbnSelchangeFatherchang)
END_MESSAGE_MAP()


// Cclassset ��Ϣ�������

BOOL Cclassset::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	classinit();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

bool Cclassset::classinit()
{

	CString cmdsql;
	cmdsql=_T("select * from (select id,classname,parentid,iif(parentid=0,id,parentid) AS gid from class) order by gid ASC,parentid ASC");
	CConndb getclass;
	getclass.search(cmdsql);
	

	m_addFather.ResetContent();
	m_delclass.ResetContent();
	m_changeClassname.ResetContent();
	m_fatherChangeName.ResetContent();
	m_fatherFather.ResetContent();
	
	//�������˵���ӱ���ѡ
	m_addFather.AddString(_T("��Ϊ������"));
	m_addFather.SetItemData(0,0);
	m_addFather.SetCurSel(0);

	m_fatherFather.AddString(_T("��Ϊ������"));
	m_fatherFather.SetItemData(0,0);
	m_fatherFather.SetCurSel(0);

	

	if(!getclass.m_pRecordset->BOF)
	{
		getclass.m_pRecordset->MoveFirst();
		CString classname;
		_variant_t var;
		DWORD cid;
		DWORD pid;
		int i=0;
		int di=1;
		while(!getclass.m_pRecordset->adoEOF)
		{
			var=getclass.m_pRecordset->GetCollect("id");
			if(var.vt!=VT_NULL)
				cid=var.lVal;
			
			var=getclass.m_pRecordset->GetCollect("classname");
			if(var.vt!=VT_NULL)
				classname=(LPCSTR)_bstr_t(var);
			var=getclass.m_pRecordset->GetCollect("parentid");
			if(var.vt!=VT_NULL)
				pid=var.lVal;
			if(pid!=0)
			{
				m_delclass.AddString(classname);
				m_delclass.SetItemData(i,cid);

				m_changeClassname.AddString(classname);
				m_changeClassname.SetItemData(i,cid);

				m_fatherChangeName.AddString(classname);
				m_fatherChangeName.SetItemData(i,cid);

			}
			else
			{				
				
				//����Ƕ�����
				m_addFather.AddString(classname);
				m_addFather.SetItemData(di,cid);

				m_delclass.AddString(classname);
				m_delclass.SetItemData(i,cid);
				
				m_changeClassname.AddString(classname);
				m_changeClassname.SetItemData(i,cid);

				m_fatherChangeName.AddString(classname);
				m_fatherChangeName.SetItemData(i,cid);

				m_fatherFather.AddString(classname);
				m_fatherFather.SetItemData(di,cid);

				di++;
			}
			
			i++;
			getclass.m_pRecordset->MoveNext();
		}
	}

	m_delclass.SetCurSel(0);

	m_changeClassname.SetCurSel(0);
	OnCbnSelchangeChangeclass();
	
	m_fatherChangeName.SetCurSel(0);

	return true;
}
void Cclassset::OnBnClickedAddclass()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString classname;
	GetDlgItem(IDC_ADDCLASSNAME)->GetWindowText(classname);
	if(classname.IsEmpty())
	{
		MessageBox(_T("��������Ϊ��"));
		return;
	}
	int pid;
	int index;
	index=m_addFather.GetCurSel();
	pid=(int)m_addFather.GetItemData(index);
	CString sqlcmd;
	sqlcmd.Format(_T("insert into class (classname,parentid) values('%s',%d)"),classname,pid);
	CConndb add;
	if(add.insert(sqlcmd)>=1)
	{
		MessageBox(_T("��ӳɹ�"));
		classinit();
	}
	else
		MessageBox(_T("���ʧ��,������"));


}

void Cclassset::OnBnClickedChange()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString asCn;
	GetDlgItem(IDC_CHANGEASCLASS)->GetWindowText(asCn);
	if(asCn.IsEmpty())
	{
		MessageBox(_T("��������Ϊ��,����д"));
		GetDlgItem(IDC_CHANGEASCLASS)->SetFocus();
		return;
	}
	int index,cid;
	CString sqlcmd;
	index=m_changeClassname.GetCurSel();
	cid=m_changeClassname.GetItemData(index);
	sqlcmd.Format(_T("update class set classname='%s' where id=%d"),asCn,cid);
	CConndb update;
	update.excuteSql(sqlcmd);
	if((int)update.RecordsAffecteds>=1)
	{

		MessageBox(_T("�޸ĳɹ�"));
		classinit();
	}
	else
		MessageBox(_T("�޸�ʧ��,������"));
	

}

void Cclassset::OnCbnSelchangeChangeclass()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString cn;
	m_changeClassname.GetLBText(m_changeClassname.GetCurSel(),cn);
	GetDlgItem(IDC_CHANGEASCLASS)->SetWindowTextW(cn);
}

void Cclassset::OnBnClickedDel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(BST_CHECKED==(((CButton*)GetDlgItem(IDC_DELARTICLE))->GetCheck()))
	{
		if(IDCANCEL==MessageBoxW(_T("���Ƿ�ȷ��ɾ����������£�"),_T("ȷ��ɾ��"),MB_OKCANCEL))
			return;
	}
	else
	{
		if(IDCANCEL==MessageBoxW(_T("���Ƿ�ȷ��ɾ�����ࣿ"),_T("ȷ��ɾ��"),MB_OKCANCEL))
			return;
	}
	int cid;
	cid=(int)m_delclass.GetItemData(m_delclass.GetCurSel());
	CString sqlcmd;
	sqlcmd.Format(_T("delete from class where id=%d or parentid=%d"),cid,cid);
	CConndb del;
	del.excuteSql(sqlcmd);
	int cnum; //ɾ���������Ŀ
	cnum=(int)del.RecordsAffecteds;
	CString msg;
	msg.Format(_T("���ι�ɾ��%d����"),cnum);
	if(BST_CHECKED==(((CButton*)GetDlgItem(IDC_DELARTICLE))->GetCheck()))
	{
		sqlcmd.Format(_T("delete from articles where classid=%d"),cid);
		del.excuteSql(sqlcmd);
		cnum=del.RecordsAffecteds;
		msg.Format(_T("%s��%d���¡�"),msg,cnum);
	}
	MessageBox(msg);
	classinit();
}

void Cclassset::OnBnClickedChangefather()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int id,pid;
	id=(int)m_fatherChangeName.GetItemData(m_fatherChangeName.GetCurSel());
	pid=(int)m_fatherFather.GetItemData(m_fatherFather.GetCurSel());
	CString sqlcmd;
	sqlcmd.Format(_T("update class set parentid=%d where id=%d"),pid,id);
	CConndb chg;
	chg.excuteSql(sqlcmd);
	classinit();
}

void Cclassset::OnCbnSelchangeFatherchang()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//int pid=(int)m_fatherChangeName.GetItemData(m_fatherChangeName.GetCurSel());
	//int ptemp;
	//for(int i=0;i<m_fatherFather.GetCount();i++)
	//{
	//	ptemp=(int)m_fatherFather.GetItemData(i);
	//	if(ptemp==pid)
	//	{
	//		m_fatherFather.SetCurSel(i);
	//		break;
	//	}
	//}
}
