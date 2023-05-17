// SettingVision.cpp: 구현 파일
//

#include "pch.h"
#include "JettingVision.h"
#include "SettingVision.h"
#include "afxdialogex.h"

#include "JettingVisionDlg.h"

// SettingVision 대화 상자

IMPLEMENT_DYNAMIC(SettingVision, CDialogEx)

SettingVision::SettingVision(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SETTING_VISION, pParent)
{

}

SettingVision::~SettingVision()
{
}

void SettingVision::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_CAMERA_RESOLUTION_X, m_edit_camera_resolution_x);
	DDX_Control(pDX, IDC_EDIT_CAMERA_RESOLUTION_Y, m_edit_camera_resolution_y);
	DDX_Control(pDX, IDC_EDIT_CAMERA_PIXELSIZE, m_edit_camera_pixelsize);
	DDX_Control(pDX, IDC_EDIT_CAMERA_MAGNI, m_edit_camera_magni);
	DDX_Control(pDX, IDC_EDIT_LIGHT_1, m_edit_light_1);
	DDX_Control(pDX, IDC_EDIT_LIGHT_2, m_edit_light_2);
	DDX_Control(pDX, IDC_EDIT_GAP_COUNT, m_edit_gap_count);
	DDX_Control(pDX, IDC_EDIT_GAP_RANGE, m_edit_gap_range);
	DDX_Control(pDX, IDC_EDIT_GAP_LIMIT, m_edit_gap_limit);
	DDX_Control(pDX, IDC_EDIT_UVLED, m_edit_uvled);
	DDX_Control(pDX, IDC_EDIT_ALIGN_ROI_START_X, m_edit_align_roi_start_x);
	DDX_Control(pDX, IDC_EDIT_ALIGN_ROI_START_Y, m_edit_align_roi_start_y);
	DDX_Control(pDX, IDC_EDIT_ALIGN_ROI_END_X, m_edit_align_roi_end_x);
	DDX_Control(pDX, IDC_EDIT_ALIGN_ROI_END_Y, m_edit_align_roi_end_y);
	DDX_Control(pDX, IDC_EDIT_ALIGN_LIMIT_STAGE_X, m_edit_align_limit_stage_x);
	DDX_Control(pDX, IDC_EDIT_ALIGN_LIMIT_STAGE_Y, m_edit_align_limit_stage_y);
	DDX_Control(pDX, IDC_EDIT_ALIGN_LIMIT_STAGE_T, m_edit_align_limit_stage_t);
}


BEGIN_MESSAGE_MAP(SettingVision, CDialogEx)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_EDIT_LIGHT_1, &SettingVision::OnEnChangeEditLight1)
	ON_EN_CHANGE(IDC_EDIT_LIGHT_2, &SettingVision::OnEnChangeEditLight2)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_LIGHT_1, &SettingVision::OnDeltaposSpinLight1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_LIGHT_2, &SettingVision::OnDeltaposSpinLight2)
END_MESSAGE_MAP()


// SettingVision 메시지 처리기


int SettingVision::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}


HBRUSH SettingVision::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


