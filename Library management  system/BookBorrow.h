#if !defined(AFX_BOOKBORROW_H__5D4E220E_312B_4D5A_8FA7_8A4441C37C61__INCLUDED_)
#define AFX_BOOKBORROW_H__5D4E220E_312B_4D5A_8FA7_8A4441C37C61__INCLUDED_
#include "Book.h"
#include "Record.h"
#include "Borrower.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BookBorrow.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBookBorrow dialog

class CBookBorrow : public CDialog
{
// Construction
public:
	CBookBorrow(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBookBorrow)
	enum { IDD = IDD_BOOK_Borrow };
	CString	m_strBookNum;
	CString	m_strCardNum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBookBorrow)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBookBorrow)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	bool BorrowBook(const CString & cardNum,const CString & bookNum);
	bool AllowedToBorrow(const CString &bno);
	bool IsValidCard(const CString &cardNum);
	CRecord m_borrowSet;
	CBorrower m_cardSet;
	CBook m_bookSet;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BOOKBORROW_H__5D4E220E_312B_4D5A_8FA7_8A4441C37C61__INCLUDED_)
