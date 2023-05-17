// SettingMotion.cpp: 구현 파일
//

#include "pch.h"
#include "JettingVision.h"
#include "SettingMotion.h"
#include "afxdialogex.h"

#include "JettingVisionDlg.h"

// SettingMotion 대화 상자

IMPLEMENT_DYNAMIC(SettingMotion, CDialogEx)

SettingMotion::SettingMotion(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SETTING_MOTION, pParent)
{

}

SettingMotion::~SettingMotion()
{
}

void SettingMotion::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_AXIS_NUM_STAGE_X, m_edit_axis_num_stage_x);
	DDX_Control(pDX, IDC_EDIT_AXIS_NUM_STAGE_Y, m_edit_axis_num_stage_y);
	DDX_Control(pDX, IDC_EDIT_AXIS_NUM_STAGE_T, m_edit_axis_num_stage_t);
	DDX_Control(pDX, IDC_EDIT_MAXSPEED_STAGE_X, m_edit_maxspeed_stage_x);
	DDX_Control(pDX, IDC_EDIT_MAXSPEED_STAGE_Y, m_edit_maxspeed_stage_y);
	DDX_Control(pDX, IDC_EDIT_MAXSPEED_STAGE_T, m_edit_maxspeed_stage_t);
	DDX_Control(pDX, IDC_EDIT_MINPOS_STAGE_X, m_edit_minpos_stage_x);
	DDX_Control(pDX, IDC_EDIT_MINPOS_STAGE_Y, m_edit_minpos_stage_y);
	DDX_Control(pDX, IDC_EDIT_MINPOS_STAGE_T, m_edit_minpos_stage_t);
	DDX_Control(pDX, IDC_EDIT_MAXPOS_STAGE_X, m_edit_maxpos_stage_x);
	DDX_Control(pDX, IDC_EDIT_MAXPOS_STAGE_Y, m_edit_maxpos_stage_y);
	DDX_Control(pDX, IDC_EDIT_MAXPOS_STAGE_T, m_edit_maxpos_stage_t);
	DDX_Control(pDX, IDC_EDIT_HOMEOFFSET_STAGE_X, m_edit_homeoffset_stage_x);
	DDX_Control(pDX, IDC_EDIT_HOMEOFFSET_STAGE_Y, m_edit_homeoffset_stage_y);
	DDX_Control(pDX, IDC_EDIT_HOMEOFFSET_STAGE_T, m_edit_homeoffset_stage_t);
	DDX_Control(pDX, IDC_EDIT_HOMEOFFSET_VEL_STAGE_X, m_edit_homeoffset_vel_stage_x);
	DDX_Control(pDX, IDC_EDIT_HOMEOFFSET_VEL_STAGE_Y, m_edit_homeoffset_vel_stage_y);
	DDX_Control(pDX, IDC_EDIT_HOMEOFFSET_VEL_STAGE_T, m_edit_homeoffset_vel_stage_t);
	DDX_Control(pDX, IDC_EDIT_POS_LOADING_STAGE_X, m_edit_pos_loading_stage_x);
	DDX_Control(pDX, IDC_EDIT_POS_LOADING_STAGE_Y, m_edit_pos_loading_stage_y);
	DDX_Control(pDX, IDC_EDIT_POS_LOADING_STAGE_T, m_edit_pos_loading_stage_t);
	DDX_Control(pDX, IDC_EDIT_POS_UNLOADING_STAGE_X, m_edit_pos_unloading_stage_x);
	DDX_Control(pDX, IDC_EDIT_POS_UNLOADING_STAGE_Y, m_edit_pos_unloading_stage_y);
	DDX_Control(pDX, IDC_EDIT_POS_UNLOADING_STAGE_T, m_edit_pos_unloading_stage_t);
	DDX_Control(pDX, IDC_EDIT_POS_SAFETY_STAGE_X, m_edit_pos_safety_stage_x);
	DDX_Control(pDX, IDC_EDIT_POS_SAFETY_STAGE_Y, m_edit_pos_safety_stage_y);
	DDX_Control(pDX, IDC_EDIT_POS_SAFETY_STAGE_T, m_edit_pos_safety_stage_t);
	DDX_Control(pDX, IDC_EDIT_POS_LEFTALIGN_STAGE_X, m_edit_pos_leftalign_stage_x);
	DDX_Control(pDX, IDC_EDIT_POS_LEFTALIGN_STAGE_Y, m_edit_pos_leftalign_stage_y);
	DDX_Control(pDX, IDC_EDIT_POS_LEFTALIGN_STAGE_T, m_edit_pos_leftalign_stage_t);
	DDX_Control(pDX, IDC_EDIT_POS_RIGHTALIGN_STAGE_X, m_edit_pos_rightalign_stage_x);
	DDX_Control(pDX, IDC_EDIT_POS_RIGHTALIGN_STAGE_Y, m_edit_pos_rightalign_stage_y);
	DDX_Control(pDX, IDC_EDIT_POS_RIGHTALIGN_STAGE_T, m_edit_pos_rightalign_stage_t);
	DDX_Control(pDX, IDC_EDIT_POS_GAPSTART_STAGE_X, m_edit_pos_gapstart_stage_x);
	DDX_Control(pDX, IDC_EDIT_POS_GAPSTART_STAGE_Y, m_edit_pos_gapstart_stage_y);
	DDX_Control(pDX, IDC_EDIT_POS_GAPSTART_STAGE_T, m_edit_pos_gapstart_stage_t);
	DDX_Control(pDX, IDC_EDIT_POS_GAPEND_STAGE_X, m_edit_pos_gapend_stage_x);
	DDX_Control(pDX, IDC_EDIT_POS_GAPEND_STAGE_Y, m_edit_pos_gapend_stage_y);
	DDX_Control(pDX, IDC_EDIT_POS_GAPEND_STAGE_T, m_edit_pos_gapend_stage_t);
	DDX_Control(pDX, IDC_EDIT_POS_PROCSTART_STAGE_X, m_edit_pos_procstart_stage_x);
	DDX_Control(pDX, IDC_EDIT_POS_PROCSTART_STAGE_Y, m_edit_pos_procstart_stage_y);
	DDX_Control(pDX, IDC_EDIT_POS_PROCSTART_STAGE_T, m_edit_pos_procstart_stage_t);
	DDX_Control(pDX, IDC_EDIT_POS_PROCEND_STAGE_X, m_edit_pos_procend_stage_x);
	DDX_Control(pDX, IDC_EDIT_POS_PROCEND_STAGE_Y, m_edit_pos_procend_stage_y);
	DDX_Control(pDX, IDC_EDIT_POS_PROCEND_STAGE_T, m_edit_pos_procend_stage_t);
	DDX_Control(pDX, IDC_EDIT_POS_REVIEW_STAGE_X, m_edit_pos_review_stage_x);
	DDX_Control(pDX, IDC_EDIT_POS_REVIEW_STAGE_Y, m_edit_pos_review_stage_y);
	DDX_Control(pDX, IDC_EDIT_POS_REVIEW_STAGE_T, m_edit_pos_review_stage_t);
	DDX_Control(pDX, IDC_EDIT_MOVING_SPEED_STAGE_X, m_edit_moving_speed_stage_x);
	DDX_Control(pDX, IDC_EDIT_MOVING_SPEED_STAGE_Y, m_edit_moving_speed_stage_y);
	DDX_Control(pDX, IDC_EDIT_MOVING_SPEED_STAGE_T, m_edit_moving_speed_stage_t);
	DDX_Control(pDX, IDC_EDIT_JETTING_SPEED_STAGE_X, m_edit_jetting_speed_stage_x);
	DDX_Control(pDX, IDC_EDIT_JETTING_SPEED_STAGE_Y, m_edit_jetting_speed_stage_y);
	DDX_Control(pDX, IDC_EDIT_JETTING_SPEED_STAGE_T, m_edit_jetting_speed_stage_t);
}


