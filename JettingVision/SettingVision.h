#pragma once


// SettingVision 대화 상자

class SettingVision : public CDialogEx
{
	DECLARE_DYNAMIC(SettingVision)

public:
	SettingVision(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SettingVision();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETTING_VISION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	CEdit m_edit_camera_resolution_x;
	CEdit m_edit_camera_resolution_y;
	CEdit m_edit_camera_pixelsize;
	CEdit m_edit_camera_magni;
	CEdit m_edit_light_1;
	CEdit m_edit_light_2;
	CEdit m_edit_gap_count;
	CEdit m_edit_gap_range;
	CEdit m_edit_gap_limit;
	CEdit m_edit_uvled;
	CEdit m_edit_align_roi_start_x;
	CEdit m_edit_align_roi_start_y;
	CEdit m_edit_align_roi_end_x;
	CEdit m_edit_align_roi_end_y;
	CEdit m_edit_align_limit_stage_x;
	CEdit m_edit_align_limit_stage_y;
	CEdit m_edit_align_limit_stage_t;

	HFONT staticFont;

	void SettingModify(BOOL nCase);

	void LoadRecipe();
	void SaveRecipe();

	int nCamResolutionX;
	int nCamResolutionY;
	double dPixelSize;
	int nMagni;

	int nUpperLight;
	int nSideLight;

	int nGapCount;
	double dGapRange;
	double dGapLimit;

	int nUVLED;

	CPoint pRoiStart;
	CPoint pRoiEnd;

	double dAlignLimitX;
	double dAlignLimitY;
	double dAlignLimitT;

	
	afx_msg void OnEnChangeEditLight1();
	afx_msg void OnEnChangeEditLight2();
	afx_msg void OnDeltaposSpinLight1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinLight2(NMHDR* pNMHDR, LRESULT* pResult);
};
