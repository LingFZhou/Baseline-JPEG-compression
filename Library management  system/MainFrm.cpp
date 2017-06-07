// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Library.h"
#include "LogIn.h"
#include "SelectBook.h"
#include "BookBorrow.h"
#include "BookReturn.h"
#include "CardInfo.h"
#include "ADDCARD.h"
#include "DELETECARD.h"
#include "GetBookSingle.h"
#include "GetBookMany.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_LOGIN, OnLogin)
	ON_COMMAND(ID_SELECTBOOK, OnSelectbook)
	ON_COMMAND(ID_BORROWBOOK, OnBorrowbook)
	ON_COMMAND(ID_RETURNBOOK, OnReturnbook)
	ON_COMMAND(ID_INFORMATION, OnInformation)
	ON_COMMAND(ID_ADDCARD, OnAddcard)
	ON_COMMAND(ID_DELETECARD, OnDeletecard)
	ON_COMMAND(ID_GETBOOKSINGLE, OnGetbooksingle)
	ON_COMMAND(ID_GETBOOKMANY, OnGetbookmany)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnLogin() 
{
	// TODO: Add your command handler code here
	CLogIn logInDlg;
	logInDlg.DoModal();
}

void CMainFrame::OnSelectbook() 
{
	// TODO: Add your command handler code here
	CSelectBook SelectBook;
	SelectBook.DoModal();
}

void CMainFrame::OnBorrowbook() 
{
	// TODO: Add your command handler code here
	CBookBorrow bookBorrow;
	bookBorrow.DoModal();
}

void CMainFrame::OnReturnbook() 
{
	// TODO: Add your command handler code here
	CBookReturn bookReturn;
	bookReturn.DoModal();
}

void CMainFrame::OnInformation() 
{
	// TODO: Add your command handler code here
	CCardInfo CardInfo;
	CardInfo.DoModal();
}

void CMainFrame::OnAddcard() 
{
	// TODO: Add your command handler code here
	CADDCARD addcard;
	addcard.DoModal();
}

void CMainFrame::OnDeletecard() 
{
	// TODO: Add your command handler code here
	CDELETECARD deletecard;
	deletecard.DoModal();
}

void CMainFrame::OnGetbooksingle() 
{
	// TODO: Add your command handler code here
	CGetBookSingle BookSingle;
	BookSingle.DoModal();
}

void CMainFrame::OnGetbookmany() 
{
	// TODO: Add your command handler code here
	CGetBookMany getbookmany;
	getbookmany.DoModal();
}