BOOL SettingVision::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	GetDlgItem(IDC_STATIC_CAMERA_RESOLUTION_X)->MoveWindow(20, 20, 90, 30);
	GetDlgItem(IDC_STATIC_CAMERA_RESOLUTION_Y)->MoveWindow(210, 20, 90, 30);
	GetDlgItem(IDC_EDIT_CAMERA_RESOLUTION_X)->MoveWindow(110, 20, 80, 30);
	GetDlgItem(IDC_EDIT_CAMERA_RESOLUTION_Y)->MoveWindow(300, 20, 80, 30);

	GetDlgItem(IDC_STATIC_CAMERA_PIXELSIZE)->MoveWindow(20, 70, 90, 30);
	GetDlgItem(IDC_STATIC_CAMERA_MAGNI)->MoveWindow(210, 70, 90, 30);
	GetDlgItem(IDC_EDIT_CAMERA_PIXELSIZE)->MoveWindow(110, 70, 80, 30);
	GetDlgItem(IDC_EDIT_CAMERA_MAGNI)->MoveWindow(300, 70, 80, 30);

	GetDlgItem(IDC_STATIC_LIGHT)->MoveWindow(20, 140, 60, 30);
	GetDlgItem(IDC_STATIC_LIGHT_1)->MoveWindow(90, 140, 60, 30);
	GetDlgItem(IDC_STATIC_LIGHT_2)->MoveWindow(90, 180, 60, 30);
	GetDlgItem(IDC_SPIN_LIGHT_1)->MoveWindow(160, 140, 130, 30);
	GetDlgItem(IDC_SPIN_LIGHT_2)->MoveWindow(160, 180, 130, 30);
	GetDlgItem(IDC_EDIT_LIGHT_1)->MoveWindow(300, 140, 80, 30);
	GetDlgItem(IDC_EDIT_LIGHT_2)->MoveWindow(300, 180, 80, 30);

	GetDlgItem(IDC_STATIC_GAP_COUNT)->MoveWindow(20, 250, 100, 30);
	GetDlgItem(IDC_STATIC_GAP_RANGE)->MoveWindow(20, 290, 100, 30);
	GetDlgItem(IDC_STATIC_GAP_LIMIT)->MoveWindow(20, 330, 100, 30);

	GetDlgItem(IDC_EDIT_GAP_COUNT)->MoveWindow(120, 250, 80, 30);
	GetDlgItem(IDC_EDIT_GAP_RANGE)->MoveWindow(120, 290, 80, 30);
	GetDlgItem(IDC_EDIT_GAP_LIMIT)->MoveWindow(120, 330, 80, 30);

	GetDlgItem(IDC_STATIC_UVLED)->MoveWindow(20, 400, 100, 30);
	GetDlgItem(IDC_EDIT_UVLED)->MoveWindow(120, 400, 80, 30);

	GetDlgItem(IDC_STATIC_ALIGN_ROI)->MoveWindow(20, 470, 100, 30);
	GetDlgItem(IDC_EDIT_ALIGN_ROI_START_X)->MoveWindow(120, 470, 80, 30);
	GetDlgItem(IDC_EDIT_ALIGN_ROI_START_Y)->MoveWindow(220, 470, 80, 30);
	GetDlgItem(IDC_EDIT_ALIGN_ROI_END_X)->MoveWindow(120, 510, 80, 30);
	GetDlgItem(IDC_EDIT_ALIGN_ROI_END_Y)->MoveWindow(220, 510, 80, 30);

	GetDlgItem(IDC_STATIC_ALIGN_LIMIT_STAGE_X)->MoveWindow(100, 580, 80, 30);
	GetDlgItem(IDC_STATIC_ALIGN_LIMIT_STAGE_Y)->MoveWindow(195, 580, 80, 30);
	GetDlgItem(IDC_STATIC_ALIGN_LIMIT_STAGE_T)->MoveWindow(290, 580, 80, 30);
	GetDlgItem(IDC_STATIC_ALIGN_LIMIT)->MoveWindow(20, 620, 80, 30);
	GetDlgItem(IDC_EDIT_ALIGN_LIMIT_STAGE_X)->MoveWindow(100, 620, 80, 30);
	GetDlgItem(IDC_EDIT_ALIGN_LIMIT_STAGE_Y)->MoveWindow(195, 620, 80, 30);
	GetDlgItem(IDC_EDIT_ALIGN_LIMIT_STAGE_T)->MoveWindow(290, 620, 80, 30);

	//m_slider_light_1.SetRange(0, 255);
	//m_slider_light_2.SetRange(0, 255);

	staticFont = CreateFont(15, 6, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_MODERN, _T("맑은 고딕"));

	GetDlgItem(IDC_STATIC_CAMERA_RESOLUTION_X)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_CAMERA_RESOLUTION_Y)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_CAMERA_PIXELSIZE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_CAMERA_MAGNI)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_LIGHT)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_LIGHT_1)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_LIGHT_2)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_GAP_COUNT)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_GAP_RANGE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_GAP_LIMIT)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_UVLED)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ALIGN_ROI)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ALIGN_LIMIT)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ALIGN_LIMIT_STAGE_X)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ALIGN_LIMIT_STAGE_Y)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ALIGN_LIMIT_STAGE_T)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);

	CRect rectEdit;

	((CEdit*)GetDlgItem(IDC_EDIT_CAMERA_RESOLUTION_X))->GetRect(rectEdit);

	rectEdit.top += 4;

	((CEdit*)GetDlgItem(IDC_EDIT_CAMERA_RESOLUTION_X))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_CAMERA_RESOLUTION_Y))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_CAMERA_PIXELSIZE))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_CAMERA_MAGNI))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_LIGHT_1))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_LIGHT_2))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_GAP_COUNT))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_GAP_RANGE))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_GAP_LIMIT))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_UVLED))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_ALIGN_ROI_START_X))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_ALIGN_ROI_START_Y))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_ALIGN_ROI_END_X))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_ALIGN_ROI_END_Y))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_ALIGN_LIMIT_STAGE_X))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_ALIGN_LIMIT_STAGE_Y))->SetRect(rectEdit);
	((CEdit*)GetDlgItem(IDC_EDIT_ALIGN_LIMIT_STAGE_T))->SetRect(rectEdit);

	SettingModify(false);

	LoadRecipe();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL SettingVision::PreTranslateMessage(MSG* pMsg)
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

