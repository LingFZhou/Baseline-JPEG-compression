; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Library.h"
LastPage=0

ClassCount=18
Class1=CLibraryApp
Class2=CLibraryDoc
Class3=CLibraryView
Class4=CMainFrame

ResourceCount=11
Resource1=IDD_BOOK_Borrow
Class5=CAboutDlg
Class6=CManager
Class7=CBook
Class8=CBorrower
Class9=CRecord
Resource2=IDD_DELETECARD
Class10=CLogIn
Resource3=IDD_ADDCARD
Class11=CSelectBook
Resource4=IDD_BOOK_RETURN
Class12=CBookBorrow
Resource5=IDD_LOGIN
Class13=CBookReturn
Resource6=IDD_ABOUTBOX
Class14=CCardInfo
Resource7=IDD_CARDINFO
Class15=CADDCARD
Resource8=IDD_SELECTBOOK
Class16=CDELETECARD
Resource9=IDR_MAINFRAME
Class17=CGetBookSingle
Resource10=IDD_GETBOOKSINGLE
Class18=CGetBookMany
Resource11=IDD_GETBOOKMANY

[CLS:CLibraryApp]
Type=0
HeaderFile=Library.h
ImplementationFile=Library.cpp
Filter=N

[CLS:CLibraryDoc]
Type=0
HeaderFile=LibraryDoc.h
ImplementationFile=LibraryDoc.cpp
Filter=N

[CLS:CLibraryView]
Type=0
HeaderFile=LibraryView.h
ImplementationFile=LibraryView.cpp
Filter=C


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_GETBOOKMANY
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=Library.cpp
ImplementationFile=Library.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_LOGIN
Command2=ID_GETBOOKSINGLE
Command3=ID_GETBOOKMANY
Command4=ID_SELECTBOOK
Command5=ID_BORROWBOOK
Command6=ID_RETURNBOOK
Command7=ID_INFORMATION
Command8=ID_ADDCARD
Command9=ID_DELETECARD
CommandCount=9

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[CLS:CManager]
Type=0
HeaderFile=Manager.h
ImplementationFile=Manager.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r

[DB:CManager]
DB=1
DBType=ODBC
ColumnCount=4
Column1=[manager_id], 1, 15
Column2=[manager_name], 1, 15
Column3=[psw], 1, 15
Column4=[phone_number], 1, 15

[CLS:CBook]
Type=0
HeaderFile=Book.h
ImplementationFile=Book.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r

[DB:CBook]
DB=1
DBType=ODBC
ColumnCount=9
Column1=[book_id], 1, 15
Column2=[book_type], 1, 15
Column3=[book_name], 1, 15
Column4=[publish_comp], 1, 15
Column5=[pub_year], 4, 4
Column6=[author], 1, 15
Column7=[pirce], 6, 8
Column8=[tot_num], 4, 4
Column9=[cur_num], 4, 4

[CLS:CBorrower]
Type=0
HeaderFile=Borrower.h
ImplementationFile=Borrower.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r

[DB:CBorrower]
DB=1
DBType=ODBC
ColumnCount=4
Column1=[borrower_id], 1, 15
Column2=[borrower_name], 1, 15
Column3=[borrower_depart], 1, 15
Column4=[borrower_type], 1, 15

[CLS:CRecord]
Type=0
HeaderFile=Record.h
ImplementationFile=Record.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r

[DB:CRecord]
DB=1
DBType=ODBC
ColumnCount=5
Column1=[manager_id], 1, 15
Column2=[borrower_id], 1, 15
Column3=[book_id], 1, 15
Column4=[borrower_time], 11, 16
Column5=[back_time], 11, 16

[DLG:IDD_LOGIN]
Type=1
Class=CLogIn
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_MANAGER,edit,1350631552
Control6=IDC_PASSWORD,edit,1350631552

[CLS:CLogIn]
Type=0
HeaderFile=LogIn.h
ImplementationFile=LogIn.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_PASSWORD

[CLS:CSelectBook]
Type=0
HeaderFile=SelectBook.h
ImplementationFile=SelectBook.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CSelectBook

