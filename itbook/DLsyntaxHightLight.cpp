#include "StdAfx.h"
#include "DLsyntaxHightLight.h"

DLsyntaxHightLight::DLsyntaxHightLight(void)
{
}

DLsyntaxHightLight::~DLsyntaxHightLight(void)
{
}

DLsyntaxHightLight::ReadKeyWord()
{
	TCHAR buffer[1024];
	DWORD BlockSize;
	LPVOID pTemp;
	DWORD nRet;

	RtlZeroMemory(CppSyntaxArray,sizeof(CppSyntaxArray));
	//��ʼ�� CppSyntaxArray Ϊ 0 ��

	//	GetModuleFileName(g_hInstance,buffer,sizeof(buffer));
	//int nLen = lstrlen(buffer);
	//TCHAR *pChar = buffer + nLen -1;
	//while(*pChar != '\\')
	//{
	//	pChar --;
	//}
	//*pChar = '\0';
	//lstrcat(buffer,WordFileName);
	//���� wordfile.txt ����ȫ·���� �Ҽٶ����ļ����Ǹ������ļ���ͬһ���ļ��С�

		//if(GetFileAttributes(buffer) != -1)
		//{
			//��ʹ��������������ټ���һ���ļ��Ƿ���ڡ�

	BlockSize = 1024 *10;
	pTemp = HeapAlloc(GetProcessHeap(),0,BlockSize);
	//�����ڴ������������ʡ�ȱʡ��10K���Ǵ�ȱʡ���з���ġ�

				while(1)
				{
					nRet = GetPrivateProfileString(CppSection,C1Key,ZeroString,(char *)pTemp,BlockSize,buffer);
					if(nRet != 0)
					{
						//��ʹ�� GetPrivateProfileString ������ wordfile.txt ��ÿһ���ؼ��ֵ����ݡ��ؼ��ִ� C1 ��C10��
							nRet ++;
						if(nRet == BlockSize)
						{
							BlockSize += 1024 *10;
							pTemp = HeapReAlloc(hMainHeap,0,pTemp,BlockSize);
							continue;
						}
						//����ڴ���Ƿ��㹻����������Ļ������Ǿ�����10K��ֱ���㹻��Ϊֹ��

							ParseBuffer(hMainHeap,pTemp,nRet,CppColorArray[0],CppSyntaxArray);
						break;    
					}
					else
						break;

				}

}