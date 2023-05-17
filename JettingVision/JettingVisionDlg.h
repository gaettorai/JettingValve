
// JettingVisionDlg.h: 헤더 파일
//

#include "ViewerCam1.h"
#include "ViewerCam2.h"
#include "SettingMotion.h"
#include "SettingVision.h"
#include "MotionCycle.h"

#include "PopupAlarm.h"

#include "connect_Baumer.h"

#include "ACSMotion.h"

#include "CommThread.h"

#include <afxsock.h>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

#pragma once

void BGAPI2CALL BufferHandler1(void* callBackOwner, Buffer* pBufferFilled);
void BGAPI2CALL BufferHandler2(void* callBackOwner, Buffer* pBufferFilled);

enum eProcSeq
{
	MoveSafetyPos,
	SafetyPosComplete,
	MoveLeftAlignPos,
	LeftAlignPosComplete,
	MoveRightAlignPos,
	RightAlignPosComplete,
	Alignment,
	AlignmentComplete,
	MoveGapPosition,
	GapMeasure,
	GapComplete,
	MoveProcPosition,
	ProcPositionComplete,
	Processing,
	ProcComplete,
	MoveReviewPositoin,
	ReviewPositionComplete,
	ReviewComplete,
	MoveUnloadingPosition,
	UnloadingComplete,
};

enum eAlignResult
{
	BEFORE,
	AFTER,
};

// CJettingVisionDlg 대화 상자
class CJettingVisionDlg : public CDialogEx
{
// 생성입니다.
public:
	CJettingVisionDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	ViewerCam1* dlgViewerCam1;
	ViewerCam2* dlgViewerCam2;

	SettingMotion* dlgSettingMotion;
	SettingVision* dlgSettingVision;
	MotionCycle* dlgCycle;
	PopupAlarm	dlgPopupAlarm;

	connect_Baumer* cBaumer;

	CACSM* m_pAcs;

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_JETTINGVISION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	HFONT staticTitleFont;
	HFONT staticFont;
	HFONT btnFont;
	HFONT listFont;

	CMFCButton m_btn_align_use;
	CMFCButton m_btn_align_unuse;
	CMFCButton m_btn_gap_use;
	CMFCButton m_btn_gap_unuse;
	CMFCButton m_btn_uvled_use;
	CMFCButton m_btn_uvled_unuse;
	CMFCButton m_btn_jetting_use;
	CMFCButton m_btn_jetting_unuse;
	CMFCButton m_btn_review_use;
	CMFCButton m_btn_review_unuse;
	CMFCButton m_btn_setting_motion;
	CMFCButton m_btn_setting_vision;
	CMFCButton m_btn_setting_modify;
	CMFCButton m_btn_setting_apply;
	CMFCButton m_btn_setting_cancel;
	CMFCButton m_btn_abs;
	CMFCButton m_btn_rel;
	CMFCButton m_btn_jog_slow;
	CMFCButton m_btn_jog_fast;

	CListCtrl m_list_measure;

