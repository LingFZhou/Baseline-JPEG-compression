// Borrower.cpp : implementation file
//

#include "stdafx.h"
#include "Library.h"
#include "Borrower.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBorrower

IMPLEMENT_DYNAMIC(CBorrower, CRecordset)

CBorrower::CBorrower(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CBorrower)
	m_borrower_id = _T("");
	m_borrower_name = _T("");
	m_borrower_depart = _T("");
	m_borrower_type = _T("");
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CBorrower::GetDefaultConnect()
{
	return _T("ODBC;DSN=SQL10;UID=user931;PWD=10101010");
}

CString CBorrower::GetDefaultSQL()
{
	return _T("[user931].[borrower]");
}

void CBorrower::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CBorrower)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[borrower_id]"), m_borrower_id);
	RFX_Text(pFX, _T("[borrower_name]"), m_borrower_name);
	RFX_Text(pFX, _T("[borrower_depart]"), m_borrower_depart);
	RFX_Text(pFX, _T("[borrower_type]"), m_borrower_type);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CBorrower diagnostics

#ifdef _DEBUG
void CBorrower::AssertValid() const
{
	CRecordset::AssertValid();
}

void CBorrower::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
