#if !defined(AFX_SELECTBOOK_H__287B6322_403B_4823_8021_6FF024989D87__INCLUDED_)
#define AFX_SELECTBOOK_H__287B6322_403B_4823_8021_6FF024989D87__INCLUDED_
#include "Book.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectBook.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelectBook dialog

class CSelectBook : public CDialog
{
// Construction
public:
	CListBox m_listResult;
	CListBox m_listDetail;
	CSelectBook(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSelectBook)
	enum { IDD = IDD_SELECTBOOK };
	CString	m_andOr1;
	CString	m_andOr2;
	CString	m_andOr3;
	CString	m_andOr4;
	CString	m_andOr5;
	CString	m_andOr6;
	CString	m_price1;
	CString	m_price2;
	CString	m_keyword1;
	CString	m_keyword2;
	CString	m_keyword3;
	CString	m_keyword4;
	CString	m_year1;
	CString	m_year2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectBook)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelectBook)
	afx_msg void OnButton1();
	afx_msg void OnSelchangeList1Result2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CBook m_bookSet;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTBOOK_H__287B6322_403B_4823_8021_6FF024989D87__INCLUDED_)
