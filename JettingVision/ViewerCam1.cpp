// ViewerCam1.cpp: 구현 파일
//

#include "pch.h"
#include "JettingVision.h"
#include "ViewerCam1.h"
#include "afxdialogex.h"

#include "JettingVisionDlg.h"

// ViewerCam1 대화 상자

IMPLEMENT_DYNAMIC(ViewerCam1, CDialogEx)

const int m_nLineSize = 10;
const int m_nBasic = 10;
const int m_nRepeat = 10;

ViewerCam1::ViewerCam1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VIEWER_CAM1, pParent)
{

}

ViewerCam1::~ViewerCam1()
{
}

void ViewerCam1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ViewerCam1, CDialogEx)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// ViewerCam1 메시지 처리기


int ViewerCam1::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	magni = 4;

	return 0;
}


HBRUSH ViewerCam1::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void ViewerCam1::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	ViewWidth_ = 2448 / magni;
	ViewHeight_ = 2048 / magni;

	int HScrollMax = 0;
	HPageSize_ = 0;

	if (cx < ViewWidth_)
	{
		HScrollMax = ViewWidth_ - 1;
		HPageSize_ = cx;
		HScrollPos_ = MIN(HScrollPos_, ViewWidth_ - HPageSize_ - 1);
	}

	SCROLLINFO si;
	si.fMask = SIF_PAGE | SIF_RANGE | SIF_POS;
	si.nMin = 0;
	si.nMax = HScrollMax;
	si.nPos = HScrollPos_;
	si.nPage = HPageSize_;
	SetScrollInfo(SB_HORZ, &si, TRUE);

	int VScrollMax = 0;
	VPageSize_ = 0;

	if (cy < ViewHeight_)
	{
		VScrollMax = ViewHeight_ - 1;
		VPageSize_ = cy;
		VScrollPos_ = MIN(VScrollPos_, ViewHeight_ - VPageSize_ - 1);
	}

	si.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
	si.nMin = 0;
	si.nMax = VScrollMax;
	si.nPos = VScrollPos_;
	si.nPage = VPageSize_;
	SetScrollInfo(SB_VERT, &si, TRUE);
}


void ViewerCam1::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_nHdelta = 0;

	switch (nSBCode)
	{
	case SB_LINELEFT:
		m_nHdelta = -m_nBasic;
		break;
	case SB_PAGELEFT:
		m_nHdelta = -HPageSize_;
		break;
	case SB_THUMBTRACK:
		m_nHdelta = static_cast<int>(nPos) - HScrollPos_;
		break;
	case SB_PAGERIGHT:
		m_nHdelta = HPageSize_;
		break;
	case SB_LINERIGHT:
		m_nHdelta = m_nBasic;
		break;
	default:
		return;
	}

	int scrollpos = HScrollPos_ + m_nHdelta;
	int maxpos = ViewWidth_ - HPageSize_;

	if (scrollpos < 0)
		m_nHdelta = -HScrollPos_;
	else
		if (scrollpos > maxpos)
			m_nHdelta = maxpos - HScrollPos_;

	mouse_scroll_x = scrollpos;

	if (m_nHdelta != 0)
	{
		HScrollPos_ += m_nHdelta;
		SetScrollPos(SB_HORZ, HScrollPos_, TRUE);
		ScrollWindow(-m_nHdelta, 0);
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void ViewerCam1::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	int delta;

	switch (nSBCode)
	{
	case SB_LINEUP:
		delta = -m_nBasic;
		break;
	case SB_PAGEUP:
		delta = -VPageSize_;
		break;
	case SB_THUMBTRACK:
		delta = static_cast<int>(nPos) - VScrollPos_;
		break;
	case SB_PAGEDOWN:
		delta = VPageSize_;
		break;
	case SB_LINEDOWN:
		delta = m_nBasic;
		break;
	default:
		return;
	}

	scrollpos = VScrollPos_ + delta;
	int maxpos = ViewHeight_ - VPageSize_;
	if (scrollpos < 0)
		delta = -VScrollPos_;
	else
		if (scrollpos > maxpos)
			delta = maxpos - VScrollPos_;

	mouse_scroll_y = scrollpos;
	if (delta != 0)
	{
		VScrollPos_ += delta;
		SetScrollPos(SB_VERT, VScrollPos_, TRUE);
		ScrollWindow(0, -delta);
	}

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


BOOL ViewerCam1::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	GetDlgItem(IDC_PIC_CAM)->MoveWindow(0, 0, 2448 / magni, 2048 / magni);

	scrollpos = 0;
	VScrollPos_ = 0;
	HScrollPos_ = 0;
	mouse_scroll_x = 0;
	mouse_scroll_y = 0;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL ViewerCam1::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialogEx::PreTranslateMessage(pMsg);
}


void ViewerCam1::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CJettingVisionDlg* pDlg = (CJettingVisionDlg*)AfxGetMainWnd();

	if (pDlg->bChkMeasurement == true)
	{

	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void ViewerCam1::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CJettingVisionDlg* pDlg = (CJettingVisionDlg*)AfxGetMainWnd();

	if (pDlg->bChkMeasurement == true)
	{

	}

	CDialogEx::OnMouseMove(nFlags, point);
}