	afx_msg void OnBnClickedBtnSettingMotion();
	afx_msg void OnBnClickedBtnSettingVision();
	afx_msg void OnBnClickedBtnSettingModify();
	afx_msg void OnBnClickedBtnSettingApply();
	afx_msg void OnBnClickedBtnSettingCancel();
	afx_msg void OnBnClickedBtnMeasureMode();
	afx_msg void OnBnClickedBtnMeasureLine();
	afx_msg void OnBnClickedBtnMeasureRectangle();
	afx_msg void OnBnClickedBtnMeasureClear();
	afx_msg void OnBnClickedBtnAlignUse();
	afx_msg void OnBnClickedBtnAlignUnuse();
	afx_msg void OnBnClickedBtnGapUse();
	afx_msg void OnBnClickedBtnGapUnuse();
	afx_msg void OnBnClickedBtnUvledUse();
	afx_msg void OnBnClickedBtnUvledUnuse();
	afx_msg void OnBnClickedBtnJettingUse();
	afx_msg void OnBnClickedBtnJettingUnuse();
	afx_msg void OnBnClickedBtnReviewUse();
	afx_msg void OnBnClickedBtnReviewUnuse();
	afx_msg void OnBnClickedBtnReviewComplete();
	afx_msg void OnBnClickedBtnStageXMove();
	afx_msg void OnBnClickedBtnStageYMove();
	afx_msg void OnBnClickedBtnStageTMove();
	afx_msg void OnBnClickedBtnPresetSafety();
	afx_msg void OnBnClickedBtnPresetLoading();
	afx_msg void OnBnClickedBtnPresetAlignLeft();
	afx_msg void OnBnClickedBtnPresetAlignRight();
	afx_msg void OnBnClickedBtnPresetProcStart();
	afx_msg void OnBnClickedBtnPresetProcEnd();
	afx_msg void OnBnClickedBtnPresetReview();
	afx_msg void OnBnClickedBtnPresetUnloading();
	afx_msg void OnBnClickedBtnAuto();
	afx_msg void OnBnClickedBtnPause();
	afx_msg void OnBnClickedBtnStop();
	afx_msg void OnBnClickedBtnOrigin();
	afx_msg void OnBnClickedBtnAlarm();
	afx_msg void OnBnClickedBtnReset();
	afx_msg void OnBnClickedBtnExit();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();

	CString strDataFilePath;
	CString strRecipeFilePath;

	int SelectRecipe;

	// 상부, 측면부 카메라 Display
	static UINT Vision_Thread(LPVOID pParam);
	CWinThread* Vision = NULL;

	// Process Thread
	static UINT Proc_Thread(LPVOID pParam);
	CWinThread* Proc = NULL;

	static UINT Cycle_Thread(LPVOID pParam);
	CWinThread* Cycle = NULL;

	void DisplayCam_0();
	void DisplayCam_1();

	void DisplayDrawAlign(CDC* pDC, int nCase);		// align

	void InitUI();
	void InitParam();
	void InitClass();

	// 판정 결과
	BOOL bJudgeAlignLeft;
	BOOL bJudgeAlignRight;
	BOOL bJudgeModifyX;
	BOOL bJudgeModifyY;
	BOOL bJudgeModifyT;
	BOOL bJudgeGapAvg;

	// 공정 CHECK
	BOOL bChkAlign;
	BOOL bChkGap;
	BOOL bChkUVLED;
	BOOL bChkJetting;
	BOOL bChkReview;

	// 공정 진행
	BOOL bProcStart;
	BOOL bProcStop;
	BOOL bProcPause;
	BOOL bProcReview;

	void MovingCycleStart();
	BOOL bCycleStart;

	int nCycle;

	// MANUAL MOVE
	BOOL bChkABS;
	BOOL bChkREL;
	BOOL bChkJogSlow;
	BOOL bChkJogFast;
	BOOL bChkMeasurement;

	int MeasurementCase;		// 측정 유형
	int MeasurementCount;		// 측정 횟수
	int clickCount;;			// 클릭 횟수

	int nAlignCount;
	int nGapCount;

	double dGapStep;
	double dGapSum;
	double dGapAvg;

	CPoint pAlignLeft;
	CPoint pAlignRight;

	double dAlignModifyX;
	double dAlignModifyY;
	double dAlignModifyT;

	double dJettinOffset;
	double dJettingLength;

	void InitMotion();

	BOOL MotorsReadMap();
	
	int m_nMotCnt;
	ACS_COMM_CONFIG	m_comm_conf;
	
	CCommThread		m_ComPortLight;	// LVS Light
	CCommThread		m_ComPortUV;	// UV Led

	// Ethernet
	int sock;
	struct sockaddr_in addr;

	void InitSocket();

	CString byIndexComPort(int xPort);
	DWORD byIndexBaud(int xBaud);
	BYTE byIndexData(int xData);
	BYTE byIndexParity(int xParity);
	BYTE byIndexStop(int xStop);

