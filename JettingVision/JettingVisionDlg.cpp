
// JettingVisionDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "JettingVision.h"
#include "JettingVisionDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CJettingVisionDlg* g_pDialog = NULL;
extern CJettingVisionDlg* g_pDialog;
HWND hCommWnd;

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
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


// CJettingVisionDlg 대화 상자



CJettingVisionDlg::CJettingVisionDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_JETTINGVISION_DIALOG, pParent)
{
	g_pDialog = this;

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CJettingVisionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_ALIGN_USE, m_btn_align_use);
	DDX_Control(pDX, IDC_BTN_ALIGN_UNUSE, m_btn_align_unuse);
	DDX_Control(pDX, IDC_BTN_GAP_USE, m_btn_gap_use);
	DDX_Control(pDX, IDC_BTN_GAP_UNUSE, m_btn_gap_unuse);
	DDX_Control(pDX, IDC_BTN_UVLED_USE, m_btn_uvled_use);
	DDX_Control(pDX, IDC_BTN_UVLED_UNUSE, m_btn_uvled_unuse);
	DDX_Control(pDX, IDC_BTN_JETTING_USE, m_btn_jetting_use);
	DDX_Control(pDX, IDC_BTN_JETTING_UNUSE, m_btn_jetting_unuse);
	DDX_Control(pDX, IDC_BTN_REVIEW_USE, m_btn_review_use);
	DDX_Control(pDX, IDC_BTN_REVIEW_UNUSE, m_btn_review_unuse);
	DDX_Control(pDX, IDC_PIC_ALIGN_LEFT, m_pic_align_left);
	DDX_Control(pDX, IDC_PIC_ALIGN_RIGHT, m_pic_align_right);
	DDX_Control(pDX, IDC_LIST_MEASURE, m_list_measure);
	DDX_Control(pDX, IDC_BTN_SETTING_MOTION, m_btn_setting_motion);
	DDX_Control(pDX, IDC_BTN_SETTING_VISION, m_btn_setting_vision);
	DDX_Control(pDX, IDC_BTN_SETTING_MODIFY, m_btn_setting_modify);
	DDX_Control(pDX, IDC_BTN_SETTING_APPLY, m_btn_setting_apply);
	DDX_Control(pDX, IDC_BTN_SETTING_CANCEL, m_btn_setting_cancel);
	DDX_Control(pDX, IDC_BTN_ABS, m_btn_abs);
	DDX_Control(pDX, IDC_BTN_REL, m_btn_rel);
	DDX_Control(pDX, IDC_BTN_JOG_SLOW, m_btn_jog_slow);
	DDX_Control(pDX, IDC_BTN_JOG_FAST, m_btn_jog_fast);
	DDX_Control(pDX, IDC_ICON_STAGE_X_MOVE, m_icon_stage_x_move);
	DDX_Control(pDX, IDC_ICON_STAGE_X_STATUS, m_icon_stage_x_status);
	DDX_Control(pDX, IDC_ICON_STAGE_X_HOME, m_icon_stage_x_home);
	DDX_Control(pDX, IDC_ICON_STAGE_Y_MOVE, m_icon_stage_y_move);
	DDX_Control(pDX, IDC_ICON_STAGE_Y_STATUS, m_icon_stage_y_status);
	DDX_Control(pDX, IDC_ICON_STAGE_Y_HOME, m_icon_stage_y_home);
	DDX_Control(pDX, IDC_ICON_STAGE_T_MOVE, m_icon_stage_t_move);
	DDX_Control(pDX, IDC_ICON_STAGE_T_STATUS, m_icon_stage_t_status);
	DDX_Control(pDX, IDC_ICON_STAGE_T_HOME, m_icon_stage_t_home);
	DDX_Control(pDX, IDC_BTN_MEASURE_MODE, m_btn_measure_mode);
	DDX_Control(pDX, IDC_BTN_MEASURE_LINE, m_btn_measure_line);
	DDX_Control(pDX, IDC_BTN_MEASURE_RECTANGLE, m_btn_measure_rectangle);
	DDX_Control(pDX, IDC_BTN_MEASURE_CLEAR, m_btn_measure_clear);
}

BEGIN_MESSAGE_MAP(CJettingVisionDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_SETTING_MOTION, &CJettingVisionDlg::OnBnClickedBtnSettingMotion)
	ON_BN_CLICKED(IDC_BTN_SETTING_VISION, &CJettingVisionDlg::OnBnClickedBtnSettingVision)
	ON_BN_CLICKED(IDC_BTN_SETTING_MODIFY, &CJettingVisionDlg::OnBnClickedBtnSettingModify)
	ON_BN_CLICKED(IDC_BTN_SETTING_APPLY, &CJettingVisionDlg::OnBnClickedBtnSettingApply)
	ON_BN_CLICKED(IDC_BTN_SETTING_CANCEL, &CJettingVisionDlg::OnBnClickedBtnSettingCancel)
	ON_BN_CLICKED(IDC_BTN_MEASURE_MODE, &CJettingVisionDlg::OnBnClickedBtnMeasureMode)
	ON_BN_CLICKED(IDC_BTN_MEASURE_LINE, &CJettingVisionDlg::OnBnClickedBtnMeasureLine)
	ON_BN_CLICKED(IDC_BTN_MEASURE_RECTANGLE, &CJettingVisionDlg::OnBnClickedBtnMeasureRectangle)
	ON_BN_CLICKED(IDC_BTN_MEASURE_CLEAR, &CJettingVisionDlg::OnBnClickedBtnMeasureClear)
	ON_BN_CLICKED(IDC_BTN_ALIGN_USE, &CJettingVisionDlg::OnBnClickedBtnAlignUse)
	ON_BN_CLICKED(IDC_BTN_ALIGN_UNUSE, &CJettingVisionDlg::OnBnClickedBtnAlignUnuse)
	ON_BN_CLICKED(IDC_BTN_GAP_USE, &CJettingVisionDlg::OnBnClickedBtnGapUse)
	ON_BN_CLICKED(IDC_BTN_GAP_UNUSE, &CJettingVisionDlg::OnBnClickedBtnGapUnuse)
	ON_BN_CLICKED(IDC_BTN_UVLED_USE, &CJettingVisionDlg::OnBnClickedBtnUvledUse)
	ON_BN_CLICKED(IDC_BTN_UVLED_UNUSE, &CJettingVisionDlg::OnBnClickedBtnUvledUnuse)
	ON_BN_CLICKED(IDC_BTN_JETTING_USE, &CJettingVisionDlg::OnBnClickedBtnJettingUse)
	ON_BN_CLICKED(IDC_BTN_JETTING_UNUSE, &CJettingVisionDlg::OnBnClickedBtnJettingUnuse)
	ON_BN_CLICKED(IDC_BTN_REVIEW_USE, &CJettingVisionDlg::OnBnClickedBtnReviewUse)
	ON_BN_CLICKED(IDC_BTN_REVIEW_UNUSE, &CJettingVisionDlg::OnBnClickedBtnReviewUnuse)
	ON_BN_CLICKED(IDC_BTN_STAGE_X_MOVE, &CJettingVisionDlg::OnBnClickedBtnStageXMove)
	ON_BN_CLICKED(IDC_BTN_STAGE_Y_MOVE, &CJettingVisionDlg::OnBnClickedBtnStageYMove)
	ON_BN_CLICKED(IDC_BTN_STAGE_T_MOVE, &CJettingVisionDlg::OnBnClickedBtnStageTMove)
	ON_BN_CLICKED(IDC_BTN_PRESET_SAFETY, &CJettingVisionDlg::OnBnClickedBtnPresetSafety)
	ON_BN_CLICKED(IDC_BTN_PRESET_LOADING, &CJettingVisionDlg::OnBnClickedBtnPresetLoading)
	ON_BN_CLICKED(IDC_BTN_PRESET_ALIGN_LEFT, &CJettingVisionDlg::OnBnClickedBtnPresetAlignLeft)
	ON_BN_CLICKED(IDC_BTN_PRESET_ALIGN_RIGHT, &CJettingVisionDlg::OnBnClickedBtnPresetAlignRight)
	ON_BN_CLICKED(IDC_BTN_PRESET_PROC_START, &CJettingVisionDlg::OnBnClickedBtnPresetProcStart)
	ON_BN_CLICKED(IDC_BTN_PRESET_PROC_END, &CJettingVisionDlg::OnBnClickedBtnPresetProcEnd)
	ON_BN_CLICKED(IDC_BTN_PRESET_REVIEW, &CJettingVisionDlg::OnBnClickedBtnPresetReview)
	ON_BN_CLICKED(IDC_BTN_PRESET_UNLOADING, &CJettingVisionDlg::OnBnClickedBtnPresetUnloading)
	ON_BN_CLICKED(IDC_BTN_AUTO, &CJettingVisionDlg::OnBnClickedBtnAuto)
	ON_BN_CLICKED(IDC_BTN_PAUSE, &CJettingVisionDlg::OnBnClickedBtnPause)
	ON_BN_CLICKED(IDC_BTN_STOP, &CJettingVisionDlg::OnBnClickedBtnStop)
	ON_BN_CLICKED(IDC_BTN_ORIGIN, &CJettingVisionDlg::OnBnClickedBtnOrigin)
	ON_BN_CLICKED(IDC_BTN_ALARM, &CJettingVisionDlg::OnBnClickedBtnAlarm)
	ON_BN_CLICKED(IDC_BTN_RESET, &CJettingVisionDlg::OnBnClickedBtnReset)
	ON_BN_CLICKED(IDC_BTN_EXIT, &CJettingVisionDlg::OnBnClickedBtnExit)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_ABS, &CJettingVisionDlg::OnBnClickedBtnAbs)
	ON_BN_CLICKED(IDC_BTN_REL, &CJettingVisionDlg::OnBnClickedBtnRel)
	ON_BN_CLICKED(IDC_BTN_JOG_SLOW, &CJettingVisionDlg::OnBnClickedBtnJogSlow)
	ON_BN_CLICKED(IDC_BTN_JOG_FAST, &CJettingVisionDlg::OnBnClickedBtnJogFast)
	ON_EN_CHANGE(IDC_EDIT_STAGE_X_INPUT, &CJettingVisionDlg::OnEnChangeEditStageXInput)
	ON_EN_CHANGE(IDC_EDIT_STAGE_Y_INPUT, &CJettingVisionDlg::OnEnChangeEditStageYInput)
	ON_EN_CHANGE(IDC_EDIT_STAGE_T_INPUT, &CJettingVisionDlg::OnEnChangeEditStageTInput)
	ON_EN_CHANGE(IDC_EDIT_STAGE_X_SPEED, &CJettingVisionDlg::OnEnChangeEditStageXSpeed)
	ON_EN_CHANGE(IDC_EDIT_STAGE_Y_SPEED, &CJettingVisionDlg::OnEnChangeEditStageYSpeed)
	ON_EN_CHANGE(IDC_EDIT_STAGE_T_SPEED, &CJettingVisionDlg::OnEnChangeEditStageTSpeed)
	ON_STN_CLICKED(IDC_ICON_STAGE_X_STATUS, &CJettingVisionDlg::OnStnClickedIconStageXStatus)
	ON_STN_CLICKED(IDC_ICON_STAGE_Y_STATUS, &CJettingVisionDlg::OnStnClickedIconStageYStatus)
	ON_STN_CLICKED(IDC_ICON_STAGE_T_STATUS, &CJettingVisionDlg::OnStnClickedIconStageTStatus)
	ON_STN_CLICKED(IDC_ICON_STAGE_X_HOME, &CJettingVisionDlg::OnStnClickedIconStageXHome)
	ON_STN_CLICKED(IDC_ICON_STAGE_Y_HOME, &CJettingVisionDlg::OnStnClickedIconStageYHome)
	ON_STN_CLICKED(IDC_ICON_STAGE_T_HOME, &CJettingVisionDlg::OnStnClickedIconStageTHome)
	ON_BN_CLICKED(IDC_BTN_REVIEW_COMPLETE, &CJettingVisionDlg::OnBnClickedBtnReviewComplete)
	ON_BN_CLICKED(IDC_BTN_CYCLE, &CJettingVisionDlg::OnBnClickedBtnCycle)
END_MESSAGE_MAP()


// CJettingVisionDlg 메시지 처리기

BOOL CJettingVisionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	InitUI();

	InitClass();

	InitParam();

	InitSocket();

	dlgViewerCam1 = new ViewerCam1;
	dlgViewerCam1->Create(IDD_VIEWER_CAM1);
	dlgViewerCam1->MoveWindow(870, 5, 400, 350);
	dlgViewerCam1->ShowWindow(SW_SHOW);

	dlgViewerCam2 = new ViewerCam2;
	dlgViewerCam2->Create(IDD_VIEWER_CAM2);
	dlgViewerCam2->MoveWindow(870, 360, 400, 350);
	dlgViewerCam2->ShowWindow(SW_SHOW);

	dlgSettingMotion = new SettingMotion;
	dlgSettingMotion->Create(IDD_SETTING_MOTION);
	dlgSettingMotion->MoveWindow(1280, 5, 390, WindowHeight - 115);
	dlgSettingMotion->ShowWindow(SW_SHOW);

	dlgSettingVision = new SettingVision;
	dlgSettingVision->Create(IDD_SETTING_VISION);
	dlgSettingVision->MoveWindow(1280, 5, 390, WindowHeight - 115);
	dlgSettingVision->ShowWindow(SW_HIDE);

	dlgCycle = new MotionCycle;
	dlgCycle->Create(IDD_MOTION_CYCLE);
	dlgCycle->MoveWindow(0, 5, 370, 480);
	dlgCycle->ShowWindow(SW_HIDE);

	cBaumer = new connect_Baumer;

	cBaumer->Init();
	cBaumer->Open();
	cBaumer->Connect();

	InitMotion();

	bProcStart = false;
	bCycleStart = false;

	m_pAcs->m_pACSMotion[0].m_nAxis = 1;
	Vision = NULL;
	Vision = AfxBeginThread(Vision_Thread, this);

	Proc = NULL;
	Proc = AfxBeginThread(Proc_Thread, this);

	Cycle = NULL;
	Cycle = AfxBeginThread(Cycle_Thread, this);

	SetTimer(1, 100, NULL);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CJettingVisionDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CJettingVisionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CJettingVisionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



int CJettingVisionDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}


HBRUSH CJettingVisionDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	UINT nID = pWnd->GetDlgCtrlID();

	switch (nID)
	{
	case IDC_STATIC_ALIGN_LEFT_JUDGE:
		pDC->SetBkMode(TRANSPARENT);

		if (bJudgeAlignLeft == true)
			pDC->SetTextColor(ColorGreen);

		else if (bJudgeAlignLeft == false)
			pDC->SetTextColor(ColorRed);

		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
		break;

	case IDC_STATIC_ALIGN_RIGHT_JUDGE:
		pDC->SetBkMode(TRANSPARENT);

		if (bJudgeAlignRight == true)
			pDC->SetTextColor(ColorGreen);

		else if (bJudgeAlignRight == false)
			pDC->SetTextColor(ColorRed);

		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
		break;
	case IDC_STATIC_ALIGN_MODIFY_X_JUDGE:
		//pDC->SetBkMode(TRANSPARENT);

		if (bJudgeModifyX == true)
			pDC->SetTextColor(ColorGreen);

		else if (bJudgeModifyX == false)
			pDC->SetTextColor(ColorRed);

		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
		break;
	case IDC_STATIC_ALIGN_MODIFY_Y_JUDGE:
		//pDC->SetBkMode(TRANSPARENT);

		if (bJudgeModifyY == true)
			pDC->SetTextColor(ColorGreen);

		else if (bJudgeModifyY == false)
			pDC->SetTextColor(ColorRed);

		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
		break;
	case IDC_STATIC_ALIGN_MODIFY_T_JUDGE:
		//pDC->SetBkMode(TRANSPARENT);

		if (bJudgeModifyT == true)
			pDC->SetTextColor(ColorGreen);

		else if (bJudgeModifyT == false)
			pDC->SetTextColor(ColorRed);

		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
		break;
	case IDC_STATIC_GAP_JUDGE:
		//pDC->SetBkMode(TRANSPARENT);

		if (bJudgeGapAvg == true)
			pDC->SetTextColor(ColorGreen);

		else if (bJudgeGapAvg == false)
			pDC->SetTextColor(ColorRed);

		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
		break;

	}	return hbr;
}


