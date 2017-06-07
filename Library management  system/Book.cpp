// Book.cpp : implementation file
//

#include "stdafx.h"
#include "Library.h"
#include "Book.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBook

IMPLEMENT_DYNAMIC(CBook, CRecordset)

CBook::CBook(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CBook)
	m_book_id = _T("");
	m_book_type = _T("");
	m_book_name = _T("");
	m_publish_comp = _T("");
	m_pub_year = 0;
	m_author = _T("");
	m_price = 0.0;
	m_tot_num = 0;
	m_cur_num = 0;
	m_nFields = 9;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CBook::GetDefaultConnect()
{
	return _T("ODBC;DSN=SQL10;UID=user931;PWD=10101010");
}

CString CBook::GetDefaultSQL()
{
	return _T("[user931].[book]");
}

void CBook::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CBook)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[book_id]"), m_book_id);
	RFX_Text(pFX, _T("[book_type]"), m_book_type);
	RFX_Text(pFX, _T("[book_name]"), m_book_name);
	RFX_Text(pFX, _T("[publish_comp]"), m_publish_comp);
	RFX_Long(pFX, _T("[pub_year]"), m_pub_year);
	RFX_Text(pFX, _T("[author]"), m_author);
	RFX_Double(pFX, _T("[price]"), m_price);
	RFX_Long(pFX, _T("[tot_num]"), m_tot_num);
	RFX_Long(pFX, _T("[cur_num]"), m_cur_num);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CBook diagnostics

#ifdef _DEBUG
void CBook::AssertValid() const
{
	CRecordset::AssertValid();
}

void CBook::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
