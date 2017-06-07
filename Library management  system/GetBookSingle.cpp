// GetBookSingle.cpp : implementation file
//

#include "stdafx.h"
#include "Library.h"
#include "Book.h"
#include "GetBookSingle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGetBookSingle dialog


CGetBookSingle::CGetBookSingle(CWnd* pParent /*=NULL*/)
	: CDialog(CGetBookSingle::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGetBookSingle)
	m_strBookNum = _T("");
	m_strAuthor = _T("");
	m_strName = _T("");
	m_strPress = _T("");
	m_strType = _T("");
	m_strNumber = _T("");
	m_strPrice = _T("");
	m_strYear = _T("");
	//}}AFX_DATA_INIT
}


void CGetBookSingle::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGetBookSingle)
	DDX_Text(pDX, IDC_BOOK_NUM, m_strBookNum);
	DDX_Text(pDX, IDC_BOOK_AUTHOR, m_strAuthor);
	DDX_Text(pDX, IDC_BOOK_NAME, m_strName);
	DDX_Text(pDX, IDC_BOOK_PRESS, m_strPress);
	DDX_Text(pDX, IDC_BOOK_TYPE, m_strType);
	DDX_Text(pDX, IDC_BOOK_NUMBER, m_strNumber);
	DDX_Text(pDX, IDC_BOOK_PRICE, m_strPrice);
	DDX_Text(pDX, IDC_BOOK_YEAR, m_strYear);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGetBookSingle, CDialog)
	//{{AFX_MSG_MAP(CGetBookSingle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGetBookSingle message handlers

void CGetBookSingle::OnOK() 
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
	if(!m_bookSet.IsOpen())
		m_bookSet.Open();

	if(m_strBookNum.IsEmpty())
	{
		AfxMessageBox("请输入书号！");
		return;
	} 
	if(m_strType.IsEmpty())
	{
		AfxMessageBox("请输入类别！");
		return;
	} 
	if(m_strName.IsEmpty())
	{
		AfxMessageBox("请输入书名！");
		return;
	} 	
	if(m_strPress.IsEmpty())
	{
		AfxMessageBox("请输入出版社！");
		return;
	} 
	if(m_strYear.IsEmpty())
	{
		AfxMessageBox("请输入年份！");
		return;
	} 	
	if(m_strAuthor.IsEmpty())
	{
		AfxMessageBox("请输入作者！");
		return;
	} 
	if(m_strPrice.IsEmpty())
	{
		AfxMessageBox("请输入价格！");
		return;
	} 	
	if(m_strNumber.IsEmpty())
	{
		AfxMessageBox("请输入数量！");
		return;
	} 
	
	m_bookSet.AddNew();
	m_bookSet.m_book_id=m_strBookNum;
	m_bookSet.m_book_name=m_strName;
	m_bookSet.m_book_type=m_strType;
	m_bookSet.m_publish_comp=m_strPress;
	m_bookSet.m_pub_year=atoi(m_strYear);
	m_bookSet.m_author=m_strAuthor;
	m_bookSet.m_price=atof(m_strPrice);
	m_bookSet.m_tot_num=atoi(m_strNumber);
	m_bookSet.m_cur_num=atoi(m_strNumber);

	m_bookSet.Update();
	m_bookSet.Requery();
	
	AfxMessageBox("单本入库成功！");
	
	CDialog::OnOK();
	}
}