BOOL CJettingVisionDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN) // ENTER키 눌릴 시
			return TRUE;
		else if (pMsg->wParam == VK_ESCAPE) // ESC키 눌릴 시
			return TRUE;
	}

	if (pMsg->message == WM_LBUTTONDOWN)
	{
		pButton = (CButton*)GetDlgItem(IDC_BTN_STAGE_X_JOG_PLUS);
		pButton->GetWindowRect(rect_stage_x_plus);
		if (rect_stage_x_plus.PtInRect(pMsg->pt))
			StageMoveJog(0, _T("POSITIVE"));

		pButton = (CButton*)GetDlgItem(IDC_BTN_STAGE_Y_JOG_PLUS);
		pButton->GetWindowRect(rect_stage_y_plus);
		if (rect_stage_y_plus.PtInRect(pMsg->pt))
			StageMoveJog(1, _T("POSITIVE"));

		pButton = (CButton*)GetDlgItem(IDC_BTN_STAGE_T_JOG_PLUS);
		pButton->GetWindowRect(rect_stage_t_plus);
		if (rect_stage_t_plus.PtInRect(pMsg->pt))
			StageMoveJog(2, _T("POSITIVE"));

		pButton = (CButton*)GetDlgItem(IDC_BTN_STAGE_X_JOG_MINUS);
		pButton->GetWindowRect(rect_stage_x_minus);
		if (rect_stage_x_minus.PtInRect(pMsg->pt))
			StageMoveJog(0, _T("NEGATIVE"));

		pButton = (CButton*)GetDlgItem(IDC_BTN_STAGE_Y_JOG_MINUS);
		pButton->GetWindowRect(rect_stage_y_minus);
		if (rect_stage_y_minus.PtInRect(pMsg->pt))
			StageMoveJog(1, _T("NEGATIVE"));

		pButton = (CButton*)GetDlgItem(IDC_BTN_STAGE_T_JOG_MINUS);
		pButton->GetWindowRect(rect_stage_t_minus);
		if (rect_stage_t_minus.PtInRect(pMsg->pt))
			StageMoveJog(2, _T("NEGATIVE"));

	}

	else if (pMsg->message == WM_LBUTTONUP)
	{
		if (rect_stage_x_plus.PtInRect(pMsg->pt) || rect_stage_x_minus.PtInRect(pMsg->pt))
			StageBreak(0);

		if (rect_stage_y_plus.PtInRect(pMsg->pt) || rect_stage_y_minus.PtInRect(pMsg->pt))
			StageBreak(1);

		if (rect_stage_t_plus.PtInRect(pMsg->pt) || rect_stage_t_minus.PtInRect(pMsg->pt))
			StageBreak(2);
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CJettingVisionDlg::InitUI()
{
	SetWindowPos(&wndTop, 0, 0, WindowWidth, WindowHeight, SWP_HIDEWINDOW);

	GetDlgItem(IDC_EDIT_PROC_STEP)->MoveWindow(10, 10, 490, 30);

	GetDlgItem(IDC_BTN_ALIGN_USE)->MoveWindow(10, 50, 90, 30);
	GetDlgItem(IDC_BTN_ALIGN_UNUSE)->MoveWindow(10, 90, 90, 30);
	GetDlgItem(IDC_BTN_GAP_USE)->MoveWindow(110, 50, 90, 30);
	GetDlgItem(IDC_BTN_GAP_UNUSE)->MoveWindow(110, 90, 90, 30);
	GetDlgItem(IDC_BTN_UVLED_USE)->MoveWindow(210, 50, 90, 30);
	GetDlgItem(IDC_BTN_UVLED_UNUSE)->MoveWindow(210, 90, 90, 30);
	GetDlgItem(IDC_BTN_JETTING_USE)->MoveWindow(310, 50, 90, 30);
	GetDlgItem(IDC_BTN_JETTING_UNUSE)->MoveWindow(310, 90, 90, 30);
	GetDlgItem(IDC_BTN_REVIEW_USE)->MoveWindow(410, 50, 90, 30);
	GetDlgItem(IDC_BTN_REVIEW_UNUSE)->MoveWindow(410, 90, 90, 30);

	GetDlgItem(IDC_STATIC_ALIGN_LEFT)->MoveWindow(20, 130, 60, 30);
	GetDlgItem(IDC_STATIC_ALIGN_RIGHT)->MoveWindow(20, 170, 60, 30);
	GetDlgItem(IDC_STATIC_ALIGN_LEFT_MATCHRATE)->MoveWindow(90, 130, 80, 30);
	GetDlgItem(IDC_STATIC_ALIGN_RIGHT_MATCHRATE)->MoveWindow(90, 170, 80, 30);
	GetDlgItem(IDC_STATIC_ALIGN_LEFT_JUDGE)->MoveWindow(190, 130, 40, 30);
	GetDlgItem(IDC_STATIC_ALIGN_RIGHT_JUDGE)->MoveWindow(190, 170, 40, 30);
	GetDlgItem(IDC_STATIC_ALIGN_MODIFY_X)->MoveWindow(20, 210, 60, 30);
	GetDlgItem(IDC_STATIC_ALIGN_MODIFY_Y)->MoveWindow(20, 250, 60, 30);
	GetDlgItem(IDC_STATIC_ALIGN_MODIFY_T)->MoveWindow(20, 290, 60, 30);
	GetDlgItem(IDC_STATIC_ALIGN_MODIFY_X_VALUE)->MoveWindow(90, 210, 80, 30);
	GetDlgItem(IDC_STATIC_ALIGN_MODIFY_Y_VALUE)->MoveWindow(90, 250, 80, 30);
	GetDlgItem(IDC_STATIC_ALIGN_MODIFY_T_VALUE)->MoveWindow(90, 290, 80, 30);
	GetDlgItem(IDC_STATIC_ALIGN_MODIFY_X_JUDGE)->MoveWindow(190, 210, 40, 30);
	GetDlgItem(IDC_STATIC_ALIGN_MODIFY_Y_JUDGE)->MoveWindow(190, 250, 40, 30);
	GetDlgItem(IDC_STATIC_ALIGN_MODIFY_T_JUDGE)->MoveWindow(190, 290, 40, 30);


	GetDlgItem(IDC_STATIC_GAP)->MoveWindow(280, 250, 60, 30);
	GetDlgItem(IDC_STATIC_GAP_VALUE)->MoveWindow(350, 250, 80, 30);
	GetDlgItem(IDC_STATIC_GAP_STEP)->MoveWindow(450, 250, 40, 30);
	GetDlgItem(IDC_STATIC_GAP_AVG)->MoveWindow(280, 290, 60, 30);
	GetDlgItem(IDC_STATIC_GAP_VALUE_AVG)->MoveWindow(350, 290, 80, 30);
	GetDlgItem(IDC_STATIC_GAP_JUDGE)->MoveWindow(450, 290, 40, 30);

	GetDlgItem(IDC_BTN_ALIGN_MANUAL)->MoveWindow(310, 130, 90, 30);
	GetDlgItem(IDC_BTN_ALIGN_PASS)->MoveWindow(410, 130, 90, 30);
	GetDlgItem(IDC_BTN_REVIEW_COMPLETE)->MoveWindow(410, 170, 90, 30);

	GetDlgItem(IDC_STATIC_TACKTIME)->MoveWindow(520, 10, 80, 30);
	GetDlgItem(IDC_STATIC_TACKTIME_LOADING)->MoveWindow(520, 50, 80, 30);
	GetDlgItem(IDC_STATIC_TACKTIME_ALIGN)->MoveWindow(520, 90, 80, 30);
	GetDlgItem(IDC_STATIC_TACKTIME_GAP)->MoveWindow(520, 130, 80, 30);
	GetDlgItem(IDC_STATIC_TACKTIME_JETTING)->MoveWindow(520, 170, 80, 30);
	GetDlgItem(IDC_STATIC_TACKTIME_UNLOADING)->MoveWindow(520, 210, 80, 30);
	GetDlgItem(IDC_STATIC_TACKTIME_TOTAL)->MoveWindow(520, 290, 80, 30);
	GetDlgItem(IDC_STATIC_TACKTIME_LOADING_VALUE)->MoveWindow(600, 50, 80, 30);
	GetDlgItem(IDC_STATIC_TACKTIME_ALIGN_VALUE)->MoveWindow(600, 90, 80, 30);
	GetDlgItem(IDC_STATIC_TACKTIME_GAP_VALUE)->MoveWindow(600, 130, 80, 30);
	GetDlgItem(IDC_STATIC_TACKTIME_JETTING_VALUE)->MoveWindow(600, 170, 80, 30);
	GetDlgItem(IDC_STATIC_TACKTIME_UNLOADING_VALUE)->MoveWindow(600, 210, 80, 30);
	GetDlgItem(IDC_STATIC_TACKTIME_TOTAL_VALUE)->MoveWindow(600, 290, 80, 30);


	GetDlgItem(IDC_BTN_MEASURE_MODE)->MoveWindow(695, 10, 30, 30);
	GetDlgItem(IDC_BTN_MEASURE_LINE)->MoveWindow(730, 10, 30, 30);
	GetDlgItem(IDC_BTN_MEASURE_RECTANGLE)->MoveWindow(765, 10, 30, 30);
	GetDlgItem(IDC_BTN_MEASURE_CLEAR)->MoveWindow(830, 10, 30, 30);
	GetDlgItem(IDC_LIST_MEASURE)->MoveWindow(695, 50, 170, 267);

	GetDlgItem(IDC_BTN_AUTO)->MoveWindow(10, WindowHeight - 45, 80, 40);
	GetDlgItem(IDC_BTN_PAUSE)->MoveWindow(90, WindowHeight - 45, 80, 40);
	GetDlgItem(IDC_BTN_STOP)->MoveWindow(170, WindowHeight - 45, 80, 40);
	GetDlgItem(IDC_BTN_ORIGIN)->MoveWindow(250, WindowHeight - 45, 80, 40);
	GetDlgItem(IDC_BTN_ALARM)->MoveWindow(330, WindowHeight - 45, 80, 40);
	GetDlgItem(IDC_BTN_RESET)->MoveWindow(410, WindowHeight - 45, 80, 40);
	GetDlgItem(IDC_BTN_CYCLE)->MoveWindow(490, WindowHeight - 45, 80, 40);
	GetDlgItem(IDC_BTN_EXIT)->MoveWindow(WindowWidth - 90, WindowHeight - 45, 80, 40);

	GetDlgItem(IDC_STATIC_CAM1_CONNECT)->MoveWindow(590, WindowHeight - 40, 50, 30);
	GetDlgItem(IDC_ICON_CAM1_CONNECT)->MoveWindow(630, WindowHeight - 35, 20, 20);
	GetDlgItem(IDC_STATIC_CAM2_CONNECT)->MoveWindow(690, WindowHeight - 40, 50, 30);
	GetDlgItem(IDC_ICON_CAM2_CONNECT)->MoveWindow(730, WindowHeight - 35, 20, 20);
	GetDlgItem(IDC_STATIC_LIGHT_CONNECT)->MoveWindow(790, WindowHeight - 40, 50, 30);
	GetDlgItem(IDC_ICON_LIGHT_CONNECT)->MoveWindow(830, WindowHeight - 35, 20, 20);
	GetDlgItem(IDC_STATIC_GAP_CONNECT)->MoveWindow(890, WindowHeight - 40, 50, 30);
	GetDlgItem(IDC_ICON_GAP_CONNECT)->MoveWindow(930, WindowHeight - 35, 20, 20);
	GetDlgItem(IDC_STATIC_UVLED_CONNECT)->MoveWindow(990, WindowHeight - 40, 50, 30);
	GetDlgItem(IDC_ICON_UVLED_CONNECT)->MoveWindow(1050, WindowHeight - 35, 20, 20);



	GetDlgItem(IDC_PIC_DRAW)->MoveWindow(10, 330, 500, 380);
	GetDlgItem(IDC_PIC_STAGE)->MoveWindow(515, 540, 350, 170);
	GetDlgItem(IDC_STATIC_STAGE_STATUS)->MoveWindow(520, 550, 330, 30);
	GetDlgItem(IDC_STATIC_STAGE_X)->MoveWindow(520, 590, 90, 20);
	GetDlgItem(IDC_STATIC_STAGE_Y)->MoveWindow(640, 590, 90, 20);
	GetDlgItem(IDC_STATIC_STAGE_T)->MoveWindow(760, 590, 90, 20);
	GetDlgItem(IDC_STATIC_STAGE_X_MOVE)->MoveWindow(520, 620, 60, 20);
	GetDlgItem(IDC_STATIC_STAGE_X_STATUS)->MoveWindow(520, 650, 60, 20);
	GetDlgItem(IDC_STATIC_STAGE_X_HOME)->MoveWindow(520, 680, 60, 20);
	GetDlgItem(IDC_ICON_STAGE_X_MOVE)->MoveWindow(590, 620, 20, 20);
	GetDlgItem(IDC_ICON_STAGE_X_STATUS)->MoveWindow(590, 650, 20, 20);
	GetDlgItem(IDC_ICON_STAGE_X_HOME)->MoveWindow(590, 680, 20, 20);
	GetDlgItem(IDC_STATIC_STAGE_Y_MOVE)->MoveWindow(640, 620, 60, 20);
	GetDlgItem(IDC_STATIC_STAGE_Y_STATUS)->MoveWindow(640, 650, 60, 20);
	GetDlgItem(IDC_STATIC_STAGE_Y_HOME)->MoveWindow(640, 680, 60, 20);
	GetDlgItem(IDC_ICON_STAGE_Y_MOVE)->MoveWindow(710, 620, 20, 20);
	GetDlgItem(IDC_ICON_STAGE_Y_STATUS)->MoveWindow(710, 650, 20, 20);
	GetDlgItem(IDC_ICON_STAGE_Y_HOME)->MoveWindow(710, 680, 20, 20);
	GetDlgItem(IDC_STATIC_STAGE_T_MOVE)->MoveWindow(760, 620, 60, 20);
	GetDlgItem(IDC_STATIC_STAGE_T_STATUS)->MoveWindow(760, 650, 60, 20);
	GetDlgItem(IDC_STATIC_STAGE_T_HOME)->MoveWindow(760, 680, 60, 20);
	GetDlgItem(IDC_ICON_STAGE_T_MOVE)->MoveWindow(830, 620, 20, 20);
	GetDlgItem(IDC_ICON_STAGE_T_STATUS)->MoveWindow(830, 650, 20, 20);
	GetDlgItem(IDC_ICON_STAGE_T_HOME)->MoveWindow(830, 680, 20, 20);

	GetDlgItem(IDC_STATIC_ALIGN_LEFT_DISPLAY)->MoveWindow(515, 330, 170, 30);
	GetDlgItem(IDC_STATIC_ALIGN_RIGHT_DISPLAY)->MoveWindow(695, 330, 170, 30);
	GetDlgItem(IDC_PIC_ALIGN_LEFT)->MoveWindow(515, 360, 170, 170);
	GetDlgItem(IDC_PIC_ALIGN_RIGHT)->MoveWindow(695, 360, 170, 170);

	GetDlgItem(IDC_PIC_GRP_1)->MoveWindow(10, 720, 790, 170);
	GetDlgItem(IDC_STATIC_MANUAL)->MoveWindow(355, 730, 100, 30);
	GetDlgItem(IDC_STATIC_STAGE_X_MANUAL)->MoveWindow(20, 800, 60, 20);
	GetDlgItem(IDC_STATIC_STAGE_Y_MANUAL)->MoveWindow(20, 830, 60, 20);
	GetDlgItem(IDC_STATIC_STAGE_T_MANUAL)->MoveWindow(20, 860, 60, 20);
	GetDlgItem(IDC_STATIC_COMMAND)->MoveWindow(120, 770, 80, 20);
	GetDlgItem(IDC_STATIC_LIMIT_MIN)->MoveWindow(220, 770, 80, 20);
	GetDlgItem(IDC_STATIC_ACTUAL)->MoveWindow(320, 770, 80, 20);
	GetDlgItem(IDC_STATIC_LIMIT_MAX)->MoveWindow(420, 770, 80, 20);
	GetDlgItem(IDC_STATIC_SPEED)->MoveWindow(520, 770, 80, 20);
	GetDlgItem(IDC_STATIC_INPUT)->MoveWindow(620, 770, 80, 20);
	GetDlgItem(IDC_EDIT_STAGE_X_COMMAND)->MoveWindow(120, 800, 80, 20);
	GetDlgItem(IDC_EDIT_STAGE_X_LIMIT_MIN)->MoveWindow(220, 800, 80, 20);
	GetDlgItem(IDC_EDIT_STAGE_X_ACTUAL)->MoveWindow(320, 800, 80, 20);
	GetDlgItem(IDC_EDIT_STAGE_X_LIMIT_MAX)->MoveWindow(420, 800, 80, 20);
	GetDlgItem(IDC_EDIT_STAGE_X_SPEED)->MoveWindow(520, 800, 80, 20);
	GetDlgItem(IDC_EDIT_STAGE_X_INPUT)->MoveWindow(620, 800, 80, 20);
	GetDlgItem(IDC_EDIT_STAGE_Y_COMMAND)->MoveWindow(120, 830, 80, 20);
	GetDlgItem(IDC_EDIT_STAGE_Y_LIMIT_MIN)->MoveWindow(220, 830, 80, 20);
	GetDlgItem(IDC_EDIT_STAGE_Y_ACTUAL)->MoveWindow(320, 830, 80, 20);
	GetDlgItem(IDC_EDIT_STAGE_Y_LIMIT_MAX)->MoveWindow(420, 830, 80, 20);
	GetDlgItem(IDC_EDIT_STAGE_Y_SPEED)->MoveWindow(520, 830, 80, 20);
	GetDlgItem(IDC_EDIT_STAGE_Y_INPUT)->MoveWindow(620, 830, 80, 20);
	GetDlgItem(IDC_EDIT_STAGE_T_COMMAND)->MoveWindow(120, 860, 80, 20);
	GetDlgItem(IDC_EDIT_STAGE_T_LIMIT_MIN)->MoveWindow(220, 860, 80, 20);
	GetDlgItem(IDC_EDIT_STAGE_T_ACTUAL)->MoveWindow(320, 860, 80, 20);
	GetDlgItem(IDC_EDIT_STAGE_T_LIMIT_MAX)->MoveWindow(420, 860, 80, 20);
	GetDlgItem(IDC_EDIT_STAGE_T_SPEED)->MoveWindow(520, 860, 80, 20);
	GetDlgItem(IDC_EDIT_STAGE_T_INPUT)->MoveWindow(620, 860, 80, 20);
	GetDlgItem(IDC_BTN_STAGE_X_MOVE)->MoveWindow(720, 800, 60, 20);
	GetDlgItem(IDC_BTN_STAGE_Y_MOVE)->MoveWindow(720, 830, 60, 20);
	GetDlgItem(IDC_BTN_STAGE_T_MOVE)->MoveWindow(720, 860, 60, 20);
	GetDlgItem(IDC_BTN_ABS)->MoveWindow(650, 730, 60, 20);
	GetDlgItem(IDC_BTN_REL)->MoveWindow(720, 730, 60, 20);

	GetDlgItem(IDC_PIC_GRP_2)->MoveWindow(810, 720, 210, 170);
	GetDlgItem(IDC_STATIC_PRESET)->MoveWindow(820, 730, 190, 30);
	GetDlgItem(IDC_BTN_PRESET_SAFETY)->MoveWindow(830, 770, 80, 25);
	GetDlgItem(IDC_BTN_PRESET_LOADING)->MoveWindow(920, 770, 80, 25);
	GetDlgItem(IDC_BTN_PRESET_ALIGN_LEFT)->MoveWindow(830, 800, 80, 25);
	GetDlgItem(IDC_BTN_PRESET_ALIGN_RIGHT)->MoveWindow(920, 800, 80, 25);
	GetDlgItem(IDC_BTN_PRESET_PROC_START)->MoveWindow(830, 830, 80, 25);
	GetDlgItem(IDC_BTN_PRESET_PROC_END)->MoveWindow(920, 830, 80, 25);
	GetDlgItem(IDC_BTN_PRESET_REVIEW)->MoveWindow(830, 860, 80, 25);
	GetDlgItem(IDC_BTN_PRESET_UNLOADING)->MoveWindow(920, 860, 80, 25);

	GetDlgItem(IDC_PIC_GRP_3)->MoveWindow(1030, 720, 240, 170);
	GetDlgItem(IDC_STATIC_JOG)->MoveWindow(1040, 730, 220, 30);
	GetDlgItem(IDC_STATIC_JOG_ACTUAL)->MoveWindow(1110, 770, 80, 20);
	GetDlgItem(IDC_BTN_STAGE_X_JOG_MINUS)->MoveWindow(1050, 800, 50, 20);
	GetDlgItem(IDC_EDIT_STAGE_X_JOG_ACTUAL)->MoveWindow(1110, 800, 80, 20);
	GetDlgItem(IDC_BTN_STAGE_X_JOG_PLUS)->MoveWindow(1200, 800, 50, 20);
	GetDlgItem(IDC_BTN_STAGE_Y_JOG_MINUS)->MoveWindow(1050, 830, 50, 20);
	GetDlgItem(IDC_EDIT_STAGE_Y_JOG_ACTUAL)->MoveWindow(1110, 830, 80, 20);
	GetDlgItem(IDC_BTN_STAGE_Y_JOG_PLUS)->MoveWindow(1200, 830, 50, 20);
	GetDlgItem(IDC_BTN_STAGE_T_JOG_MINUS)->MoveWindow(1050, 860, 50, 20);
	GetDlgItem(IDC_EDIT_STAGE_T_JOG_ACTUAL)->MoveWindow(1110, 860, 80, 20);
	GetDlgItem(IDC_BTN_STAGE_T_JOG_PLUS)->MoveWindow(1200, 860, 50, 20);
	GetDlgItem(IDC_BTN_JOG_SLOW)->MoveWindow(1050, 735, 60, 20);
	GetDlgItem(IDC_BTN_JOG_FAST)->MoveWindow(1190, 735, 60, 20);

	GetDlgItem(IDC_PIC_UNDERBAR)->MoveWindow(0, WindowHeight - 50, WindowWidth, 50);

	GetDlgItem(IDC_BTN_SETTING_MOTION)->MoveWindow(1280, 855, 70, 30);
	GetDlgItem(IDC_BTN_SETTING_VISION)->MoveWindow(1350, 855, 70, 30);
	GetDlgItem(IDC_BTN_SETTING_MODIFY)->MoveWindow(1460, 855, 70, 30);
	GetDlgItem(IDC_BTN_SETTING_APPLY)->MoveWindow(1530, 855, 70, 30);
	GetDlgItem(IDC_BTN_SETTING_CANCEL)->MoveWindow(1600, 855, 70, 30);

	staticTitleFont = CreateFont(19, 8, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_MODERN, _T("맑은 고딕"));
	staticFont = CreateFont(15, 6, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_MODERN, _T("맑은 고딕"));
	btnFont = CreateFont(15, 6, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_MODERN, _T("맑은 고딕"));
	listFont = CreateFont(20, 5, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_MODERN, _T("맑은 고딕"));

	GetDlgItem(IDC_STATIC_STAGE_X)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_STAGE_Y)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_STAGE_T)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_STAGE_X_MANUAL)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_STAGE_Y_MANUAL)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_STAGE_T_MANUAL)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_COMMAND)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_LIMIT_MIN)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ACTUAL)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_LIMIT_MAX)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_SPEED)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_INPUT)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_JOG_ACTUAL)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_STAGE_X_MOVE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_STAGE_X_STATUS)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_STAGE_X_HOME)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_STAGE_Y_MOVE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_STAGE_Y_STATUS)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_STAGE_Y_HOME)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_STAGE_T_MOVE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_STAGE_T_STATUS)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_STAGE_T_HOME)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_TACKTIME_LOADING)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_TACKTIME_ALIGN)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_TACKTIME_GAP)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_TACKTIME_JETTING)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_TACKTIME_UNLOADING)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_TACKTIME_TOTAL)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_TACKTIME_LOADING_VALUE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_TACKTIME_ALIGN_VALUE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_TACKTIME_GAP_VALUE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_TACKTIME_JETTING_VALUE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_TACKTIME_UNLOADING_VALUE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_TACKTIME_TOTAL_VALUE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ALIGN_LEFT)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ALIGN_RIGHT)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ALIGN_LEFT_MATCHRATE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ALIGN_RIGHT_MATCHRATE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ALIGN_LEFT_JUDGE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ALIGN_RIGHT_JUDGE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ALIGN_MODIFY_X)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ALIGN_MODIFY_Y)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ALIGN_MODIFY_T)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ALIGN_MODIFY_X_VALUE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ALIGN_MODIFY_Y_VALUE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ALIGN_MODIFY_T_VALUE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ALIGN_MODIFY_X_JUDGE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ALIGN_MODIFY_Y_JUDGE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ALIGN_MODIFY_T_JUDGE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_GAP)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_GAP_VALUE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_GAP_STEP)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_GAP_AVG)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_GAP_VALUE_AVG)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_GAP_JUDGE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_CAM1_CONNECT)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_CAM2_CONNECT)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_LIGHT_CONNECT)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_GAP_CONNECT)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_UVLED_CONNECT)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);

	GetDlgItem(IDC_STATIC_STAGE_STATUS)->SendMessage(WM_SETFONT, (WPARAM)staticTitleFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_MANUAL)->SendMessage(WM_SETFONT, (WPARAM)staticTitleFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_PRESET)->SendMessage(WM_SETFONT, (WPARAM)staticTitleFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_JOG)->SendMessage(WM_SETFONT, (WPARAM)staticTitleFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ALIGN_LEFT_DISPLAY)->SendMessage(WM_SETFONT, (WPARAM)staticTitleFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ALIGN_RIGHT_DISPLAY)->SendMessage(WM_SETFONT, (WPARAM)staticTitleFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_TACKTIME)->SendMessage(WM_SETFONT, (WPARAM)staticTitleFont, (LPARAM)TRUE);

	GetDlgItem(IDC_BTN_AUTO)->SendMessage(WM_SETFONT, (WPARAM)btnFont, (LPARAM)TRUE);
	GetDlgItem(IDC_BTN_PAUSE)->SendMessage(WM_SETFONT, (WPARAM)btnFont, (LPARAM)TRUE);
	GetDlgItem(IDC_BTN_STOP)->SendMessage(WM_SETFONT, (WPARAM)btnFont, (LPARAM)TRUE);
	GetDlgItem(IDC_BTN_ORIGIN)->SendMessage(WM_SETFONT, (WPARAM)btnFont, (LPARAM)TRUE);
	GetDlgItem(IDC_BTN_ALARM)->SendMessage(WM_SETFONT, (WPARAM)btnFont, (LPARAM)TRUE);
	GetDlgItem(IDC_BTN_RESET)->SendMessage(WM_SETFONT, (WPARAM)btnFont, (LPARAM)TRUE);
	GetDlgItem(IDC_BTN_CYCLE)->SendMessage(WM_SETFONT, (WPARAM)btnFont, (LPARAM)TRUE);
	GetDlgItem(IDC_BTN_EXIT)->SendMessage(WM_SETFONT, (WPARAM)btnFont, (LPARAM)TRUE);
	GetDlgItem(IDC_BTN_ALIGN_USE)->SendMessage(WM_SETFONT, (WPARAM)btnFont, (LPARAM)TRUE);
	GetDlgItem(IDC_BTN_ALIGN_UNUSE)->SendMessage(WM_SETFONT, (WPARAM)btnFont, (LPARAM)TRUE);;
	GetDlgItem(IDC_BTN_GAP_USE)->SendMessage(WM_SETFONT, (WPARAM)btnFont, (LPARAM)TRUE);
	GetDlgItem(IDC_BTN_GAP_UNUSE)->SendMessage(WM_SETFONT, (WPARAM)btnFont, (LPARAM)TRUE);
	GetDlgItem(IDC_BTN_UVLED_USE)->SendMessage(WM_SETFONT, (WPARAM)btnFont, (LPARAM)TRUE);
	GetDlgItem(IDC_BTN_UVLED_UNUSE)->SendMessage(WM_SETFONT, (WPARAM)btnFont, (LPARAM)TRUE);
	GetDlgItem(IDC_BTN_JETTING_USE)->SendMessage(WM_SETFONT, (WPARAM)btnFont, (LPARAM)TRUE);
	GetDlgItem(IDC_BTN_JETTING_UNUSE)->SendMessage(WM_SETFONT, (WPARAM)btnFont, (LPARAM)TRUE);
	GetDlgItem(IDC_BTN_REVIEW_USE)->SendMessage(WM_SETFONT, (WPARAM)btnFont, (LPARAM)TRUE);
	GetDlgItem(IDC_BTN_REVIEW_UNUSE)->SendMessage(WM_SETFONT, (WPARAM)btnFont, (LPARAM)TRUE);
	GetDlgItem(IDC_BTN_STAGE_X_MOVE)->SendMessage(WM_SETFONT, (WPARAM)btnFont, (LPARAM)TRUE);
	GetDlgItem(IDC_BTN_STAGE_Y_MOVE)->SendMessage(WM_SETFONT, (WPARAM)btnFont, (LPARAM)TRUE);
	GetDlgItem(IDC_BTN_STAGE_T_MOVE)->SendMessage(WM_SETFONT, (WPARAM)btnFont, (LPARAM)TRUE);
	GetDlgItem(IDC_BTN_PRESET_SAFETY)->SendMessage(WM_SETFONT, (WPARAM)btnFont, (LPARAM)TRUE);
	GetDlgItem(IDC_BTN_PRESET_LOADING)->SendMessage(WM_SETFONT, (WPARAM)btnFont, (LPARAM)TRUE);
	GetDlgItem(IDC_BTN_PRESET_ALIGN_LEFT)->SendMessage(WM_SETFONT, (WPARAM)btnFont, (LPARAM)TRUE);
	GetDlgItem(IDC_BTN_PRESET_ALIGN_RIGHT)->SendMessage(WM_SETFONT, (WPARAM)btnFont, (LPARAM)TRUE);
	GetDlgItem(IDC_BTN_PRESET_PROC_START)->SendMessage(WM_SETFONT, (WPARAM)btnFont, (LPARAM)TRUE);
	GetDlgItem(IDC_BTN_PRESET_PROC_END)->SendMessage(WM_SETFONT, (WPARAM)btnFont, (LPARAM)TRUE);
	GetDlgItem(IDC_BTN_PRESET_REVIEW)->SendMessage(WM_SETFONT, (WPARAM)btnFont, (LPARAM)TRUE);
	GetDlgItem(IDC_BTN_PRESET_UNLOADING)->SendMessage(WM_SETFONT, (WPARAM)btnFont, (LPARAM)TRUE);
	GetDlgItem(IDC_BTN_SETTING_MOTION)->SendMessage(WM_SETFONT, (WPARAM)btnFont, (LPARAM)TRUE);
	GetDlgItem(IDC_BTN_SETTING_VISION)->SendMessage(WM_SETFONT, (WPARAM)btnFont, (LPARAM)TRUE);
	GetDlgItem(IDC_BTN_SETTING_MODIFY)->SendMessage(WM_SETFONT, (WPARAM)btnFont, (LPARAM)TRUE);
	GetDlgItem(IDC_BTN_SETTING_APPLY)->SendMessage(WM_SETFONT, (WPARAM)btnFont, (LPARAM)TRUE);
	GetDlgItem(IDC_BTN_SETTING_CANCEL)->SendMessage(WM_SETFONT, (WPARAM)btnFont, (LPARAM)TRUE);
	GetDlgItem(IDC_BTN_ALIGN_MANUAL)->SendMessage(WM_SETFONT, (WPARAM)btnFont, (LPARAM)TRUE);
	GetDlgItem(IDC_BTN_ALIGN_PASS)->SendMessage(WM_SETFONT, (WPARAM)btnFont, (LPARAM)TRUE);
	GetDlgItem(IDC_BTN_REVIEW_COMPLETE)->SendMessage(WM_SETFONT, (WPARAM)btnFont, (LPARAM)TRUE);
	GetDlgItem(IDC_BTN_ABS)->SendMessage(WM_SETFONT, (WPARAM)btnFont, (LPARAM)TRUE);
	GetDlgItem(IDC_BTN_REL)->SendMessage(WM_SETFONT, (WPARAM)btnFont, (LPARAM)TRUE);
	GetDlgItem(IDC_BTN_JOG_SLOW)->SendMessage(WM_SETFONT, (WPARAM)btnFont, (LPARAM)TRUE);
	GetDlgItem(IDC_BTN_JOG_FAST)->SendMessage(WM_SETFONT, (WPARAM)btnFont, (LPARAM)TRUE);

	GetDlgItem(IDC_LIST_MEASURE)->SendMessage(WM_SETFONT, (WPARAM)listFont, (LPARAM)TRUE);

	m_btn_align_use.EnableWindowsTheming(FALSE);
	m_btn_align_unuse.EnableWindowsTheming(FALSE);
	m_btn_gap_use.EnableWindowsTheming(FALSE);
	m_btn_gap_unuse.EnableWindowsTheming(FALSE);
	m_btn_uvled_use.EnableWindowsTheming(FALSE);
	m_btn_uvled_unuse.EnableWindowsTheming(FALSE);
	m_btn_jetting_use.EnableWindowsTheming(FALSE);
	m_btn_jetting_unuse.EnableWindowsTheming(FALSE);
	m_btn_review_use.EnableWindowsTheming(FALSE);
	m_btn_review_unuse.EnableWindowsTheming(FALSE);
	m_btn_setting_motion.EnableWindowsTheming(FALSE);
	m_btn_setting_vision.EnableWindowsTheming(FALSE);
	m_btn_abs.EnableWindowsTheming(FALSE);
	m_btn_rel.EnableWindowsTheming(FALSE);
	m_btn_jog_slow.EnableWindowsTheming(FALSE);
	m_btn_jog_fast.EnableWindowsTheming(FALSE);

	m_list_measure.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES);

	m_list_measure.InsertColumn(1, _T("No."), LVCFMT_CENTER, 50);
	m_list_measure.InsertColumn(3, _T("Value_1"), LVCFMT_CENTER, 60);
	m_list_measure.InsertColumn(4, _T("Value_2"), LVCFMT_CENTER, 60);
}