void SettingVision::SettingModify(BOOL nCase)
{
	GetDlgItem(IDC_EDIT_CAMERA_RESOLUTION_X)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_CAMERA_RESOLUTION_Y)->EnableWindow(nCase);

	GetDlgItem(IDC_EDIT_CAMERA_PIXELSIZE)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_CAMERA_MAGNI)->EnableWindow(nCase);

	GetDlgItem(IDC_SPIN_LIGHT_1)->EnableWindow(nCase);
	GetDlgItem(IDC_SPIN_LIGHT_2)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_LIGHT_1)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_LIGHT_2)->EnableWindow(nCase);

	GetDlgItem(IDC_EDIT_GAP_COUNT)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_GAP_RANGE)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_GAP_LIMIT)->EnableWindow(nCase);

	GetDlgItem(IDC_EDIT_UVLED)->EnableWindow(nCase);

	GetDlgItem(IDC_EDIT_ALIGN_ROI_START_X)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_ALIGN_ROI_START_Y)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_ALIGN_ROI_END_X)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_ALIGN_ROI_END_Y)->EnableWindow(nCase);

	GetDlgItem(IDC_EDIT_ALIGN_LIMIT_STAGE_X)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_ALIGN_LIMIT_STAGE_Y)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_ALIGN_LIMIT_STAGE_T)->EnableWindow(nCase);
}

