// itbook.h : itbook Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"  // ������
#include "CommResours.h" 

// CitbookApp:
// �йش����ʵ�֣������ itbook.cpp
//


class CitbookApp : public CWinApp
{
public:
	CitbookApp();
	
	
// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnNewtitfile();
	//����չ��

	afx_msg void OnNewtxtfile();
	afx_msg void seltNewfile();
};

extern CitbookApp theApp;