	void GetMotorStatus();
	void GetMotorMoving();
	void GetHomeStatus();
	void GetAPos();
	void GetVelocity();

	void StageMove(int nStage, double TargetPos, BOOL nABS, BOOL nREL, double ManualSpped);
	void StageBreak(int nStage);
	void StageMoveJog(int nStage, CString nCase);
	void SetMotionSpeed();
	CButton* pButton;

	CRect rect_stage_x_minus;
	CRect rect_stage_y_minus;
	CRect rect_stage_t_minus;

	CRect rect_stage_x_plus;
	CRect rect_stage_y_plus;
	CRect rect_stage_t_plus;


//	HICON	m_greenIcon;
//	HICON	m_redIcon;
	CStatic m_pic_align_left;
	CStatic m_pic_align_right;

	CStatic m_icon_stage_x_move;
	CStatic m_icon_stage_x_status;
	CStatic m_icon_stage_x_home;
	CStatic m_icon_stage_y_move;
	CStatic m_icon_stage_y_status;
	CStatic m_icon_stage_y_home;
	CStatic m_icon_stage_t_move;
	CStatic m_icon_stage_t_status;
	CStatic m_icon_stage_t_home;

	CBitmap m_bmp_green;
	CBitmap m_bmp_red;
	CBitmap m_bmp_yellow;
	CBitmap m_bmp_measure_on;
	CBitmap m_bmp_measure_off;
	CBitmap m_bmp_line_on;
	CBitmap m_bmp_line_off;
	CBitmap m_bmp_rectangle_on;
	CBitmap m_bmp_rectangle_off;
	CBitmap m_bmp_clear;

	CButton	m_btn_measure_mode;
	CButton	m_btn_measure_line;
	CButton	m_btn_measure_rectangle;
	CButton	m_btn_measure_clear;

	afx_msg void OnBnClickedBtnAbs();
	afx_msg void OnBnClickedBtnRel();
	afx_msg void OnBnClickedBtnJogSlow();
	afx_msg void OnBnClickedBtnJogFast();
	afx_msg void OnEnChangeEditStageXInput();
	afx_msg void OnEnChangeEditStageYInput();
	afx_msg void OnEnChangeEditStageTInput();
	afx_msg void OnEnChangeEditStageXSpeed();
	afx_msg void OnEnChangeEditStageYSpeed();
	afx_msg void OnEnChangeEditStageTSpeed();
	afx_msg void OnStnClickedIconStageXStatus();
	afx_msg void OnStnClickedIconStageYStatus();
	afx_msg void OnStnClickedIconStageTStatus();
	afx_msg void OnStnClickedIconStageXHome();
	afx_msg void OnStnClickedIconStageYHome();
	afx_msg void OnStnClickedIconStageTHome();

	void AlarmMessageDisplay(CString strMessage, int nCase);

	eProcSeq	m_ProcSeq;
	eAlignResult	m_AlignResult;

	// 조명 활성화
	void SetVisionLight(int nCam);
	void ControlVisionLight(int nValue);

	// align 이미지 저장 및 alignment
	void ImageSave(BOOL bLeft, BOOL bRight, BOOL bBefore, BOOL bAfter);
	void ImageAlignment(BOOL bLeft, BOOL bRight);
	void AlignCalcuration();

	// gap 측정
	void GapMeasurement(int gapCount);

	// uv 활성화
	void SetUV(bool nCase);

	void SetJetting();

	CDC* pDCAlignLeft;
	CDC* pDCAlignRight;

	HDC hdcAlignLeft;
	HDC hdcAlignRight;

	char m_chBmpBuf[2448];
	BITMAPINFO* m_pBmpInfo = 0;

	void ChkStageX();
	void ChkStageY();
	void ChkStageT();

	void DisplayAlignImage(BOOL bLeft, BOOL bRight, Mat Image);


	CString strYearPath;
	CString strDayPath;
	CString strTimePath;
	CString strAlignPath;
	CString strAlignBeforePath;
	CString strAlignAfterPath;

	afx_msg void OnBnClickedBtnCycle();
};

