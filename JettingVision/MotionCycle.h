#pragma once


// MotionCycle 대화 상자

class MotionCycle : public CDialogEx
{
	DECLARE_DYNAMIC(MotionCycle)

public:
	MotionCycle(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~MotionCycle();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MOTION_CYCLE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	HFONT staticFont;
	HFONT btnFont;

	CString strVal;
	double dXStart;
	double dYStart;
	double dYEnd;
	double dYSpeed;
	double dYMovingSpeed;
	double dYDelay;

	double dXShift;
	double dXSpeed;
	double dXMovingSpeed;
	int nXCount;
	double dXDelay;

	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnBnClickedBtnStop();
	CEdit m_edit_x_start;
	CEdit m_edit_y_start;
	CEdit m_edit_y_end;
	CEdit m_edit_y_speed;
	CEdit m_edit_y_delay;
	CEdit m_edit_x_shift;
	CEdit m_edit_x_repeat;
	CEdit m_edit_x_delay;
	CEdit m_edit_x_speed;
	CEdit m_edit_y_movingspeed;
	CEdit m_edit_x_movingspeed;
};