void CJettingVisionDlg::InitClass()
{

}

void CJettingVisionDlg::InitParam()
{
	m_bmp_green.LoadBitmapW(IDB_BITMAP_GREEN);
	m_bmp_red.LoadBitmapW(IDB_BITMAP_RED);
	m_bmp_yellow.LoadBitmapW(IDB_BITMAP_YELLOW);

	m_bmp_measure_on.LoadBitmapW(IDB_BITMAP_MEASURE_ON);
	m_bmp_measure_off.LoadBitmapW(IDB_BITMAP_MEASURE_OFF);
	m_bmp_line_on.LoadBitmapW(IDB_BITMAP_LINE_ON);
	m_bmp_line_off.LoadBitmapW(IDB_BITMAP_LINE_OFF);
	m_bmp_rectangle_on.LoadBitmapW(IDB_BITMAP_RECTANGLE_ON);
	m_bmp_rectangle_off.LoadBitmapW(IDB_BITMAP_RECTANGLE_OFF);
	m_bmp_clear.LoadBitmapW(IDB_BITMAP_CLEAR);

	m_btn_align_use.SetFaceColor(ColorGreen);
	m_btn_align_unuse.SetFaceColor(ColorBasic);
	m_btn_gap_use.SetFaceColor(ColorGreen);
	m_btn_gap_unuse.SetFaceColor(ColorBasic);
	m_btn_uvled_use.SetFaceColor(ColorGreen);
	m_btn_uvled_unuse.SetFaceColor(ColorBasic);
	m_btn_jetting_use.SetFaceColor(ColorGreen);
	m_btn_jetting_unuse.SetFaceColor(ColorBasic);
	m_btn_review_use.SetFaceColor(ColorGreen);
	m_btn_review_unuse.SetFaceColor(ColorBasic);
	m_btn_setting_motion.SetFaceColor(ColorGreen);
	m_btn_setting_vision.SetFaceColor(ColorBasic);
	m_btn_abs.SetFaceColor(ColorGreen);
	m_btn_rel.SetFaceColor(ColorBasic);
	m_btn_jog_slow.SetFaceColor(ColorGreen);
	m_btn_jog_fast.SetFaceColor(ColorBasic);

	m_icon_stage_x_move.SetBitmap(m_bmp_red);
	m_icon_stage_x_status.SetBitmap(m_bmp_red);
	m_icon_stage_x_home.SetBitmap(m_bmp_red);

	m_icon_stage_y_move.SetBitmap(m_bmp_red);
	m_icon_stage_y_status.SetBitmap(m_bmp_red);
	m_icon_stage_y_home.SetBitmap(m_bmp_red);

	m_icon_stage_t_move.SetBitmap(m_bmp_red);
	m_icon_stage_t_status.SetBitmap(m_bmp_red);
	m_icon_stage_t_home.SetBitmap(m_bmp_red);

	m_btn_measure_mode.SetBitmap(m_bmp_measure_off);
	m_btn_measure_line.SetBitmap(m_bmp_line_off);
	m_btn_measure_rectangle.SetBitmap(m_bmp_rectangle_off);
	m_btn_measure_clear.SetBitmap(m_bmp_clear);

	m_btn_measure_line.EnableWindow(false);
	m_btn_measure_rectangle.EnableWindow(false);

	GetDlgItem(IDC_EDIT_STAGE_X_SPEED)->SetWindowTextW(_T("10"));
	GetDlgItem(IDC_EDIT_STAGE_Y_SPEED)->SetWindowTextW(_T("10"));
	GetDlgItem(IDC_EDIT_STAGE_T_SPEED)->SetWindowTextW(_T("10"));

	GetDlgItem(IDC_EDIT_STAGE_X_INPUT)->SetWindowTextW(_T("0.0000"));
	GetDlgItem(IDC_EDIT_STAGE_Y_INPUT)->SetWindowTextW(_T("0.0000"));
	GetDlgItem(IDC_EDIT_STAGE_T_INPUT)->SetWindowTextW(_T("0.00000000"));

	GetDlgItem(IDC_EDIT_STAGE_X_COMMAND)->SetWindowTextW(_T("0.0000"));
	GetDlgItem(IDC_EDIT_STAGE_Y_COMMAND)->SetWindowTextW(_T("0.0000"));
	GetDlgItem(IDC_EDIT_STAGE_T_COMMAND)->SetWindowTextW(_T("0.00000000"));


	bJudgeAlignLeft = false;
	bJudgeAlignRight = false;
	bJudgeModifyX = false;
	bJudgeModifyY = false;
	bJudgeModifyT = false;
	bJudgeGapAvg = false;

	// 공정 CHECK
	bChkAlign = true;
	bChkGap = true;
	bChkUVLED = true;
	bChkJetting = true;
	bChkReview = true;

	// 공정 진행
	BOOL bProcStart;
	BOOL bProcStop;
	BOOL bProcPause;

	// MANUAL MOVE
	bChkABS = true;
	bChkREL = false;
	bChkJogSlow = true;
	bChkJogFast = false;
	bChkMeasurement = false;

	strDataFilePath = _T("D:\\JettingVision\\Data");
	strRecipeFilePath = _T("D:\\JettingVision\\Config");

	// 마지막 Recipe 항목 load
	SelectRecipe = _ttoi(AfxGetApp()->GetProfileStringW(_T("Recipe"), _T("Last Recipe")));

	CString strRecipe;
	strRecipe.Format(_T("\\%d\\"), SelectRecipe);
	// 초기 Recipe 값 확인
	strRecipeFilePath = strRecipeFilePath + strRecipe;

}


void CJettingVisionDlg::OnBnClickedBtnSettingMotion()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_btn_setting_motion.SetFaceColor(ColorGreen);
	m_btn_setting_vision.SetFaceColor(ColorBasic);

	dlgSettingMotion->ShowWindow(SW_SHOW);
	dlgSettingVision->ShowWindow(SW_HIDE);

}


void CJettingVisionDlg::OnBnClickedBtnSettingVision()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_btn_setting_motion.SetFaceColor(ColorBasic);
	m_btn_setting_vision.SetFaceColor(ColorGreen);

	dlgSettingMotion->ShowWindow(SW_HIDE);
	dlgSettingVision->ShowWindow(SW_SHOW);
}


void CJettingVisionDlg::OnBnClickedBtnSettingModify()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	dlgSettingMotion->SettingModify(true);
	dlgSettingVision->SettingModify(true);

	GetDlgItem(IDC_BTN_SETTING_MODIFY)->EnableWindow(false);
	GetDlgItem(IDC_BTN_SETTING_APPLY)->EnableWindow(true);
	GetDlgItem(IDC_BTN_SETTING_CANCEL)->EnableWindow(true);
}


void CJettingVisionDlg::OnBnClickedBtnSettingApply()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	dlgSettingMotion->SettingModify(false);
	dlgSettingVision->SettingModify(false);

	GetDlgItem(IDC_BTN_SETTING_MODIFY)->EnableWindow(true);
	GetDlgItem(IDC_BTN_SETTING_APPLY)->EnableWindow(false);
	GetDlgItem(IDC_BTN_SETTING_CANCEL)->EnableWindow(false);

	dlgSettingMotion->SaveRecipe();
	dlgSettingVision->SaveRecipe();

	dlgSettingMotion->LoadRecipe();
	dlgSettingVision->LoadRecipe();
}


void CJettingVisionDlg::OnBnClickedBtnSettingCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	dlgSettingMotion->SettingModify(false);
	dlgSettingVision->SettingModify(false);

	GetDlgItem(IDC_BTN_SETTING_MODIFY)->EnableWindow(true);
	GetDlgItem(IDC_BTN_SETTING_APPLY)->EnableWindow(false);
	GetDlgItem(IDC_BTN_SETTING_CANCEL)->EnableWindow(false);

	dlgSettingMotion->LoadRecipe();
	dlgSettingVision->LoadRecipe();
}


void CJettingVisionDlg::OnBnClickedBtnMeasureMode()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_btn_measure_mode.GetBitmap() == m_bmp_measure_off)
	{
		m_btn_measure_mode.SetBitmap(m_bmp_measure_on);

		m_btn_measure_line.EnableWindow(TRUE);
		m_btn_measure_rectangle.EnableWindow(TRUE);
	}

	else if (m_btn_measure_mode.GetBitmap() == m_bmp_measure_on)
	{
		m_btn_measure_mode.SetBitmap(m_bmp_measure_off);

		m_btn_measure_line.EnableWindow(FALSE);
		m_btn_measure_rectangle.EnableWindow(FALSE);
	}
}


void CJettingVisionDlg::OnBnClickedBtnMeasureLine()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CJettingVisionDlg::OnBnClickedBtnMeasureRectangle()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CJettingVisionDlg::OnBnClickedBtnMeasureClear()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CJettingVisionDlg::OnBnClickedBtnAlignUse()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_btn_align_use.SetFaceColor(ColorGreen);
	m_btn_align_unuse.SetFaceColor(ColorBasic);

	bChkAlign = true;
}


void CJettingVisionDlg::OnBnClickedBtnAlignUnuse()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_btn_align_use.SetFaceColor(ColorBasic);
	m_btn_align_unuse.SetFaceColor(ColorGreen);

	bChkAlign = false;
}


void CJettingVisionDlg::OnBnClickedBtnGapUse()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_btn_gap_use.SetFaceColor(ColorGreen);
	m_btn_gap_unuse.SetFaceColor(ColorBasic);

	bChkGap = true;
}


void CJettingVisionDlg::OnBnClickedBtnGapUnuse()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_btn_gap_use.SetFaceColor(ColorBasic);
	m_btn_gap_unuse.SetFaceColor(ColorGreen);

	bChkGap = false;
}


void CJettingVisionDlg::OnBnClickedBtnUvledUse()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_btn_uvled_use.SetFaceColor(ColorGreen);
	m_btn_uvled_unuse.SetFaceColor(ColorBasic);

	bChkUVLED = true;
}


void CJettingVisionDlg::OnBnClickedBtnUvledUnuse()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_btn_uvled_use.SetFaceColor(ColorBasic);
	m_btn_uvled_unuse.SetFaceColor(ColorGreen);

	bChkUVLED = false;
}


void CJettingVisionDlg::OnBnClickedBtnJettingUse()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_btn_jetting_use.SetFaceColor(ColorGreen);
	m_btn_jetting_unuse.SetFaceColor(ColorBasic);

	bChkJetting = true;
}


void CJettingVisionDlg::OnBnClickedBtnJettingUnuse()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_btn_jetting_use.SetFaceColor(ColorBasic);
	m_btn_jetting_unuse.SetFaceColor(ColorGreen);

	bChkJetting = false;
}


void CJettingVisionDlg::OnBnClickedBtnReviewUse()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_btn_review_use.SetFaceColor(ColorGreen);
	m_btn_review_unuse.SetFaceColor(ColorBasic);
}


void CJettingVisionDlg::OnBnClickedBtnReviewUnuse()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_btn_review_use.SetFaceColor(ColorBasic);
	m_btn_review_unuse.SetFaceColor(ColorGreen);
}


void CJettingVisionDlg::OnBnClickedBtnReviewComplete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	bProcReview = FALSE;
}


