#pragma once

class Ccommon
{
public:
	Ccommon(void);
	~Ccommon(void);

	//accessת�壭�����żӱ�
	void transFormSinQuote(CString &source);
	void getExeUrl(CString *url);
	// ɾ��Ŀ¼�������ļ�
	bool DeleteDirectory(const CString &pathName);
};
