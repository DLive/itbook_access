// CntrItem.cpp : CitbookCntrItem ���ʵ��
//

#include "stdafx.h"
#include "itbook.h"

#include "itbookDoc.h"
#include "itbookView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CitbookCntrItem ��ʵ��

IMPLEMENT_SERIAL(CitbookCntrItem, CRichEditCntrItem, 0)

CitbookCntrItem::CitbookCntrItem(REOBJECT* preo, CitbookDoc* pContainer)
	: CRichEditCntrItem(preo, pContainer)
{
	// TODO: �ڴ����һ���Թ������
}

CitbookCntrItem::~CitbookCntrItem()
{
	// TODO: �ڴ˴�����������
}


// CitbookCntrItem ���

#ifdef _DEBUG
void CitbookCntrItem::AssertValid() const
{
	CRichEditCntrItem::AssertValid();
}

void CitbookCntrItem::Dump(CDumpContext& dc) const
{
	CRichEditCntrItem::Dump(dc);
}
#endif

