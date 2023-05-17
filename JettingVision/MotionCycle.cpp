// MotionCycle.cpp: 구현 파일
//

#include "pch.h"
#include "JettingVision.h"
#include "MotionCycle.h"
#include "afxdialogex.h"

#include "JettingVisionDlg.h"
// MotionCycle 대화 상자

IMPLEMENT_DYNAMIC(MotionCycle, CDialogEx)

MotionCycle::MotionCycle(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MOTION_CYCLE, pParent)
{

}

MotionCycle::~MotionCycle()
{
}

void MotionCycle::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_Y_START, m_edit_y_start);
	DDX_Control(pDX, IDC_EDIT_Y_END, m_edit_y_end);
	DDX_Control(pDX, IDC_EDIT_Y_SPEED, m_edit_y_speed);
	DDX_Control(pDX, IDC_EDIT_Y_DELAY, m_edit_y_delay);
	DDX_Control(pDX, IDC_EDIT_X_SHIFT, m_edit_x_shift);
	DDX_Control(pDX, IDC_EDIT_X_REPEAT, m_edit_x_repeat);
	DDX_Control(pDX, IDC_EDIT_X_DELAY, m_edit_x_delay);
	DDX_Control(pDX, IDC_EDIT_X_START, m_edit_x_start);
	DDX_Control(pDX, IDC_EDIT_X_SPEED, m_edit_x_speed);
	DDX_Control(pDX, IDC_EDIT_Y_MOVINGSPEED, m_edit_y_movingspeed);
	DDX_Control(pDX, IDC_EDIT_X_MOVINGSPEED, m_edit_x_movingspeed);
}


BEGIN_MESSAGE_MAP(MotionCycle, CDialogEx)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_START, &MotionCycle::OnBnClickedBtnStart)
	ON_BN_CLICKED(IDC_BTN_STOP, &MotionCycle::OnBnClickedBtnStop)
END_MESSAGE_MAP()


// MotionCycle 메시지 처리기


int MotionCycle::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}


HBRUSH MotionCycle::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


