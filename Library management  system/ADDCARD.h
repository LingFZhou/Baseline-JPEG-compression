#if !defined(AFX_ADDCARD_H__35907A3F_797E_4B47_9937_8FA4B028BDF1__INCLUDED_)
#define AFX_ADDCARD_H__35907A3F_797E_4B47_9937_8FA4B028BDF1__INCLUDED_
#include "Borrower.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ADDCARD.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CADDCARD dialog

class CADDCARD : public CDialog
{
// Construction
public:
	CADDCARD(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CADDCARD)
	enum { IDD = IDD_ADDCARD };
	CString	m_cardNum;
	CString	m_name;
	CString	m_type;
	CString	m_unit;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CADDCARD)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CADDCARD)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CBorrower m_cardSet;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDCARD_H__35907A3F_797E_4B47_9937_8FA4B028BDF1__INCLUDED_)
