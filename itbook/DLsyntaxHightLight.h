#pragma once


typedef struct WORDINFO
{
	DWORD      WordLen;   //�ʵĳ��ȣ��������ٱȽ�
	LPTSTR     pszWord;   //�ʵ�ָ��
	COLORREF   Color;   //��ɫֵ
	WORDINFO * NextLink;     //��һ�� WORDINFO �ṹ
}WORDINFO;

class DLsyntaxHightLight
{
public:
	DLsyntaxHightLight(void);
	~DLsyntaxHightLight(void);

	void ReadKeyWord();

	//����
public:
	DWORD CppSyntaxArray[256];
};
