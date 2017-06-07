#if !defined(AFX_BOOKRETURN_H__1003054E_8561_4958_99CF_1BC8A14F0898__INCLUDED_)
#define AFX_BOOKRETURN_H__1003054E_8561_4958_99CF_1BC8A14F0898__INCLUDED_

#include "Book.h"
#include "Record.h"
#include "Borrower.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BookReturn.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBookReturn dialog

class CBookReturn : public CDialog
{
// Construction
public:
	CBookReturn(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBookReturn)
	enum { IDD = IDD_BOOK_RETURN };
	CString	m_strBookNum;
	CString	m_strCardNum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBookReturn)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
private:
	CBorrower m_cardSet;
	CBook m_bookSet;
	CRecord m_borrowSet;

	// Generated message map functions
	//{{AFX_MSG(CBookReturn)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BOOKRETURN_H__1003054E_8561_4958_99CF_1BC8A14F0898__INCLUDED_)
