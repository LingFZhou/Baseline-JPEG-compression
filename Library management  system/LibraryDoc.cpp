// LibraryDoc.cpp : implementation of the CLibraryDoc class
//

#include "stdafx.h"
#include "Library.h"

#include "LibraryDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLibraryDoc

IMPLEMENT_DYNCREATE(CLibraryDoc, CDocument)

BEGIN_MESSAGE_MAP(CLibraryDoc, CDocument)
	//{{AFX_MSG_MAP(CLibraryDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLibraryDoc construction/destruction

CLibraryDoc::CLibraryDoc()
{
	// TODO: add one-time construction code here

}

CLibraryDoc::~CLibraryDoc()
{
}

BOOL CLibraryDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CLibraryDoc serialization

void CLibraryDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CLibraryDoc diagnostics

#ifdef _DEBUG
void CLibraryDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLibraryDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLibraryDoc commands