BEGIN_MESSAGE_MAP(SettingMotion, CDialogEx)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// SettingMotion 메시지 처리기


int SettingMotion::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}


HBRUSH SettingMotion::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


BOOL SettingMotion::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	
	GetDlgItem(IDC_STATIC_STAGE_X)->MoveWindow(100, 20, 80, 30);
	GetDlgItem(IDC_STATIC_STAGE_Y)->MoveWindow(195, 20, 80, 30);
	GetDlgItem(IDC_STATIC_STAGE_T)->MoveWindow(290, 20, 80, 30);

	GetDlgItem(IDC_STATIC_STAGE_AXIS_NUM)->MoveWindow(10, 60, 80, 30);
	GetDlgItem(IDC_STATIC_STAGE_MAXSPEED)->MoveWindow(10, 100, 80, 30);
	GetDlgItem(IDC_STATIC_STAGE_MINPOS)->MoveWindow(10, 140, 80, 30);
	GetDlgItem(IDC_STATIC_STAGE_MAXPOS)->MoveWindow(10, 180, 80, 30);
	GetDlgItem(IDC_STATIC_STAGE_HOMEOFFSET)->MoveWindow(10, 220, 80, 30);
	GetDlgItem(IDC_STATIC_STAGE_HOMEOFFSET_VEL)->MoveWindow(10, 260, 80, 30);

	GetDlgItem(IDC_EDIT_AXIS_NUM_STAGE_X)->MoveWindow(100, 60, 80, 30);
	GetDlgItem(IDC_EDIT_MAXSPEED_STAGE_X)->MoveWindow(100, 100, 80, 30);
	GetDlgItem(IDC_EDIT_MINPOS_STAGE_X)->MoveWindow(100, 140, 80, 30);
	GetDlgItem(IDC_EDIT_MAXPOS_STAGE_X)->MoveWindow(100, 180, 80, 30);
	GetDlgItem(IDC_EDIT_HOMEOFFSET_STAGE_X)->MoveWindow(100, 220, 80, 30);
	GetDlgItem(IDC_EDIT_HOMEOFFSET_VEL_STAGE_X)->MoveWindow(100, 260, 80, 30);

	GetDlgItem(IDC_EDIT_AXIS_NUM_STAGE_Y)->MoveWindow(195, 60, 80, 30);
	GetDlgItem(IDC_EDIT_MAXSPEED_STAGE_Y)->MoveWindow(195, 100, 80, 30);
	GetDlgItem(IDC_EDIT_MINPOS_STAGE_Y)->MoveWindow(195, 140, 80, 30);
	GetDlgItem(IDC_EDIT_MAXPOS_STAGE_Y)->MoveWindow(195, 180, 80, 30);
	GetDlgItem(IDC_EDIT_HOMEOFFSET_STAGE_Y)->MoveWindow(195, 220, 80, 30);
	GetDlgItem(IDC_EDIT_HOMEOFFSET_VEL_STAGE_Y)->MoveWindow(195, 260, 80, 30);

	GetDlgItem(IDC_EDIT_AXIS_NUM_STAGE_T)->MoveWindow(290, 60, 80, 30);
	GetDlgItem(IDC_EDIT_MAXSPEED_STAGE_T)->MoveWindow(290, 100, 80, 30);
	GetDlgItem(IDC_EDIT_MINPOS_STAGE_T)->MoveWindow(290, 140, 80, 30);
	GetDlgItem(IDC_EDIT_MAXPOS_STAGE_T)->MoveWindow(290, 180, 80, 30);
	GetDlgItem(IDC_EDIT_HOMEOFFSET_STAGE_T)->MoveWindow(290, 220, 80, 30);
	GetDlgItem(IDC_EDIT_HOMEOFFSET_VEL_STAGE_T)->MoveWindow(290, 260, 80, 30);

	GetDlgItem(IDC_STATIC_POS_LOADING)->MoveWindow(10, 330, 80, 30);
	GetDlgItem(IDC_STATIC_POS_UNLOADING)->MoveWindow(10, 370, 80, 30);
	GetDlgItem(IDC_STATIC_POS_SAFETY)->MoveWindow(10, 410, 80, 30);
	GetDlgItem(IDC_STATIC_POS_LEFTALIGN)->MoveWindow(10, 450, 80, 30);
	GetDlgItem(IDC_STATIC_POS_RIGHTALIGN)->MoveWindow(10, 490, 80, 30);
	GetDlgItem(IDC_STATIC_POS_GAPSTART)->MoveWindow(10, 530, 80, 30);
	GetDlgItem(IDC_STATIC_POS_GAPEND)->MoveWindow(10, 570, 80, 30);
	GetDlgItem(IDC_STATIC_POS_PROCSTART)->MoveWindow(10, 610, 80, 30);
	GetDlgItem(IDC_STATIC_POS_PROCEND)->MoveWindow(10, 650, 80, 30);
	GetDlgItem(IDC_STATIC_POS_REVIEW)->MoveWindow(10, 690, 80, 30);
	GetDlgItem(IDC_STATIC_MOVING_SPEED)->MoveWindow(10, 730, 80, 30);
	GetDlgItem(IDC_STATIC_JETTING_SPEED)->MoveWindow(10, 770, 80, 30);

	GetDlgItem(IDC_EDIT_POS_LOADING_STAGE_X)->MoveWindow(100, 330, 80, 30);
	GetDlgItem(IDC_EDIT_POS_UNLOADING_STAGE_X)->MoveWindow(100, 370, 80, 30);
	GetDlgItem(IDC_EDIT_POS_SAFETY_STAGE_X)->MoveWindow(100, 410, 80, 30);
	GetDlgItem(IDC_EDIT_POS_LEFTALIGN_STAGE_X)->MoveWindow(100, 450, 80, 30);
	GetDlgItem(IDC_EDIT_POS_RIGHTALIGN_STAGE_X)->MoveWindow(100, 490, 80, 30);
	GetDlgItem(IDC_EDIT_POS_GAPSTART_STAGE_X)->MoveWindow(100, 530, 80, 30);
	GetDlgItem(IDC_EDIT_POS_GAPEND_STAGE_X)->MoveWindow(100, 570, 80, 30);
	GetDlgItem(IDC_EDIT_POS_PROCSTART_STAGE_X)->MoveWindow(100, 610, 80, 30);
	GetDlgItem(IDC_EDIT_POS_PROCEND_STAGE_X)->MoveWindow(100, 650, 80, 30);
	GetDlgItem(IDC_EDIT_POS_REVIEW_STAGE_X)->MoveWindow(100, 690, 80, 30);
	GetDlgItem(IDC_EDIT_MOVING_SPEED_STAGE_X)->MoveWindow(100, 730, 80, 30);
	GetDlgItem(IDC_EDIT_JETTING_SPEED_STAGE_X)->MoveWindow(100, 770, 80, 30);

	GetDlgItem(IDC_EDIT_POS_LOADING_STAGE_Y)->MoveWindow(195, 330, 80, 30);
	GetDlgItem(IDC_EDIT_POS_UNLOADING_STAGE_Y)->MoveWindow(195, 370, 80, 30);
	GetDlgItem(IDC_EDIT_POS_SAFETY_STAGE_Y)->MoveWindow(195, 410, 80, 30);
	GetDlgItem(IDC_EDIT_POS_LEFTALIGN_STAGE_Y)->MoveWindow(195, 450, 80, 30);
	GetDlgItem(IDC_EDIT_POS_RIGHTALIGN_STAGE_Y)->MoveWindow(195, 490, 80, 30);
	GetDlgItem(IDC_EDIT_POS_GAPSTART_STAGE_Y)->MoveWindow(195, 530, 80, 30);
	GetDlgItem(IDC_EDIT_POS_GAPEND_STAGE_Y)->MoveWindow(195, 570, 80, 30);
	GetDlgItem(IDC_EDIT_POS_PROCSTART_STAGE_Y)->MoveWindow(195, 610, 80, 30);
	GetDlgItem(IDC_EDIT_POS_PROCEND_STAGE_Y)->MoveWindow(195, 650, 80, 30);
	GetDlgItem(IDC_EDIT_POS_REVIEW_STAGE_Y)->MoveWindow(195, 690, 80, 30);
	GetDlgItem(IDC_EDIT_MOVING_SPEED_STAGE_Y)->MoveWindow(195, 730, 80, 30);
	GetDlgItem(IDC_EDIT_JETTING_SPEED_STAGE_Y)->MoveWindow(195, 770, 80, 30);

	GetDlgItem(IDC_EDIT_POS_LOADING_STAGE_T)->MoveWindow(290, 330, 80, 30);
	GetDlgItem(IDC_EDIT_POS_UNLOADING_STAGE_T)->MoveWindow(290, 370, 80, 30);
	GetDlgItem(IDC_EDIT_POS_SAFETY_STAGE_T)->MoveWindow(290, 410, 80, 30);
	GetDlgItem(IDC_EDIT_POS_LEFTALIGN_STAGE_T)->MoveWindow(290, 450, 80, 30);
	GetDlgItem(IDC_EDIT_POS_RIGHTALIGN_STAGE_T)->MoveWindow(290, 490, 80, 30);
	GetDlgItem(IDC_EDIT_POS_GAPSTART_STAGE_T)->MoveWindow(290, 530, 80, 30);
	GetDlgItem(IDC_EDIT_POS_GAPEND_STAGE_T)->MoveWindow(290, 570, 80, 30);
	GetDlgItem(IDC_EDIT_POS_PROCSTART_STAGE_T)->MoveWindow(290, 610, 80, 30);
	GetDlgItem(IDC_EDIT_POS_PROCEND_STAGE_T)->MoveWindow(290, 650, 80, 30);
	GetDlgItem(IDC_EDIT_POS_REVIEW_STAGE_T)->MoveWindow(290, 690, 80, 30);
	GetDlgItem(IDC_EDIT_MOVING_SPEED_STAGE_T)->MoveWindow(290, 730, 80, 30);
	GetDlgItem(IDC_EDIT_JETTING_SPEED_STAGE_T)->MoveWindow(290, 770, 80, 30);

	staticFont = CreateFont(15, 6, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_MODERN, _T("맑은 고딕"));

	GetDlgItem(IDC_STATIC_STAGE_X)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_STAGE_Y)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_STAGE_T)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_POS_LOADING)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_POS_UNLOADING)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_POS_SAFETY)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_POS_LEFTALIGN)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_POS_RIGHTALIGN)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_POS_GAPSTART)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_POS_GAPEND)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_POS_PROCSTART)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_POS_PROCEND)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_POS_REVIEW)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_MOVING_SPEED)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_JETTING_SPEED)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_STAGE_AXIS_NUM)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_STAGE_MAXSPEED)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_STAGE_MINPOS)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_STAGE_MAXPOS)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_STAGE_HOMEOFFSET)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_STAGE_HOMEOFFSET_VEL)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);

	SettingModify(false);

	CRect rectEdit;

	((CEdit*)GetDlgItem(IDC_EDIT_MAXSPEED_STAGE_X))->GetRect(rectEdit);

	rectEdit.top += 4;

	((CEdit*)GetDlgItem(IDC_EDIT_AXIS_NUM_STAGE_X))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_MAXSPEED_STAGE_X))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_MINPOS_STAGE_X))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_MAXPOS_STAGE_X))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_HOMEOFFSET_STAGE_X))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_HOMEOFFSET_VEL_STAGE_X))->SetRect(rectEdit);

	((CEdit*)GetDlgItem(IDC_EDIT_AXIS_NUM_STAGE_Y))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_MAXSPEED_STAGE_Y))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_MINPOS_STAGE_Y))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_MAXPOS_STAGE_Y))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_HOMEOFFSET_STAGE_Y))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_HOMEOFFSET_VEL_STAGE_Y))->SetRect(rectEdit);

	((CEdit*)GetDlgItem(IDC_EDIT_AXIS_NUM_STAGE_T))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_MAXSPEED_STAGE_T))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_MINPOS_STAGE_T))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_MAXPOS_STAGE_T))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_HOMEOFFSET_STAGE_T))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_HOMEOFFSET_VEL_STAGE_T))->SetRect(rectEdit);

	((CEdit*)GetDlgItem(IDC_EDIT_POS_LOADING_STAGE_X))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_POS_UNLOADING_STAGE_X))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_POS_SAFETY_STAGE_X))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_POS_LEFTALIGN_STAGE_X))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_POS_RIGHTALIGN_STAGE_X))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_POS_GAPSTART_STAGE_X))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_POS_GAPEND_STAGE_X))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_POS_PROCSTART_STAGE_X))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_POS_PROCEND_STAGE_X))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_POS_REVIEW_STAGE_X))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_MOVING_SPEED_STAGE_X))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_JETTING_SPEED_STAGE_X))->SetRect(rectEdit);

	((CEdit*)GetDlgItem(IDC_EDIT_POS_LOADING_STAGE_Y))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_POS_UNLOADING_STAGE_Y))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_POS_SAFETY_STAGE_Y))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_POS_LEFTALIGN_STAGE_Y))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_POS_RIGHTALIGN_STAGE_Y))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_POS_GAPSTART_STAGE_Y))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_POS_GAPEND_STAGE_Y))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_POS_PROCSTART_STAGE_Y))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_POS_PROCEND_STAGE_Y))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_POS_REVIEW_STAGE_Y))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_MOVING_SPEED_STAGE_Y))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_JETTING_SPEED_STAGE_Y))->SetRect(rectEdit);

	((CEdit*)GetDlgItem(IDC_EDIT_POS_LOADING_STAGE_T))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_POS_UNLOADING_STAGE_T))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_POS_SAFETY_STAGE_T))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_POS_LEFTALIGN_STAGE_T))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_POS_RIGHTALIGN_STAGE_T))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_POS_GAPSTART_STAGE_T))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_POS_GAPEND_STAGE_T))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_POS_PROCSTART_STAGE_T))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_POS_PROCEND_STAGE_T))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_POS_REVIEW_STAGE_T))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_MOVING_SPEED_STAGE_T))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_JETTING_SPEED_STAGE_T))->SetRect(rectEdit);

	LoadRecipe();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL SettingMotion::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN) // ENTER키 눌릴 시
			return TRUE;
		else if (pMsg->wParam == VK_ESCAPE) // ESC키 눌릴 시
			return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void SettingMotion::SettingModify(BOOL nCase)
{
	GetDlgItem(IDC_EDIT_AXIS_NUM_STAGE_X)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_MAXSPEED_STAGE_X)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_MINPOS_STAGE_X)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_MAXPOS_STAGE_X)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_HOMEOFFSET_STAGE_X)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_HOMEOFFSET_STAGE_X)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_HOMEOFFSET_VEL_STAGE_X)->EnableWindow(nCase);

	GetDlgItem(IDC_EDIT_AXIS_NUM_STAGE_Y)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_MAXSPEED_STAGE_Y)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_MINPOS_STAGE_Y)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_MAXPOS_STAGE_Y)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_HOMEOFFSET_STAGE_Y)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_HOMEOFFSET_VEL_STAGE_Y)->EnableWindow(nCase);

	GetDlgItem(IDC_EDIT_AXIS_NUM_STAGE_T)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_MAXSPEED_STAGE_T)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_MINPOS_STAGE_T)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_MAXPOS_STAGE_T)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_HOMEOFFSET_STAGE_T)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_HOMEOFFSET_VEL_STAGE_T)->EnableWindow(nCase);

	GetDlgItem(IDC_EDIT_POS_LOADING_STAGE_X)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_POS_UNLOADING_STAGE_X)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_POS_SAFETY_STAGE_X)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_POS_LEFTALIGN_STAGE_X)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_POS_RIGHTALIGN_STAGE_X)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_POS_GAPSTART_STAGE_X)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_POS_GAPEND_STAGE_X)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_POS_PROCSTART_STAGE_X)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_POS_PROCEND_STAGE_X)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_POS_REVIEW_STAGE_X)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_MOVING_SPEED_STAGE_X)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_JETTING_SPEED_STAGE_X)->EnableWindow(nCase);

	GetDlgItem(IDC_EDIT_POS_LOADING_STAGE_Y)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_POS_UNLOADING_STAGE_Y)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_POS_SAFETY_STAGE_Y)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_POS_LEFTALIGN_STAGE_Y)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_POS_RIGHTALIGN_STAGE_Y)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_POS_GAPSTART_STAGE_Y)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_POS_GAPEND_STAGE_Y)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_POS_PROCSTART_STAGE_Y)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_POS_PROCEND_STAGE_Y)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_POS_REVIEW_STAGE_Y)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_MOVING_SPEED_STAGE_Y)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_JETTING_SPEED_STAGE_Y)->EnableWindow(nCase);

	GetDlgItem(IDC_EDIT_POS_LOADING_STAGE_T)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_POS_UNLOADING_STAGE_T)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_POS_SAFETY_STAGE_T)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_POS_LEFTALIGN_STAGE_T)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_POS_RIGHTALIGN_STAGE_T)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_POS_GAPSTART_STAGE_T)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_POS_GAPEND_STAGE_T)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_POS_PROCSTART_STAGE_T)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_POS_PROCEND_STAGE_T)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_POS_REVIEW_STAGE_T)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_MOVING_SPEED_STAGE_T)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_JETTING_SPEED_STAGE_T)->EnableWindow(nCase);
}


