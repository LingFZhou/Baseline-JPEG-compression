#if !defined(AFX_DELETECARD_H__431B5D2E_09D5_4578_9D32_90BF17459A22__INCLUDED_)
#define AFX_DELETECARD_H__431B5D2E_09D5_4578_9D32_90BF17459A22__INCLUDED_
#include "Borrower.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DELETECARD.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDELETECARD dialog

class CDELETECARD : public CDialog
{
// Construction
public:
	CDELETECARD(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDELETECARD)
	enum { IDD = IDD_DELETECARD };
	CString	m_cardNum;
	CString	m_name;
	CString	m_type;
	CString	m_unit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDELETECARD)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDELETECARD)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CBorrower m_cardSet;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DELETECARD_H__431B5D2E_09D5_4578_9D32_90BF17459A22__INCLUDED_)