void CJettingVisionDlg::OnBnClickedBtnStageXMove()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strMove;
	GetDlgItem(IDC_BTN_STAGE_X_MOVE)->GetWindowTextW(strMove);

	if (strMove == _T("MOVE"))
	{
		CString strVal;
		double TargetVal;
		double ManualSpeed;

		GetDlgItem(IDC_EDIT_STAGE_X_INPUT)->GetWindowTextW(strVal);
		TargetVal = _wtof(strVal);

		GetDlgItem(IDC_EDIT_STAGE_X_SPEED)->GetWindowTextW(strVal);
		ManualSpeed = _wtof(strVal);

		StageMove(0, TargetVal, bChkABS, bChkREL, ManualSpeed);
	}

	// stage break
	else if (strMove == _T("STOP"))
		StageBreak(0);

}


void CJettingVisionDlg::OnBnClickedBtnStageYMove()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strMove;
	GetDlgItem(IDC_BTN_STAGE_Y_MOVE)->GetWindowTextW(strMove);

	if (strMove == _T("MOVE"))
	{
		CString strVal;
		double TargetVal;
		double ManualSpeed;

		GetDlgItem(IDC_EDIT_STAGE_Y_INPUT)->GetWindowTextW(strVal);
		TargetVal = _wtof(strVal);

		GetDlgItem(IDC_EDIT_STAGE_Y_SPEED)->GetWindowTextW(strVal);
		ManualSpeed = _wtof(strVal);

		StageMove(1, TargetVal, bChkABS, bChkREL, ManualSpeed);
	}

	// stage break
	else if (strMove == _T("STOP"))
		StageBreak(1);
}


void CJettingVisionDlg::OnBnClickedBtnStageTMove()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strMove;
	GetDlgItem(IDC_BTN_STAGE_T_MOVE)->GetWindowTextW(strMove);

	if (strMove == _T("MOVE"))
	{
		CString strVal;
		double TargetVal;
		double ManualSpeed;

		GetDlgItem(IDC_EDIT_STAGE_T_INPUT)->GetWindowTextW(strVal);
		TargetVal = _wtof(strVal);

		GetDlgItem(IDC_EDIT_STAGE_T_SPEED)->GetWindowTextW(strVal);
		ManualSpeed = _wtof(strVal);

		StageMove(2, TargetVal, bChkABS, bChkREL, ManualSpeed);
	}

	// stage break
	else if (strMove == _T("STOP"))
		StageBreak(2);
}


void CJettingVisionDlg::OnBnClickedBtnPresetSafety()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BOOL motion_x;
	BOOL motion_y;
	BOOL motion_t;

	// safety position 으로 이동 (x->y->t 순서로)
	m_pAcs->m_pACSMotion[0].MoveAbs(NULL, dlgSettingMotion->dPosSafetyX, NULL);
	do
	{
		motion_x = CACSM::m_pACSMotion[0].IsMoving();
	} while (motion_x == TRUE);

	m_pAcs->m_pACSMotion[1].MoveAbs(NULL, dlgSettingMotion->dPosSafetyY, NULL);
	do
	{
		motion_y = CACSM::m_pACSMotion[1].IsMoving();
	} while (motion_y == TRUE);

	m_pAcs->m_pACSMotion[2].MoveAbs(NULL, dlgSettingMotion->dPosSafetyT, NULL);
	do
	{
		motion_t = CACSM::m_pACSMotion[2].IsMoving();
	} while (motion_t == TRUE);
}


void CJettingVisionDlg::OnBnClickedBtnPresetLoading()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BOOL motion_x;
	BOOL motion_y;
	BOOL motion_t;

	// safety position 으로 이동 (x->y->t 순서로)
	m_pAcs->m_pACSMotion[0].MoveAbs(NULL, dlgSettingMotion->dPosLoadingX, NULL);
	do
	{
		motion_x = CACSM::m_pACSMotion[0].IsMoving();
	} while (motion_x == TRUE);

	m_pAcs->m_pACSMotion[1].MoveAbs(NULL, dlgSettingMotion->dPosLoadingY, NULL);
	do
	{
		motion_y = CACSM::m_pACSMotion[1].IsMoving();
	} while (motion_y == TRUE);

	m_pAcs->m_pACSMotion[2].MoveAbs(NULL, dlgSettingMotion->dPosLoadingT, NULL);
	do
	{
		motion_t = CACSM::m_pACSMotion[2].IsMoving();
	} while (motion_t == TRUE);
}


void CJettingVisionDlg::OnBnClickedBtnPresetAlignLeft()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BOOL motion_x;
	BOOL motion_y;
	BOOL motion_t;

	// safety position 으로 이동 (x->y->t 순서로)
	m_pAcs->m_pACSMotion[0].MoveAbs(NULL, dlgSettingMotion->dPosAlignleftX, NULL);
	do
	{
		motion_x = CACSM::m_pACSMotion[0].IsMoving();
	} while (motion_x == TRUE);

	m_pAcs->m_pACSMotion[1].MoveAbs(NULL, dlgSettingMotion->dPosAlignleftY, NULL);
	do
	{
		motion_y = CACSM::m_pACSMotion[1].IsMoving();
	} while (motion_y == TRUE);

	m_pAcs->m_pACSMotion[2].MoveAbs(NULL, dlgSettingMotion->dPosAlignleftT, NULL);
	do
	{
		motion_t = CACSM::m_pACSMotion[2].IsMoving();
	} while (motion_t == TRUE);
}


void CJettingVisionDlg::OnBnClickedBtnPresetAlignRight()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BOOL motion_x;
	BOOL motion_y;
	BOOL motion_t;

	// safety position 으로 이동 (x->y->t 순서로)
	m_pAcs->m_pACSMotion[0].MoveAbs(NULL, dlgSettingMotion->dPosAlignrightX, NULL);
	do
	{
		motion_x = CACSM::m_pACSMotion[0].IsMoving();
	} while (motion_x == TRUE);

	m_pAcs->m_pACSMotion[1].MoveAbs(NULL, dlgSettingMotion->dPosAlignrightY, NULL);
	do
	{
		motion_y = CACSM::m_pACSMotion[1].IsMoving();
	} while (motion_y == TRUE);

	m_pAcs->m_pACSMotion[2].MoveAbs(NULL, dlgSettingMotion->dPosAlignrightT, NULL);
	do
	{
		motion_t = CACSM::m_pACSMotion[2].IsMoving();
	} while (motion_t == TRUE);
}


void CJettingVisionDlg::OnBnClickedBtnPresetProcStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BOOL motion_x;
	BOOL motion_y;
	BOOL motion_t;

	// safety position 으로 이동 (x->y->t 순서로)
	m_pAcs->m_pACSMotion[0].MoveAbs(NULL, dlgSettingMotion->dPosProcstartX, NULL);
	do
	{
		motion_x = CACSM::m_pACSMotion[0].IsMoving();
	} while (motion_x == TRUE);

	m_pAcs->m_pACSMotion[1].MoveAbs(NULL, dlgSettingMotion->dPosProcstartY, NULL);
	do
	{
		motion_y = CACSM::m_pACSMotion[1].IsMoving();
	} while (motion_y == TRUE);

	m_pAcs->m_pACSMotion[2].MoveAbs(NULL, dlgSettingMotion->dPosProcstartT, NULL);
	do
	{
		motion_t = CACSM::m_pACSMotion[2].IsMoving();
	} while (motion_t == TRUE);
}


void CJettingVisionDlg::OnBnClickedBtnPresetProcEnd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BOOL motion_x;
	BOOL motion_y;
	BOOL motion_t;

	// safety position 으로 이동 (x->y->t 순서로)
	m_pAcs->m_pACSMotion[0].MoveAbs(NULL, dlgSettingMotion->dPosProcendX, NULL);
	do
	{
		motion_x = CACSM::m_pACSMotion[0].IsMoving();
	} while (motion_x == TRUE);

	m_pAcs->m_pACSMotion[1].MoveAbs(NULL, dlgSettingMotion->dPosProcendY, NULL);
	do
	{
		motion_y = CACSM::m_pACSMotion[1].IsMoving();
	} while (motion_y == TRUE);

	m_pAcs->m_pACSMotion[2].MoveAbs(NULL, dlgSettingMotion->dPosProcendT, NULL);
	do
	{
		motion_t = CACSM::m_pACSMotion[2].IsMoving();
	} while (motion_t == TRUE);
}


void CJettingVisionDlg::OnBnClickedBtnPresetReview()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BOOL motion_x;
	BOOL motion_y;
	BOOL motion_t;

	// safety position 으로 이동 (x->y->t 순서로)
	m_pAcs->m_pACSMotion[0].MoveAbs(NULL, dlgSettingMotion->dPosReviewX, NULL);
	do
	{
		motion_x = CACSM::m_pACSMotion[0].IsMoving();
	} while (motion_x == TRUE);

	m_pAcs->m_pACSMotion[1].MoveAbs(NULL, dlgSettingMotion->dPosReviewY, NULL);
	do
	{
		motion_y = CACSM::m_pACSMotion[1].IsMoving();
	} while (motion_y == TRUE);

	m_pAcs->m_pACSMotion[2].MoveAbs(NULL, dlgSettingMotion->dPosReviewT, NULL);
	do
	{
		motion_t = CACSM::m_pACSMotion[2].IsMoving();
	} while (motion_t == TRUE);
}


void CJettingVisionDlg::OnBnClickedBtnPresetUnloading()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BOOL motion_x;
	BOOL motion_y;
	BOOL motion_t;

	// safety position 으로 이동 (x->y->t 순서로)
	m_pAcs->m_pACSMotion[0].MoveAbs(NULL, dlgSettingMotion->dPosUnloadingX, NULL);
	do
	{
		motion_x = CACSM::m_pACSMotion[0].IsMoving();
	} while (motion_x == TRUE);

	m_pAcs->m_pACSMotion[1].MoveAbs(NULL, dlgSettingMotion->dPosUnloadingY, NULL);
	do
	{
		motion_y = CACSM::m_pACSMotion[1].IsMoving();
	} while (motion_y == TRUE);

	m_pAcs->m_pACSMotion[2].MoveAbs(NULL, dlgSettingMotion->dPosUnloadingT, NULL);
	do
	{
		motion_t = CACSM::m_pACSMotion[2].IsMoving();
	} while (motion_t == TRUE);
}


void CJettingVisionDlg::OnBnClickedBtnAuto()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// Gap 측정 초기화
	// Align 측정 초기화
	nAlignCount = 0;
	nGapCount = 0;

	if (dlgSettingVision->nGapCount == 1)
		dGapStep = 0;

	else if (dlgSettingVision->nGapCount > 1)
		dGapStep = (dlgSettingMotion->dPosGapendY - dlgSettingMotion->dPosGapstartY) / (dlgSettingVision->nGapCount - 1);

	dGapSum = 0;
	dGapAvg = 0;

	pAlignLeft = { 0,0 };
	pAlignRight = { 0,0 };

	dAlignModifyX = 0.0;
	dAlignModifyY = 0.0;
	dAlignModifyT = 0.0;

	m_pAcs->m_pACSMotion[0].m_movingVelocity = dlgSettingMotion->dMovingSpeedX;
	m_pAcs->m_pACSMotion[0].SetVelocityMoving(NULL);

	m_pAcs->m_pACSMotion[1].m_movingVelocity = dlgSettingMotion->dMovingSpeedY;
	m_pAcs->m_pACSMotion[1].SetVelocityMoving(NULL);

	m_pAcs->m_pACSMotion[2].m_movingVelocity = dlgSettingMotion->dMovingSpeedT;
	m_pAcs->m_pACSMotion[2].SetVelocityMoving(NULL);

	// 공정 순서
	m_ProcSeq = eProcSeq::MoveSafetyPos;
	m_AlignResult = eAlignResult::BEFORE;

	bProcStart = TRUE;		// 동작 
	bProcStop = FALSE;		// 정지
	bProcPause = FALSE;		// 공정 중 대기
	bProcReview = FALSE;

	CTime strCreateTime = CTime::GetCurrentTime();
	CString strPath;

	if (bChkAlign == TRUE)
	{
		strYearPath.Format(_T("D:\\JettingVision\\Data\\Alignment\\%04d"), strCreateTime.GetYear());
		CreateDirectory(strYearPath, NULL);

		strPath.Format(_T("\\%02d%02d"), strCreateTime.GetMonth(), strCreateTime.GetDay());
		strDayPath = strYearPath + strPath;
		CreateDirectory(strDayPath, NULL);

		strTimePath.Format(_T("\\_%02d%02d%02d"), strCreateTime.GetHour(), strCreateTime.GetMinute(), strCreateTime.GetSecond());
		strAlignPath = strDayPath + strTimePath;
		CreateDirectory(strAlignPath, NULL);

		strAlignBeforePath = strAlignPath + _T("\\1. Before");
		CreateDirectory(strAlignBeforePath, NULL);

		strAlignAfterPath = strAlignPath + _T("\\2. After");
		CreateDirectory(strAlignAfterPath, NULL);
	}

	//m_baumer->folder_name = proc_time;
	//m_baumer->before_align = before_align;
	//m_baumer->after_align = after_align;

	//// MOTOR 가 전부 ENABLE 상태에서

	//// Home Done 이 되어 있는 상태일 경우에

	//// 값이 전부 Read 되어 있고

	//// 이동하는 값이 LIMIT를 넘지 않은 경우에만 실행
}


void CJettingVisionDlg::OnBnClickedBtnPause()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (bProcPause == TRUE)
		bProcPause = FALSE;

	else if (bProcPause == FALSE)
		bProcPause = TRUE;

}


void CJettingVisionDlg::OnBnClickedBtnStop()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다
	bProcStart = FALSE;
	bProcStop = TRUE;
}


void CJettingVisionDlg::OnBnClickedBtnOrigin()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CJettingVisionDlg::OnBnClickedBtnAlarm()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CJettingVisionDlg::OnBnClickedBtnReset()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CJettingVisionDlg::OnBnClickedBtnExit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	AlarmMessageDisplay(_T("Window 를 종료하시겠습니까?"), 6);
}


void CJettingVisionDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent == 1)
	{
		GetMotorMoving();
		GetMotorStatus();
		GetHomeStatus();
		//GetAPos();
		GetVelocity();
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CJettingVisionDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	if (Vision != NULL)
	{
		for (int i = 0; i < CamCount; i++)
		{
			if (cBaumer->Status[i] == true)
			{
				cBaumer->m_camera_set[i].pDataStreamf->UnregisterNewBufferEvent();
			}
		}

		Vision->SuspendThread();

		DWORD dwResult;
		::GetExitCodeThread(Vision->m_hThread, &dwResult);
		delete Vision;
		Vision = NULL;

		delete cBaumer;
	}

	if (Proc != NULL)
	{
		Proc->SuspendThread();

		DWORD dwResult;
		::GetExitCodeThread(Proc->m_hThread, &dwResult);
		delete Proc;
		Proc = NULL;
	}

	if (Cycle != NULL)
	{
		Cycle->SuspendThread();

		DWORD dwResult;
		::GetExitCodeThread(Cycle->m_hThread, &dwResult);
		delete Cycle;
		Cycle = NULL;
	}

	SetVisionLight(3);

	ControlVisionLight(0);

	CString strRecipe;
	strRecipe.Format(_T("%d"), SelectRecipe);
	AfxGetApp()->WriteProfileStringW(_T("Recipe"), _T("Last Recipe"), strRecipe);
}


UINT CJettingVisionDlg::Vision_Thread(LPVOID pParam)
{
	CJettingVisionDlg* dlg_vision = (CJettingVisionDlg*)pParam;

	while (1)
	{
		if (dlg_vision->cBaumer->Status[0] == true)
		{
			if (dlg_vision->cBaumer->m_camera_set[0].m_updisplay == 1)
				dlg_vision->DisplayCam_0();
		}

		if (dlg_vision->cBaumer->Status[1] == true)
		{
			if (dlg_vision->cBaumer->m_camera_set[1].m_updisplay == 1)
				dlg_vision->DisplayCam_1();
		}
	}
	return 0;
}


