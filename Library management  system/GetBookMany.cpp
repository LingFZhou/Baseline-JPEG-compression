// GetBookMany.cpp : implementation file
//

#include "stdafx.h"
#include "Library.h"
#include "Book.h"
#include "GetBookMany.h"
#include <cstring>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGetBookMany dialog


CGetBookMany::CGetBookMany(CWnd* pParent /*=NULL*/)
	: CDialog(CGetBookMany::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGetBookMany)
	m_strFileName = _T("");
	//}}AFX_DATA_INIT
}


void CGetBookMany::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGetBookMany)
	DDX_Text(pDX, IDC_FILENAME, m_strFileName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGetBookMany, CDialog)
	//{{AFX_MSG_MAP(CGetBookMany)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGetBookMany message handlers

void CGetBookMany::OnOK() 
{
	// TODO: Add extra validation here
	extern bool logIn;
	if(logIn==false)
	{
		AfxMessageBox("只有管理员才能进行此操作，请您先登入！");
	    CDialog::OnOK();
	}
	else{
	char * pszFileName;
	char * token;
	GetDlgItem(IDC_FILENAME)-> GetWindowText(m_strFileName);
	pszFileName=m_strFileName.GetBuffer(m_strFileName.GetLength());
	
	CStdioFile myFile;
    CFileException fileException;
	CString m_book[9];

	UpdateData();
	if(!m_bookSet.IsOpen())
		m_bookSet.Open();

    if(myFile.Open(pszFileName,CFile::typeText|CFile::modeRead),&fileException)
    {
		myFile.SeekToBegin();
        CString str;
		char * pstr;
		char * token;
		while(myFile.ReadString(str))
		{
			pstr=str.GetBuffer(str.GetLength());
			//AfxMessageBox(str);
			//AfxMessageBox(pstr);
			token=strtok(pstr," ");
		    m_book[0]=token;
			int i=1;
			while(token!=NULL&&i<=8)
			{
				//AfxMessageBox(token);
				token=strtok(NULL," ");
				m_book[i]=token;
				//AfxMessageBox(m_book[i]);
				i++;
			}

			m_bookSet.AddNew();
			m_bookSet.m_book_id=m_book[0];
			m_bookSet.m_book_type=m_book[1];
			m_bookSet.m_book_name=m_book[2];
			m_bookSet.m_publish_comp=m_book[3];
			m_bookSet.m_pub_year=atoi(m_book[4]);
			m_bookSet.m_author=m_book[5];
			m_bookSet.m_price=atof(m_book[6]);
			m_bookSet.m_tot_num=atoi(m_book[7]);
			m_bookSet.m_cur_num=atoi(m_book[8]);
			m_bookSet.Update();
			m_bookSet.Requery();
		}
	}
	else
		TRACE("Can't open file %s,error=%u\n",pszFileName,fileException.m_cause);
	
	myFile.Close();
	AfxMessageBox("批量入库成功！");

	CDialog::OnOK();
	}
}