[DLG:IDD_SELECTBOOK]
Type=1
Class=CSelectBook
ControlCount=26
Control1=IDC_BUTTON1,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_KEY_WORD1,edit,1350631552
Control10=IDC_KEY_WORD3,edit,1350631552
Control11=IDC_KEY_WORD2,edit,1350631552
Control12=IDC_KEY_WORD4,edit,1350631552
Control13=IDC_KEY_YEAR1,edit,1350631552
Control14=IDC_KEY_YEAR2,edit,1350631552
Control15=IDC_STATIC,static,1342308352
Control16=IDC_KEY_PRICE1,edit,1350631552
Control17=IDC_KEY_PRICE2,edit,1350631552
Control18=IDC_STATIC,static,1342308352
Control19=IDC_LIST1_RESULT2,listbox,1352728835
Control20=IDC_AND_OR2,combobox,1344340226
Control21=IDC_AND_OR1,combobox,1344340226
Control22=IDC_AND_OR3,combobox,1344340226
Control23=IDC_AND_OR4,combobox,1344340226
Control24=IDC_AND_OR5,combobox,1344340226
Control25=IDC_AND_OR6,combobox,1344340226
Control26=IDC_LIST_DETAIL2,listbox,1352728835

[DLG:IDD_BOOK_Borrow]
Type=1
Class=CBookBorrow
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_CARD_NUM,edit,1350631552
Control6=IDC_BOOK_NUM,edit,1350631552

[CLS:CBookBorrow]
Type=0
HeaderFile=BookBorrow.h
ImplementationFile=BookBorrow.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_BOOK_NUM

[DLG:IDD_BOOK_RETURN]
Type=1
Class=CBookReturn
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_CARD_NUM,edit,1350631552
Control6=IDC_BOOK_NUM,edit,1350631552

[CLS:CBookReturn]
Type=0
HeaderFile=BookReturn.h
ImplementationFile=BookReturn.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

[DLG:IDD_CARDINFO]
Type=1
Class=CCardInfo
ControlCount=6
Control1=IDC_BUTTON,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_KEY_WORD,edit,1350631552
Control5=IDC_LIST_RESULT,listbox,1352728835
Control6=IDC_LIST_DETAIL,listbox,1352728835

[CLS:CCardInfo]
Type=0
HeaderFile=CardInfo.h
ImplementationFile=CardInfo.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CCardInfo

[DLG:IDD_ADDCARD]
Type=1
Class=CADDCARD
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_CARD_NUM,edit,1350631552
Control8=IDC_UNIT,edit,1350631552
Control9=IDC_NAME,edit,1350631552
Control10=IDC_TYPE,edit,1350631552

[CLS:CADDCARD]
Type=0
HeaderFile=ADDCARD.h
ImplementationFile=ADDCARD.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

[DLG:IDD_DELETECARD]
Type=1
Class=CDELETECARD
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_CARD_NUM,edit,1350631552

[CLS:CDELETECARD]
Type=0
HeaderFile=DELETECARD.h
ImplementationFile=DELETECARD.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

[DLG:IDD_GETBOOKSINGLE]
Type=1
Class=CGetBookSingle
ControlCount=18
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_BOOK_NUM,edit,1350631552
Control12=IDC_BOOK_YEAR,edit,1350631552
Control13=IDC_BOOK_NAME,edit,1350631552
Control14=IDC_BOOK_PRICE,edit,1350631552
Control15=IDC_BOOK_TYPE,edit,1350631552
Control16=IDC_BOOK_PRESS,edit,1350631552
Control17=IDC_BOOK_AUTHOR,edit,1350631552
Control18=IDC_BOOK_NUMBER,edit,1350631552

[CLS:CGetBookSingle]
Type=0
HeaderFile=GetBookSingle.h
ImplementationFile=GetBookSingle.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

[DLG:IDD_GETBOOKMANY]
Type=1
Class=CGetBookMany
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_FILENAME,edit,1350631552

[CLS:CGetBookMany]
Type=0
HeaderFile=GetBookMany.h
ImplementationFile=GetBookMany.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

