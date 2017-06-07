#if !defined(AFX_BORROWER_H__53506522_75E2_4A5B_A3AE_BE54FF254359__INCLUDED_)
#define AFX_BORROWER_H__53506522_75E2_4A5B_A3AE_BE54FF254359__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Borrower.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBorrower recordset

class CBorrower : public CRecordset
{
public:
	CBorrower(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CBorrower)

// Field/Param Data
	//{{AFX_FIELD(CBorrower, CRecordset)
	CString	m_borrower_id;
	CString	m_borrower_name;
	CString	m_borrower_depart;
	CString	m_borrower_type;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBorrower)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BORROWER_H__53506522_75E2_4A5B_A3AE_BE54FF254359__INCLUDED_)
