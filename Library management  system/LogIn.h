#if !defined(AFX_LOGIN_H__AC4B7024_C61C_4A4B_B1FE_246BB6870259__INCLUDED_)
#define AFX_LOGIN_H__AC4B7024_C61C_4A4B_B1FE_246BB6870259__INCLUDED_

#include "Manager.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LogIn.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLogIn dialog

class CLogIn : public CDialog
{
// Construction
public:
	
	CLogIn(CWnd* pParent = NULL);   // standard constructor
	
// Dialog Data
	//{{AFX_DATA(CLogIn)
	enum { IDD = IDD_LOGIN };
	CString m_strPassword;
	CString m_strManager;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogIn)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLogIn)
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnChangeManager();
	afx_msg void OnChangePassword();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CManager m_manageset;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGIN_H__AC4B7024_C61C_4A4B_B1FE_246BB6870259__INCLUDED_)
