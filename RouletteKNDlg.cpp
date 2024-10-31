
// RouletteKNDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "RouletteKN.h"
#include "RouletteKNDlg.h"
#include "afxdialogex.h"
#include <random>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CRouletteKNDlg dialog



CRouletteKNDlg::CRouletteKNDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ROULETTEKN_DIALOG, pParent)
	, Display(_T("Awaiting bet..."))
	, res()
	, CurrBet(0)
	//, uBal(20.00)
	, payout(0.00)
	, GameOn(false)
	, UserWin(false)
	, custombet(0)
	, rino(even)
	, codeUsed(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRouletteKNDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_1, r1);
	DDX_Control(pDX, IDC_10, r10);
	DDX_Control(pDX, IDC_11, r11);
	DDX_Control(pDX, IDC_12, r12);
	DDX_Control(pDX, IDC_13, r13);
	DDX_Control(pDX, IDC_14, r14);
	DDX_Control(pDX, IDC_15, r15);
	DDX_Control(pDX, IDC_16, r16);
	DDX_Control(pDX, IDC_17, r17);
	DDX_Control(pDX, IDC_18, r18);
	DDX_Control(pDX, IDC_2, r2);
	DDX_Control(pDX, IDC_3, r3);
	DDX_Control(pDX, IDC_4, r4);
	DDX_Control(pDX, IDC_5, r5);
	DDX_Control(pDX, IDC_6, r6);
	DDX_Control(pDX, IDC_7, r7);
	DDX_Control(pDX, IDC_8, r8);
	DDX_Control(pDX, IDC_9, r9);
	DDX_Control(pDX, IDC_0, r0);
	DDX_Control(pDX, IDC_WORL, WinOrLose);
	DDX_Control(pDX, IDC_RESULT, res);
	DDX_Control(pDX, IDC_BETB, betB);
	DDX_Text(pDX, IDC_CB, CurrBet);
	DDX_Text(pDX, IDC_BALa2, uBal);
	DDX_Control(pDX, IDC_ZERO, BetOn0);
	DDX_Control(pDX, IDC_INSERT, Custom);
	DDX_Text(pDX, IDC_DISPLAY, Display);
	DDX_Control(pDX, IDC_TABLE, tableview);
}

BEGIN_MESSAGE_MAP(CRouletteKNDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BETB, &CRouletteKNDlg::OnBnClickedBetb)
	ON_BN_CLICKED(IDC_ZERO, &CRouletteKNDlg::OnBnClickedZero)
	ON_BN_CLICKED(IDC_1ST6, &CRouletteKNDlg::OnBnClicked1st6)
	ON_BN_CLICKED(IDC_MIDDLEROW, &CRouletteKNDlg::OnBnClickedMiddlerow)
	ON_BN_CLICKED(IDC_2ND6, &CRouletteKNDlg::OnBnClicked2nd6)
	ON_BN_CLICKED(IDC_BOTTOMROW, &CRouletteKNDlg::OnBnClickedBottomrow)
	ON_BN_CLICKED(IDC_1to9, &CRouletteKNDlg::OnBnClicked1to9)
	ON_BN_CLICKED(IDC_TOPROW, &CRouletteKNDlg::OnBnClickedToprow)
	ON_BN_CLICKED(IDC_CUSTO, &CRouletteKNDlg::OnBnClickedCustom)
	ON_BN_CLICKED(IDC_10to18, &CRouletteKNDlg::OnBnClicked10to18)
	ON_BN_CLICKED(IDC_EVEN, &CRouletteKNDlg::OnBnClickedEven)
	ON_BN_CLICKED(IDC_RED, &CRouletteKNDlg::OnBnClickedRed)
	ON_BN_CLICKED(IDC_BLACK, &CRouletteKNDlg::OnBnClickedBlack)
	ON_BN_CLICKED(IDC_ODD, &CRouletteKNDlg::OnBnClickedOdd)
	ON_BN_CLICKED(IDC_3RD6, &CRouletteKNDlg::OnBnClicked3rd6)
	ON_BN_CLICKED(IDC_50c, &CRouletteKNDlg::OnBnClicked50c)
	ON_BN_CLICKED(IDC_1d, &CRouletteKNDlg::OnBnClicked1d)
	ON_BN_CLICKED(IDC_5d, &CRouletteKNDlg::OnBnClicked5d)
	ON_BN_CLICKED(IDC_10d, &CRouletteKNDlg::OnBnClicked10d)
END_MESSAGE_MAP()


// CRouletteKNDlg message handlers