void SettingMotion::LoadRecipe()
{
	CJettingVisionDlg* pDlg = (CJettingVisionDlg*)AfxGetMainWnd();

	bool		bRet;
	CString		strPath;
	CString		strData;
	TCHAR		szData[MAX_PATH];

	strPath = _T("D:\\JettingVision\\Config\\1\\RecipeMotion.ini");

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("STAGE X"), _T("LOADING"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	dPosLoadingX = _wtof(szData);
	GetDlgItem(IDC_EDIT_POS_LOADING_STAGE_X)->SetWindowTextW(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("STAGE X"), _T("UNLOADING"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	dPosUnloadingX = _wtof(szData);
	GetDlgItem(IDC_EDIT_POS_UNLOADING_STAGE_X)->SetWindowTextW(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("STAGE X"), _T("SAFETY"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	dPosSafetyX = _wtof(szData);
	GetDlgItem(IDC_EDIT_POS_SAFETY_STAGE_X)->SetWindowTextW(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("STAGE X"), _T("ALIGNLEFT"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	dPosAlignleftX = _wtof(szData);
	GetDlgItem(IDC_EDIT_POS_LEFTALIGN_STAGE_X)->SetWindowTextW(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("STAGE X"), _T("ALIGNRIGHT"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	dPosAlignrightX = _wtof(szData);
	GetDlgItem(IDC_EDIT_POS_RIGHTALIGN_STAGE_X)->SetWindowTextW(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("STAGE X"), _T("GAPSTART"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	dPosGapstartX = _wtof(szData);
	GetDlgItem(IDC_EDIT_POS_GAPSTART_STAGE_X)->SetWindowTextW(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("STAGE X"), _T("GAPEND"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	dPosGapendX = _wtof(szData);
	GetDlgItem(IDC_EDIT_POS_GAPEND_STAGE_X)->SetWindowTextW(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("STAGE X"), _T("PROCSTART"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	dPosProcstartX = _wtof(szData);
	GetDlgItem(IDC_EDIT_POS_PROCSTART_STAGE_X)->SetWindowTextW(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("STAGE X"), _T("PROCEND"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	dPosProcendX = _wtof(szData);
	GetDlgItem(IDC_EDIT_POS_PROCEND_STAGE_X)->SetWindowTextW(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("STAGE X"), _T("REVIEW"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	dPosReviewX = _wtof(szData);
	GetDlgItem(IDC_EDIT_POS_REVIEW_STAGE_X)->SetWindowTextW(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("STAGE X"), _T("MOVINGSPEED"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	dMovingSpeedX = _wtof(szData);
	GetDlgItem(IDC_EDIT_MOVING_SPEED_STAGE_X)->SetWindowTextW(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("STAGE X"), _T("JETTINGSPEED"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	dJettingSpeedX = _wtof(szData);
	GetDlgItem(IDC_EDIT_JETTING_SPEED_STAGE_X)->SetWindowTextW(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("STAGE Y"), _T("LOADING"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	dPosLoadingY = _wtof(szData);
	GetDlgItem(IDC_EDIT_POS_LOADING_STAGE_Y)->SetWindowTextW(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("STAGE Y"), _T("UNLOADING"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	dPosUnloadingY = _wtof(szData);
	GetDlgItem(IDC_EDIT_POS_UNLOADING_STAGE_Y)->SetWindowTextW(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("STAGE Y"), _T("SAFETY"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	dPosSafetyY = _wtof(szData);
	GetDlgItem(IDC_EDIT_POS_SAFETY_STAGE_Y)->SetWindowTextW(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("STAGE Y"), _T("ALIGNLEFT"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	dPosAlignleftY = _wtof(szData);
	GetDlgItem(IDC_EDIT_POS_LEFTALIGN_STAGE_Y)->SetWindowTextW(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("STAGE Y"), _T("ALIGNRIGHT"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	dPosAlignrightY = _wtof(szData);
	GetDlgItem(IDC_EDIT_POS_RIGHTALIGN_STAGE_Y)->SetWindowTextW(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("STAGE Y"), _T("GAPSTART"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	dPosGapstartY = _wtof(szData);
	GetDlgItem(IDC_EDIT_POS_GAPSTART_STAGE_Y)->SetWindowTextW(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("STAGE Y"), _T("GAPEND"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	dPosGapendY = _wtof(szData);
	GetDlgItem(IDC_EDIT_POS_GAPEND_STAGE_Y)->SetWindowTextW(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("STAGE Y"), _T("PROCSTART"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	dPosProcstartY = _wtof(szData);
	GetDlgItem(IDC_EDIT_POS_PROCSTART_STAGE_Y)->SetWindowTextW(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("STAGE Y"), _T("PROCEND"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	dPosProcendY = _wtof(szData);
	GetDlgItem(IDC_EDIT_POS_PROCEND_STAGE_Y)->SetWindowTextW(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("STAGE Y"), _T("REVIEW"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	dPosReviewY = _wtof(szData);
	GetDlgItem(IDC_EDIT_POS_REVIEW_STAGE_Y)->SetWindowTextW(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("STAGE Y"), _T("MOVINGSPEED"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	dMovingSpeedY = _wtof(szData);
	GetDlgItem(IDC_EDIT_MOVING_SPEED_STAGE_Y)->SetWindowTextW(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("STAGE Y"), _T("JETTINGSPEED"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	dJettingSpeedY = _wtof(szData);
	GetDlgItem(IDC_EDIT_JETTING_SPEED_STAGE_Y)->SetWindowTextW(szData);


	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("STAGE T"), _T("LOADING"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	dPosLoadingT = _wtof(szData);
	GetDlgItem(IDC_EDIT_POS_LOADING_STAGE_T)->SetWindowTextW(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("STAGE T"), _T("UNLOADING"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	dPosUnloadingT = _wtof(szData);
	GetDlgItem(IDC_EDIT_POS_UNLOADING_STAGE_T)->SetWindowTextW(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("STAGE T"), _T("SAFETY"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	dPosSafetyT = _wtof(szData);
	GetDlgItem(IDC_EDIT_POS_SAFETY_STAGE_T)->SetWindowTextW(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("STAGE T"), _T("ALIGNLEFT"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	dPosAlignleftT = _wtof(szData);
	GetDlgItem(IDC_EDIT_POS_LEFTALIGN_STAGE_T)->SetWindowTextW(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("STAGE T"), _T("ALIGNRIGHT"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	dPosAlignrightT = _wtof(szData);
	GetDlgItem(IDC_EDIT_POS_RIGHTALIGN_STAGE_T)->SetWindowTextW(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("STAGE T"), _T("GAPSTART"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	dPosGapstartT = _wtof(szData);
	GetDlgItem(IDC_EDIT_POS_GAPSTART_STAGE_T)->SetWindowTextW(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("STAGE T"), _T("GAPEND"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	dPosGapendT = _wtof(szData);
	GetDlgItem(IDC_EDIT_POS_GAPEND_STAGE_T)->SetWindowTextW(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("STAGE T"), _T("PROCSTART"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	dPosProcstartT = _wtof(szData);
	GetDlgItem(IDC_EDIT_POS_PROCSTART_STAGE_T)->SetWindowTextW(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("STAGE T"), _T("PROCEND"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	dPosProcendT = _wtof(szData);
	GetDlgItem(IDC_EDIT_POS_PROCEND_STAGE_T)->SetWindowTextW(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("STAGE T"), _T("REVIEW"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	dPosReviewT = _wtof(szData);
	GetDlgItem(IDC_EDIT_POS_REVIEW_STAGE_T)->SetWindowTextW(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("STAGE T"), _T("MOVINGSPEED"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	dMovingSpeedT = _wtof(szData);
	GetDlgItem(IDC_EDIT_MOVING_SPEED_STAGE_T)->SetWindowTextW(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("STAGE T"), _T("JETTINGSPEED"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	dJettingSpeedT = _wtof(szData);
	GetDlgItem(IDC_EDIT_JETTING_SPEED_STAGE_T)->SetWindowTextW(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("JETTING"), _T("JETTING_OFFSET"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	pDlg->dJettinOffset = _wtof(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("JETTING"), _T("JETTING_LENGTH"), _T("10"), szData, MAX_PATH, strPath);
	strData = szData;
	pDlg->dJettingLength = _wtof(szData);
}


void SettingMotion::SaveRecipe()
{
	bool		bRet;
	CString		strPath;
	CString		strTag;
	CString		strData;

	strPath = _T("D:\\JettingVision\\Config\\1\\RecipeMotion.ini");

	m_edit_pos_loading_stage_x.GetWindowTextW(strData);
	WritePrivateProfileString(_T("STAGE X"), _T("LOADING"), strData, strPath);

	m_edit_pos_unloading_stage_x.GetWindowTextW(strData);
	WritePrivateProfileString(_T("STAGE X"), _T("UNLOADING"), strData, strPath);

	m_edit_pos_safety_stage_x.GetWindowTextW(strData);
	WritePrivateProfileString(_T("STAGE X"), _T("SAFETY"), strData, strPath);

	m_edit_pos_leftalign_stage_x.GetWindowTextW(strData);
	WritePrivateProfileString(_T("STAGE X"), _T("ALIGNLEFT"), strData, strPath);

	m_edit_pos_rightalign_stage_x.GetWindowTextW(strData);
	WritePrivateProfileString(_T("STAGE X"), _T("ALIGNRIGHT"), strData, strPath);

	m_edit_pos_gapstart_stage_x.GetWindowTextW(strData);
	WritePrivateProfileString(_T("STAGE X"), _T("GAPSTART"), strData, strPath);

	m_edit_pos_gapend_stage_x.GetWindowTextW(strData);
	WritePrivateProfileString(_T("STAGE X"), _T("GAPEND"), strData, strPath);

	m_edit_pos_procstart_stage_x.GetWindowTextW(strData);
	WritePrivateProfileString(_T("STAGE X"), _T("PROCSTART"), strData, strPath);

	m_edit_pos_procend_stage_x.GetWindowTextW(strData);
	WritePrivateProfileString(_T("STAGE X"), _T("PROCEND"), strData, strPath);

	m_edit_pos_review_stage_x.GetWindowTextW(strData);
	WritePrivateProfileString(_T("STAGE X"), _T("REVIEW"), strData, strPath);

	m_edit_moving_speed_stage_x.GetWindowTextW(strData);
	WritePrivateProfileString(_T("STAGE X"), _T("MOVINGSPEED"), strData, strPath);

	m_edit_jetting_speed_stage_x.GetWindowTextW(strData);
	WritePrivateProfileString(_T("STAGE X"), _T("JETTINGSPEED"), strData, strPath);


	m_edit_pos_loading_stage_y.GetWindowTextW(strData);
	WritePrivateProfileString(_T("STAGE Y"), _T("LOADING"), strData, strPath);

	m_edit_pos_unloading_stage_y.GetWindowTextW(strData);
	WritePrivateProfileString(_T("STAGE Y"), _T("UNLOADING"), strData, strPath);

	m_edit_pos_safety_stage_y.GetWindowTextW(strData);
	WritePrivateProfileString(_T("STAGE Y"), _T("SAFETY"), strData, strPath);

	m_edit_pos_leftalign_stage_y.GetWindowTextW(strData);
	WritePrivateProfileString(_T("STAGE Y"), _T("ALIGNLEFT"), strData, strPath);

	m_edit_pos_rightalign_stage_y.GetWindowTextW(strData);
	WritePrivateProfileString(_T("STAGE Y"), _T("ALIGNRIGHT"), strData, strPath);

	m_edit_pos_gapstart_stage_y.GetWindowTextW(strData);
	WritePrivateProfileString(_T("STAGE Y"), _T("GAPSTART"), strData, strPath);

	m_edit_pos_gapend_stage_y.GetWindowTextW(strData);
	WritePrivateProfileString(_T("STAGE Y"), _T("GAPEND"), strData, strPath);

	m_edit_pos_procstart_stage_y.GetWindowTextW(strData);
	WritePrivateProfileString(_T("STAGE Y"), _T("PROCSTART"), strData, strPath);

	m_edit_pos_procend_stage_y.GetWindowTextW(strData);
	WritePrivateProfileString(_T("STAGE Y"), _T("PROCEND"), strData, strPath);

	m_edit_pos_review_stage_y.GetWindowTextW(strData);
	WritePrivateProfileString(_T("STAGE Y"), _T("REVIEW"), strData, strPath);

	m_edit_moving_speed_stage_y.GetWindowTextW(strData);
	WritePrivateProfileString(_T("STAGE Y"), _T("MOVINGSPEED"), strData, strPath);

	m_edit_jetting_speed_stage_y.GetWindowTextW(strData);
	WritePrivateProfileString(_T("STAGE Y"), _T("JETTINGSPEED"), strData, strPath);


	m_edit_pos_loading_stage_t.GetWindowTextW(strData);
	WritePrivateProfileString(_T("STAGE T"), _T("LOADING"), strData, strPath);

	m_edit_pos_unloading_stage_t.GetWindowTextW(strData);
	WritePrivateProfileString(_T("STAGE T"), _T("UNLOADING"), strData, strPath);

	m_edit_pos_safety_stage_t.GetWindowTextW(strData);
	WritePrivateProfileString(_T("STAGE T"), _T("SAFETY"), strData, strPath);

	m_edit_pos_leftalign_stage_t.GetWindowTextW(strData);
	WritePrivateProfileString(_T("STAGE T"), _T("ALIGNLEFT"), strData, strPath);

	m_edit_pos_rightalign_stage_t.GetWindowTextW(strData);
	WritePrivateProfileString(_T("STAGE T"), _T("ALIGNRIGHT"), strData, strPath);

	m_edit_pos_gapstart_stage_t.GetWindowTextW(strData);
	WritePrivateProfileString(_T("STAGE T"), _T("GAPSTART"), strData, strPath);

	m_edit_pos_gapend_stage_t.GetWindowTextW(strData);
	WritePrivateProfileString(_T("STAGE T"), _T("GAPEND"), strData, strPath);

	m_edit_pos_procstart_stage_t.GetWindowTextW(strData);
	WritePrivateProfileString(_T("STAGE T"), _T("PROCSTART"), strData, strPath);

	m_edit_pos_procend_stage_t.GetWindowTextW(strData);
	WritePrivateProfileString(_T("STAGE T"), _T("PROCEND"), strData, strPath);

	m_edit_pos_review_stage_t.GetWindowTextW(strData);
	WritePrivateProfileString(_T("STAGE T"), _T("REVIEW"), strData, strPath);

	m_edit_moving_speed_stage_t.GetWindowTextW(strData);
	WritePrivateProfileString(_T("STAGE T"), _T("MOVINGSPEED"), strData, strPath);

	m_edit_jetting_speed_stage_t.GetWindowTextW(strData);
	WritePrivateProfileString(_T("STAGE T"), _T("JETTINGSPEED"), strData, strPath);
}