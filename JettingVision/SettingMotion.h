#pragma once


// SettingMotion 대화 상자

class SettingMotion : public CDialogEx
{
	DECLARE_DYNAMIC(SettingMotion)

public:
	SettingMotion(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SettingMotion();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETTING_MOTION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	CEdit m_edit_axis_num_stage_x;
	CEdit m_edit_axis_num_stage_y;
	CEdit m_edit_axis_num_stage_t;
	CEdit m_edit_maxspeed_stage_x;
	CEdit m_edit_maxspeed_stage_y;
	CEdit m_edit_maxspeed_stage_t;
	CEdit m_edit_minpos_stage_x;
	CEdit m_edit_minpos_stage_y;
	CEdit m_edit_minpos_stage_t;
	CEdit m_edit_maxpos_stage_x;
	CEdit m_edit_maxpos_stage_y;
	CEdit m_edit_maxpos_stage_t;
	CEdit m_edit_homeoffset_stage_x;
	CEdit m_edit_homeoffset_stage_y;
	CEdit m_edit_homeoffset_stage_t;
	CEdit m_edit_homeoffset_vel_stage_x;
	CEdit m_edit_homeoffset_vel_stage_y;
	CEdit m_edit_homeoffset_vel_stage_t;
	CEdit m_edit_pos_loading_stage_x;
	CEdit m_edit_pos_loading_stage_y;
	CEdit m_edit_pos_loading_stage_t;
	CEdit m_edit_pos_unloading_stage_x;
	CEdit m_edit_pos_unloading_stage_y;
	CEdit m_edit_pos_unloading_stage_t;
	CEdit m_edit_pos_safety_stage_x;
	CEdit m_edit_pos_safety_stage_y;
	CEdit m_edit_pos_safety_stage_t;
	CEdit m_edit_pos_leftalign_stage_x;
	CEdit m_edit_pos_leftalign_stage_y;
	CEdit m_edit_pos_leftalign_stage_t;
	CEdit m_edit_pos_rightalign_stage_x;
	CEdit m_edit_pos_rightalign_stage_y;
	CEdit m_edit_pos_rightalign_stage_t;
	CEdit m_edit_pos_gapstart_stage_x;
	CEdit m_edit_pos_gapstart_stage_y;
	CEdit m_edit_pos_gapstart_stage_t;
	CEdit m_edit_pos_gapend_stage_x;
	CEdit m_edit_pos_gapend_stage_y;
	CEdit m_edit_pos_gapend_stage_t;
	CEdit m_edit_pos_procstart_stage_x;
	CEdit m_edit_pos_procstart_stage_y;
	CEdit m_edit_pos_procstart_stage_t;
	CEdit m_edit_pos_procend_stage_x;
	CEdit m_edit_pos_procend_stage_y;
	CEdit m_edit_pos_procend_stage_t;
	CEdit m_edit_pos_review_stage_x;
	CEdit m_edit_pos_review_stage_y;
	CEdit m_edit_pos_review_stage_t;
	CEdit m_edit_moving_speed_stage_x;
	CEdit m_edit_moving_speed_stage_y;
	CEdit m_edit_moving_speed_stage_t;
	CEdit m_edit_jetting_speed_stage_x;
	CEdit m_edit_jetting_speed_stage_y;
	CEdit m_edit_jetting_speed_stage_t;
	HFONT staticFont;

	void SettingModify(BOOL nCase);

	void LoadRecipe();
	void SaveRecipe();

	double dPosLoadingX;
	double dPosUnloadingX;
	double dPosSafetyX;
	double dPosAlignleftX;
	double dPosAlignrightX;
	double dPosGapstartX;
	double dPosGapendX;
	double dPosProcstartX;
	double dPosProcendX;
	double dPosReviewX;
	double dMovingSpeedX;
	double dJettingSpeedX;

	double dPosLoadingY;
	double dPosUnloadingY;
	double dPosSafetyY;
	double dPosAlignleftY;
	double dPosAlignrightY;
	double dPosGapstartY;
	double dPosGapendY;
	double dPosProcstartY;
	double dPosProcendY;
	double dPosReviewY;
	double dMovingSpeedY;
	double dJettingSpeedY;

	double dPosLoadingT;
	double dPosUnloadingT;
	double dPosSafetyT;
	double dPosAlignleftT;
	double dPosAlignrightT;
	double dPosGapstartT;
	double dPosGapendT;
	double dPosProcstartT;
	double dPosProcendT;
	double dPosReviewT;
	double dMovingSpeedT;
	double dJettingSpeedT;
};
