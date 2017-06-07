// Manager.cpp : implementation file
//

#include "stdafx.h"
#include "Library.h"
#include "Manager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CManager

IMPLEMENT_DYNAMIC(CManager, CRecordset)

CManager::CManager(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CManager)
	m_manager_id = _T("");
	m_manager_name = _T("");
	m_psw = _T("");
	m_phone_number = _T("");
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CManager::GetDefaultConnect()
{
	return _T("ODBC;DSN=SQL10;UID=user931;PWD=10101010");
}

CString CManager::GetDefaultSQL()
{
	return _T("[user931].[manager]");
}

void CManager::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CManager)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[manager_id]"), m_manager_id);
	RFX_Text(pFX, _T("[manager_name]"), m_manager_name);
	RFX_Text(pFX, _T("[psw]"), m_psw);
	RFX_Text(pFX, _T("[phone_number]"), m_phone_number);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CManager diagnostics

#ifdef _DEBUG
void CManager::AssertValid() const
{
	CRecordset::AssertValid();
}

void CManager::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