UINT CJettingVisionDlg::Proc_Thread(LPVOID pParam)
{
	CJettingVisionDlg* dlg_proc = (CJettingVisionDlg*)pParam;

	BOOL motion_x;
	BOOL motion_y;
	BOOL motion_t;

	while (1)
	{
		while (dlg_proc->bProcStart == TRUE)
		{
			switch (dlg_proc->m_ProcSeq)
			{
			case MoveSafetyPos:

				dlg_proc->GetDlgItem(IDC_EDIT_PROC_STEP)->SetWindowTextW(_T("Move Safety Pos"));
				// safety position 으로 이동 (x->y->t 순서로)
				dlg_proc->m_pAcs->m_pACSMotion[0].MoveAbs(NULL, dlg_proc->dlgSettingMotion->dPosSafetyX, NULL);
				do
				{
					motion_x = CACSM::m_pACSMotion[0].IsMoving();
				} while (motion_x == TRUE);

				dlg_proc->m_pAcs->m_pACSMotion[1].MoveAbs(NULL, dlg_proc->dlgSettingMotion->dPosSafetyY, NULL);
				do
				{
					motion_y = CACSM::m_pACSMotion[1].IsMoving();
				} while (motion_y == TRUE);

				dlg_proc->m_pAcs->m_pACSMotion[2].MoveAbs(NULL, dlg_proc->dlgSettingMotion->dPosSafetyT, NULL);
				do
				{
					motion_t = CACSM::m_pACSMotion[2].IsMoving();
				} while (motion_t == TRUE);

				dlg_proc->m_ProcSeq = eProcSeq::SafetyPosComplete;
				break;

			case SafetyPosComplete:

				// 일시정지 상태가 아니라면 다음 공정으로 진행
				// align 진행 유무에 따라 align 또는 align complete 위치로 이동

				dlg_proc->GetDlgItem(IDC_EDIT_PROC_STEP)->SetWindowTextW(_T("Safety Pos Complete"));

				if (dlg_proc->bProcPause == FALSE)
				{
					if (dlg_proc->bChkAlign == true)
						dlg_proc->m_ProcSeq = eProcSeq::MoveLeftAlignPos;

					else if (dlg_proc->bChkAlign == false)
						dlg_proc->m_ProcSeq = eProcSeq::AlignmentComplete;
				}

				else
					dlg_proc->GetDlgItem(IDC_EDIT_PROC_STEP)->SetWindowTextW(_T("일시 정지"));

				break;

			case MoveLeftAlignPos:

				if (dlg_proc->m_AlignResult == eAlignResult::BEFORE)
					dlg_proc->GetDlgItem(IDC_EDIT_PROC_STEP)->SetWindowTextW(_T("Move Left Align Pos(1st)"));

				else if (dlg_proc->m_AlignResult == eAlignResult::AFTER)
					dlg_proc->GetDlgItem(IDC_EDIT_PROC_STEP)->SetWindowTextW(_T("Move Left Align Pos(2nd)"));

				// align 위치로 이동 (left 먼저) 
				// 동작 순서는 Theta->x->y로
				dlg_proc->m_pAcs->m_pACSMotion[2].MoveAbs(NULL, dlg_proc->dlgSettingMotion->dPosAlignleftT + dlg_proc->dAlignModifyT, NULL);
				do
				{
					motion_t = CACSM::m_pACSMotion[2].IsMoving();
				} while (motion_t == TRUE);

				dlg_proc->m_pAcs->m_pACSMotion[0].MoveAbs(NULL, dlg_proc->dlgSettingMotion->dPosAlignleftX + dlg_proc->dAlignModifyX, NULL);
				do
				{
					motion_x = CACSM::m_pACSMotion[0].IsMoving();
				} while (motion_x == TRUE);

				dlg_proc->m_pAcs->m_pACSMotion[1].MoveAbs(NULL, dlg_proc->dlgSettingMotion->dPosAlignleftY + dlg_proc->dAlignModifyY, NULL);
				do
				{
					motion_y = CACSM::m_pACSMotion[1].IsMoving();
				} while (motion_y == TRUE);

				dlg_proc->m_ProcSeq = eProcSeq::LeftAlignPosComplete;
				break;

			case LeftAlignPosComplete:

				Sleep(500);

				// 일시정지 상태라면 멈추어라
				// 아니라면 이미지를 지정된 폴더에 저장하고 다음 align 위치로 이동
				if (dlg_proc->bProcPause == FALSE)
				{
					if (dlg_proc->m_AlignResult == eAlignResult::BEFORE)
					{
						dlg_proc->ImageSave(true, false, true, false);
						dlg_proc->ImageAlignment(true, false);
						dlg_proc->m_ProcSeq = eProcSeq::MoveRightAlignPos;
					}

					else if (dlg_proc->m_AlignResult == eAlignResult::AFTER)
					{
						dlg_proc->ImageSave(true, false, false, true);
						dlg_proc->ImageAlignment(true, false);
						dlg_proc->m_ProcSeq = eProcSeq::MoveRightAlignPos;
					}
				}

				else
					dlg_proc->GetDlgItem(IDC_EDIT_PROC_STEP)->SetWindowTextW(_T("일시 정지"));

				break;

			case MoveRightAlignPos:

				if (dlg_proc->m_AlignResult == eAlignResult::BEFORE)
					dlg_proc->GetDlgItem(IDC_EDIT_PROC_STEP)->SetWindowTextW(_T("Move Right Align Pos(1st)"));

				else if (dlg_proc->m_AlignResult == eAlignResult::AFTER)
					dlg_proc->GetDlgItem(IDC_EDIT_PROC_STEP)->SetWindowTextW(_T("Move Right Align Pos(2nd)"));

				// align 진행 시 y축 값만 이동을 한다. 
				dlg_proc->m_pAcs->m_pACSMotion[1].MoveAbs(NULL, dlg_proc->dlgSettingMotion->dPosAlignrightY + dlg_proc->dAlignModifyY, NULL);
				do
				{
					motion_y = CACSM::m_pACSMotion[1].IsMoving();
				} while (motion_y == TRUE);

				dlg_proc->m_ProcSeq = eProcSeq::RightAlignPosComplete;

				break;

			case RightAlignPosComplete:

				Sleep(500);

				// 일시정지 상태라면 멈추어라
				// 아니라면 이미지를 저장하고 align을 진행하여라
				if (dlg_proc->bProcPause == FALSE)
				{
					if (dlg_proc->m_AlignResult == eAlignResult::BEFORE)
					{
						dlg_proc->ImageSave(false, true, true, false);
						dlg_proc->ImageAlignment(false, true);
					}


					else if (dlg_proc->m_AlignResult == eAlignResult::AFTER)
					{
						dlg_proc->ImageSave(false, true, false, true);
						dlg_proc->ImageAlignment(false, true);
					}
				}

				else
					dlg_proc->GetDlgItem(IDC_EDIT_PROC_STEP)->SetWindowTextW(_T("일시 정지"));

				dlg_proc->m_ProcSeq = eProcSeq::Alignment;

				break;

			case Alignment:

				// 일시정지 상태라면 멈추어라
				// 획득한 이미지를 이용하여 ALIGN을 진행하고 
				// 확인한 ALIGN OK 판정 범위 이내인 경우 그대로 진행
				// OK 판정 범위보다는 크지만 ALIGN 보정 범위보다 작을때는 해당 수치만큼 이동
				// OK 판정 범위보다 작을 때 까지 ALIGN 진행
				// ALIGN 보정 범위보다 큰 경우 NG로 판정을 하고 사용자가 판단할 수 있게


				if (dlg_proc->bProcPause == FALSE)
				{
					dlg_proc->GetDlgItem(IDC_EDIT_PROC_STEP)->SetWindowTextW(_T("Alignment Calcuration"));

					dlg_proc->AlignCalcuration();

					if (dlg_proc->m_AlignResult == eAlignResult::BEFORE)
					{
						dlg_proc->m_ProcSeq = eProcSeq::MoveLeftAlignPos;
						dlg_proc->m_AlignResult = eAlignResult::AFTER;
					}

					else if (dlg_proc->m_AlignResult == eAlignResult::AFTER)
						dlg_proc->m_ProcSeq = eProcSeq::AlignmentComplete;
				}

				else
					dlg_proc->GetDlgItem(IDC_EDIT_PROC_STEP)->SetWindowTextW(_T("일시 정지"));

				break;

			case AlignmentComplete:

				// 일시정지 상태라면 멈추어라
				// GAP 측정 유무에 따라 GAP 위치 또는 GAP COMPLETE로 이동

				if (dlg_proc->bChkAlign == false)
				{
					dlg_proc->m_pAcs->m_pACSMotion[2].MoveAbs(NULL, dlg_proc->dlgSettingMotion->dPosAlignleftT, NULL);
					do
					{
						motion_t = CACSM::m_pACSMotion[2].IsMoving();
					} while (motion_t == TRUE);

					dlg_proc->m_pAcs->m_pACSMotion[0].MoveAbs(NULL, dlg_proc->dlgSettingMotion->dPosAlignleftX, NULL);
					do
					{
						motion_x = CACSM::m_pACSMotion[0].IsMoving();
					} while (motion_x == TRUE);

					dlg_proc->m_pAcs->m_pACSMotion[1].MoveAbs(NULL, dlg_proc->dlgSettingMotion->dPosAlignleftY, NULL);
					do
					{
						motion_y = CACSM::m_pACSMotion[1].IsMoving();
					} while (motion_y == TRUE);
				}

				if (dlg_proc->bProcPause == FALSE)
				{
					if (dlg_proc->bChkGap == true)
						dlg_proc->m_ProcSeq = eProcSeq::MoveGapPosition;

					else if (dlg_proc->bChkGap == false)
						dlg_proc->m_ProcSeq = eProcSeq::GapComplete;
				}

				else
					dlg_proc->GetDlgItem(IDC_EDIT_PROC_STEP)->SetWindowTextW(_T("일시 정지"));

				break;

			case MoveGapPosition:

				dlg_proc->GetDlgItem(IDC_EDIT_PROC_STEP)->SetWindowTextW(_T("Move Gap Measurement Pos"));

				// Gap Count 만큼 위치를 이동하고 GAP 측정을 진행
				if (dlg_proc->nGapCount == 0)
				{
					dlg_proc->m_pAcs->m_pACSMotion[1].MoveAbs(NULL, dlg_proc->dlgSettingMotion->dPosGapstartY + dlg_proc->dAlignModifyY, NULL);
					do
					{
						motion_y = CACSM::m_pACSMotion[1].IsMoving();
					} while (motion_y == TRUE);
				}

				else if (dlg_proc->nGapCount > 0 && dlg_proc->nGapCount < dlg_proc->dlgSettingVision->nGapCount - 1)
				{
					dlg_proc->m_pAcs->m_pACSMotion[1].MoveAbs(NULL, dlg_proc->dlgSettingMotion->dPosGapstartY + dlg_proc->dAlignModifyY + dlg_proc->dGapStep * dlg_proc->nGapCount, NULL);
					do
					{
						motion_y = CACSM::m_pACSMotion[1].IsMoving();
					} while (motion_y == TRUE);
				}

				else if (dlg_proc->nGapCount == dlg_proc->dlgSettingVision->nGapCount - 1)
				{
					dlg_proc->m_pAcs->m_pACSMotion[1].MoveAbs(NULL, dlg_proc->dlgSettingMotion->dPosGapendY + dlg_proc->dAlignModifyY, NULL);
					do
					{
						motion_y = CACSM::m_pACSMotion[1].IsMoving();
					} while (motion_y == TRUE);
				}

				dlg_proc->m_ProcSeq = eProcSeq::GapMeasure;

				break;

			case GapMeasure:

				dlg_proc->GetDlgItem(IDC_EDIT_PROC_STEP)->SetWindowTextW(_T("Gap Measurement"));

				// Gap Count만큼 측정을 하고
				// 전부 다 측정한 다음 Gap Avg 값을 계산하고
				if (dlg_proc->nGapCount < dlg_proc->dlgSettingVision->nGapCount)
				{
					dlg_proc->nGapCount++;
					dlg_proc->GapMeasurement(dlg_proc->nGapCount);

					dlg_proc->m_ProcSeq = eProcSeq::MoveGapPosition;
				}

				else if (dlg_proc->nGapCount == dlg_proc->dlgSettingVision->nGapCount)
				{
					dlg_proc->m_ProcSeq = eProcSeq::GapComplete;
				}

				break;

			case GapComplete:

				// gap 범위를 기준으로 판단한다.
				// 또한 Process 유무에 따라 ProcPos 또는 ProcComplete로 이동

				if (dlg_proc->bProcPause == FALSE)
				{
					if (dlg_proc->bChkJetting == true)
						dlg_proc->m_ProcSeq = eProcSeq::MoveProcPosition;

					else if (dlg_proc->bChkJetting == false)
						dlg_proc->m_ProcSeq = eProcSeq::ProcComplete;
				}

				else
					dlg_proc->GetDlgItem(IDC_EDIT_PROC_STEP)->SetWindowTextW(_T("일시 정지"));

				break;

			case MoveProcPosition:

				dlg_proc->GetDlgItem(IDC_EDIT_PROC_STEP)->SetWindowTextW(_T("Move Process Pos"));

				// Y만 이동
				dlg_proc->m_pAcs->m_pACSMotion[1].MoveAbs(NULL, dlg_proc->dlgSettingMotion->dPosProcstartY + dlg_proc->dAlignModifyY, NULL);
				do
				{
					motion_y = CACSM::m_pACSMotion[1].IsMoving();
				} while (motion_y == TRUE);

				dlg_proc->m_ProcSeq = eProcSeq::ProcPositionComplete;

				break;

			case ProcPositionComplete:

				// 일시정지 상태라면 멈추어라
				// Stage 이동 속도는 Jetting 속도로 변경하고
				// UV 유무 확인하여라

				if (dlg_proc->bProcPause == FALSE)
				{
					dlg_proc->GetDlgItem(IDC_EDIT_PROC_STEP)->SetWindowTextW(_T("Moving Speed Change (For Jetting)"));

					dlg_proc->m_pAcs->m_pACSMotion[0].m_jettingVelocity = dlg_proc->dlgSettingMotion->dJettingSpeedX;
					dlg_proc->m_pAcs->m_pACSMotion[0].SetVelocityJetting(NULL);

					dlg_proc->m_pAcs->m_pACSMotion[1].m_jettingVelocity = dlg_proc->dlgSettingMotion->dJettingSpeedY;
					dlg_proc->m_pAcs->m_pACSMotion[1].SetVelocityJetting(NULL);

					dlg_proc->m_pAcs->m_pACSMotion[2].m_jettingVelocity = dlg_proc->dlgSettingMotion->dJettingSpeedT;
					dlg_proc->m_pAcs->m_pACSMotion[2].SetVelocityJetting(NULL);

					if (dlg_proc->bChkUVLED == true)
						dlg_proc->SetUV(TRUE);
				}

				else
					dlg_proc->GetDlgItem(IDC_EDIT_PROC_STEP)->SetWindowTextW(_T("일시 정지"));

				dlg_proc->m_ProcSeq = eProcSeq::Processing;

				break;

			case Processing:

				dlg_proc->GetDlgItem(IDC_EDIT_PROC_STEP)->SetWindowTextW(_T("Processing.."));

				// jetting 유무에 따라 판단한다. 
				// jetting 영역은 Recipe 상에 있는 offset, length 값을 기반으로 peg 설정을 한다. 
				if (dlg_proc->bChkJetting == true)
				{
					dlg_proc->SetJetting();
				}

				// Y만 이동
				dlg_proc->m_pAcs->m_pACSMotion[1].MoveAbs(NULL, dlg_proc->dlgSettingMotion->dPosProcendY + dlg_proc->dAlignModifyY, NULL);
				do
				{
					motion_y = CACSM::m_pACSMotion[1].IsMoving();
				} while (motion_y == TRUE);

				dlg_proc->m_ProcSeq = eProcSeq::ProcComplete;

				break;

			case ProcComplete:

				if (dlg_proc->bProcPause == FALSE)
				{
					dlg_proc->GetDlgItem(IDC_EDIT_PROC_STEP)->SetWindowTextW(_T("Process Complete"));

					dlg_proc->m_pAcs->m_pACSMotion[0].m_jettingVelocity = dlg_proc->dlgSettingMotion->dMovingSpeedX;
					dlg_proc->m_pAcs->m_pACSMotion[0].SetVelocityJetting(NULL);

					dlg_proc->m_pAcs->m_pACSMotion[1].m_jettingVelocity = dlg_proc->dlgSettingMotion->dMovingSpeedY;
					dlg_proc->m_pAcs->m_pACSMotion[1].SetVelocityJetting(NULL);

					dlg_proc->m_pAcs->m_pACSMotion[2].m_jettingVelocity = dlg_proc->dlgSettingMotion->dMovingSpeedT;
					dlg_proc->m_pAcs->m_pACSMotion[2].SetVelocityJetting(NULL);

					if (dlg_proc->bChkUVLED == true)
						dlg_proc->SetUV(FALSE);

					if (dlg_proc->bChkReview == true)
						dlg_proc->m_ProcSeq = eProcSeq::MoveReviewPositoin;

					else if (dlg_proc->bChkReview == false)
						dlg_proc->m_ProcSeq = eProcSeq::ReviewComplete;
				}

				else
					dlg_proc->GetDlgItem(IDC_EDIT_PROC_STEP)->SetWindowTextW(_T("일시 정지"));

				break;

			case MoveReviewPositoin:

				dlg_proc->GetDlgItem(IDC_EDIT_PROC_STEP)->SetWindowTextW(_T("Move Review Pos"));

				// review position 으로 이동 (x->y->t 순서로)
				dlg_proc->m_pAcs->m_pACSMotion[0].MoveAbs(NULL, dlg_proc->dlgSettingMotion->dPosReviewX, NULL);
				do
				{
					motion_x = CACSM::m_pACSMotion[0].IsMoving();
				} while (motion_x == TRUE);

				dlg_proc->m_pAcs->m_pACSMotion[1].MoveAbs(NULL, dlg_proc->dlgSettingMotion->dPosReviewY, NULL);
				do
				{
					motion_y = CACSM::m_pACSMotion[1].IsMoving();
				} while (motion_y == TRUE);

				dlg_proc->m_pAcs->m_pACSMotion[2].MoveAbs(NULL, dlg_proc->dlgSettingMotion->dPosReviewT, NULL);
				do
				{
					motion_t = CACSM::m_pACSMotion[2].IsMoving();
				} while (motion_t == TRUE);


				dlg_proc->m_ProcSeq = eProcSeq::ReviewPositionComplete;

				break;

			case ReviewPositionComplete:

				dlg_proc->bProcReview = TRUE;
				dlg_proc->GetDlgItem(IDC_BTN_REVIEW_COMPLETE)->EnableWindow(true);
				dlg_proc->m_ProcSeq = eProcSeq::ReviewComplete;

				break;

			case ReviewComplete:

				dlg_proc->GetDlgItem(IDC_EDIT_PROC_STEP)->SetWindowTextW(_T("Image Review"));

				if (dlg_proc->bProcReview == FALSE)
				{
					dlg_proc->GetDlgItem(IDC_EDIT_PROC_STEP)->SetWindowTextW(_T("Image Review Complete"));

					dlg_proc->GetDlgItem(IDC_BTN_REVIEW_COMPLETE)->EnableWindow(false);
					dlg_proc->m_ProcSeq = eProcSeq::MoveUnloadingPosition;
				}


				break;

			case MoveUnloadingPosition:

				dlg_proc->GetDlgItem(IDC_EDIT_PROC_STEP)->SetWindowTextW(_T("Move Unloading Pos"));

				dlg_proc->m_pAcs->m_pACSMotion[0].MoveAbs(NULL, dlg_proc->dlgSettingMotion->dPosUnloadingX, NULL);
				do
				{
					motion_x = CACSM::m_pACSMotion[0].IsMoving();
				} while (motion_x == TRUE);

				dlg_proc->m_pAcs->m_pACSMotion[1].MoveAbs(NULL, dlg_proc->dlgSettingMotion->dPosUnloadingY, NULL);
				do
				{
					motion_y = CACSM::m_pACSMotion[1].IsMoving();
				} while (motion_y == TRUE);

				dlg_proc->m_pAcs->m_pACSMotion[2].MoveAbs(NULL, dlg_proc->dlgSettingMotion->dPosUnloadingT, NULL);
				do
				{
					motion_t = CACSM::m_pACSMotion[2].IsMoving();
				} while (motion_t == TRUE);

				dlg_proc->m_ProcSeq = eProcSeq::UnloadingComplete;

				break;

			case UnloadingComplete:

				dlg_proc->GetDlgItem(IDC_EDIT_PROC_STEP)->SetWindowTextW(_T("Unloading Pos Complete"));

				dlg_proc->bProcStart = FALSE;
				dlg_proc->bProcStop = TRUE;

				break;
			}
		}
	}

	return 0;
}

void CJettingVisionDlg::MovingCycleStart()
{
	/*BOOL motion_x;
	BOOL motion_y;

	m_pAcs->m_pACSMotion[1].MoveAbs(NULL, dlgCycle->dYStart, NULL);
	do
	{
		motion_y = CACSM::m_pACSMotion[1].IsMoving();
	} while (motion_y == TRUE);

	m_pAcs->m_pACSMotion[0].MoveAbs(NULL, dlgCycle->dXStart, NULL);
	do
	{
		motion_x = CACSM::m_pACSMotion[0].IsMoving();
	} while (motion_x == TRUE);*/

	AlarmMessageDisplay(_T("CYCLE 동작을 시작하시겠습니까?"), 7);

}


UINT CJettingVisionDlg::Cycle_Thread(LPVOID pParam)
{
	CJettingVisionDlg* dlg_cycle = (CJettingVisionDlg*)pParam;

	BOOL motion_x;
	BOOL motion_y;

	while (1)
	{
		while (dlg_cycle->bCycleStart == TRUE && dlg_cycle->nCycle < dlg_cycle->dlgCycle->nXCount)
		{
			switch (dlg_cycle->nCycle % 2)
			{
			case 0:
				// 시작 위치로 이동

				dlg_cycle->m_pAcs->m_pACSMotion[1].MoveAbs(NULL, dlg_cycle->dlgCycle->dYEnd, NULL);
				do
				{
					motion_y = CACSM::m_pACSMotion[1].IsMoving();
				} while (motion_y == TRUE);

				Sleep(dlg_cycle->dlgCycle->dYDelay * 1000);

				if (dlg_cycle->nCycle != dlg_cycle->dlgCycle->nXCount - 1)
				{
					dlg_cycle->m_pAcs->m_pACSMotion[0].MoveAbs(NULL, dlg_cycle->dlgCycle->dXStart + (dlg_cycle->nCycle + 1) * dlg_cycle->dlgCycle->dXShift, NULL);
					do
					{
						motion_x = CACSM::m_pACSMotion[0].IsMoving();
					} while (motion_x == TRUE);

					Sleep(dlg_cycle->dlgCycle->dXDelay * 1000);
				}

				else if (dlg_cycle->nCycle == dlg_cycle->dlgCycle->nXCount - 1)
				{
					dlg_cycle->bCycleStart = false;
				}
				
				dlg_cycle->nCycle++;
				break;

			case 1:

				dlg_cycle->m_pAcs->m_pACSMotion[1].MoveAbs(NULL, dlg_cycle->dlgCycle->dYStart, NULL);
				do
				{
					motion_y = CACSM::m_pACSMotion[1].IsMoving();
				} while (motion_y == TRUE);

				Sleep(dlg_cycle->dlgCycle->dYDelay * 1000);

				if (dlg_cycle->nCycle != dlg_cycle->dlgCycle->nXCount - 1)
				{
					dlg_cycle->m_pAcs->m_pACSMotion[0].MoveAbs(NULL, dlg_cycle->dlgCycle->dXStart + (dlg_cycle->nCycle + 1) * dlg_cycle->dlgCycle->dXShift, NULL);
					do
					{
						motion_x = CACSM::m_pACSMotion[0].IsMoving();
					} while (motion_x == TRUE);
					
					Sleep(dlg_cycle->dlgCycle->dXDelay * 1000);
				}

				else if (dlg_cycle->nCycle == dlg_cycle->dlgCycle->nXCount - 1)
				{
					dlg_cycle->bCycleStart = false;
				}

				dlg_cycle->nCycle++;
				break;
			}

		}
	}
}

void BGAPI2CALL BufferHandler1(void* callBackOwner, Buffer* pBufferFilled)
{
	if (pBufferFilled == NULL)
	{

	}
	else if (pBufferFilled->GetIsIncomplete() == true)
	{

		pBufferFilled->QueueBuffer();
	}
	else if (pBufferFilled->GetIsIncomplete() == false)
	{
		g_pDialog->cBaumer->m_camera_set[0].m_buf = pBufferFilled->GetMemPtr();
		g_pDialog->cBaumer->m_camera_set[0].m_updisplay = 1;
		g_pDialog->Invalidate(FALSE);
		pBufferFilled->QueueBuffer();
	}
	return;
}

void BGAPI2CALL BufferHandler2(void* callBackOwner, Buffer* pBufferFilled)
{
	if (pBufferFilled == NULL)
	{

	}
	else if (pBufferFilled->GetIsIncomplete() == true)
	{

		pBufferFilled->QueueBuffer();
	}
	else if (pBufferFilled->GetIsIncomplete() == false)
	{
		g_pDialog->cBaumer->m_camera_set[1].m_buf = pBufferFilled->GetMemPtr();
		g_pDialog->cBaumer->m_camera_set[1].m_updisplay = 1;
		g_pDialog->Invalidate(FALSE);
		pBufferFilled->QueueBuffer();
	}
	return;
}

