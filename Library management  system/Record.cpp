// Record.cpp : implementation file
//

#include "stdafx.h"
#include "Library.h"
#include "Record.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRecord

IMPLEMENT_DYNAMIC(CRecord, CRecordset)

CRecord::CRecord(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRecord)
	m_manager_id = _T("");
	m_borrower_id = _T("");
	m_book_id = _T("");
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CRecord::GetDefaultConnect()
{
	return _T("ODBC;DSN=SQL10;UID=user931;PWD=10101010");
}

CString CRecord::GetDefaultSQL()
{
	return _T("[user931].[record]");
}

void CRecord::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRecord)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[manager_id]"), m_manager_id);
	RFX_Text(pFX, _T("[borrower_id]"), m_borrower_id);
	RFX_Text(pFX, _T("[book_id]"), m_book_id);
	RFX_Date(pFX, _T("[borrower_time]"), m_borrower_time);
	RFX_Date(pFX, _T("[back_time]"), m_back_time);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRecord diagnostics

#ifdef _DEBUG
void CRecord::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRecord::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
