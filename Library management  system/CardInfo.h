#if !defined(AFX_CARDINFO_H__CA9BCC35_5144_46F8_ACD3_C77A714A8B27__INCLUDED_)
#define AFX_CARDINFO_H__CA9BCC35_5144_46F8_ACD3_C77A714A8B27__INCLUDED_

#include "Record.h"
#include "Book.h"
#include "Borrower.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CardInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCardInfo dialog

class CCardInfo : public CDialog
{
// Construction
public:
	CCardInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCardInfo)
	enum { IDD = IDD_CARDINFO };
	CListBox	m_listDetail;
	CListBox	m_listResult;
	CString	m_keyword;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCardInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCardInfo)
	afx_msg void OnSelchangeListResult();
	afx_msg void OnButton();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CBook m_bookSet;
	CRecord m_borrowSet;
	CBorrower m_cardSet;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CARDINFO_H__CA9BCC35_5144_46F8_ACD3_C77A714A8B27__INCLUDED_)
