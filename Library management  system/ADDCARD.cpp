// ADDCARD.cpp : implementation file
//

#include "stdafx.h"
#include "Library.h"
#include "Borrower.h"
#include "ADDCARD.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CADDCARD dialog


CADDCARD::CADDCARD(CWnd* pParent /*=NULL*/)
	: CDialog(CADDCARD::IDD, pParent)
{
	//{{AFX_DATA_INIT(CADDCARD)
	m_cardNum = _T("");
	m_name = _T("");
	m_type = _T("");
	m_unit = _T("");
	//}}AFX_DATA_INIT
}


void CADDCARD::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CADDCARD)
	DDX_Text(pDX, IDC_CARD_NUM, m_cardNum);
	DDX_Text(pDX, IDC_NAME, m_name);
	DDX_Text(pDX, IDC_TYPE, m_type);
	DDX_Text(pDX, IDC_UNIT, m_unit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CADDCARD, CDialog)
	//{{AFX_MSG_MAP(CADDCARD)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CADDCARD message handlers

void CADDCARD::OnOK() 
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
	if(!m_cardSet.IsOpen())
		m_cardSet.Open();

	if(m_cardNum.IsEmpty())
	{
		AfxMessageBox("请输入卡号！");
		return;
	} 
	
	if(m_name.IsEmpty())
	{
		AfxMessageBox("请输入姓名！");
		return;
	} 
			
	if(m_unit.IsEmpty())
	{
		AfxMessageBox("请输入单位！");
		return;
	} 
	
	if(m_type.IsEmpty())
	{
		AfxMessageBox("请输入类别！");
		return;
	} 

	m_cardSet.m_strFilter.Format("borrower_id='%s'",m_cardNum);
	m_cardSet.Requery();
	if(m_cardSet.IsEOF())
	{
	m_cardSet.AddNew();
	m_cardSet.m_borrower_id=m_cardNum;
	m_cardSet.m_borrower_name=m_name;
	m_cardSet.m_borrower_depart=m_unit;
	m_cardSet.m_borrower_type=m_type;
	m_cardSet.Update();
	m_cardSet.Requery();
	AfxMessageBox("增加成功！");
	}
	else
		AfxMessageBox("卡号已存在，增加失败！");
	
	CDialog::OnOK();
	}
	
}
