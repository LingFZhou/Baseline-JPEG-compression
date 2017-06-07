#if !defined(AFX_GETBOOKMANY_H__81876930_8463_49F9_B86D_20625BB7E0B1__INCLUDED_)
#define AFX_GETBOOKMANY_H__81876930_8463_49F9_B86D_20625BB7E0B1__INCLUDED_
#include "Book.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GetBookMany.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGetBookMany dialog

class CGetBookMany : public CDialog
{
// Construction
public:
	CGetBookMany(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGetBookMany)
	enum { IDD = IDD_GETBOOKMANY };
	CString	m_strFileName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGetBookMany)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGetBookMany)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CBook m_bookSet;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GETBOOKMANY_H__81876930_8463_49F9_B86D_20625BB7E0B1__INCLUDED_)
