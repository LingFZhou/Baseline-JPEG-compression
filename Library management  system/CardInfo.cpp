// CardInfo.cpp : implementation file
//

#include "stdafx.h"
#include "Library.h"
#include "Book.h"
#include "Borrower.h"
#include "Record.h"
#include "CardInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCardInfo dialog


CCardInfo::CCardInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CCardInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCardInfo)
	m_keyword = _T("");
	//}}AFX_DATA_INIT
}


void CCardInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCardInfo)
	DDX_Control(pDX, IDC_LIST_DETAIL, m_listDetail);
	DDX_Control(pDX, IDC_LIST_RESULT, m_listResult);
	DDX_Text(pDX, IDC_KEY_WORD, m_keyword);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCardInfo, CDialog)
	//{{AFX_MSG_MAP(CCardInfo)
	ON_LBN_SELCHANGE(IDC_LIST_RESULT, OnSelchangeListResult)
	ON_BN_CLICKED(IDC_BUTTON, OnButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCardInfo message handlers

void CCardInfo::OnButton() 
{
	// TODO: Add your control notification handler code here
	extern bool logIn;
	if(logIn==false)
	{
		AfxMessageBox("只有管理员才能进行此操作，请您先登入！");
	    CDialog::OnOK();
	}
	else{	
	m_listResult.ResetContent();
	UpdateData();
	CString strDetail;
	if(!m_borrowSet.IsOpen())
		m_borrowSet.Open();
	if(!m_cardSet.IsOpen())
		m_cardSet.Open();
	if(!m_bookSet.IsOpen())
		m_bookSet.Open();
	
	if(m_keyword.IsEmpty())
	{
		AfxMessageBox("请输入借书卡号！");
		return;
	} 

	m_borrowSet.m_strFilter.Format("borrower_id='%s'",m_keyword);
	m_borrowSet.Requery();
	if(m_borrowSet.IsEOF())
	{
		AfxMessageBox("该卡号不存在或未借过书！");
		return;
	}

	while(!m_borrowSet.IsEOF())
	{
		m_listResult.AddString(m_borrowSet.m_book_id);
		m_borrowSet.MoveNext();
	}
	}
}

void CCardInfo::OnSelchangeListResult() 
{
	// TODO: Add your control notification handler code here
	CString m_list_text;
	m_listResult.GetText(m_listResult.GetCurSel(),m_list_text);

	CString aColCaption[9];
	aColCaption[0]="书号：         ";
	aColCaption[1]="类别：         ";
	aColCaption[2]="书名：         ";
	aColCaption[3]="出版社：     ";
	aColCaption[4]="年份：         ";
	aColCaption[5]="作者：         ";
	aColCaption[6]="价格：         ";
	aColCaption[7]="总藏书量： ";
	aColCaption[8]="库存：         ";

	CString str[9];

	if(!m_bookSet.IsOpen())
		m_bookSet.Open();

	m_bookSet.m_strFilter.Format("book_id='%s'",m_list_text);
	m_bookSet.Requery();

	str[0]=m_bookSet.m_book_id;
	str[1]=m_bookSet.m_book_type;
	str[2]=m_bookSet.m_book_name;
	str[3]=m_bookSet.m_publish_comp;
	str[4].Format(_T("%ld"),m_bookSet.m_pub_year);
	str[5]=m_bookSet.m_author;
	str[6].Format("%s",m_bookSet.m_price);
	str[7].Format(_T("%ld"),m_bookSet.m_tot_num);
	str[8].Format(_T("%ld"),m_bookSet.m_cur_num);
	
	m_listDetail.ResetContent();

	CString strLine;

	for(int i=0;i<9;i++)
	{
		strLine.Empty();
		strLine+=aColCaption[i];
		strLine+=str[i];
		m_listDetail.AddString(strLine);
	}

}