BOOL CRouletteKNDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	HBITMAP startBitmap = (HBITMAP)LoadImage(NULL, L"BMP\\potholderz.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetDlgItem(IDC_BALa2)->ModifyStyle(0, WS_DISABLED);
	GetDlgItem(IDC_DISPLAY)->ModifyStyle(0, WS_DISABLED);
	NumInit();
	/*
	CBitmap Tablespoon;
	int width = 30;
	int height = 30;
	CStatic* pMyPicture = (CStatic*)GetDlgItem(IDC_TABLE);
	pMyPicture->SetWindowPos(NULL, 0, 0, width, height, SWP_NOZORDER | SWP_NOMOVE); //Don't reorder control layering
	Tablespoon.LoadBitmap(IDB_BITMAP1);
	pMyPicture->SetBitmap(Tablespoon);
	*/
	/*
	HBITMAP hBitmap;
	hBitmap = LoadBitmap(;

	BITMAP BMP;
	GetObject(hBitmap, sizeof(BMP), &BMP); // Here we get the BMP header info.

	HDC BMPDC = CreateCompatibleDC(NULL); // This will hold the BMP image itself.

	HDC hDC = GetDC(hWnd);
	SelectObject(BMPDC, hBitmap); // Put the image into the DC.

	BitBlt(hDC, X, y, BMP.bmWidth, BMP.bmHeight, BMPDC, 0, 0, SRCCOPY); // Finally, Draw it 
	
	*/
	
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRouletteKNDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRouletteKNDlg::NumInit() {
	//lengthy
	{
		r0.SetWindowTextW(_T("0"));
		GetDlgItem(IDC_0)->ModifyStyle(0, WS_DISABLED);
		r1.SetWindowTextW(_T("\"3\""));
		GetDlgItem(IDC_1)->ModifyStyle(0, WS_DISABLED);
		r2.SetWindowTextW(_T("6"));
		GetDlgItem(IDC_2)->ModifyStyle(0, WS_DISABLED);
		r3.SetWindowTextW(_T("\"9\""));
		GetDlgItem(IDC_3)->ModifyStyle(0, WS_DISABLED);
		r4.SetWindowTextW(_T("\"12\""));
		GetDlgItem(IDC_4)->ModifyStyle(0, WS_DISABLED);
	}
	{r5.SetWindowTextW(_T("15"));
	GetDlgItem(IDC_5)->ModifyStyle(0, WS_DISABLED);
	r6.SetWindowTextW(_T("\"18\""));
	GetDlgItem(IDC_6)->ModifyStyle(0, WS_DISABLED);
	r7.SetWindowTextW(_T("2"));
	GetDlgItem(IDC_7)->ModifyStyle(0, WS_DISABLED);
	r8.SetWindowTextW(_T("\"5\""));
	GetDlgItem(IDC_8)->ModifyStyle(0, WS_DISABLED);
	}
	{
	r9.SetWindowTextW(_T("8"));
	GetDlgItem(IDC_9)->ModifyStyle(0, WS_DISABLED);
	r10.SetWindowTextW(_T("11"));
	GetDlgItem(IDC_10)->ModifyStyle(0, WS_DISABLED);
	r11.SetWindowTextW(_T("\"14\""));
	GetDlgItem(IDC_11)->ModifyStyle(0, WS_DISABLED);
	r12.SetWindowTextW(_T("17"));
	GetDlgItem(IDC_12)->ModifyStyle(0, WS_DISABLED);
	r13.SetWindowTextW(_T("\"1\""));
	GetDlgItem(IDC_13)->ModifyStyle(0, WS_DISABLED);
}
{
	r14.SetWindowTextW(_T("4"));
	GetDlgItem(IDC_14)->ModifyStyle(0, WS_DISABLED);
	r15.SetWindowTextW(_T("\"7\""));
	GetDlgItem(IDC_15)->ModifyStyle(0, WS_DISABLED);
	r16.SetWindowTextW(_T("10"));
	GetDlgItem(IDC_16)->ModifyStyle(0, WS_DISABLED);
	r17.SetWindowTextW(_T("13"));
	GetDlgItem(IDC_17)->ModifyStyle(0, WS_DISABLED);
	r18.SetWindowTextW(_T("\"16\""));
	GetDlgItem(IDC_18)->ModifyStyle(0, WS_DISABLED);
}
}
void CRouletteKNDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CRouletteKNDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

 int CRouletteKNDlg::RandomNum() {

	std::random_device rd;     // Used once to initialise (seed) engine
	std::mt19937 rng(rd());  
	std::uniform_int_distribution<int> uni(0, 18); // Guaranteed unbiased

	return uni(rng);
}

void CRouletteKNDlg::spinner() {
	UpdateData(true);
	int counter = 0;
	if (CurrBet == 0) {
		res.SetWindowTextW(_T("Select a bet amount."));
		return;
	}
	WinOrLose.SetWindowTextW(_T(" "));
	GameOn = true;
	betB.EnableWindow(false);
	res.SetWindowTextW(_T("Game in progress..."));
	while( counter <= 15){
		int man = RandomNum();
		Display.Format(_T("%i"), man);
		Display += " ...";
		Sleep(50);
		UpdateData(false);
		UpdateWindow();
		counter++;
	
	}
	result = RandomNum();
	CString Fye;
	Fye.Format(_T("%i"), result);
	Display = "";
	Display = Fye;
	UpdateData(false);
	UpdateData(true);
	res.SetWindowTextW(_T("The result is: ") + Fye);
	CString pay;
	pay.Format(_T("%.2f"), payout);
	CheckResult(result);
	if (UserWin) {
		WinOrLose.SetWindowTextW(_T("You won! Your payout is: ") + pay + "\nPress \"Bet\" to play again.");
		uBal += payout;
	}
	else {
		WinOrLose.SetWindowTextW(_T("You lost. Your payout is: 0.00.\nPress \"Bet\" to play again."));
	}
	GameOn = false;
	betB.EnableWindow(true);
	UserWin = false;
	UpdateData(false);
}



void CRouletteKNDlg::CheckResult(int reso) {
	UpdateData(true);
	UserWin = false;
	/*	zero, cust, first, second, third, onehalf, secondhalf, even, red, black,
	odd, top, middle, bottom
*/
	int a_red[9] = { 1,3,5,7,9,12,14,16,18 };
	int a_blk[9] = { 2,4,6,8,10,11,13,15,17 };
	int a_mid[6] = { 2,5,8,11,14,17 };
	int a_top[6] = { 3,6,9,12,15,18 };
	switch (rino) {
	case zero:
		if (reso == 0) {
			UserWin = true;
		}
		break;
	case cust:
		if (reso == custombet) {
			UserWin = true;
		}
		break;
	case first:
		if (reso >= 1 && reso <= 6) {
			UserWin = true;
		}
		break;
	case second:
		if (reso >= 7 && reso <= 12) {
			UserWin = true;
		}
		break;
	case third:
		if (reso >= 13 && reso <= 18) {
			UserWin = true;
		}
		break;
	case onehalf:
		if (reso >= 1 && reso <= 9) {
			UserWin = true;
		}
		break;
	case secondhalf:
		if (reso >= 10 && reso <= 18) {
			UserWin = true;
		
		}
		break;
	case even:
		if (reso % 2 == 0) {
			UserWin = true;
		}
		break;
	case red:
		for (int i = 0; i < 6; i++) {
			if (reso == a_red[i]) {
				UserWin = true;
				break;
			}
		}
		break;
	case black:
		for (int i = 0; i < 6; i++) {
			if (reso == a_blk[i]) {
				UserWin = true;
				break;
			}
		}
		break;
	case odd:
		if (reso % 2 != 0) {
			UserWin = true;
		}
		break;
	case top:
		for (int i = 0; i < 6; i++) {
			if (reso == a_top[i]) {
				UserWin = true;
				break;
			}
		}
		break;
	case middle:
		for (int i = 0; i < 6; i++) {
			if (reso == a_mid[i]) {
				UserWin = true;
				break;
			}
		}
		break;
	case bottom:
		int a_bot[6] = { 1,4,7,10,13,16 };
		for (int i = 0; i < 6; i++) {
			if (reso == a_bot[i]) {
				UserWin = true;
				break;
			}
		}
		break;
	}
}
void CRouletteKNDlg::OnBnClickedBetb()
{
	UpdateData(true);
	WinOrLose.SetWindowTextW(_T(" "));
	CString csto;
	if (GameOn == false) {
		if (rino == cust) {
			Custom.GetWindowTextW(csto);
			CustomB();
			if (csto == "kev" || csto == "KEV" || csto == "Kev") {
				if (codeUsed == false) {
					res.SetWindowTextW(_T("You found the cheat code!"));
					WinOrLose.SetWindowTextW(_T("You have been given 15 coins free."));
					uBal += 15;
					codeUsed = true;
					UpdateData(false);
					return;
				}
			if (codeUsed == true) {
					res.SetWindowTextW(_T("You already used this cheat code."));
					WinOrLose.SetWindowTextW(_T(""));
					UpdateData(false);
					return;
				}
			if (custombet > 18 || custombet <= 0) {
				res.SetWindowTextW(_T("Your custom bet must be between 1 and 18."));
				WinOrLose.SetWindowTextW(_T("I'm sure you wouldn't want INF:1 odds."));
				return;
			}
		}
	}
		if (CurrBet > uBal) {
			WinOrLose.SetWindowTextW(_T(" "));
			res.SetWindowTextW(_T("Your bet is more than you can afford."));
		}
		if (CurrBet <= uBal) {
			Custom.EnableWindow(false);
			res.SetWindowTextW(_T("Good luck!"));
			payout = CurrBet * multiplier;
			uBal -= CurrBet;
			UpdateData(false);
			spinner();
		}
		
	}
	UpdateData(false);
}

	void CRouletteKNDlg::OnBnClickedZero()
	{
		UpdateData(true);
		Custom.EnableWindow(false);
		multiplier = 18;
		rino = zero;
		UpdateData(false);
	}
	void CRouletteKNDlg::OnBnClickedCustom()
	{
		UpdateData(true);
		rino = cust;
		multiplier = 18;
		CustomB();
		UpdateData(false);
	}

	void CRouletteKNDlg::CustomB() {
		CString csto;
		Custom.EnableWindow();
		Custom.GetWindowTextW((csto));
		custombet = _ttoi(csto);
	}

	void CRouletteKNDlg::OnBnClicked1st6()
	{
		UpdateData(true);
		multiplier = 3;
		Custom.EnableWindow(false);
		Custom.EnableWindow(false);
		rino = first;
		UpdateData(false);
	}

	void CRouletteKNDlg::OnBnClicked2nd6()
	{
		UpdateData(true);
		Custom.EnableWindow(false);
		multiplier = 3;
		rino = second;
		UpdateData(false);
	}

	HBRUSH CRouletteKNDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
	{
		/*
		switch (nCtlColor) {

		case CTLCOLOR_EDIT:
		case CTLCOLOR_MSGBOX:
				pDC->SetTextColor(RGB(255, 0, 0));
			if (r1 in { == TRUE)
			{
				pDC->SetBkColor(RGB(0, 0, 0));
				ChangeColor = FALSE;
			}
			//return (HBRUSH)(r3BkBrush->GetSafeHandle());

		default:
			return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
			*/

			return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
		}
	void CRouletteKNDlg::OnBnClickedToprow()
	{
		UpdateData(true);
		Custom.EnableWindow(false);
		multiplier = 3;
		rino = top;
		UpdateData(false);
	}

	void CRouletteKNDlg::OnBnClickedMiddlerow()
	{
		UpdateData(true);
		Custom.EnableWindow(false);
		rino = middle;
		multiplier = 3;
		UpdateData(false);
	}

	void CRouletteKNDlg::OnBnClickedBottomrow()
	{
		UpdateData(true);
		Custom.EnableWindow(false);
		rino = bottom;
		multiplier = 3;
		UpdateData(false);
	}


void CRouletteKNDlg::OnBnClicked1to9()
{
	UpdateData(true);
	Custom.EnableWindow(false);
	rino = onehalf;
	multiplier = 2;
	UpdateData(false);
}

void CRouletteKNDlg::OnBnClicked10to18()
{
	UpdateData(true);
	Custom.EnableWindow(false);
	rino = secondhalf;
	multiplier = 2;
	UpdateData(false);
}

void CRouletteKNDlg::OnBnClickedEven()
{
	UpdateData(true);
	Custom.EnableWindow(false);
	rino = even;
	multiplier = 2;
	UpdateData(false);
}


void CRouletteKNDlg::OnBnClickedRed()
{
	UpdateData(true);
	Custom.EnableWindow(false);
	rino = red;
	multiplier = 2;
	UpdateData(false);
}


void CRouletteKNDlg::OnBnClickedBlack()
{
	UpdateData(true);
	Custom.EnableWindow(false);
	rino = black;
	multiplier = 2;
	UpdateData(false);
}


void CRouletteKNDlg::OnBnClickedOdd()
{
	UpdateData(true);
	Custom.EnableWindow(false);
	rino = odd;
	multiplier = 2;
	UpdateData(false);
}

void CRouletteKNDlg::OnBnClicked3rd6()
{
	UpdateData(true);
	Custom.EnableWindow(false);
	rino = third;
	multiplier = 3;
	UpdateData(false);
}


void CRouletteKNDlg::OnBnClicked50c(){
	UpdateData(true);
	CurrBet = 0.5;
	UpdateData(false);
}


void CRouletteKNDlg::OnBnClicked1d(){
	UpdateData(true);
	CurrBet = 1;
	UpdateData(false);
}


void CRouletteKNDlg::OnBnClicked5d(){
	UpdateData(true);
	CurrBet = 5;
	UpdateData(false);
}


void CRouletteKNDlg::OnBnClicked10d(){
	UpdateData(true);
	CurrBet = 10;
	UpdateData(false);
}




