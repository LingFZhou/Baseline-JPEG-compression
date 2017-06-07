#if !defined(AFX_RECORD_H__78DC096C_AD79_4423_9C5B_0E04BC2988C7__INCLUDED_)
#define AFX_RECORD_H__78DC096C_AD79_4423_9C5B_0E04BC2988C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Record.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRecord recordset

class CRecord : public CRecordset
{
public:
	CRecord(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRecord)

// Field/Param Data
	//{{AFX_FIELD(CRecord, CRecordset)
	CString	m_manager_id;
	CString	m_borrower_id;
	CString	m_book_id;
	CTime	m_borrower_time;
	CTime	m_back_time;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecord)
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

#endif // !defined(AFX_RECORD_H__78DC096C_AD79_4423_9C5B_0E04BC2988C7__INCLUDED_)