void SettingVision::LoadRecipe()
{
	CJettingVisionDlg* pDlg = (CJettingVisionDlg*)AfxGetMainWnd();

	bool		bRet;
	CString		strPath;
	CString		strData;
	TCHAR		szData[MAX_PATH];

	strPath = _T("D:\\JettingVision\\Config\\1\\RecipeVision.ini");

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("CAMERA"), _T("RESOLUTION X"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	nCamResolutionX = _ttoi(szData);
	GetDlgItem(IDC_EDIT_CAMERA_RESOLUTION_X)->SetWindowTextW(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("CAMERA"), _T("RESOLUTION Y"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	nCamResolutionY = _ttoi(szData);
	GetDlgItem(IDC_EDIT_CAMERA_RESOLUTION_Y)->SetWindowTextW(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("CAMERA"), _T("PIXELSIZE"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	dPixelSize = _wtof(szData);
	GetDlgItem(IDC_EDIT_CAMERA_PIXELSIZE)->SetWindowTextW(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("CAMERA"), _T("MAGNI"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	nMagni = _ttoi(szData);
	GetDlgItem(IDC_EDIT_CAMERA_MAGNI)->SetWindowTextW(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("LIGHT"), _T("UPPER LIGHT VALUE"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	nUpperLight = _ttoi(szData);
	GetDlgItem(IDC_EDIT_LIGHT_1)->SetWindowTextW(szData);
	
	pDlg->SetVisionLight(1);
	pDlg->ControlVisionLight(nUpperLight);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("LIGHT"), _T("SIDE LIGHT VALUE"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	nSideLight = _ttoi(szData);
	GetDlgItem(IDC_EDIT_LIGHT_2)->SetWindowTextW(szData);

	pDlg->SetVisionLight(2);
	pDlg->ControlVisionLight(nSideLight);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("GAP"), _T("GAP COUNT"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	nGapCount = _ttoi(szData);
	GetDlgItem(IDC_EDIT_GAP_COUNT)->SetWindowTextW(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("GAP"), _T("GAP RANGE"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	dGapRange = _wtof(szData);
	GetDlgItem(IDC_EDIT_GAP_RANGE)->SetWindowTextW(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("GAP"), _T("GAP LIMIT"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	dGapLimit = _wtof(szData);
	GetDlgItem(IDC_EDIT_GAP_LIMIT)->SetWindowTextW(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("UVLED"), _T("UVLED VALUE"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	nUVLED = _ttoi(szData);
	GetDlgItem(IDC_EDIT_UVLED)->SetWindowTextW(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("ALIGN"), _T("ROI START X"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	pRoiStart.x = _ttoi(szData);
	GetDlgItem(IDC_EDIT_ALIGN_ROI_START_X)->SetWindowTextW(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("ALIGN"), _T("ROI START Y"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	pRoiStart.y = _ttoi(szData);
	GetDlgItem(IDC_EDIT_ALIGN_ROI_START_Y)->SetWindowTextW(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("ALIGN"), _T("ROI END X"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	pRoiEnd.x = _ttoi(szData);
	GetDlgItem(IDC_EDIT_ALIGN_ROI_END_X)->SetWindowTextW(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("ALIGN"), _T("ROI END Y"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	pRoiEnd.y = _ttoi(szData);
	GetDlgItem(IDC_EDIT_ALIGN_ROI_END_Y)->SetWindowTextW(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("ALIGN"), _T("ALIGN LIMIT X"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	dAlignLimitX = _wtof(szData);
	GetDlgItem(IDC_EDIT_ALIGN_LIMIT_STAGE_X)->SetWindowTextW(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("ALIGN"), _T("ALIGN LIMIT Y"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	dAlignLimitY = _wtof(szData);
	GetDlgItem(IDC_EDIT_ALIGN_LIMIT_STAGE_Y)->SetWindowTextW(szData);

	ZeroMemory(szData, MAX_PATH);
	GetPrivateProfileString(_T("ALIGN"), _T("ALIGN LIMIT T"), _T("0"), szData, MAX_PATH, strPath);
	strData = szData;
	dAlignLimitT = _wtof(szData);
	GetDlgItem(IDC_EDIT_ALIGN_LIMIT_STAGE_T)->SetWindowTextW(szData);

}


void SettingVision::SaveRecipe()
{
	bool		bRet;
	CString		strPath;
	CString		strTag;
	CString		strData;

	// Camera
	strPath = _T("D:\\JettingVision\\Config\\1\\RecipeVision.ini");

	//////
	m_edit_camera_resolution_x.GetWindowTextW(strData);
	WritePrivateProfileString(_T("CAMERA"), _T("RESOLUTION X"), strData, strPath);

	m_edit_camera_resolution_y.GetWindowTextW(strData);
	WritePrivateProfileString(_T("CAMERA"), _T("RESOLUTION Y"), strData, strPath);

	m_edit_camera_pixelsize.GetWindowTextW(strData);
	WritePrivateProfileString(_T("CAMERA"), _T("PIXELSIZE"), strData, strPath);

	m_edit_camera_magni.GetWindowTextW(strData);
	WritePrivateProfileString(_T("CAMERA"), _T("MAGNI"), strData, strPath);

	m_edit_light_1.GetWindowTextW(strData);
	WritePrivateProfileString(_T("LIGHT"), _T("UPPER LIGHT VALUE"), strData, strPath);

	m_edit_light_2.GetWindowTextW(strData);
	WritePrivateProfileString(_T("LIGHT"), _T("SIDE LIGHT VALUE"), strData, strPath);

	m_edit_gap_count.GetWindowTextW(strData);
	WritePrivateProfileString(_T("GAP"), _T("GAP COUNT"), strData, strPath);

	m_edit_gap_range.GetWindowTextW(strData);
	WritePrivateProfileString(_T("GAP"), _T("GAP RANGE"), strData, strPath);

	m_edit_gap_limit.GetWindowTextW(strData);
	WritePrivateProfileString(_T("GAP"), _T("GAP LIMIT"), strData, strPath);

	m_edit_uvled.GetWindowTextW(strData);
	WritePrivateProfileString(_T("UVLED"), _T("UVLED VALUE"), strData, strPath);

	m_edit_align_roi_start_x.GetWindowTextW(strData);
	WritePrivateProfileString(_T("ALIGN"), _T("ROI START X"), strData, strPath);

	m_edit_align_roi_start_y.GetWindowTextW(strData);
	WritePrivateProfileString(_T("ALIGN"), _T("ROI START Y"), strData, strPath);

	m_edit_align_roi_end_x.GetWindowTextW(strData);
	WritePrivateProfileString(_T("ALIGN"), _T("ROI END X"), strData, strPath);

	m_edit_align_roi_end_y.GetWindowTextW(strData);
	WritePrivateProfileString(_T("ALIGN"), _T("ROI END Y"), strData, strPath);

	m_edit_align_limit_stage_x.GetWindowTextW(strData);
	WritePrivateProfileString(_T("ALIGN"), _T("ALIGN LIMIT X"), strData, strPath);

	m_edit_align_limit_stage_y.GetWindowTextW(strData);
	WritePrivateProfileString(_T("ALIGN"), _T("ALIGN LIMIT Y"), strData, strPath);

	m_edit_align_limit_stage_t.GetWindowTextW(strData);
	WritePrivateProfileString(_T("ALIGN"), _T("ALIGN LIMIT T"), strData, strPath);
}


void SettingVision::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//if (pScrollBar == (CScrollBar*)&m_slider_light_1)
	//{
	//	int nPos = m_slider_light_1.GetPos();
	//	CString strPos;
	//	strPos.Format(_T("%d"), nPos);
	//	m_edit_light_1.SetWindowTextW(strPos);
	//}

	//if (pScrollBar == (CScrollBar*)&m_slider_light_2)
	//{
	//	int nPos = m_slider_light_2.GetPos();
	//	CString strPos;
	//	strPos.Format(_T("%d"), nPos);
	//	m_edit_light_2.SetWindowTextW(strPos);
	//}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void SettingVision::OnEnChangeEditLight1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

}


void SettingVision::OnEnChangeEditLight2()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

}


void SettingVision::OnDeltaposSpinLight1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	CJettingVisionDlg* pDlg = (CJettingVisionDlg*)AfxGetMainWnd();

	int nValue;
	CString strValue;

	m_edit_light_1.GetWindowTextW(strValue);
	nValue = _ttoi(strValue);

	if (pNMUpDown->iDelta < 0)
	{
		if (nValue < 10)
			nValue++;
	}

	else if (pNMUpDown->iDelta > 0)
	{
		if (nValue > 0)
			nValue--;
	}

	if (nValue >= 0 && nValue <= 10)
	{
		strValue.Format(_T("%d"), nValue);
		m_edit_light_1.SetWindowTextW(strValue);

		pDlg->SetVisionLight(1);
		pDlg->ControlVisionLight(nValue);
	}
}


void SettingVision::OnDeltaposSpinLight2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	CJettingVisionDlg* pDlg = (CJettingVisionDlg*)AfxGetMainWnd();

	int nValue;
	CString strValue;

	m_edit_light_2.GetWindowTextW(strValue);
	nValue = _ttoi(strValue);

	if (pNMUpDown->iDelta < 0)
	{
		if (nValue < 10)
			nValue++;
	}

	else if (pNMUpDown->iDelta > 0)
	{
		if (nValue > 0)
			nValue--;
	}

	if (nValue >= 0 && nValue <= 10)
	{
		strValue.Format(_T("%d"), nValue);
		m_edit_light_2.SetWindowTextW(strValue);

		pDlg->SetVisionLight(2);
		pDlg->ControlVisionLight(nValue);
	}
}
