#if !defined(AFX_MANAGER_H__BD87C0A9_B6E0_43D6_9EAF_5EA3153A853D__INCLUDED_)
#define AFX_MANAGER_H__BD87C0A9_B6E0_43D6_9EAF_5EA3153A853D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Manager.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CManager recordset

class CManager : public CRecordset
{
public:
	CManager(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CManager)

// Field/Param Data
	//{{AFX_FIELD(CManager, CRecordset)
	CString	m_manager_id;
	CString	m_manager_name;
	CString	m_psw;
	CString	m_phone_number;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CManager)
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

#endif // !defined(AFX_MANAGER_H__BD87C0A9_B6E0_43D6_9EAF_5EA3153A853D__INCLUDED_)
