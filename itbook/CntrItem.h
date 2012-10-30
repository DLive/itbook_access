// CntrItem.h : CitbookCntrItem ��Ľӿ�
//

#pragma once

class CitbookDoc;
class CitbookView;

class CitbookCntrItem : public CRichEditCntrItem
{
	DECLARE_SERIAL(CitbookCntrItem)

// ���캯��
public:
	CitbookCntrItem(REOBJECT* preo = NULL, CitbookDoc* pContainer = NULL);
		// ע��: ���� pContainer Ϊ NULL ������ IMPLEMENT_SERIALIZE
		//  IMPLEMENT_SERIALIZE Ҫ������д���
		//  �����Ĺ��캯����OLE ��ͨ������
		//  �� NULL �ĵ�ָ�빹���

// ����
public:
	CitbookDoc* GetDocument()
		{ return reinterpret_cast<CitbookDoc*>(CRichEditCntrItem::GetDocument()); }
	CitbookView* GetActiveView()
		{ return reinterpret_cast<CitbookView*>(CRichEditCntrItem::GetActiveView()); }

	public:
	protected:

// ʵ��
public:
	~CitbookCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

