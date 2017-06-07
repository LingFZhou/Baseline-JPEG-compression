// BookReturn.cpp : implementation file
//

#include "stdafx.h"
#include "Library.h"
#include "Book.h"
#include "Borrower.h"
#include "Record.h"
#include "BookReturn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBookReturn dialog


CBookReturn::CBookReturn(CWnd* pParent /*=NULL*/)
	: CDialog(CBookReturn::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBookReturn)
	m_strBookNum = _T("");
	m_strCardNum = _T("");
	//}}AFX_DATA_INIT
}


void CBookReturn::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBookReturn)
	DDX_Text(pDX, IDC_BOOK_NUM, m_strBookNum);
	DDX_Text(pDX, IDC_CARD_NUM, m_strCardNum);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBookReturn, CDialog)
	//{{AFX_MSG_MAP(CBookReturn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBookReturn message handlers

void CBookReturn::OnOK() 
{
	// TODO: Add extra validation here
	extern bool logIn;
	if(logIn==false)
	{
		AfxMessageBox("只有管理员才能进行此操作，请您先登入！");
	    CDialog::OnOK();
	}
	else{
	UpdateData();
	if(!m_borrowSet.IsOpen())
		m_borrowSet.Open();
	if(!m_bookSet.IsOpen())
		m_bookSet.Open();

	if(m_strCardNum.IsEmpty())
	{
		AfxMessageBox("请输入借书卡号！");
		return;
	} 

	if(m_strBookNum.IsEmpty())
	{
		AfxMessageBox("请输入藏书编号！");
		return;
	} 

	m_borrowSet.m_strFilter.Format("book_id='%s' and borrower_id='%s' and back_time is null ",m_strBookNum,m_strCardNum);
	m_borrowSet.Requery();

	if(m_borrowSet.IsEOF())
	{
		AfxMessageBox("此书不存在或已经还掉！");
		CDialog::OnOK();
		return;
	}

	m_borrowSet.Edit();
	m_bookSet.Edit();
	m_borrowSet.m_back_time=CTime::GetCurrentTime();
	m_bookSet.m_cur_num=m_bookSet.m_cur_num+1;
	m_borrowSet.Update();
	m_bookSet.Update();
	AfxMessageBox("还书成功！");

	CDialog::OnOK();
	}
}
