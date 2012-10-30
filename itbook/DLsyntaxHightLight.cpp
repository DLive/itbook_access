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
	//初始化 CppSyntaxArray 为 0 。

	//	GetModuleFileName(g_hInstance,buffer,sizeof(buffer));
	//int nLen = lstrlen(buffer);
	//TCHAR *pChar = buffer + nLen -1;
	//while(*pChar != '\\')
	//{
	//	pChar --;
	//}
	//*pChar = '\0';
	//lstrcat(buffer,WordFileName);
	//构建 wordfile.txt 的完全路径： 我假定该文件总是跟程序文件在同一个文件夹。

		//if(GetFileAttributes(buffer) != -1)
		//{
			//我使用这个方法来快速检验一个文件是否存在。

	BlockSize = 1024 *10;
	pTemp = HeapAlloc(GetProcessHeap(),0,BlockSize);
	//分配内存块来保存高亮词。缺省是10K。是从缺省堆中分配的。

				while(1)
				{
					nRet = GetPrivateProfileString(CppSection,C1Key,ZeroString,(char *)pTemp,BlockSize,buffer);
					if(nRet != 0)
					{
						//我使用 GetPrivateProfileString 来检索 wordfile.txt 中每一个关键字的内容。关键字从 C1 到C10。
							nRet ++;
						if(nRet == BlockSize)
						{
							BlockSize += 1024 *10;
							pTemp = HeapReAlloc(hMainHeap,0,pTemp,BlockSize);
							continue;
						}
						//检查内存块是否足够大。如果不够的话，我们就增大10K，直到足够大为止。

							ParseBuffer(hMainHeap,pTemp,nRet,CppColorArray[0],CppSyntaxArray);
						break;    
					}
					else
						break;

				}

}