void CJettingVisionDlg::DisplayCam_0()
{
	CClientDC dc(dlgViewerCam1->GetDlgItem(IDC_PIC_CAM));
	CDC memDC;
	CBitmap* pOldBitmap, bitmap;
	CRect rect;

	cBaumer->m_camera_set[0].m_updisplay = 0;

	memDC.CreateCompatibleDC(&dc);
	dlgViewerCam1->GetDlgItem(IDC_PIC_CAM)->GetClientRect(&rect);
	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.PatBlt(0, 0, rect.Width(), rect.Height(), BLACKNESS);

	DisplayDrawAlign(&memDC, 0);

	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
	memDC.SelectObject(pOldBitmap);

	memDC.DeleteDC();
	bitmap.DeleteObject();
}


void CJettingVisionDlg::DisplayCam_1()
{
	CClientDC dc(dlgViewerCam2->GetDlgItem(IDC_PIC_CAM));
	CDC memDC;
	CBitmap* pOldBitmap, bitmap;
	CRect rect;

	cBaumer->m_camera_set[0].m_updisplay = 0;

	memDC.CreateCompatibleDC(&dc);
	dlgViewerCam2->GetDlgItem(IDC_PIC_CAM)->GetClientRect(&rect);
	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.PatBlt(0, 0, rect.Width(), rect.Height(), BLACKNESS);

	DisplayDrawAlign(&memDC, 1);

	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
	memDC.SelectObject(pOldBitmap);

	memDC.DeleteDC();
	bitmap.DeleteObject();

}


void CJettingVisionDlg::DisplayDrawAlign(CDC* pDC, int nCase)
{
	pDC->SetStretchBltMode(COLORONCOLOR);
	HDC hDC = pDC->GetSafeHdc();

	cBaumer->m_camera_set[nCase].m_pBitmapInfo->bmiHeader.biWidth = cBaumer->m_camera_set[nCase].m_SizeX;
	cBaumer->m_camera_set[nCase].m_pBitmapInfo->bmiHeader.biHeight = -cBaumer->m_camera_set[nCase].m_SizeY;

	int nSrcX = 0;
	int nSrcY = 0;
	int nSrcW = cBaumer->m_camera_set[nCase].m_SizeX;
	int nSrcH = cBaumer->m_camera_set[nCase].m_SizeY;

	int nRatio = 4;

	int nDstX = 0;
	int nDstY = 0;
	int nDstW = nSrcW / nRatio;
	int nDstH = nSrcH / nRatio;

	StretchDIBits(hDC, nDstX, nDstY, nDstW, nDstH, nSrcX, nSrcY, nSrcW, nSrcH,
		cBaumer->m_camera_set[nCase].m_buf, cBaumer->m_camera_set[nCase].m_pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);

	pDC->SelectStockObject(NULL_BRUSH);
}


void CJettingVisionDlg::InitMotion()
{
	m_nMotCnt = MotorCount;
	m_pAcs->m_nMotCnt = MotorCount;

	m_pAcs = new CACSM(this);
	CACSM::InitOnce(MotorCount);

	MotorsReadMap();

	m_pAcs->InitOpen(m_comm_conf);

	int Axis[] = { ACSC_AXIS_1, ACSC_AXIS_3, -1 };
	m_pAcs->Motion_Group(Axis, NULL);
}



BOOL CJettingVisionDlg::MotorsReadMap()
{
	bool		bRet;
	int			nData;
	BOOL		result;
	CString		strPath;
	CString		strTemp;
	CString		strTag;
	CString		strSubTag;
	CString		strData;
	TCHAR		szData[MAX_PATH];


	if (m_nMotCnt < 1)
		return -1;

	strPath = strRecipeFilePath + _T("RecipeStage.ini");
	if (PathFileExists(strPath) == false)
	{
		return FALSE;
	}

	strTag = _T("COMMON_COMM_CONFIG");

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(strTag, _T("IP"), _T("10.0.0.100"), szData, MAX_PATH, strPath);
	strData = szData;
	m_comm_conf.str_ip = strData;

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(strTag, _T("PORT"), _T("701"), szData, MAX_PATH, strPath);
	strData = szData;
	m_comm_conf.n_port = _ttoi(strData);


	for (int i = 0; i < m_nMotCnt; i++)
	{
		strTag.Format(_T("MOTOR%d"), i);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("NAME"), _T("Test"), szData, MAX_PATH, strPath);
		strData = szData;
		m_pAcs->m_pACSMotion[i].m_strMotorName = strData;

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("Velo"), _T("40"), szData, MAX_PATH, strPath);
		strData = szData;
		m_pAcs->m_pACSMotion[i].m_dVelocity = _ttof(strData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("Acc"), _T("400"), szData, MAX_PATH, strPath);
		strData = szData;
		m_pAcs->m_pACSMotion[i].m_dAccel = _ttof(strData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("Decel"), _T("400"), szData, MAX_PATH, strPath);
		strData = szData;
		m_pAcs->m_pACSMotion[i].m_dDecel = _ttof(strData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("KillDecel"), _T("1200"), szData, MAX_PATH, strPath);
		strData = szData;
		m_pAcs->m_pACSMotion[i].m_dKillDecel = _ttof(strData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("Jerk"), _T("1200"), szData, MAX_PATH, strPath);
		strData = szData;
		m_pAcs->m_pACSMotion[i].m_dJerk = _ttof(strData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("Velo LOW"), _T("40"), szData, MAX_PATH, strPath);
		strData = szData;
		m_pAcs->m_pACSMotion[i].m_dLowSpd = _ttof(strData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("Acc LOW"), _T("400"), szData, MAX_PATH, strPath);
		strData = szData;
		m_pAcs->m_pACSMotion[i].m_dLowAcc = _ttof(strData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("Decel LOW"), _T("400"), szData, MAX_PATH, strPath);
		strData = szData;
		m_pAcs->m_pACSMotion[i].m_dLowDecel = _ttof(strData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("KillDecel LOW"), _T("1200"), szData, MAX_PATH, strPath);
		strData = szData;
		m_pAcs->m_pACSMotion[i].m_dLowKillDecel = _ttof(strData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("Jerk LOW"), _T("1200"), szData, MAX_PATH, strPath);
		strData = szData;
		m_pAcs->m_pACSMotion[i].m_dLowJerk = _ttof(strData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("Velo MID"), _T("40"), szData, MAX_PATH, strPath);
		strData = szData;
		m_pAcs->m_pACSMotion[i].m_dMidSpd = _ttof(strData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("Acc MID"), _T("400"), szData, MAX_PATH, strPath);
		strData = szData;
		m_pAcs->m_pACSMotion[i].m_dMidAcc = _ttof(strData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("Decel MID"), _T("400"), szData, MAX_PATH, strPath);
		strData = szData;
		m_pAcs->m_pACSMotion[i].m_dMidDecel = _ttof(strData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("KillDecel MID"), _T("1200"), szData, MAX_PATH, strPath);
		strData = szData;
		m_pAcs->m_pACSMotion[i].m_dMidKillDecel = _ttof(strData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("Jerk MID"), _T("1200"), szData, MAX_PATH, strPath);
		strData = szData;
		m_pAcs->m_pACSMotion[i].m_dMidJerk = _ttof(strData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("Velo HIGH"), _T("40"), szData, MAX_PATH, strPath);
		strData = szData;
		m_pAcs->m_pACSMotion[i].m_dHighSpd = _ttof(strData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("Acc HIGH"), _T("400"), szData, MAX_PATH, strPath);
		strData = szData;
		m_pAcs->m_pACSMotion[i].m_dHighAcc = _ttof(strData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("Decel HIGH"), _T("400"), szData, MAX_PATH, strPath);
		strData = szData;
		m_pAcs->m_pACSMotion[i].m_dHighDecel = _ttof(strData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("KillDecel HIGH"), _T("1200"), szData, MAX_PATH, strPath);
		strData = szData;
		m_pAcs->m_pACSMotion[i].m_dHighKillDecel = _ttof(strData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("Jerk HIGH"), _T("1200"), szData, MAX_PATH, strPath);
		strData = szData;
		m_pAcs->m_pACSMotion[i].m_dHighJerk = _ttof(strData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("MaxSpd"), _T("400"), szData, MAX_PATH, strPath);
		strData = szData;
		m_pAcs->m_pACSMotion[i].m_dMaxSpd = _ttof(strData);

		if (m_pAcs->m_pACSMotion[i].m_strMotorName == _T("Stage_X"))
			dlgSettingMotion->GetDlgItem(IDC_EDIT_MAXSPEED_STAGE_X)->SetWindowTextW(strData);

		else if (m_pAcs->m_pACSMotion[i].m_strMotorName == _T("Stage_Y"))
			dlgSettingMotion->GetDlgItem(IDC_EDIT_MAXSPEED_STAGE_Y)->SetWindowTextW(strData);

		else if (m_pAcs->m_pACSMotion[i].m_strMotorName == _T("Stage_Turn"))
			dlgSettingMotion->GetDlgItem(IDC_EDIT_MAXSPEED_STAGE_T)->SetWindowTextW(strData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("MaxStroke"), _T("800"), szData, MAX_PATH, strPath);
		strData = szData;
		m_pAcs->m_pACSMotion[i].m_dMaxStroke = _ttof(strData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("Max Pos"), _T("800"), szData, MAX_PATH, strPath);
		strData = szData;
		m_pAcs->m_pACSMotion[i].m_dMaxPos = _ttof(strData);

		if (m_pAcs->m_pACSMotion[i].m_strMotorName == _T("Stage_X"))
		{
			GetDlgItem(IDC_EDIT_STAGE_X_LIMIT_MAX)->SetWindowTextW(strData);
			dlgSettingMotion->GetDlgItem(IDC_EDIT_MAXPOS_STAGE_X)->SetWindowTextW(strData);
		}

		else if (m_pAcs->m_pACSMotion[i].m_strMotorName == _T("Stage_Y"))
		{
			GetDlgItem(IDC_EDIT_STAGE_Y_LIMIT_MAX)->SetWindowTextW(strData);
			dlgSettingMotion->GetDlgItem(IDC_EDIT_MAXPOS_STAGE_Y)->SetWindowTextW(strData);
		}

		else if (m_pAcs->m_pACSMotion[i].m_strMotorName == _T("Stage_Turn"))
		{
			GetDlgItem(IDC_EDIT_STAGE_T_LIMIT_MAX)->SetWindowTextW(strData);
			dlgSettingMotion->GetDlgItem(IDC_EDIT_MAXPOS_STAGE_T)->SetWindowTextW(strData);
		}

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("Min Pos"), _T("800"), szData, MAX_PATH, strPath);
		strData = szData;
		m_pAcs->m_pACSMotion[i].m_dMinPos = _ttof(strData);

		if (m_pAcs->m_pACSMotion[i].m_strMotorName == _T("Stage_X"))
		{
			GetDlgItem(IDC_EDIT_STAGE_X_LIMIT_MIN)->SetWindowTextW(strData);
			dlgSettingMotion->GetDlgItem(IDC_EDIT_MINPOS_STAGE_X)->SetWindowTextW(strData);
		}

		else if (m_pAcs->m_pACSMotion[i].m_strMotorName == _T("Stage_Y"))
		{
			GetDlgItem(IDC_EDIT_STAGE_Y_LIMIT_MIN)->SetWindowTextW(strData);
			dlgSettingMotion->GetDlgItem(IDC_EDIT_MINPOS_STAGE_Y)->SetWindowTextW(strData);
		}

		else if (m_pAcs->m_pACSMotion[i].m_strMotorName == _T("Stage_Turn"))
		{
			GetDlgItem(IDC_EDIT_STAGE_T_LIMIT_MIN)->SetWindowTextW(strData);
			dlgSettingMotion->GetDlgItem(IDC_EDIT_MINPOS_STAGE_T)->SetWindowTextW(strData);
		}

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("HomeBufferIdx"), _T("0"), szData, MAX_PATH, strPath);
		strData = szData;
		m_pAcs->m_pACSMotion[i].m_nHomeBufferIdx = _ttoi(strData);
		ZeroMemory(szData, MAX_PATH);

		GetPrivateProfileString(strTag, _T("HomeReturnVarName"), _T("HomeFlag"), szData, MAX_PATH, strPath);
		strData = szData;
		m_pAcs->m_pACSMotion[i].m_strHomeRetVarName = strData;
		ZeroMemory(szData, MAX_PATH);

		GetPrivateProfileString(strTag, _T("HomeOffsetVarName"), _T("HomeOffset"), szData, MAX_PATH, strPath);
		strData = szData;
		m_pAcs->m_pACSMotion[i].m_strHomeOffsetVarName = strData;
		ZeroMemory(szData, MAX_PATH);

		GetPrivateProfileString(strTag, _T("HomeOffset"), _T("0"), szData, MAX_PATH, strPath);
		strData = szData;
		m_pAcs->m_pACSMotion[i].m_dHomeOffset = _ttof(strData);
		ZeroMemory(szData, MAX_PATH);

		if (m_pAcs->m_pACSMotion[i].m_strMotorName == _T("Stage_X"))
			dlgSettingMotion->GetDlgItem(IDC_EDIT_HOMEOFFSET_STAGE_X)->SetWindowTextW(strData);

		else if (m_pAcs->m_pACSMotion[i].m_strMotorName == _T("Stage_Y"))
			dlgSettingMotion->GetDlgItem(IDC_EDIT_HOMEOFFSET_STAGE_Y)->SetWindowTextW(strData);

		else if (m_pAcs->m_pACSMotion[i].m_strMotorName == _T("Stage_Turn"))
			dlgSettingMotion->GetDlgItem(IDC_EDIT_HOMEOFFSET_STAGE_T)->SetWindowTextW(strData);

		GetPrivateProfileString(strTag, _T("HomeOffsetVel "), _T("0"), szData, MAX_PATH, strPath);
		strData = szData;
		m_pAcs->m_pACSMotion[i].m_dHomeOffsetVel = _ttof(strData);
		ZeroMemory(szData, MAX_PATH);

		if (m_pAcs->m_pACSMotion[i].m_strMotorName == _T("Stage_X"))
			dlgSettingMotion->GetDlgItem(IDC_EDIT_HOMEOFFSET_VEL_STAGE_X)->SetWindowTextW(strData);

		else if (m_pAcs->m_pACSMotion[i].m_strMotorName == _T("Stage_Y"))
			dlgSettingMotion->GetDlgItem(IDC_EDIT_HOMEOFFSET_VEL_STAGE_Y)->SetWindowTextW(strData);

		else if (m_pAcs->m_pACSMotion[i].m_strMotorName == _T("Stage_Turn"))
			dlgSettingMotion->GetDlgItem(IDC_EDIT_HOMEOFFSET_VEL_STAGE_T)->SetWindowTextW(strData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("Axis"), _T("0"), szData, MAX_PATH, strPath);
		strData = szData;
		m_pAcs->m_pACSMotion[i].m_nAxis = _ttoi(strData);

		if (m_pAcs->m_pACSMotion[i].m_strMotorName == _T("Stage_X"))
			dlgSettingMotion->GetDlgItem(IDC_EDIT_AXIS_NUM_STAGE_X)->SetWindowTextW(strData);

		else if (m_pAcs->m_pACSMotion[i].m_strMotorName == _T("Stage_Y"))
			dlgSettingMotion->GetDlgItem(IDC_EDIT_AXIS_NUM_STAGE_Y)->SetWindowTextW(strData);

		else if (m_pAcs->m_pACSMotion[i].m_strMotorName == _T("Stage_Turn"))
			dlgSettingMotion->GetDlgItem(IDC_EDIT_AXIS_NUM_STAGE_T)->SetWindowTextW(strData);

		//외부 엔코더 축 설정
		m_pAcs->m_pACSMotion[i].m_nEncAxis = m_pAcs->m_pACSMotion[i].m_nAxis + 1;
	}

	return TRUE;
}


void CJettingVisionDlg::InitSocket()
{
	m_ComPortLight.OpenPort(byIndexComPort(1), byIndexBaud(3), byIndexData(3), byIndexParity(0), byIndexStop(0));
	m_ComPortUV.OpenPort(byIndexComPort(0), byIndexBaud(1), byIndexData(3), byIndexParity(0), byIndexStop(0));

	WSADATA temp;
	WSAStartup(MAKEWORD(2, 0), &temp);	// 생성자

	sock = socket(AF_INET, SOCK_DGRAM, 0);

	addr.sin_family = AF_INET;
	addr.sin_port = htons(GAP_PORT);
	//addr.sin_addr.s_addr = inet_addr(GAP_IP);
	inet_pton(AF_INET, GAP_IP, &(addr.sin_addr.s_addr));

	// Jetting Valve
	AfxSocketInit();
}


CString CJettingVisionDlg::byIndexComPort(int xPort)
{
	CString PortName = _T("");
	switch (xPort)
	{
	case 0:		PortName = "COM1"; 			break;

	case 1:		PortName = "COM2";			break;

	case 2:		PortName = "COM3"; 			break;

	case 3:		PortName = "COM4";			break;

	case 4:		PortName = "COM5";			break;

	case 5:		PortName = "COM6";			break;

	case 6:		PortName = "COM7";			break;

	case 7:		PortName = "COM8";			break;

	case 8:		PortName = "COM9";		 	break;

	case 9:		PortName = "COM10";			break;
	}

	return PortName;
}


DWORD CJettingVisionDlg::byIndexBaud(int xBaud)
{
	DWORD dwBaud = 0;
	switch (xBaud)
	{
	case 0:		dwBaud = CBR_4800;		break;

	case 1:		dwBaud = CBR_9600;		break;

	case 2:		dwBaud = CBR_14400;		break;

	case 3:		dwBaud = CBR_19200;		break;

	case 4:		dwBaud = CBR_38400;		break;

	case 5:		dwBaud = CBR_56000;		break;

	case 6:		dwBaud = CBR_57600;		break;

	case 7:		dwBaud = CBR_115200;	break;
	}

	return dwBaud;
}


BYTE CJettingVisionDlg::byIndexData(int xData)
{
	BYTE byData = 0;
	switch (xData)
	{
	case 0:	byData = 5;			break;

	case 1:	byData = 6;			break;

	case 2:	byData = 7;			break;

	case 3:	byData = 8;			break;
	}

	return byData;
}


BYTE CJettingVisionDlg::byIndexParity(int xParity)
{
	BYTE byParity = 0;
	switch (xParity)
	{
	case 0:	byParity = NOPARITY;	break;

	case 1:	byParity = ODDPARITY;	break;

	case 2:	byParity = EVENPARITY;	break;
	}

	return byParity;
}


BYTE CJettingVisionDlg::byIndexStop(int xStop)
{
	BYTE byStop = 0;
	if (xStop == 0)
	{
		byStop = ONESTOPBIT;
	}
	else
	{
		byStop = TWOSTOPBITS;
	}
	return byStop;
}


void CJettingVisionDlg::GetMotorStatus()
{
	switch (CACSM::m_pACSMotion[0].IsEnable())
	{
	case TRUE:
		m_icon_stage_x_status.SetBitmap(m_bmp_green);
		break;
	case FALSE:
		m_icon_stage_x_status.SetBitmap(m_bmp_red);
		break;
	}

	switch (CACSM::m_pACSMotion[1].IsEnable())
	{
	case TRUE:
		m_icon_stage_y_status.SetBitmap(m_bmp_green);
		break;
	case FALSE:
		m_icon_stage_y_status.SetBitmap(m_bmp_red);
		break;
	}

	switch (CACSM::m_pACSMotion[2].IsEnable())
	{
	case TRUE:
		m_icon_stage_t_status.SetBitmap(m_bmp_green);
		break;
	case FALSE:
		m_icon_stage_t_status.SetBitmap(m_bmp_red);
		break;
	}
}


void CJettingVisionDlg::GetMotorMoving()
{
	switch (CACSM::m_pACSMotion[0].IsMoving())
	{
	case TRUE:
		m_icon_stage_x_move.SetBitmap(m_bmp_green);
		GetDlgItem(IDC_BTN_STAGE_X_MOVE)->SetWindowTextW(_T("STOP"));
		break;
	case FALSE:
		m_icon_stage_x_move.SetBitmap(m_bmp_red);
		GetDlgItem(IDC_BTN_STAGE_X_MOVE)->SetWindowTextW(_T("MOVE"));
		ChkStageX();
		break;
	}

	switch (CACSM::m_pACSMotion[1].IsMoving())
	{
	case TRUE:
		m_icon_stage_y_move.SetBitmap(m_bmp_green);
		GetDlgItem(IDC_BTN_STAGE_Y_MOVE)->SetWindowTextW(_T("STOP"));
		break;
	case FALSE:
		m_icon_stage_y_move.SetBitmap(m_bmp_red);
		GetDlgItem(IDC_BTN_STAGE_Y_MOVE)->SetWindowTextW(_T("MOVE"));
		ChkStageY();
		break;
	}

	switch (CACSM::m_pACSMotion[2].IsMoving())
	{
	case TRUE:
		m_icon_stage_t_move.SetBitmap(m_bmp_green);
		GetDlgItem(IDC_BTN_STAGE_T_MOVE)->SetWindowTextW(_T("STOP"));
		break;
	case FALSE:
		m_icon_stage_t_move.SetBitmap(m_bmp_red);
		GetDlgItem(IDC_BTN_STAGE_T_MOVE)->SetWindowTextW(_T("MOVE"));
		ChkStageT();
		break;
	}
}


