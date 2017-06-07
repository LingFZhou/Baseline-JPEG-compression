// DELETECARD.cpp : implementation file
//

#include "stdafx.h"
#include "Library.h"
#include "DELETECARD.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDELETECARD dialog


CDELETECARD::CDELETECARD(CWnd* pParent /*=NULL*/)
	: CDialog(CDELETECARD::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDELETECARD)
	m_cardNum = _T("");
	//}}AFX_DATA_INIT
}


void CDELETECARD::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDELETECARD)
	DDX_Text(pDX, IDC_CARD_NUM, m_cardNum);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDELETECARD, CDialog)
	//{{AFX_MSG_MAP(CDELETECARD)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDELETECARD message handlers

void CDELETECARD::OnOK() 
{
	// TODO: Add extra validation here
	extern bool logIn;
	if(logIn==false)
	{
		AfxMessageBox("ֻ�й���Ա���ܽ��д˲����������ȵ��룡");
	    CDialog::OnOK();
	}
	else{
	UpdateData();	
	if(!m_cardSet.IsOpen())
		m_cardSet.Open();
	
	if(m_cardNum.IsEmpty())
	{
		AfxMessageBox("��������鿨�ţ�");
		return;
	} 

	m_cardSet.m_strFilter.Format("borrower_id='%s'",m_cardNum);
	m_cardSet.Requery();
	if(!m_cardSet.IsEOF())
	{
		m_cardSet.m_strFilter.Format("borrower_id='%s'",m_cardNum);
		m_cardSet.Delete();
		m_cardSet.Requery();
		AfxMessageBox("ɾ���ɹ���");
	}
	else
		AfxMessageBox("���Ų����ڣ�ɾ��ʧ�ܣ�");

	CDialog::OnOK();
	}
}
