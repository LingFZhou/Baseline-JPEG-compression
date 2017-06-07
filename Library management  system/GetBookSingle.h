#if !defined(AFX_GETBOOKSINGLE_H__4268A990_2D22_46E2_965D_0955F53A74F0__INCLUDED_)
#define AFX_GETBOOKSINGLE_H__4268A990_2D22_46E2_965D_0955F53A74F0__INCLUDED_
#include "Book.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GetBookSingle.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGetBookSingle dialog

class CGetBookSingle : public CDialog
{
// Construction
public:
	CGetBookSingle(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGetBookSingle)
	enum { IDD = IDD_GETBOOKSINGLE };
	CString	m_strBookNum;
	CString	m_strAuthor;
	CString	m_strName;
	CString	m_strPress;
	CString	m_strType;
	CString	m_strNumber;
	CString	m_strPrice;
	CString	m_strYear;
	
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGetBookSingle)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGetBookSingle)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CBook m_bookSet;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GETBOOKSINGLE_H__4268A990_2D22_46E2_965D_0955F53A74F0__INCLUDED_)