BOOL MotionCycle::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	
	GetDlgItem(IDC_PIC_GRP_START)->MoveWindow(5, 5, 330, 40);
	GetDlgItem(IDC_STATIC_START)->MoveWindow(10, 10, 120, 30);
	GetDlgItem(IDC_EDIT_X_START)->MoveWindow(150, 15, 80, 20);
	GetDlgItem(IDC_EDIT_Y_START)->MoveWindow(240, 15, 80, 20);

	GetDlgItem(IDC_PIC_GRP_Y)->MoveWindow(5, 55, 240, 160);
	GetDlgItem(IDC_STATIC_Y_END)->MoveWindow(10, 60, 120, 30);
	GetDlgItem(IDC_STATIC_Y_SPEED)->MoveWindow(10, 100, 120, 30);
	GetDlgItem(IDC_STATIC_Y_MOVING_SPEED)->MoveWindow(10, 140, 120, 30);
	GetDlgItem(IDC_STATIC_Y_DELAY)->MoveWindow(10, 180, 120, 30);
	
	GetDlgItem(IDC_PIC_GRP_X)->MoveWindow(5, 225, 240, 200);
	GetDlgItem(IDC_STATIC_X_SHIFT)->MoveWindow(10, 230, 120, 30);
	GetDlgItem(IDC_STATIC_X_SPEED)->MoveWindow(10, 270, 120, 30);
	GetDlgItem(IDC_STATIC_X_MOVING_SPEED)->MoveWindow(10, 310, 120, 30);
	GetDlgItem(IDC_STATIC_X_REPEAT)->MoveWindow(10, 350, 120, 30);
	GetDlgItem(IDC_STATIC_X_DELAY)->MoveWindow(10, 390, 120, 30);

	GetDlgItem(IDC_EDIT_Y_END)->MoveWindow(150, 65, 80, 20);
	GetDlgItem(IDC_EDIT_Y_SPEED)->MoveWindow(150, 105, 80, 20);
	GetDlgItem(IDC_EDIT_Y_MOVINGSPEED)->MoveWindow(150, 145, 80, 20);
	GetDlgItem(IDC_EDIT_Y_DELAY)->MoveWindow(150, 185, 80, 20);

	GetDlgItem(IDC_EDIT_X_SHIFT)->MoveWindow(150, 235, 80, 20);
	GetDlgItem(IDC_EDIT_X_SPEED)->MoveWindow(150, 275, 80, 20);
	GetDlgItem(IDC_EDIT_X_MOVINGSPEED)->MoveWindow(150, 315, 80, 20);
	GetDlgItem(IDC_EDIT_X_REPEAT)->MoveWindow(150, 355, 80, 20);
	GetDlgItem(IDC_EDIT_X_DELAY)->MoveWindow(150, 395, 80, 20);

	GetDlgItem(IDC_BTN_START)->MoveWindow(285, 315, 50, 50);
	GetDlgItem(IDC_BTN_STOP)->MoveWindow(285, 375, 50, 50);

	staticFont = CreateFont(15, 6, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_MODERN, _T("맑은 고딕"));
	btnFont = CreateFont(15, 6, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_MODERN, _T("맑은 고딕"));

	GetDlgItem(IDC_STATIC_START)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_Y_END)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_Y_SPEED)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_Y_MOVING_SPEED)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_Y_DELAY)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_X_SHIFT)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_X_SPEED)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_X_MOVING_SPEED)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_X_REPEAT)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_X_DELAY)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);

	GetDlgItem(IDC_BTN_START)->SendMessage(WM_SETFONT, (WPARAM)btnFont, (LPARAM)TRUE);
	GetDlgItem(IDC_BTN_STOP)->SendMessage(WM_SETFONT, (WPARAM)btnFont, (LPARAM)TRUE);


	// registry에 저장된 값 가져오기

	dXStart = _wtof(AfxGetApp()->GetProfileStringW(_T("Cycle"), _T("X Start")));
	dYStart = _wtof(AfxGetApp()->GetProfileStringW(_T("Cycle"), _T("Y Start")));
	dYEnd = _wtof(AfxGetApp()->GetProfileStringW(_T("Cycle"), _T("Y End")));
	dYSpeed = _wtof(AfxGetApp()->GetProfileStringW(_T("Cycle"), _T("Y Speed")));
	dYMovingSpeed = _wtof(AfxGetApp()->GetProfileStringW(_T("Cycle"), _T("Y Moving Speed")));
	dYDelay = _wtof(AfxGetApp()->GetProfileStringW(_T("Cycle"), _T("Y Delay")));

	dXShift = _wtof(AfxGetApp()->GetProfileStringW(_T("Cycle"), _T("X Shift")));
	dXSpeed = _wtof(AfxGetApp()->GetProfileStringW(_T("Cycle"), _T("X Speed")));
	dXMovingSpeed = _wtof(AfxGetApp()->GetProfileStringW(_T("Cycle"), _T("X Moving Speed")));
	nXCount = _ttoi(AfxGetApp()->GetProfileStringW(_T("Cycle"), _T("X Count")));
	dXDelay = _wtof(AfxGetApp()->GetProfileStringW(_T("Cycle"), _T("X Delay")));

	CString strVal;
	strVal.Format(_T("%.3f"), dXStart);
	m_edit_x_start.SetWindowTextW(strVal);

	strVal.Format(_T("%.3f"), dYStart);
	m_edit_y_start.SetWindowTextW(strVal);

	strVal.Format(_T("%.3f"), dYEnd);
	m_edit_y_end.SetWindowTextW(strVal);

	strVal.Format(_T("%.3f"), dYSpeed);
	m_edit_y_speed.SetWindowTextW(strVal);

	strVal.Format(_T("%.3f"), dYMovingSpeed);
	m_edit_y_movingspeed.SetWindowTextW(strVal);

	strVal.Format(_T("%.3f"), dYDelay);
	m_edit_y_delay.SetWindowTextW(strVal);

	strVal.Format(_T("%.3f"), dXShift);
	m_edit_x_shift.SetWindowTextW(strVal);

	strVal.Format(_T("%.3f"), dXSpeed);
	m_edit_x_speed.SetWindowTextW(strVal);

	strVal.Format(_T("%.3f"), dXMovingSpeed);
	m_edit_x_movingspeed.SetWindowTextW(strVal);

	strVal.Format(_T("%d"), nXCount);
	m_edit_x_repeat.SetWindowTextW(strVal);

	strVal.Format(_T("%.3f"), dXDelay);
	m_edit_x_delay.SetWindowTextW(strVal);



	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL MotionCycle::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialogEx::PreTranslateMessage(pMsg);
}


