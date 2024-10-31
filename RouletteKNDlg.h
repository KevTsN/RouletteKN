
// RouletteKNDlg.h : header file
//

#pragma once
#include <windows.h>
#include <atlimage.h>
#include <Gdiplusimaging.h>


enum Btype {
	zero, cust, first, second, third, onehalf, secondhalf, even, red, black,
	odd, top, middle, bottom
};

// CRouletteKNDlg dialog
class CRouletteKNDlg : public CDialogEx
{
// Construction
public:
	CRouletteKNDlg(CWnd* pParent = nullptr);	// standard constructor
	//CEdit[19] todisable = { r0, r1,r2,r3,r4,r5,r6,r7,r8,r9,10,r11,r12,r13,r14,
		//r15,r16,r17,r18 };
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ROULETTEKN_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void NumInit();
	void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	afx_msg int RandomNum();
	 int result = 100;
	afx_msg void spinner();
	CEdit r1;
	CEdit r10;
	CEdit r11;
	CEdit r12;
	CEdit r13;
	CEdit r14;
	CEdit r15;
	CEdit r16;
	CEdit r17;
	CEdit r18;
	CEdit r2;
	CEdit r3;
	CEdit r4;
	CEdit r5;
	CEdit r6;
	CEdit r7;
	CEdit r8;
	CEdit r9;
	CEdit r0;
	bool codeUsed;
	double multiplier = 0;
	bool UserWin = false;
	double payout;
	CStatic WinOrLose;
	CStatic res;
	CButton betB;
	bool GameOn = false;
	double CurrBet;
	afx_msg void CheckResult(int reso);
	void OnBnClickedBetb();
	double uBal = 20.00;
	CButton BetOn0;
	afx_msg void OnBnClickedZero();
	afx_msg void OnBnClicked1st6();
	afx_msg void OnBnClickedMiddlerow();
	afx_msg void OnBnClicked2nd6();
	afx_msg void OnBnClickedBottomrow();
	afx_msg void OnBnClicked1to9();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	void OnBnClickedToprow();
	CEdit Custom;
	afx_msg void OnBnClickedCustom();
	afx_msg void CustomB();
	unsigned int custombet;
	afx_msg void OnBnClicked10to18();
	afx_msg void OnBnClickedEven();
	afx_msg void OnBnClickedRed();
	afx_msg void OnBnClickedBlack();
	afx_msg void OnBnClickedOdd();
	Btype rino;
	CButton betB2;
	afx_msg void OnBnClicked3rd6();
	afx_msg void OnBnClicked50c();
	afx_msg void OnBnClicked1d();
	afx_msg void OnBnClicked5d();
	afx_msg void OnBnClicked10d();
	CString Display;
	CStatic tableview;

};
