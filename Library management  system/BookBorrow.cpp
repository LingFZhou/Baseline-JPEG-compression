// BookBorrow.cpp : implementation file
//

#include "stdafx.h"
#include "Library.h"
#include "Book.h"
#include "Borrower.h"
#include "Record.h"
#include "BookBorrow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBookBorrow dialog


CBookBorrow::CBookBorrow(CWnd* pParent /*=NULL*/)
	: CDialog(CBookBorrow::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBookBorrow)
	m_strBookNum = _T("");
	m_strCardNum = _T("");
	//}}AFX_DATA_INIT
}


void CBookBorrow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBookBorrow)
	DDX_Text(pDX, IDC_BOOK_NUM, m_strBookNum);
	DDX_Text(pDX, IDC_CARD_NUM, m_strCardNum);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBookBorrow, CDialog)
	//{{AFX_MSG_MAP(CBookBorrow)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBookBorrow message handlers

void CBookBorrow::OnOK() 
{
	// TODO: Add extra validation here
	extern bool logIn;
	extern CString adminTrans;
	if(logIn==false)
	{
		AfxMessageBox("只有管理员才能进行此操作，请您先登入！");
	    CDialog::OnOK();
	}
	else{
	UpdateData();

	if(m_strCardNum.IsEmpty())
	{
		AfxMessageBox("请输入借书卡号！");
		return;
	} 

	if(!IsValidCard(m_strCardNum))
	{
		CDialog::OnOK();
		return;
	}

	if(m_strBookNum.IsEmpty())
	{
		AfxMessageBox("请输入藏书编号！");
		return;
	} 

	if(!AllowedToBorrow(m_strBookNum))
	{
		CDialog::OnOK();
		return;
	}
		
	if(BorrowBook(m_strCardNum,m_strBookNum))
	{
		if(!m_borrowSet.IsOpen())
		m_borrowSet.Open();

		m_borrowSet.AddNew();
		m_borrowSet.m_book_id=m_strBookNum;
		m_borrowSet.m_borrower_id=m_strCardNum;
		m_borrowSet.m_manager_id=adminTrans;
		m_borrowSet.m_borrower_time=CTime::GetCurrentTime();
		m_borrowSet.Update();
		m_borrowSet.Requery();
		AfxMessageBox("借书成功");
	}
	else
		AfxMessageBox("借书失败");

	CDialog::OnOK();
	}
}
bool CBookBorrow::IsValidCard(const CString &cardNum)
{
	if(!m_cardSet.IsOpen())
		m_cardSet.Open();

	m_cardSet.m_strFilter.Format("borrower_id='%s'",cardNum);
	m_cardSet.Requery();

	if(m_cardSet.IsEOF())
	{
		AfxMessageBox("该卡号不存在");
		return false;
	}

	return true;
}

bool CBookBorrow::AllowedToBorrow(const CString &bookNum)
{
	if(!m_bookSet.IsOpen())
		m_bookSet.Open();

	m_bookSet.m_strFilter.Format("book_id=%s",bookNum);
	m_bookSet.Requery();

	if(m_bookSet.IsEOF())
	{
		AfxMessageBox("该书不存在");
		return false;
	}

	if(m_bookSet.m_cur_num==0)
	{		
		int i,j;
		CTime borrowTime[100],min,returnTime;
		CTime time1(2012,4,30,0,0,0);
		CTime time2(2012,5,30,0,0,0);

		if(!m_borrowSet.IsOpen())
			m_borrowSet.Open();
		
		m_borrowSet.m_strFilter.Format("book_id=%s AND back_time is null",bookNum);
		m_borrowSet.Requery();

		for(i=0;!m_borrowSet.IsEOF();i++)
		{
			borrowTime[i]=m_borrowSet.m_borrower_time;
		    m_borrowSet.MoveNext();
		}
		i--;

		for(j=0,min=borrowTime[0];j<=i;j++)
		{
			if(min>borrowTime[j])
				min=borrowTime[j];
		}

		returnTime=min+(time2-time1);
		CString result=returnTime.Format("%Y-%m-%d %H:%M:%S");
		result="该书已全部借出,最近的归还时间为:"+result+"!";
		AfxMessageBox(result);
		return false;
	}

	return true;
}

bool CBookBorrow::BorrowBook(const CString &cardNum, const CString &bookNum)
{
	if(!m_bookSet.IsOpen())
		m_bookSet.Open();

	m_bookSet.m_strFilter.Format("book_id=%s",bookNum);
	m_bookSet.Requery();
	m_bookSet.Edit();
	m_bookSet.m_cur_num=m_bookSet.m_cur_num-1;
	m_bookSet.Update();
	
	return true;
}