void CJettingVisionDlg::GetHomeStatus()
{
	m_pAcs->GetAllHomeStatus();

	switch (CACSM::m_pACSMotion[0].m_nHomeDone)
	{
	case MOTION_HOME_NOT:
		break;

	case MOTION_HOME_ING:
		m_icon_stage_x_home.SetBitmap(m_bmp_yellow);
		break;

	case MOTION_HOME_OK:
		m_icon_stage_x_home.SetBitmap(m_bmp_green);
		break;

	case MOTION_HOME_ERR:
		break;
	}

	switch (CACSM::m_pACSMotion[1].m_nHomeDone)
	{
	case MOTION_HOME_NOT:
		break;

	case MOTION_HOME_ING:
		m_icon_stage_y_home.SetBitmap(m_bmp_yellow);
		break;

	case MOTION_HOME_OK:
		m_icon_stage_y_home.SetBitmap(m_bmp_green);
		break;

	case MOTION_HOME_ERR:
		break;
	}

	switch (CACSM::m_pACSMotion[2].m_nHomeDone)
	{
	case MOTION_HOME_NOT:
		break;

	case MOTION_HOME_ING:
		m_icon_stage_t_home.SetBitmap(m_bmp_yellow);
		break;

	case MOTION_HOME_OK:
		m_icon_stage_t_home.SetBitmap(m_bmp_green);
		break;

	case MOTION_HOME_ERR:
		break;
	}
}


void CJettingVisionDlg::GetAPos()
{
	m_pAcs->GetActualPos();

	double actualPos_x = CACSM::GetActualPos(0);
	double actualPos_y = CACSM::GetActualPos(1);
	double actualPos_t = CACSM::GetActualPos(2);

	CString strActualPos_x;
	CString strActualPos_y;
	CString strActualPos_t;

	strActualPos_x.Format(_T("%.4f"), actualPos_x);
	strActualPos_y.Format(_T("%.4f"), actualPos_y);
	strActualPos_t.Format(_T("%.8f"), actualPos_t);

	GetDlgItem(IDC_EDIT_STAGE_X_ACTUAL)->SetWindowTextW(strActualPos_x);
	GetDlgItem(IDC_EDIT_STAGE_Y_ACTUAL)->SetWindowTextW(strActualPos_y);
	GetDlgItem(IDC_EDIT_STAGE_T_ACTUAL)->SetWindowTextW(strActualPos_t);

	GetDlgItem(IDC_EDIT_STAGE_X_JOG_ACTUAL)->SetWindowTextW(strActualPos_x);
	GetDlgItem(IDC_EDIT_STAGE_Y_JOG_ACTUAL)->SetWindowTextW(strActualPos_y);
	GetDlgItem(IDC_EDIT_STAGE_T_JOG_ACTUAL)->SetWindowTextW(strActualPos_t);
}


void CJettingVisionDlg::GetVelocity()
{
	CString strActualSpeed_x;
	CString strActualSpeed_y;
	CString strActualSpeed_t;

	for (int i = 0; i < CACSM::m_nMotCnt; i++)
	{
		//m_pAcs->m_pACSMotion[i].GetVelocity(aSpeed, NULL);

		//actualSpped[i] = aSpeed[0];
	}

	/*strActualSpeed_x.Format(_T("%.4f"), actualSpped[0]);
	strActualSpeed_y.Format(_T("%.4f"), actualSpped[1]);
	strActualSpeed_t.Format(_T("%.4f"), actualSpped[2]);*/

	/*GetDlgItem(I)->SetWindowTextW(strActualSpeed_x);
	GetDlgItem(IDC_EDIT_Y_SPEED)->SetWindowTextW(strActualSpeed_y);
	GetDlgItem(IDC_EDIT_T_SPEED)->SetWindowTextW(strActualSpeed_t);*/
}


void CJettingVisionDlg::StageMove(int nStage, double TargetPos, BOOL nABS, BOOL nREL, double ManualSpeed)
{
	// manual move 시 speed setting
	m_pAcs->m_pACSMotion[nStage].m_dVelocity = ManualSpeed;
	m_pAcs->m_pACSMotion[nStage].m_dAccel = ManualSpeed * 5;
	m_pAcs->m_pACSMotion[nStage].m_dDecel = ManualSpeed * 5;
	m_pAcs->m_pACSMotion[nStage].m_dKillDecel = ManualSpeed * 25;
	m_pAcs->m_pACSMotion[nStage].m_dJerk = ManualSpeed * 25;

	//m_pAcs->m_pACSMotion[nStage].SetVelocityManual(NULL);
	SetMotionSpeed();

	if (nABS == TRUE && nREL == FALSE)
	{
		m_pAcs->m_pACSMotion[nStage].MoveAbs(NULL, TargetPos, NULL);
	}

	else if (nABS == FALSE && nREL == TRUE)
	{
		m_pAcs->m_pACSMotion[nStage].MoveRel(ACSC_AMF_RELATIVE, TargetPos, NULL);
	}
}

void CJettingVisionDlg::StageBreak(int nStage)
{
	m_pAcs->m_pACSMotion[nStage].Motion_Stop(NULL);
}

void CJettingVisionDlg::StageMoveJog(int nStage, CString nCase)
{
	if (nCase == _T("NEGATIVE"))
		m_pAcs->m_pACSMotion[nStage].MoveJog(0, ACSC_NEGATIVE_DIRECTION, NULL);

	else if (nCase == _T("POSITIVE"))
		m_pAcs->m_pACSMotion[nStage].MoveJog(0, ACSC_POSITIVE_DIRECTION, NULL);
}


void CJettingVisionDlg::SetMotionSpeed()
{
	for (int i = 0; i < m_nMotCnt; i++)
	{
		m_pAcs->m_pACSMotion[i].SetVelocity(NULL);
		m_pAcs->m_pACSMotion[i].SetAccel(NULL);
		m_pAcs->m_pACSMotion[i].SetDecel(NULL);
		m_pAcs->m_pACSMotion[i].SetKillDecel(NULL);
		m_pAcs->m_pACSMotion[i].SetJerk(NULL);
	}
}


void CJettingVisionDlg::OnBnClickedBtnAbs()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_btn_abs.SetFaceColor(ColorGreen);
	m_btn_rel.SetFaceColor(ColorBasic);

	bChkABS = true;
	bChkREL = false;

	OnEnChangeEditStageXInput();
	OnEnChangeEditStageYInput();
	OnEnChangeEditStageTInput();
}


void CJettingVisionDlg::OnBnClickedBtnRel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_btn_abs.SetFaceColor(ColorBasic);
	m_btn_rel.SetFaceColor(ColorGreen);

	bChkABS = false;
	bChkREL = true;

	OnEnChangeEditStageXInput();
	OnEnChangeEditStageYInput();
	OnEnChangeEditStageTInput();
}


void CJettingVisionDlg::OnBnClickedBtnJogSlow()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_btn_jog_slow.SetFaceColor(ColorGreen);
	m_btn_jog_fast.SetFaceColor(ColorBasic);

	bChkJogSlow = true;
	bChkJogFast = false;
}


void CJettingVisionDlg::OnBnClickedBtnJogFast()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_btn_jog_slow.SetFaceColor(ColorBasic);
	m_btn_jog_fast.SetFaceColor(ColorGreen);

	bChkJogSlow = false;
	bChkJogFast = true;
}


void CJettingVisionDlg::OnEnChangeEditStageXInput()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString strInput;
	CString strAPos;
	CString strCommand;

	double dInput;
	double dAPos;
	double dCommand;

	GetDlgItem(IDC_EDIT_STAGE_X_INPUT)->GetWindowTextW(strInput);
	GetDlgItem(IDC_EDIT_STAGE_X_ACTUAL)->GetWindowTextW(strAPos);

	dInput = _wtof(strInput);
	dAPos = _wtof(strAPos);

	if (bChkABS == true)
	{
		strCommand = strInput;
		GetDlgItem(IDC_EDIT_STAGE_X_COMMAND)->SetWindowTextW(strCommand);

		if (_wtof(strCommand) >= CACSM::m_pACSMotion[0].m_dMinPos && _wtof(strCommand) <= CACSM::m_pACSMotion[0].m_dMaxPos)
			GetDlgItem(IDC_BTN_STAGE_X_MOVE)->EnableWindow(TRUE);

		else
			GetDlgItem(IDC_BTN_STAGE_X_MOVE)->EnableWindow(FALSE);
	}

	else if (bChkREL == true)
	{
		dCommand = dInput + dAPos;
		strCommand.Format(_T("%.4f"), dCommand);

		GetDlgItem(IDC_EDIT_STAGE_X_COMMAND)->SetWindowTextW(strCommand);

		if (_wtof(strCommand) >= CACSM::m_pACSMotion[0].m_dMinPos && _wtof(strCommand) <= CACSM::m_pACSMotion[0].m_dMaxPos)
			GetDlgItem(IDC_BTN_STAGE_X_MOVE)->EnableWindow(TRUE);

		else
			GetDlgItem(IDC_BTN_STAGE_X_MOVE)->EnableWindow(FALSE);
	}
}


void CJettingVisionDlg::OnEnChangeEditStageYInput()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strInput;
	CString strAPos;
	CString strCommand;

	double dInput;
	double dAPos;
	double dCommand;

	GetDlgItem(IDC_EDIT_STAGE_Y_INPUT)->GetWindowTextW(strInput);
	GetDlgItem(IDC_EDIT_STAGE_Y_ACTUAL)->GetWindowTextW(strAPos);

	dInput = _wtof(strInput);
	dAPos = _wtof(strAPos);

	if (bChkABS == true)
	{
		strCommand = strInput;
		GetDlgItem(IDC_EDIT_STAGE_Y_COMMAND)->SetWindowTextW(strCommand);

		if (_wtof(strCommand) >= CACSM::m_pACSMotion[1].m_dMinPos && _wtof(strCommand) <= CACSM::m_pACSMotion[1].m_dMaxPos)
			GetDlgItem(IDC_BTN_STAGE_Y_MOVE)->EnableWindow(TRUE);

		else
			GetDlgItem(IDC_BTN_STAGE_Y_MOVE)->EnableWindow(FALSE);
	}

	else if (bChkREL == true)
	{
		dCommand = dInput + dAPos;
		strCommand.Format(_T("%.4f"), dCommand);

		GetDlgItem(IDC_EDIT_STAGE_Y_COMMAND)->SetWindowTextW(strCommand);

		if (_wtof(strCommand) >= CACSM::m_pACSMotion[1].m_dMinPos && _wtof(strCommand) <= CACSM::m_pACSMotion[1].m_dMaxPos)
			GetDlgItem(IDC_BTN_STAGE_Y_MOVE)->EnableWindow(TRUE);

		else
			GetDlgItem(IDC_BTN_STAGE_Y_MOVE)->EnableWindow(FALSE);
	}
}


void CJettingVisionDlg::OnEnChangeEditStageTInput()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strInput;
	CString strAPos;
	CString strCommand;

	double dInput;
	double dAPos;
	double dCommand;

	GetDlgItem(IDC_EDIT_STAGE_T_INPUT)->GetWindowTextW(strInput);
	GetDlgItem(IDC_EDIT_STAGE_T_ACTUAL)->GetWindowTextW(strAPos);

	dInput = _wtof(strInput);
	dAPos = _wtof(strAPos);

	if (bChkABS == true)
	{
		strCommand = strInput;
		GetDlgItem(IDC_EDIT_STAGE_T_COMMAND)->SetWindowTextW(strCommand);

		if (_wtof(strCommand) >= CACSM::m_pACSMotion[2].m_dMinPos && _wtof(strCommand) <= CACSM::m_pACSMotion[2].m_dMaxPos)
			GetDlgItem(IDC_BTN_STAGE_T_MOVE)->EnableWindow(TRUE);

		else
			GetDlgItem(IDC_BTN_STAGE_T_MOVE)->EnableWindow(FALSE);
	}

	else if (bChkREL == true)
	{
		dCommand = dInput + dAPos;
		strCommand.Format(_T("%.4f"), dCommand);

		GetDlgItem(IDC_EDIT_STAGE_T_COMMAND)->SetWindowTextW(strCommand);

		if (_wtof(strCommand) >= CACSM::m_pACSMotion[2].m_dMinPos && _wtof(strCommand) <= CACSM::m_pACSMotion[2].m_dMaxPos)
			GetDlgItem(IDC_BTN_STAGE_T_MOVE)->EnableWindow(TRUE);

		else
			GetDlgItem(IDC_BTN_STAGE_T_MOVE)->EnableWindow(FALSE);
	}
}


void CJettingVisionDlg::OnEnChangeEditStageXSpeed()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strSpeed;

	GetDlgItem(IDC_EDIT_STAGE_X_SPEED)->GetWindowTextW(strSpeed);

	if (_wtof(strSpeed) <= 0)
		GetDlgItem(IDC_BTN_STAGE_X_MOVE)->EnableWindow(FALSE);

	else if (_wtof(strSpeed) > 0)
		GetDlgItem(IDC_BTN_STAGE_X_MOVE)->EnableWindow(TRUE);
}


void CJettingVisionDlg::OnEnChangeEditStageYSpeed()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strSpeed;

	GetDlgItem(IDC_EDIT_STAGE_Y_SPEED)->GetWindowTextW(strSpeed);

	if (_wtof(strSpeed) <= 0)
		GetDlgItem(IDC_BTN_STAGE_Y_MOVE)->EnableWindow(FALSE);

	else if (_wtof(strSpeed) > 0)
		GetDlgItem(IDC_BTN_STAGE_Y_MOVE)->EnableWindow(TRUE);
}


void CJettingVisionDlg::OnEnChangeEditStageTSpeed()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strSpeed;

	GetDlgItem(IDC_EDIT_STAGE_T_SPEED)->GetWindowTextW(strSpeed);

	if (_wtof(strSpeed) <= 0)
		GetDlgItem(IDC_BTN_STAGE_T_MOVE)->EnableWindow(FALSE);

	else if (_wtof(strSpeed) > 0)
		GetDlgItem(IDC_BTN_STAGE_T_MOVE)->EnableWindow(TRUE);
}




void CJettingVisionDlg::OnStnClickedIconStageXStatus()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (CACSM::m_pACSMotion[0].IsEnable())
		AlarmMessageDisplay(_T("X축 모터 DISABLE?"), 0);

	else
		AlarmMessageDisplay(_T("X축 모터 ENABLE?"), 0);
}


void CJettingVisionDlg::OnStnClickedIconStageYStatus()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (CACSM::m_pACSMotion[1].IsEnable())
		AlarmMessageDisplay(_T("Y축 모터 DISABLE?"), 1);

	else
		AlarmMessageDisplay(_T("Y축 모터 ENABLE?"), 1);
}


void CJettingVisionDlg::OnStnClickedIconStageTStatus()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (CACSM::m_pACSMotion[2].IsEnable())
		AlarmMessageDisplay(_T("Theta축 모터 DISABLE?"), 2);

	else
		AlarmMessageDisplay(_T("Theta축 모터 ENABLE?"), 2);
}


void CJettingVisionDlg::OnStnClickedIconStageXHome()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	AlarmMessageDisplay(_T("X축 모터 HOME?"), 3);
}


void CJettingVisionDlg::OnStnClickedIconStageYHome()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	AlarmMessageDisplay(_T("Y축 모터 HOME?"), 4);
}


void CJettingVisionDlg::OnStnClickedIconStageTHome()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	AlarmMessageDisplay(_T("T축 모터 HOME?"), 5);
}


void CJettingVisionDlg::AlarmMessageDisplay(CString strMessage, int nCase)
{
	CRect rcManualAlign;
	GetWindowRect(rcManualAlign);

	dlgPopupAlarm.rcDialog.top = (rcManualAlign.bottom - rcManualAlign.top) / 2;
	dlgPopupAlarm.rcDialog.left = (rcManualAlign.right - rcManualAlign.left) / 2;
	dlgPopupAlarm.rcDialog.right = dlgPopupAlarm.rcDialog.left + 300;
	dlgPopupAlarm.rcDialog.bottom = dlgPopupAlarm.rcDialog.top + 140;

	dlgPopupAlarm.strAlarm = strMessage;
	if (dlgPopupAlarm.DoModal() == IDOK)   // 다이얼로그가 종료될 때 반환되는 값을 검사, OK 버튼으로 종료되었을 경우 IDOK를 반환
	{
		if (nCase == 0 || nCase == 1 || nCase == 2)
		{
			if (CACSM::m_pACSMotion[nCase].IsEnable())
				m_pAcs->m_pACSMotion[nCase].Motion_Disable(NULL);

			else
				m_pAcs->m_pACSMotion[nCase].Motion_Enable(NULL);
		}

		else if (nCase == 3)
		{
			if (!CACSM::RunHome(1, NULL, NULL))
			{

			}
		}

		else if (nCase == 4)
		{
			if (!CACSM::RunHome(2, NULL, NULL))
			{

			}
		}


		else if (nCase == 5)
		{
			if (!CACSM::RunHome(0, NULL, NULL))
			{

			}
		}

		else if (nCase == 6)
		{
			OnDestroy();
			::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);
		}

		else if (nCase == 7)
		{
			bCycleStart = true;
		}

		else if (nCase == 8)
		{

		}

		delete dlgPopupAlarm;
	}
}

void CJettingVisionDlg::SetVisionLight(int nCam)
{
	BYTE SendData[6] = { 0x01, 0x00, 0x01, 0x20, nCam, 0X04 };
	m_ComPortLight.WriteComm(SendData, sizeof(SendData));
	m_ComPortLight.WriteComm(SendData, sizeof(SendData));
}


void CJettingVisionDlg::ControlVisionLight(int nValue)
{
	BYTE SendData[6] = { 0x01, 0x00, 0x01, 0x28, nValue, 0X04 };
	m_ComPortLight.WriteComm(SendData, sizeof(SendData));
	m_ComPortLight.WriteComm(SendData, sizeof(SendData));
}


void CJettingVisionDlg::ImageSave(BOOL bLeft, BOOL bRight, BOOL bBefore, BOOL bAfter)
{
	BYTE* Img;

	Img = reinterpret_cast<BYTE*>(cBaumer->m_camera_set[0].m_buf);

	BITMAPFILEHEADER fh;
	BITMAPINFOHEADER ih;
	RGBQUAD rgb[256];

	memset(&fh, 0, sizeof(BITMAPFILEHEADER));
	memset(&ih, 0, sizeof(BITMAPINFOHEADER));
	memset(&rgb, 0, sizeof(RGBQUAD) * 256);
	fh.bfOffBits = 1078; // RGBQUAD + InfoHeader + FileHeader only 8bit mode if 24bit == 54; 40+ 14; 

	fh.bfSize = CamWidth * CamHeight + sizeof(RGBQUAD) * 256 + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	fh.bfType = 19778;

	ih.biBitCount = 8;
	ih.biHeight = CamHeight;
	ih.biPlanes = 1;
	ih.biSize = 40;
	ih.biSizeImage = CamWidth * CamHeight;
	ih.biWidth = CamWidth;
	ih.biXPelsPerMeter = 0;
	ih.biYPelsPerMeter = 0;

	for (int i = 0; i < 256; i++)
	{
		rgb[i].rgbBlue = i;
		rgb[i].rgbGreen = i;
		rgb[i].rgbRed = i;
		rgb[i].rgbReserved = 0;
	}

	int rwsize = WIDTHBYTES(ih.biBitCount * ih.biWidth);

	BYTE* pData = new BYTE[CamWidth * CamHeight];
	memset(pData, 0, sizeof(CamWidth * CamHeight));

	for (int i = 0; i < ih.biHeight; i++)
	{
		for (int j = 0; j < rwsize; j++)
		{
			pData[i * rwsize + j] = Img[(ih.biHeight - i - 1) * rwsize + j];
		}
	}

	FILE* fp;
	CString strImageName;
	CString strFileName;

	if (bLeft == true && bRight == false)
		strImageName.Format(_T("\\Align(left).bmp"));

	else if (bLeft == false && bRight == true)
		strImageName.Format(_T("\\Align(right).bmp"));

	if (bBefore == true && bAfter == false)
		strFileName = strAlignBeforePath + strImageName;

	else if (bBefore == false && bAfter == true)
		strFileName = strAlignAfterPath + strImageName;

	_bstr_t gg(strFileName);

	fopen_s(&fp, gg, "wb");
	fwrite(&fh, sizeof(BITMAPFILEHEADER), 1, fp);
	fwrite(&ih, sizeof(BITMAPINFOHEADER), 1, fp);
	fwrite(rgb, sizeof(RGBQUAD), 256, fp);
	fwrite(pData, 1, CamWidth * CamHeight, fp);
	fclose(fp);
}

