#if !defined(AFX_BOOK_H__F0A0EE32_03FB_4ABA_B9B7_B49149E7343D__INCLUDED_)
#define AFX_BOOK_H__F0A0EE32_03FB_4ABA_B9B7_B49149E7343D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Book.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBook recordset

class CBook : public CRecordset
{
public:
	CBook(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CBook)

// Field/Param Data
	//{{AFX_FIELD(CBook, CRecordset)
	CString	m_book_id;
	CString	m_book_type;
	CString	m_book_name;
	CString	m_publish_comp;
	long	m_pub_year;
	CString	m_author;
	double	m_price;
	long	m_tot_num;
	long	m_cur_num;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBook)
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

#endif // !defined(AFX_BOOK_H__F0A0EE32_03FB_4ABA_B9B7_B49149E7343D__INCLUDED_)