void MotionCycle::OnBnClickedBtnStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CJettingVisionDlg* pDlg = (CJettingVisionDlg*)AfxGetMainWnd();

	m_edit_x_start.GetWindowTextW(strVal);
	dXStart = _wtof(strVal);

	m_edit_y_start.GetWindowTextW(strVal);
	dYStart = _wtof(strVal);

	m_edit_y_end.GetWindowTextW(strVal);
	dYEnd = _wtof(strVal);

	m_edit_y_speed.GetWindowTextW(strVal);
	dYSpeed = _wtof(strVal);

	m_edit_y_movingspeed.GetWindowTextW(strVal);
	dYMovingSpeed = _wtof(strVal);

	m_edit_y_delay.GetWindowTextW(strVal);
	dYDelay = _wtof(strVal);

	m_edit_x_shift.GetWindowTextW(strVal);
	dXShift = _wtof(strVal);

	m_edit_x_speed.GetWindowTextW(strVal);
	dXSpeed = _wtof(strVal);

	m_edit_x_movingspeed.GetWindowTextW(strVal);
	dXMovingSpeed = _wtof(strVal);

	m_edit_x_repeat.GetWindowTextW(strVal);
	nXCount = _ttoi(strVal);

	m_edit_x_delay.GetWindowTextW(strVal);
	dXDelay = _wtof(strVal);

	CString strRecipe;
	strRecipe.Format(_T("%.3f"), dXStart);
	AfxGetApp()->WriteProfileStringW(_T("Cycle"), _T("X Start"), strRecipe);

	strRecipe.Format(_T("%.3f"), dYStart);
	AfxGetApp()->WriteProfileStringW(_T("Cycle"), _T("Y Start"), strRecipe);

	strRecipe.Format(_T("%.3f"), dYEnd);
	AfxGetApp()->WriteProfileStringW(_T("Cycle"), _T("Y End"), strRecipe);

	strRecipe.Format(_T("%.3f"), dYSpeed);
	AfxGetApp()->WriteProfileStringW(_T("Cycle"), _T("Y Speed"), strRecipe);

	strRecipe.Format(_T("%.3f"), dYMovingSpeed);
	AfxGetApp()->WriteProfileStringW(_T("Cycle"), _T("Y Moving Speed"), strRecipe);

	strRecipe.Format(_T("%.3f"), dYDelay);
	AfxGetApp()->WriteProfileStringW(_T("Cycle"), _T("Y Delay"), strRecipe);

	strRecipe.Format(_T("%.3f"), dXShift);
	AfxGetApp()->WriteProfileStringW(_T("Cycle"), _T("X Shift"), strRecipe);

	strRecipe.Format(_T("%.3f"), dXSpeed);
	AfxGetApp()->WriteProfileStringW(_T("Cycle"), _T("X Speed"), strRecipe);

	strRecipe.Format(_T("%.3f"), dXMovingSpeed);
	AfxGetApp()->WriteProfileStringW(_T("Cycle"), _T("X Moving Speed"), strRecipe);

	strRecipe.Format(_T("%d"), nXCount);
	AfxGetApp()->WriteProfileStringW(_T("Cycle"), _T("X Count"), strRecipe);

	strRecipe.Format(_T("%.3f"), dXDelay);
	AfxGetApp()->WriteProfileStringW(_T("Cycle"), _T("X Delay"), strRecipe);


	if (dYStart >= CACSM::m_pACSMotion[1].m_dMinPos && dYStart <= CACSM::m_pACSMotion[1].m_dMaxPos 
		&& dYEnd >= CACSM::m_pACSMotion[1].m_dMinPos && dYEnd <= CACSM::m_pACSMotion[1].m_dMaxPos)
	{
		if (dXStart + (nXCount * dXShift) >= CACSM::m_pACSMotion[0].m_dMinPos && dXStart + (nXCount * dXShift) <= CACSM::m_pACSMotion[0].m_dMaxPos)
		{
			pDlg->nCycle = 0;

			BOOL motion_x = false;
			BOOL motion_y = false;

			pDlg->StageMove(1, dYStart, true, false, dYMovingSpeed);
			pDlg->StageMove(0, dXStart, true, false, dXMovingSpeed);


			do
			{
				motion_x = CACSM::m_pACSMotion[0].IsMoving();
			} while (motion_x == TRUE);

			do
			{
				motion_y = CACSM::m_pACSMotion[1].IsMoving();
			} while (motion_y == TRUE);

			pDlg->StageMove(1, dYStart, true, false, dYSpeed);
			pDlg->StageMove(0, dXStart, true, false, dXSpeed);

			pDlg->AlarmMessageDisplay(_T("CYCLE 동작을 시작하시겠습니까?"), 7);

		}

		else
		{
			pDlg->AlarmMessageDisplay(_T("X 축 이동량이 범위를 벗어났습니다."), 8);
		}
	}

	else
	{
		pDlg->AlarmMessageDisplay(_T("Y 축 이동량이 범위를 벗어났습니다."), 8);
	}
}


void MotionCycle::OnBnClickedBtnStop()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CJettingVisionDlg* pDlg = (CJettingVisionDlg*)AfxGetMainWnd();

	pDlg->bCycleStart = false;
}