void CJettingVisionDlg::ImageAlignment(BOOL bLeft, BOOL bRight)
{
	Mat ImageLoad;
	Mat ImageResize;
	Mat ImageGray;	// GRAY 이미지 
	Mat ImageOpen;	// MORPHOLOGY OPEN
	Mat ImageClose;	// MORPHOLOGY CLOSE
	Mat ElementOpen(1, 1, CV_8U, cv::Scalar(1));	// OPEN 파라미터
	Mat ElementClose(5, 5, CV_8U, cv::Scalar(1));	// CLOSE 파라미터
	Mat ImageBinary;	// 이미지 이진화
	Mat ImageCanny;

	CString FileName;

	if (bLeft == true)
		FileName = _T("Align(left).bmp");
	//		FileName = strAlignBeforePath + _T("\\Align(left).bmp");


	else if (bRight == true)
		FileName = _T("Align(right).bmp");
	//	FileName = strAlignBeforePath + _T("\\Align(right).bmp");

	CT2CA ConvertString(FileName);
	std::string	Image_path(ConvertString);

	ImageLoad = imread(Image_path);

	// clone 복사
	resize(ImageLoad, ImageResize, Size(ImageLoad.cols / resizeMagni, ImageLoad.rows / resizeMagni));

	// rgb2gray
	cvtColor(ImageResize, ImageGray, COLOR_BGR2GRAY);

	// morphology
	morphologyEx(ImageGray, ImageOpen, cv::MORPH_OPEN, ElementOpen);
	morphologyEx(ImageOpen, ImageClose, cv::MORPH_CLOSE, ElementClose);

	// binary
	threshold(ImageClose, ImageBinary, 90, 255/*고정 값*/, THRESH_BINARY);

	Canny(ImageBinary, ImageCanny, 10, 50, 3, false);	// canny (edge detection)

	std::vector<cv::Point> point_vertical;
	std::vector<cv::Point> point_horizontal;

	Vec4f VerticalLine;
	Vec4f HorizontalLine;

	point_vertical.clear();
	point_horizontal.clear();

	// 첫 번째 Alignment (left -> right)
	if (bLeft == TRUE && bRight == FALSE)
	{
		for (int i = 0; i < CamHeight / resizeMagni; i++)
		{
			for (int j = 0; j < CamWidth / resizeMagni; j++)
			{
				if (ImageCanny.at<uchar>(i, j) != 0)
				{
					point_vertical.push_back(cv::Point(j * resizeMagni, i * resizeMagni));
					break;
				}
			}
		}
	}

	// 두 번째 Alignment (right -> left)
	else if (bLeft == FALSE && bRight == TRUE)
	{
		for (int i = 0; i < CamHeight / resizeMagni; i++)
		{
			for (int j = CamWidth / resizeMagni - 1; j > 0; j--)
			{
				if (ImageCanny.at<uchar>(i, j) != 0)
				{
					point_vertical.push_back(cv::Point(j * resizeMagni, i * resizeMagni));
					break;
				}
			}
		}
	}

	// 하단은 아래에서 위로
	for (int i = 0; i < CamWidth / resizeMagni; i++)
	{
		for (int j = CamHeight / resizeMagni - 1; j >= 0; j--)
		{
			if (ImageCanny.at<uchar>(j, i) != 0)
			{
				point_horizontal.push_back(cv::Point(i * resizeMagni, j * resizeMagni));
				break;
			}
		}
	}

	// 둘다 검출이 안된 경우
	if (point_vertical.size() == 0 || point_horizontal.size() == 0)
	{

	}

	else
	{
		fitLine(cv::Mat(point_horizontal), HorizontalLine,
			DIST_L2,// 거리 유형
			0,   // L2 거리를 사용하지 않음
			0.01, 0.01); // 정확도

		double fSlope_horizontal = HorizontalLine.val[1] / HorizontalLine.val[0];
		double fIntercept_horizontal = HorizontalLine.val[3] - fSlope_horizontal * HorizontalLine.val[2];

		Point pHorizontalStart;
		Point pHorizontalEnd;

		pHorizontalStart.x = 0;
		pHorizontalStart.y = fIntercept_horizontal;

		pHorizontalEnd.x = CamWidth;
		pHorizontalEnd.y = CamWidth * fSlope_horizontal + fIntercept_horizontal;

		cv::line(ImageLoad, pHorizontalStart, pHorizontalEnd, Scalar(0, 0, 255), 10, 8, 0);

		fitLine(cv::Mat(point_vertical), VerticalLine,
			DIST_L2,// 거리 유형
			0,   // L2 거리를 사용하지 않음
			0.01, 0.01); // 정확도

		double fSlope_vertical = VerticalLine.val[1] / VerticalLine.val[0];
		double fIntercept_vertical = VerticalLine.val[3] - fSlope_vertical * VerticalLine.val[2];

		Point pVerticalStart;
		Point pVerticalEnd;

		pVerticalStart.x = (CamHeight - fIntercept_vertical) / fSlope_vertical;
		pVerticalStart.y = 0;

		pVerticalEnd.x = (-fIntercept_vertical / fSlope_vertical);
		pVerticalEnd.y = CamHeight;

		cv::line(ImageLoad, pVerticalStart, pVerticalEnd, Scalar(0, 0, 255), 10, 8, 0);

		if (bLeft == TRUE && bRight == FALSE)
		{
			pAlignLeft.x = (-(fIntercept_vertical - fIntercept_horizontal) / (fSlope_vertical - fSlope_horizontal));
			pAlignLeft.y = (fSlope_vertical * (-(fIntercept_vertical - fIntercept_horizontal) / (fSlope_vertical - fSlope_horizontal)) + fIntercept_vertical);
		}

		else if (bLeft == FALSE && bRight == TRUE)
		{
			pAlignRight.x = (-(fIntercept_vertical - fIntercept_horizontal) / (fSlope_vertical - fSlope_horizontal));
			pAlignRight.y = (fSlope_vertical * (-(fIntercept_vertical - fIntercept_horizontal) / (fSlope_vertical - fSlope_horizontal)) + fIntercept_vertical);
		}

		CString saveName;
		saveName = _T("22") + FileName;
		CT2CA ConvertString(saveName);
		std::string	Image_name(ConvertString);
		imwrite(Image_name, ImageLoad);

		DisplayAlignImage(bLeft, bRight, ImageLoad);
	}
}


void CJettingVisionDlg::AlignCalcuration()
{
	double dResolution;

	double dLeftPositionX;
	double dLeftPositionY;

	double dRightPositionX;
	double dRightPositionY;

	double dDistX;
	double dDistY;

	dAlignModifyX = 0.0;
	dAlignModifyY = 0.0;
	dAlignModifyT = 0.0;

	dResolution = (dlgSettingVision->dPixelSize / dlgSettingVision->nMagni) / 1000;

	dLeftPositionX = pAlignLeft.x - (CamWidth / 2);
	dLeftPositionY = (CamHeight / 2) - pAlignLeft.y;

	dRightPositionX = pAlignRight.x - (CamWidth / 2);
	dRightPositionY = (CamHeight / 2) - pAlignRight.y;

	dLeftPositionX *= dResolution;
	dLeftPositionY *= dResolution;

	dRightPositionX *= dResolution;
	dRightPositionY *= dResolution;

	dDistX = abs(dlgSettingMotion->dPosAlignrightY - dlgSettingMotion->dPosAlignleftY);
	dDistX -= dLeftPositionX;
	dDistX += dRightPositionX;

	dDistY = dRightPositionY - dLeftPositionY;

	dAlignModifyX = (dLeftPositionY + dRightPositionY) / 2;
	dAlignModifyY = -(dRightPositionX - dLeftPositionX);
	dAlignModifyT = ((dDistY / dDistX) * 180) / 3.14926535897;

	CString strVal;
	strVal.Format(_T("%.3fmm"), dAlignModifyX);
	GetDlgItem(IDC_STATIC_ALIGN_MODIFY_X_VALUE)->SetWindowTextW(strVal);

	strVal.Format(_T("%.3fmm"), dAlignModifyY);
	GetDlgItem(IDC_STATIC_ALIGN_MODIFY_Y_VALUE)->SetWindowTextW(strVal);

	strVal.Format(_T("%.4f˚"), dAlignModifyT);
	GetDlgItem(IDC_STATIC_ALIGN_MODIFY_T_VALUE)->SetWindowTextW(strVal);

	if (abs(dAlignModifyX) > dlgSettingVision->dAlignLimitX)
	{
		bProcPause = FALSE;
		bJudgeModifyX = false;
		GetDlgItem(IDC_STATIC_ALIGN_MODIFY_X_JUDGE)->SetWindowTextW(_T("NG"));
	}

	else
	{
		bJudgeModifyX = true;
		GetDlgItem(IDC_STATIC_ALIGN_MODIFY_X_JUDGE)->SetWindowTextW(_T("OK"));
	}


	if (abs(dAlignModifyY) > dlgSettingVision->dAlignLimitY)
	{
		bProcPause = FALSE;
		bJudgeModifyY = false;
		GetDlgItem(IDC_STATIC_ALIGN_MODIFY_Y_JUDGE)->SetWindowTextW(_T("NG"));
	}

	else
	{
		bJudgeModifyY = true;
		GetDlgItem(IDC_STATIC_ALIGN_MODIFY_Y_JUDGE)->SetWindowTextW(_T("OK"));
	}

	if (abs(dAlignModifyT) > dlgSettingVision->dAlignLimitT)
	{
		bProcPause = FALSE;
		bJudgeModifyT = false;
		GetDlgItem(IDC_STATIC_ALIGN_MODIFY_T_JUDGE)->SetWindowTextW(_T("NG"));
	}

	else
	{
		bJudgeModifyT = true;
		GetDlgItem(IDC_STATIC_ALIGN_MODIFY_T_JUDGE)->SetWindowTextW(_T("OK"));
	}

}


void CJettingVisionDlg::GapMeasurement(int gapCount)
{
	unsigned char command[4];
	unsigned char reply[6];

	CString strCount;
	CString strVal;

	double dVal;

	strCount.Format(_T("%d"), gapCount);
	GetDlgItem(IDC_STATIC_GAP_STEP)->SetWindowTextW(strCount);

	int k, recvlen;

	k = 0;
	command[k++] = MEM_READ;/* command code */
	command[k++] = 2;	/* command variable part; 2bytes */
	command[k++] = SHM_DISPL_VALUE >> 8;
	command[k++] = SHM_DISPL_VALUE & 0xFF;

	sendto(sock, (char*)command, 4, 0, (struct sockaddr*)&addr, sizeof(addr));
	recvlen = recv(sock, (char*)reply, sizeof(reply), 0);

	if (recvlen >= 6 && reply[0] == MEM_READ_REPLY && reply[1] >= 4)
	{
		int d = (reply[2] << 24) | (reply[3] << 16) | (reply[4] << 8) | reply[5];
		if (d != 0x7FFFFFFF)
		{

			strVal.Format(_T("%6.4lfmm"), d / 1000000.0);
			GetDlgItem(IDC_STATIC_GAP_VALUE)->SetWindowTextW(strVal);

			dVal = _wtof(strVal);

			// 범위 안에 있는 경우 
			if (dVal > dlgSettingVision->dGapRange)
			{

			}
		}
	}
	dGapSum += dVal;
	dGapAvg = dGapSum / gapCount;

	if (abs(dGapAvg) > dlgSettingVision->dGapLimit)
	{
		bJudgeGapAvg = false;
		GetDlgItem(IDC_STATIC_GAP_JUDGE)->SetWindowTextW(_T("NG"));
	}

	else
	{
		bJudgeGapAvg = true;
		GetDlgItem(IDC_STATIC_GAP_JUDGE)->SetWindowTextW(_T("OK"));
	}


	strVal.Format(_T("%6.4lfmm"), dGapAvg);
	GetDlgItem(IDC_STATIC_GAP_VALUE_AVG)->SetWindowTextW(strVal);
}

void CJettingVisionDlg::SetUV(bool nCase)
{
	char stx;
	char etx;

	stx = 0x02;
	etx = 0x03;

	// ON
	if (nCase == true)
	{
		BYTE SendData[7] = { stx,'A','L','L','O','N',etx };
		m_ComPortUV.WriteComm(SendData, sizeof(SendData));
	}

	// OFF
	else if (nCase == false)
	{
		BYTE SendData[8] = { stx ,'A','L','L','O','F','F',etx };
		m_ComPortUV.WriteComm(SendData, sizeof(SendData));
	}
}


void CJettingVisionDlg::SetJetting()
{
	m_pAcs->m_pACSMotion[1].Motion_PegInc(ACSC_AMF_SYNCHRONOUS, 1, dlgSettingMotion->dPosProcstartY + dJettinOffset, 0.005,
		dlgSettingMotion->dPosProcstartY + dJettinOffset + dJettingLength, ACSC_NONE, ACSC_NONE, NULL);
}


void CJettingVisionDlg::DisplayAlignImage(BOOL bLeft, BOOL bRight, Mat Image)
{
	pDCAlignLeft = m_pic_align_left.GetDC();
	hdcAlignLeft = pDCAlignLeft->m_hDC;

	pDCAlignRight = m_pic_align_right.GetDC();
	hdcAlignRight = pDCAlignRight->m_hDC;

	SetStretchBltMode(hdcAlignLeft, COLORONCOLOR);
	SetStretchBltMode(hdcAlignRight, COLORONCOLOR);

	m_pBmpInfo = (BITMAPINFO*)m_chBmpBuf;
	m_pBmpInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_pBmpInfo->bmiHeader.biWidth = Image.cols;
	m_pBmpInfo->bmiHeader.biHeight = -(Image.rows);
	m_pBmpInfo->bmiHeader.biBitCount = 24;
	m_pBmpInfo->bmiHeader.biPlanes = 1;
	m_pBmpInfo->bmiHeader.biCompression = BI_RGB;
	m_pBmpInfo->bmiHeader.biSizeImage = 0;
	m_pBmpInfo->bmiHeader.biXPelsPerMeter = 0;
	m_pBmpInfo->bmiHeader.biYPelsPerMeter = 0;
	m_pBmpInfo->bmiHeader.biClrUsed = 0;
	m_pBmpInfo->bmiHeader.biClrImportant = 0;

	if (bLeft == TRUE && bRight == FALSE)
		StretchDIBits(hdcAlignLeft, 0, 0, 170, 170, 0, 0, Image.cols, Image.rows,
			Image.data, m_pBmpInfo, DIB_RGB_COLORS, SRCCOPY);

	else if (bLeft == FALSE && bRight == TRUE)
		StretchDIBits(hdcAlignRight, 0, 0, 170, 170, 0, 0, Image.cols, Image.rows,
			Image.data, m_pBmpInfo, DIB_RGB_COLORS, SRCCOPY);

}


void CJettingVisionDlg::ChkStageX()
{
	CString strInput;
	CString strAPos;
	CString strCommand;

	double dInput;
	double dAPos;
	double dCommand;

	GetDlgItem(IDC_EDIT_STAGE_X_INPUT)->GetWindowTextW(strInput);
	GetDlgItem(IDC_EDIT_STAGE_X_ACTUAL)->GetWindowTextW(strAPos);

	dInput = _wtof(strInput);
	dAPos = _wtof(strAPos);

	if (bChkABS == true)
	{
		strCommand = strInput;
		GetDlgItem(IDC_EDIT_STAGE_X_COMMAND)->SetWindowTextW(strCommand);

		if (_wtof(strCommand) >= CACSM::m_pACSMotion[0].m_dMinPos && _wtof(strCommand) <= CACSM::m_pACSMotion[0].m_dMaxPos)
			GetDlgItem(IDC_BTN_STAGE_X_MOVE)->EnableWindow(TRUE);

		else
			GetDlgItem(IDC_BTN_STAGE_X_MOVE)->EnableWindow(FALSE);
	}

	else if (bChkREL == true)
	{
		dCommand = dInput + dAPos;
		strCommand.Format(_T("%.4f"), dCommand);

		GetDlgItem(IDC_EDIT_STAGE_X_COMMAND)->SetWindowTextW(strCommand);

		if (_wtof(strCommand) >= CACSM::m_pACSMotion[0].m_dMinPos && _wtof(strCommand) <= CACSM::m_pACSMotion[0].m_dMaxPos)
			GetDlgItem(IDC_BTN_STAGE_X_MOVE)->EnableWindow(TRUE);

		else
			GetDlgItem(IDC_BTN_STAGE_X_MOVE)->EnableWindow(FALSE);
	}
}


void CJettingVisionDlg::ChkStageY()
{
	CString strInput;
	CString strAPos;
	CString strCommand;

	double dInput;
	double dAPos;
	double dCommand;

	GetDlgItem(IDC_EDIT_STAGE_Y_INPUT)->GetWindowTextW(strInput);
	GetDlgItem(IDC_EDIT_STAGE_Y_ACTUAL)->GetWindowTextW(strAPos);

	dInput = _wtof(strInput);
	dAPos = _wtof(strAPos);

	if (bChkABS == true)
	{
		strCommand = strInput;
		GetDlgItem(IDC_EDIT_STAGE_Y_COMMAND)->SetWindowTextW(strCommand);

		if (_wtof(strCommand) >= CACSM::m_pACSMotion[1].m_dMinPos && _wtof(strCommand) <= CACSM::m_pACSMotion[1].m_dMaxPos)
			GetDlgItem(IDC_BTN_STAGE_Y_MOVE)->EnableWindow(TRUE);

		else
			GetDlgItem(IDC_BTN_STAGE_Y_MOVE)->EnableWindow(FALSE);
	}

	else if (bChkREL == true)
	{
		dCommand = dInput + dAPos;
		strCommand.Format(_T("%.4f"), dCommand);

		GetDlgItem(IDC_EDIT_STAGE_Y_COMMAND)->SetWindowTextW(strCommand);

		if (_wtof(strCommand) >= CACSM::m_pACSMotion[1].m_dMinPos && _wtof(strCommand) <= CACSM::m_pACSMotion[1].m_dMaxPos)
			GetDlgItem(IDC_BTN_STAGE_Y_MOVE)->EnableWindow(TRUE);

		else
			GetDlgItem(IDC_BTN_STAGE_Y_MOVE)->EnableWindow(FALSE);
	}
}


void CJettingVisionDlg::ChkStageT()
{
	CString strInput;
	CString strAPos;
	CString strCommand;

	double dInput;
	double dAPos;
	double dCommand;

	GetDlgItem(IDC_EDIT_STAGE_T_INPUT)->GetWindowTextW(strInput);
	GetDlgItem(IDC_EDIT_STAGE_T_ACTUAL)->GetWindowTextW(strAPos);

	dInput = _wtof(strInput);
	dAPos = _wtof(strAPos);

	if (bChkABS == true)
	{
		strCommand = strInput;
		GetDlgItem(IDC_EDIT_STAGE_T_COMMAND)->SetWindowTextW(strCommand);

		if (_wtof(strCommand) >= CACSM::m_pACSMotion[2].m_dMinPos && _wtof(strCommand) <= CACSM::m_pACSMotion[2].m_dMaxPos)
			GetDlgItem(IDC_BTN_STAGE_T_MOVE)->EnableWindow(TRUE);

		else
			GetDlgItem(IDC_BTN_STAGE_T_MOVE)->EnableWindow(FALSE);
	}

	else if (bChkREL == true)
	{
		dCommand = dInput + dAPos;
		strCommand.Format(_T("%.4f"), dCommand);

		GetDlgItem(IDC_EDIT_STAGE_T_COMMAND)->SetWindowTextW(strCommand);

		if (_wtof(strCommand) >= CACSM::m_pACSMotion[2].m_dMinPos && _wtof(strCommand) <= CACSM::m_pACSMotion[2].m_dMaxPos)
			GetDlgItem(IDC_BTN_STAGE_T_MOVE)->EnableWindow(TRUE);

		else
			GetDlgItem(IDC_BTN_STAGE_T_MOVE)->EnableWindow(FALSE);
	}
}


void CJettingVisionDlg::OnBnClickedBtnCycle()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	dlgCycle->ShowWindow(SW_SHOW);

}
