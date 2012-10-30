#include "StdAfx.h"
#include "Ccommon.h"

Ccommon::Ccommon(void)
{
}

Ccommon::~Ccommon(void)
{
}

void Ccommon::transFormSinQuote(CString &source)
{
	//source.Replace("'","''");
}

void Ccommon::getExeUrl(CString *url)
{
	TCHAR exefileurl[MAX_PATH];
	GetModuleFileName(NULL,exefileurl,MAX_PATH);
	(_tcsrchr(exefileurl, _T('\\')))[1] = 0;
	*url=exefileurl;
}

// ɾ��Ŀ¼�������ļ�
bool Ccommon::DeleteDirectory(const CString  &pathName)
{
	CFileFind fFind;
	CString dirName=pathName;	
	if(dirName.Right(1)!=_T("\\"))
		dirName+=_T("\\");
	CString tempName=dirName;
	dirName+=_T("*.*");
	CString deletefile;
	BOOL isFind=fFind.FindFile(dirName);
	int num=0;
	while(isFind)
	{
		num++;
		isFind=fFind.FindNextFileW();
		if(!fFind.IsDirectory() && !fFind.IsDots())
		{
			//�����ļ�
			tempName=fFind.GetFilePath();
			DeleteFile(tempName);
			num--;
		}
		else if(fFind.IsDirectory() && !fFind.IsDots())
			DeleteDirectory(fFind.GetFilePath());
	}
	fFind.Close();
	if(num==0)
		return true; //�ļ���Ϊ��
	else
		return false;
}
