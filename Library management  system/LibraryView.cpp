// LibraryView.cpp : implementation of the CLibraryView class
//

#include "stdafx.h"
#include "Library.h"

#include "LibraryDoc.h"
#include "LibraryView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLibraryView

IMPLEMENT_DYNCREATE(CLibraryView, CView)

BEGIN_MESSAGE_MAP(CLibraryView, CView)
	//{{AFX_MSG_MAP(CLibraryView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLibraryView construction/destruction

CLibraryView::CLibraryView()
{
	// TODO: add construction code here

}

CLibraryView::~CLibraryView()
{
}

BOOL CLibraryView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLibraryView drawing

void CLibraryView::OnDraw(CDC* pDC)
{
	CLibraryDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CLibraryView diagnostics
#ifdef _DEBUG
void CLibraryView::AssertValid() const
{
	CView::AssertValid();
}

void CLibraryView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLibraryDoc* CLibraryView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLibraryDoc)));
	return (CLibraryDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLibraryView message handlers
