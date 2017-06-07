// SelectBook.cpp : implementation file
//

#include "stdafx.h"
#include "Library.h"
#include "Book.h"
#include "SelectBook.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectBook dialog


CSelectBook::CSelectBook(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectBook::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelectBook)
	m_andOr1 = _T("");
	m_andOr2 = _T("");
	m_andOr3 = _T("");
	m_andOr4 = _T("");
	m_andOr5 = _T("");
	m_andOr6 = _T("");
	m_price1 = _T("");
	m_price2 = _T("");
	m_keyword1 = _T("");
	m_keyword2 = _T("");
	m_keyword3 = _T("");
	m_keyword4 = _T("");
	m_year1 = _T("");
	m_year2 = _T("");
	//}}AFX_DATA_INIT
}


void CSelectBook::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectBook)
	DDX_Control(pDX, IDC_LIST1_RESULT2, m_listResult);
	DDX_Control(pDX, IDC_LIST_DETAIL2, m_listDetail);
	DDX_CBString(pDX, IDC_AND_OR1, m_andOr1);
	DDX_CBString(pDX, IDC_AND_OR2, m_andOr2);
	DDX_CBString(pDX, IDC_AND_OR3, m_andOr3);
	DDX_CBString(pDX, IDC_AND_OR4, m_andOr4);
	DDX_CBString(pDX, IDC_AND_OR5, m_andOr5);
	DDX_CBString(pDX, IDC_AND_OR6, m_andOr6);
	DDX_Text(pDX, IDC_KEY_PRICE1, m_price1);
	DDX_Text(pDX, IDC_KEY_PRICE2, m_price2);
	DDX_Text(pDX, IDC_KEY_WORD1, m_keyword1);
	DDX_Text(pDX, IDC_KEY_WORD2, m_keyword2);
	DDX_Text(pDX, IDC_KEY_WORD3, m_keyword3);
	DDX_Text(pDX, IDC_KEY_WORD4, m_keyword4);
	DDX_Text(pDX, IDC_KEY_YEAR1, m_year1);
	DDX_Text(pDX, IDC_KEY_YEAR2, m_year2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectBook, CDialog)
	//{{AFX_MSG_MAP(CSelectBook)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_LBN_SELCHANGE(IDC_LIST1_RESULT2, OnSelchangeList1Result2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectBook message handlers

void CSelectBook::OnButton1() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	m_listResult.ResetContent();
	m_listDetail.ResetContent();
	if(!m_bookSet.IsOpen())
		m_bookSet.Open();

	CString str;
	CString strFilter;
	CString astrColumnCaption[7];

	astrColumnCaption[1]="book_type";
	astrColumnCaption[2]="book_name";
	astrColumnCaption[3]="publish_comp";
	astrColumnCaption[4]="author";
	astrColumnCaption[5]="pub_year";
	astrColumnCaption[6]="price";
	

	if(!m_keyword1.IsEmpty())
	{
		str.Format("%s='%s'",astrColumnCaption[1],m_keyword1);
		strFilter+=str;
		if( !m_keyword2.IsEmpty()||!m_keyword3.IsEmpty()||!m_keyword4.IsEmpty()||(!m_price1.IsEmpty()&&!m_price2.IsEmpty())||(!m_year1.IsEmpty()&&!m_year2.IsEmpty()))
		{
			strFilter+=" ";
			strFilter+=m_andOr1;
			strFilter+=" ";
		}
	}
	
	if(!m_keyword2.IsEmpty())
	{
		str.Format("%s like '%%%s\%%'",astrColumnCaption[2],m_keyword2);
		strFilter+=str;
		if( !m_keyword3.IsEmpty()||!m_keyword4.IsEmpty()||(!m_price1.IsEmpty()&&!m_price2.IsEmpty())||(!m_year1.IsEmpty()&&!m_year2.IsEmpty()))
		{
			strFilter+=" ";
			strFilter+=m_andOr2;
			strFilter+=" ";
		}
	}

	if(!m_keyword3.IsEmpty())
	{
		str.Format("%s='%s'",astrColumnCaption[3],m_keyword3);
		strFilter+=str;
		if( !m_keyword4.IsEmpty()||(!m_price1.IsEmpty()&&!m_price2.IsEmpty())||(!m_year1.IsEmpty()&&!m_year2.IsEmpty()))
		{
			strFilter+=" ";
			strFilter+=m_andOr3;
			strFilter+=" ";
		}
	}

	if(!m_keyword4.IsEmpty())
	{
		str.Format("%s='%s'",astrColumnCaption[4],m_keyword4);
		strFilter+=str;
		if((!m_price1.IsEmpty()&&!m_price2.IsEmpty())||(!m_year1.IsEmpty()&&!m_year2.IsEmpty()))
		{
			strFilter+=" ";
			strFilter+=m_andOr4;
			strFilter+=" ";
		}
	}

	if(!m_year1.IsEmpty()&&!m_year2.IsEmpty())
	{
		str.Format("%s between %s and %s",astrColumnCaption[5],m_year1,m_year2);
		strFilter+=str;
		if(!m_price1.IsEmpty()&&!m_price2.IsEmpty())
		{
			strFilter+=" ";
			strFilter+=m_andOr5;
			strFilter+=" ";
		}
	}

	if(!m_price1.IsEmpty()&&!m_price2.IsEmpty())
	{
		str.Format("%s between %s and %s",astrColumnCaption[6],m_price1,m_price2);
		strFilter+=str;
	}

	m_bookSet.m_strFilter=strFilter;
	m_bookSet.Requery();

	if(m_bookSet.IsEOF())
	{
		AfxMessageBox("查无此书");
		return;
	}

	while(!m_bookSet.IsEOF())
	{
		m_listResult.AddString(m_bookSet.m_book_name);
		m_bookSet.MoveNext();
	}
}

void CSelectBook::OnSelchangeList1Result2() 
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

	m_bookSet.m_strFilter.Format("book_name='%s'",m_list_text);
	m_bookSet.Requery();

	str[0]=m_bookSet.m_book_id;
	str[1]=m_bookSet.m_book_type;
	str[2]=m_bookSet.m_book_name;
	str[3]=m_bookSet.m_publish_comp;
	str[4].Format(_T("%ld"),m_bookSet.m_pub_year);
	str[5]=m_bookSet.m_author;
	str[6].Format("%f",m_bookSet.m_price);
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

