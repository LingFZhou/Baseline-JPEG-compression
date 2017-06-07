// LogIn.cpp : implementation file
//

#include "stdafx.h"
#include "Library.h"
#include "Manager.h"
#include "LogIn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLogIn dialog


CLogIn::CLogIn(CWnd* pParent /*=NULL*/)
	: CDialog(CLogIn::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLogIn)
	m_strManager = _T("");
	m_strPassword = _T("");
	//}}AFX_DATA_INIT
}


void CLogIn::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLogIn)
	DDX_Text(pDX, IDC_MANAGER, m_strManager);
	DDX_Text(pDX, IDC_PASSWORD, m_strPassword);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLogIn, CDialog)
	//{{AFX_MSG_MAP(CLogIn)
	ON_EN_CHANGE(IDC_MANAGER, OnChangeManager)
	ON_EN_CHANGE(IDC_PASSWORD, OnChangePassword)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogIn message handlers



void CLogIn::OnOK() 
{
	// TODO: Add extra validation here
	extern bool logIn;
	extern CString adminTrans;
	logIn=false;
	UpdateData();
	if (!m_manageset.IsOpen())
		m_manageset.Open();

	m_manageset.m_strFilter.Format("manager_id='%s' and psw='%s'",m_strManager,m_strPassword);
	m_manageset.Requery();

	if (logIn==false)
	{
		if (m_manageset.IsEOF())
		{
			AfxMessageBox("密码错误，请重新输入");
			return;
		}
        logIn=true;
		adminTrans=m_strManager;
    	AfxMessageBox("登陆成功，欢迎来到图书管理系统!");
    	CDialog::OnOK();
     	return;
	}
    else
	{
	    AfxMessageBox("您已登录，请勿重复登录!");
        CDialog::OnOK();
        return;
	}
	CDialog::OnOK();
}
void CLogIn::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
void CLogIn::OnChangeManager() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CLogIn::OnChangePassword() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}
