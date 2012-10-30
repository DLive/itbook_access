#pragma once

class Ccommon
{
public:
	Ccommon(void);
	~Ccommon(void);

	//access转义－单引号加倍
	void transFormSinQuote(CString &source);
	void getExeUrl(CString *url);
	// 删除目录里所有文件
	bool DeleteDirectory(const CString &pathName);
};
