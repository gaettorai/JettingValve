// PopupAlarm.cpp: 구현 파일
//

#include "pch.h"
#include "JettingVision.h"
#include "PopupAlarm.h"
#include "afxdialogex.h"


// PopupAlarm 대화 상자

IMPLEMENT_DYNAMIC(PopupAlarm, CDialogEx)

PopupAlarm::PopupAlarm(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_POPUP_ALARM, pParent)
{

}

PopupAlarm::~PopupAlarm()
{
}

void PopupAlarm::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(PopupAlarm, CDialogEx)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// PopupAlarm 메시지 처리기


int PopupAlarm::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}


HBRUSH PopupAlarm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


BOOL PopupAlarm::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	MoveWindow(rcDialog);

	GetDlgItem(IDC_STATIC_MESSAGE)->MoveWindow(10, 10, 270, 50);
	GetDlgItem(IDOK)->MoveWindow(140, 70, 60, 20);
	GetDlgItem(IDCANCEL)->MoveWindow(210, 70, 60, 20);

	staticFont = CreateFont(15, 6, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_MODERN, _T("맑은 고딕"));
	btnFont = CreateFont(15, 6, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_MODERN, _T("맑은 고딕"));

	GetDlgItem(IDC_STATIC_MESSAGE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDOK)->SendMessage(WM_SETFONT, (WPARAM)btnFont, (LPARAM)TRUE);
	GetDlgItem(IDCANCEL)->SendMessage(WM_SETFONT, (WPARAM)btnFont, (LPARAM)TRUE);

	DisplayMessage(strAlarm);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL PopupAlarm::PreTranslateMessage(MSG* pMsg)
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


void PopupAlarm::DisplayMessage(CString strMessage)
{
	GetDlgItem(IDC_STATIC_MESSAGE)->SetWindowTextW(strMessage);
}