//---------------------------------------------------------------------------

#ifndef ACSMotionH
#define ACSMotionH
//---------------------------------------------------------------------------
// #include <Classes.hpp>
// #include <Controls.hpp>
// #include <StdCtrls.hpp>
// #include <ExtCtrls.hpp>
#include "pch.h"
#include "CriticalG.h"


//#include "Define.h"

//#include "mil.h"
//#include "milmod.h"
//#include "frmMainScr.h"

typedef struct _MODULE_INFO
{
    int         nPoints;
    vector<int> vModuleNo;

    void Init()
    {
        nPoints = 0;
        vModuleNo.clear();
    }
    _MODULE_INFO()
    {
        Init();
    }

}MODULE_INFO;



typedef struct _MODULE_STATES
{
    int         nModuleCnt;
    int         nTotalPoints;

	vector<MODULE_INFO> vInfo;

	void Init()
	{
        nModuleCnt     = 0;
        nTotalPoints   = 0;
        vInfo.clear();
	}
	_MODULE_STATES()
	{
		Init();
	}

}MODULE_STATES;

typedef struct _IO_STATES
{
	USHORT_DATA_16  IO;

	CString		strNames[16];

	void Init()
	{
		IO.init();
	}
	_IO_STATES()
	{
		Init();
		for(int i=0; i<16; i++)
		{
			strNames[i] = "";
		}
	}

}IO_STATES;


struct MOTOR_STATE_FLAGES
{
    int Motor_Flags;
	CCriticalG* m_Lock;
    MOTOR_STATE_FLAGES()
    {
        Motor_Flags = 0;
//		m_Lock = new CCriticalG();
    }
	~MOTOR_STATE_FLAGES()
	{
//		delete m_Lock;
	}

    BOOL IsMoving()
    {
		BOOL bRet;
//		m_Lock->Lock();
		if (Motor_Flags & ACSC_MST_MOVE)     
			bRet = TRUE;
        else
			bRet = FALSE;
//		m_Lock->UnLock();
		return bRet;
    }
	BOOL IsAccelerating()
    {
		BOOL bRet;
//		m_Lock->Lock();
		if (Motor_Flags & ACSC_MST_ACC) 		
			bRet = TRUE;
		else
			bRet = FALSE;
//		m_Lock->UnLock();
		return bRet;
    }
	BOOL IsInPosition()
    {
		BOOL bRet;
//		m_Lock->Lock();
		if (Motor_Flags & ACSC_MST_INPOS)  		
			bRet = TRUE;
		else
			bRet = FALSE;
//		m_Lock->UnLock();
		return bRet;
    }
	BOOL IsEnable()
    {
		BOOL bRet;
//		m_Lock->Lock();
		if (Motor_Flags & ACSC_MST_ENABLE)  			
			bRet = TRUE;
		else
			bRet = FALSE;
//		m_Lock->UnLock();
		return bRet;
    }

    void SetMotorMasks(int value, BOOL enable)
    {
//		m_Lock->Lock();
        if(enable)
            Motor_Flags = Motor_Flags | value;
        else
            Motor_Flags = Motor_Flags & (~value);
//		m_Lock->UnLock();
    }

    int GetValue(int value)
    {
		int nRet;
//		m_Lock->Lock();
        Motor_Flags = Motor_Flags & value;

        if(Motor_Flags > 0)
			nRet = 1;
        else
			nRet = 0;
//		m_Lock->UnLock();
		return nRet;

    }

};

struct SAFETY_CONTROL_STATES
{
    int  Data;
    int  TempData;

    void SetSafetyMastks(int value, bool enable)
    {
        if(enable)
            Data = Data | value;
        else
            Data = Data & (~value);
    }
    int GetValue(int value)
    {
        TempData = Data & value;

        if(TempData > 0)
            return 1;
        else
            return 0;
    }

};

typedef struct _Group_Slave_Info
{
    bool    bGroup;
    int     nSlaveAxis;
   // String  strSlaveAxisName;

    void init()
    {
        bGroup = false;
        nSlaveAxis = -1;
        //strSlaveAxisName = "";
    }
    _Group_Slave_Info()
    {
        init();
    }
}Group_Slave_Info;

typedef struct _Group_Info
{
    int                         nMasterAxis;
    //String                      strMasterAxisName;
    vector<Group_Slave_Info>    vSlaveInfo;

    void init()
    {
        nMasterAxis = -1;
      //  strMasterAxisName = "";
        vSlaveInfo.clear();
    }
    _Group_Info()
    {
        init();
    }

}Group_Info;



#define TIMEOUT_PEG_READY		3000
#define X_PEG_OUTPUT_MODE		0x4444		// PEG State 출력 설정값

//#define REAL_MOTOR_CNT          11



#define PURGE_OUT(bOn)			CACSM::SetBit(3, bOn)  //Purge Sol
#define VACCUM_OUT(bOn)			CACSM::SetBit(4, !bOn)  //Vaccum Sol
#define CLEARING_OUT(bOn)		CACSM::SetBit(5, bOn)  //Clearing Sol
#define BLOW_OUT(bOn)			CACSM::SetBit(6, bOn)
#define VACCUM_MC_OUT(bOn)		CACSM::SetBit(7, bOn)
#define STAGE_LAMP1_OUT(bOn)	CACSM::SetBit(12, !bOn)
#define STAGE_LAMP2_OUT(bOn)	CACSM::SetBit(13, !bOn)
#define POM_LAMP1_OUT(bOn)		CACSM::SetBit(14, !bOn)
#define POM_LAMP2_OUT(bOn)		CACSM::SetBit(15, !bOn)
//#define AIR_BEARING_OUT(bOn)	CACSM::SetBit(2, bOn)

#define SERVO_BK(bOn)					CACSM::SetBit(0, bOn)   //SERVO B/K
#define SOL1_OUT(bOn)					CACSM::SetBit(1, !bOn)  //Sol 1
#define SOL2_OUT(bOn)		    		CACSM::SetBit(2, bOn)   //Sol 2
#define VACCUM_SCANNER_MC_OUT(bOn)		CACSM::SetBit(4, bOn)
//#define AIR_BEARING_OUT(bOn)	CACSM::SetBit(2, bOn)


//#define IsAirBearingOut			CACSM::ReadOutputBit(2)

#define IsRAFHomeSensor			CACSM::ReadInputBit(0)
#define IsAZHomeSensor			CACSM::ReadInputBit(1)
#define ISBreak					CACSM::ReadInputBit(2)
//#define NONE					CACSM::ReadInputBit(3)  // append 210304 (for using opencv mat.hpp)
#define IsNONE					CACSM::ReadInputBit(3)  // append 210304 (NONE -> IsNONE)

// #define IsVaccumHighLimit		CACSM::ReadInputBit(4)
// #define IsPurgeLowLimit			CACSM::ReadInputBit(5)
// #define IsPurgeHighLimit		CACSM::ReadInputBit(6)
// #define IsAirBearingLowLimit	CACSM::ReadInputBit(7)
// #define IsAirBearingHighLimit	CACSM::ReadInputBit(8)
// #define IsGlassExist			CACSM::ReadInputBit(9)
// #define IsEmergency		        !CACSM::ReadInputBit(10)

//Line Arc 조합은
//acsc_ExtendedSegmentedMotion
//원일때는...
//acsc_ExtArc1 이나 acsc_ExtArc2

//class TfrmLog;
class CACSMotion;
class CJettingVisionDlg;
class CNetworkConfig;
//class CField;
class CACSM
{
private:
protected:
	
	static	BOOL				m_bOpen;
    static  double              *m_dCommandPos;
    static  BOOL    OpenCommTCP(ACS_COMM_CONFIG comm_conf);

public:
	static CCriticalG*				m_pACSSyncData;
	static CJettingVisionDlg*            	m_pDuasEotsDlg;
	static HANDLE              	m_hComm;
	static int                 	m_nMotCnt;

	static  void                MotorsApplayPara();

	static  CACSMotion*         m_pACSMotion;
	static	CString				m_strErrMsg;

	static	double				*m_dInputCommandPos;
	static  double              *m_dActualPos;
	static  double              *m_dRefPos;
	static	double				*m_dTagetPos;
	static  double              *m_dLeft_SoftLimit;
	static  double              *m_dRight_SoftLimit;
	static  double              *m_dMaxSpeed;
	//static  vector<Group_Info>          m_vGroupInfo;
	static  int                 m_nMasterAxis;
    static  int                 m_nSlaveAxis;
	static  int                 m_nInitHomeBufferIdx;
	static  int                 m_nInitHomeDone;
    static  int                 m_nInitParameters;

    static  int                 REAL_MOTOR_CNT;
    static  int                 m_nCalibX;
    static  int                 m_nCalibY;
	static  vector<IO_STATES>               m_vInputStates;
	static  vector<IO_STATES>               m_vOutputStates;
	static  MODULE_STATES                   m_InputModule;
	static  MODULE_STATES                   m_OutputModule;
//  int       gMOTReadMap();
//  void      gMOTWriteMap();
//  void      gMOTApplayPara();
public:

public:

			 CACSM(CJettingVisionDlg* pFrmEdit );
	virtual	~CACSM();
	static BOOL		IsOpen();
	static	void	OpenTest(char* ch, int nPont);
    static  void    InitOnce(int nMotCnt);
	static	BOOL	InitOpen(ACS_COMM_CONFIG comm_conf);
    static  BOOL    ApplyMotionParameter(void);
    static  BOOL    ReadBaseIOConfig();
    static  BOOL    ReadIOConfig();
    static  BOOL    OpenComm(ACS_COMM_CONFIG comm_conf);
    static  BOOL    CloseComm();
    static  BOOL    GetConnectionInfo(ACSC_CONNECTION_INFO* _connection_info);
    static  BOOL    TerminateConnection(ACSC_CONNECTION_DESC* _connection);
    static  BOOL    GetPCICardsInfo(ACSC_PCI_SLOT* _cards, int _nCnt, int* _nDetectedCardsCnt);

    //다축 관련
    static  BOOL    Motions_Enable(     int *_axis,         ACSC_WAITBLOCK* _wait);
    static  BOOL    Motions_Disable(    int *_axis,         ACSC_WAITBLOCK* _wait);
    static  BOOL    Motions_Disable_All(                    ACSC_WAITBLOCK* _wait);
    static  BOOL    Motion_Group(       int *_axis,         ACSC_WAITBLOCK* _wait);
    static  BOOL    Motion_Split(       int *_axis,         ACSC_WAITBLOCK* _wait);
    static  BOOL    Motion_Split_all(                       ACSC_WAITBLOCK* _wait);
    static  BOOL    Motions_Go(         int *_axis,         ACSC_WAITBLOCK* _wait);
    static  BOOL    Motions_Stop(       int *_axis,         ACSC_WAITBLOCK* _wait);
    static  BOOL    Motions_Kill(       int *_axis,         ACSC_WAITBLOCK* _wait);
    static  BOOL    Motion_Kill_all(                        ACSC_WAITBLOCK* _wait);
    static  BOOL    Motions_Break(      int *_axis,         ACSC_WAITBLOCK* _wait);
    static  BOOL    Motions_ToPoint(    int _flags,         int *_axis,             double *_point,     ACSC_WAITBLOCK* _wait);
    static  BOOL    Motions_ExtToPoint( int _flags,         int *_axis,             double *_point,
                                            double _velo,       double _end_velo,       ACSC_WAITBLOCK* _wait);
    static  BOOL    Motions_Jog(        int _flags,         int* _axis,             int* _direction,
                                            double _velo,       ACSC_WAITBLOCK* _wait);
    static  BOOL    Motions_MultiPoint(int _flags, int* _axis, double _dwell, ACSC_WAITBLOCK* _wait);

    static  BOOL      Motions_Stopper(int* _axis, ACSC_WAITBLOCK* _wait);
    static  BOOL      Motions_Projection(int* _axis, char* _matrix, ACSC_WAITBLOCK* _wait);
    static  BOOL      Motions_AddPoint(int* _axis, double* _point , ACSC_WAITBLOCK* _wait);
    static  BOOL      Motions_ExtAddPoint(int* _axis, double* _point , double _rate,  ACSC_WAITBLOCK* _wait);

    //motion의 연속동작 구현 관련(arc, line등)
    static  BOOL      Motions_Segment(int nFlags, int* npAxis, double* dpPoint , ACSC_WAITBLOCK* pWait);
    static  BOOL      Motions_EndSequence(int* npAxis, ACSC_WAITBLOCK* pWait);
    //int _ACSCLIB_ WINAPI acsc_Arc1    (HANDLE Handle, int* Axes, double* Center, double* FinalPoint, int Rotation, ACSC_WAITBLOCK* Wait);
    //int _ACSCLIB_ WINAPI acsc_ExtArc1 (HANDLE Handle, int* Axes, double* Center, double* FinalPoint, int Rotation, double Velocity, ACSC_WAITBLOCK* Wait);
    static  BOOL      Motions_Line(int* npAxis, double* dpPoint , ACSC_WAITBLOCK* pWait);
    static  BOOL      Motions_ExtLine(int* npAxis, double* dpPoint, double dVelocity, ACSC_WAITBLOCK* pWait);
    static  BOOL      Motions_Arc1(int* npAxis, double* dpCenter, double* dpFinalPoint, int nRotation, ACSC_WAITBLOCK* pWait);
    static  BOOL      Motions_ExtArc1(int* npAxis, double* dpCenter, double* dpFinalPoint, int nRotation, double dVelocity, ACSC_WAITBLOCK* pWait);

    //추가
    static BOOL		  Motions_ExtendedSegmentedMotion(int nFlags, int* pAxis, double* pPoint, double dVel, double dEndVel, double dJunctionVel, double dAngle,
        double dStarvationMargin, char* pSegments, ACSC_WAITBLOCK* pWait);
	static BOOL		  	Motions_SegmentLine(int nFlags, int* pAxis, double* pPoint, double dVelocity, double dEndVelocity, char* pValues, char* pVariables,
		int nIndex, char* pMasks, ACSC_WAITBLOCK* pWait);
	static BOOL		  	Motions_SegmentArc2(int nFlags, int* pAxis, double* pCenter, double dAngle, double dVelocity, double dEndVelocity, char* pValues, char* pVariables,
		int nIndex, char* pMasks, ACSC_WAITBLOCK* pWait);



    static  BOOL      Motion_GetProgramState(int _buffer, int* _state , ACSC_WAITBLOCK* _wait);

	static  BOOL      Motion_GetInput(int _port, int _bit, int* _value , ACSC_WAITBLOCK* _wait);
	static  BOOL      Motion_GetInputPort(int _port, int* _value , ACSC_WAITBLOCK* _wait);
	static  BOOL      Motion_GetOutput(int _port, int _bit, int* _value , ACSC_WAITBLOCK* _wait);
    static  BOOL      Motion_GetOutputPort(int _port, int* _value , ACSC_WAITBLOCK* _wait);
    static  BOOL      Motion_SetOutput(int _port, int _bit, int _value , ACSC_WAITBLOCK* _wait);
    static  BOOL      Motion_SetOutputPort(int _port, int _value , ACSC_WAITBLOCK* _wait);
    static  BOOL      Motion_GetAnalogInput(int _port, int* _value , ACSC_WAITBLOCK* _wait);
    static  BOOL      Motion_GetAnalogOutput(int _port, int* _value , ACSC_WAITBLOCK* _wait);
    static  BOOL      Motion_SetAnalogOutput(int _port, int _value , ACSC_WAITBLOCK* _wait);
    static  BOOL      Motion_GetExtInput(int _port, int _bit, int* _value , ACSC_WAITBLOCK* _wait);
    static  BOOL      Motion_GetExtInputPort(int _port, int* _value , ACSC_WAITBLOCK* _wait);
    static  BOOL      Motion_GetExtOutput(int _port, int _bit, int* _value , ACSC_WAITBLOCK* _wait);
    static  BOOL      Motion_GetExtOutputPort(int _port, int* _value , ACSC_WAITBLOCK* _wait);
    static  BOOL      Motion_SetExtOutput(int _port, int _bit, int _value , ACSC_WAITBLOCK* _wait);
    static  BOOL      Motion_SetExtOutputPort(int _port, int _value , ACSC_WAITBLOCK* _wait);

    static  BOOL      Motions_FaultClear(int* _axis, ACSC_WAITBLOCK* _wait);

    static  BOOL      Motions_WaitForAsyncCall(void* _buf, int* _received, ACSC_WAITBLOCK* _wait, int _timeout);
    static  BOOL      Motion_WaitProgramEnd(int _buffer, int _timeout);

    static  BOOL      Motion_WaitInput(int _port, int _bit, int _state, int _timeout);
    static  BOOL      Motion_WaitUserCondition(ACSC_USER_CONDITION_FUNC _user_condition, int _timeout);

    static  BOOL      Motion_DeclareVariable(int _type, char* _name, ACSC_WAITBLOCK* _wait);
    static  BOOL      Motion_ClearVariables(ACSC_WAITBLOCK* _wait);

    static  BOOL      Motion_GetProgramError(int _buffer, int* _error, ACSC_WAITBLOCK* _wait);
    static  BOOL      Motion_GetEtherCATError(int* _error, ACSC_WAITBLOCK* _wait);

    static  BOOL      Motion_GetEtherCATState(int* _state, ACSC_WAITBLOCK* _wait);
    static  BOOL      Motion_MapEtherCATInput(int _flags, int _offset, char* _variable_name, ACSC_WAITBLOCK* _wait);
    static  BOOL      Motion_MapEtherCATOutput(int _flags, int _offset, char* _variable_name, ACSC_WAITBLOCK* _wait);
    static  BOOL      Motion_UnmapEtherCATInputsOutputs(ACSC_WAITBLOCK* _wait);

    static  BOOL      Motion_RegisterEmergencyStop();
    static  BOOL      Motion_UnregisterEmergencyStop();
    static  BOOL      Motion_AnalyzeApplication(char* _file_name, ACSC_APPSL_INFO** _info, ACSC_WAITBLOCK* _wait);
    static  BOOL      Motion_LoadApplication(char* _file_name, ACSC_APPSL_INFO* _info, ACSC_WAITBLOCK* _wait);
    static  BOOL      Motion_SaveApplication(char* _file_name, ACSC_APPSL_INFO* _info, ACSC_WAITBLOCK* _wait);
    static  BOOL      Motion_FreeApplication(ACSC_APPSL_INFO* _info);
    static  BOOL      Motion_ControllerReboot(int _timeout);


	static  BOOL      Motion_GetErrorString(int _error_code, char* _error_str, int _count, int* _received);
	static  int       Motion_GetLastError();
	static  CString		Motion_GetLastErrorMessage();
    static  CString		Motion_GetLastErrorMessage(int *nErrCode);
    static  int       Motion_GetTimeout();
    static  int       Motion_GetDefaultTimeout();
	static  BOOL      Motion_SetIterations(int _iterations);
    static  BOOL      Motion_SetCommOptions(unsigned int _options);
    static  BOOL      Motion_SetTimeout(int _timeout);
    static  BOOL      Motion_SetQueueOverflowTimeout(int _delay);
    static  int       Motion_GetQueueOverflowTimeout();
    static  BOOL      Motion_GetCommOptions(unsigned int* _Options);

    static  BOOL      Motion_ReadInteger(int _nbuf, char* _var, int _from1, int _to1, int _from2,
    int _to2, int* _values, ACSC_WAITBLOCK* _wait);
    static  BOOL      Motion_WriteInteger(int _nbuf, char* _var, int _from1, int _to1, int _from2,
    int _to2, int* _values, ACSC_WAITBLOCK* _wait);
    static  BOOL      Motion_ReadReal(int _nbuf, char* _var, int _from1, int _to1, int _from2,
    int _to2, double* _values, ACSC_WAITBLOCK* _wait);
    static  BOOL    Motion_WriteReal(int _nbuf, char* _var, int _from1, int _to1, int _from2,
    int _to2, double* _values, ACSC_WAITBLOCK* _wait);

	static  BOOL	RunHome(int nBufferIdx, char* chLabel, ACSC_WAITBLOCK* Wait);
	static  BOOL	StopHome(int nBufferIdx, ACSC_WAITBLOCK* Wait);
    static  BOOL	Motion_Transaction(char* _out_buf, int _out_cnt, char* _in_buf, int _in_cnt, int* _received, ACSC_WAITBLOCK* _wait);


	static  int		GetInitHomeStatus(void);
	static  void	GetInitHomeFlag();
    static  void    SetInitHomeFlag(int nFlag);    


	static  BOOL		GetActualPos();
	static  double		GetActualPos(int nMotidx);
	static  BOOL		GetReferencePos();
	static  double		GetRefPos(int nMotidx);
	static	BOOL		GetTargetPos();
	static	double		GetTargetPos(int nMotidx);
	static  BOOL		GetLeftSoftLimit();
    static  BOOL		SetLeftSoftLimit(int nMotSelect, double dLeftSoftLimitPos);
    static  BOOL		GetRightSoftLimit();
    static  BOOL      SetRightSoftLimit(int nMotSelect, double dRightSoftLimitPos);
    static  BOOL      GetMaxSpeed();
    static  void      SetMaxSpeed(int nMotSelect, double dMaxSpeed);
	
    static  void      SetGroupMaster(int nAxis);
    static  void      SetGroupSlave(int nMasterAxis, int nSlaveAxis);
    static  void      ReSetGroupMaster(int nAxis);
    static  void      ReSetGroupSlave(int nMasterAxis, int nSlaveAxis);
    static  BOOL      AddDefaultAxisForGroup();
    static  BOOL      Group();
    static  BOOL      UnGroup();    
    static  BOOL      SetSyncGroup(int nMasterAxis, int nSlaveAxis);
	static  BOOL      ReSetSyncGroup(int nSlaveAxis);
    static  void      SetCommandPos(int nMotidx, double dCommandPos);
    static  double    GetCommandPos(int nMotidx);
	//Sin진동 관련 함수
	//Frequency 설정함수
	static	void	SetFreq(int nMotSelect, double dFreq);
	static  void	SetPeriod(int nMotSelect, double dPeriod);
	static  void	SetFreqChange(int nMotSelect, double dChangeFreq);
	static  void	SetRunTime(int nMotSelect, int nRunTime);
	static	void	SetSinWaveAxis(int nMotSelect, int nAxis);
	static	BOOL    RunSinMove(int nBufferIdx, char* chLabel, ACSC_WAITBLOCK* Wait);
	static	void    StopSinMove(int nMotSelect);
	static	BOOL	GetCompletSinMove();

	static  int       ReadInput();
	static  BOOL      ReadInputBit(int nIdx, int nBitNo);
    
	static  BOOL      ReadInputBit(int nBitNo);

	static  BOOL      SetBit(int nIdx, int nBitNo, BOOL bOn);
	static  void      SetBit(int nBitNo, BOOL bOn);

	static  void      SetOutput(int nModuleNo, int nIdx, unsigned short nValue);
	static  void      GetOutput();
	static  BOOL      ReadOutputBit(int nIdx, int nBitNo);
	static  BOOL 	  ReadOutputBit(int nBitNo);
    static  CString	  GetNameOfAxis(int nAxis);
    static  BOOL      SetHomeOffset();
    static  BOOL      SetHomeOffsetVel();
    static  void      GetAllHomeStatus();
    static  void      GetAllSystemFault();
	static	void	  GetAllMotorStatus();


    //int _ACSCLIB_ WINAPI acsc_ExtendedSegmentedMotion(HANDLE Handle, int Flags, int* Axes, double* Point, double Velocity, double EndVelocity, double JunctionVelocity,
    //double Angle, double StarvationMargin, char* Segments, ACSC_WAITBLOCK* Wait);





};

class CCriticalG;
class CACSMotion : CACSM
{

private:

protected:
//    BOOL    OpenCommSimul();
//    BOOL    OpenCommSerial();
//    BOOL    OpenCommTCP();
//    BOOL    OpenCommUDP();
//    BOOL    OpenCommPCI();

public:
    //static   CACSMotion*    g_pACSMotion;

//
	CCriticalG*				m_pSyncData;
    int                     m_nHomeDone;        //Home 상태 저장
    CString                 m_strMotorName;          //모터의 이름 저장
    SAFETY_CONTROL_STATES   m_SafetyControlStates[3];   //0: Use/UnUse Safety, 1:Set InVersion, 2:Use Response
    MOTOR_STATE_FLAGES      m_MotorState;
    bool                    m_bMotionEnable;
	CString                 m_strErrMsg;
	CString                 m_strMotorErrMsg;
    int                     m_nSystemError;
    int                     m_nMotorErrNum;


//Common
    //String              m_strMortorName;    //Motor Name
    int                 m_nAxisIdx;         //전체 Axis에서의 Index
	CString				m_strMsg;           //motor에 관련된 Message를 저장하는 버퍼
    bool                m_bUserStop;        //사용자가 정지 시킨것 판별 유무
    double              m_dCurSpd;          //현재 Spd
    double              m_dCurAcc;          //현재 Acc
    int                 m_nHomeBufferIdx;       //Home관련 Buffer Index

//Hard Set
    int                 m_nAxis;            //축 번호
	int					m_nEncAxis;			//외부 엔코더 축 번호 기본 축번호에 1씩 증가 시켜야함..
    bool                m_bIsGroup;         //그룹 정보
    bool                m_bIsMaster;        //그룹일 경우 마스터인지 슬레이브인지
    int                 m_nFault;			//에러 정보
	int					m_nEncAxisFault;	//엔코더 축 에러 정보

    int                 m_nInv;             //Invesion 사용 유무 체크
//    double              m_dUnitPulse;       //Unit per Pulse
//    int                 m_nEncX;            //채배 설정값
//    int                 m_nPulseOut;        //Pulse Out 설정 값
//    int                 m_nUseZPhase;       //z상 사용유무
    int                 m_nUseHomeSens;     //Home Senser 사용유무
    int                 m_nHomeSensLvl;     //Home Senser Level
    int                 m_nPLimitLvl;       //Pluse Limit Senser Level 설정
    int                 m_nNLimitLvl;       //Minus Limit Senser Level 설정
    int                 m_nPSLimitLvl;      //Pluse Slow Limit Senser Level 설정
    int                 m_nNSLimitLvl;      //Pluse Slow Limit Senser Level 설정
    int                 m_nArmUse;          //Alram 신호 사용유무
    int                 m_nArmLvl;          //Alram 신호 Level 설정
    int                 m_nInposUse;        //Inposition 신호 사용유무
    int                 m_nInposLvl;        //Inposition 신호 Level를 설정
    int                 m_nSvoLvl;          //Minus Slow Limit 센서 Level설정
    int                 m_nActInv;          //Actual Pos 위치 데이터 역수 설정 여부 옵션(1:역수)
//Soft Set
    double              m_dHomeSpd;         //Home Speed
    double              m_dHomeAcc;         //Home Acc 설정

    double              m_dLowSpd;          //Maint Speed
    double              m_dLowAcc;          //Maint Acc
	double				m_dLowDecel;		//Maint Decel
	double				m_dLowKillDecel;	
	double				m_dLowJerk;

    double              m_dMidSpd;          //Maint Speed
    double              m_dMidAcc;          //Maint Acc
	double				m_dMidDecel;		//Maint Decel
	double				m_dMidKillDecel;
	double				m_dMidJerk;

    double              m_dHighSpd;         //Maint Speed
    double              m_dHighAcc;         //Maint Acc
	double				m_dHighDecel;		//Maint Decel
	double				m_dHighKillDecel;
	double				m_dHighJerk;

    double              m_dVelocity;
    double              m_manualVelocity;
    double              m_movingVelocity;
    double              m_jettingVelocity;
    double              m_dAccel;
    double              m_dDecel;
    double              m_dKillDecel;
    double              m_dJerk;




    double              m_dMaxSpd;          //Max Speed
    double              m_dStartStopSpd;    //start/stop speed
	double              m_dMaxStroke;       //Max Stroke 설정
	double              m_dMaxPos;          //Max Angle 설정
	double              m_dMinPos;          //Min Angle 설정

    int                 m_nRunTimeOut;      //Move 동작중 Timeout을 설정
    int                 m_nHomeTimeOut;     //Home 동작중 TimeOut을 설정

    int                 m_nActByCmd;        //act pos를 cmd로 표시여부
    int                 m_nDebugMode;       //모터의 마지막 상태를 기록
    int                 m_nTestMode;        //
	CString             m_strHomeRetVarName; //home done 변수
	CString             m_strHomeOffsetVarName; //home offset 변수
	double              m_dHomeOffset;      //Home 동작 할 때 Offset 거리
    double              m_dHomeOffsetVel;
	CString             m_strHomeOffsetVelVarName;

    //repeat 관련
    bool                m_bRepeatEnable;
    bool                m_bRepeatMoveDir;
    double              m_dRepeatPosStart;
    double              m_dRepeatPosEnd;
    int                 m_nRepeatCnt;
    int                 m_nRepeatAct;


//	TTimer* 		m_timer_state;

//    int             m_general_input;
//    int             m_general_output;
//	int             m_fault_mask;
//	int             m_motor_fault;
//	int             m_emergency_mask;
//	int             m_emergency_fault;
//
//    double          m_RPosition[ACS_MAX_AXIS_COUNT];		// Command Position
//	double          m_FPosition[ACS_MAX_AXIS_COUNT];		// Actual Position
//	double          m_FVelocity[ACS_MAX_AXIS_COUNT];		// Actual Velocity
//	double          m_PositionErr[ACS_MAX_AXIS_COUNT];	    // Position Error
//	int             m_MotorStatus[ACS_MAX_AXIS_COUNT];	    // Motor Status

public:
				CACSMotion();
	virtual		~CACSMotion();
//    BOOL      InitOnce();
//    BOOL      OpenComm(int _comm_type);
//    BOOL      CloseComm();
//    BOOL      GetConnectionInfo(ACSC_CONNECTION_INFO* _connection_info);
//    BOOL      TerminateConnection(ACSC_CONNECTION_DESC* _connection);

    BOOL      SetVelocity(    /*int _axis,*/      /*double _velocity,*/   ACSC_WAITBLOCK* _wait);
    BOOL      SetVelocityManual(    /*int _axis,*/      /*double _velocity,*/   ACSC_WAITBLOCK* _wait);
    BOOL      SetVelocityMoving(    /*int _axis,*/      /*double _velocity,*/   ACSC_WAITBLOCK* _wait);
    BOOL      SetVelocityJetting(    /*int _axis,*/      /*double _velocity,*/   ACSC_WAITBLOCK* _wait);
    BOOL      GetVelocity(    /*int _axis,*/      double *_velocity,  ACSC_WAITBLOCK* _wait);
    BOOL      SetAccel(       /*int _axis,*/      /*double _accel,*/      ACSC_WAITBLOCK* _wait);
    BOOL      GetAccel(       /*int _axis,*/      double *_accel,     ACSC_WAITBLOCK* _wait);
    BOOL      SetDecel(       /*int _axis,*/      /*double _decel,*/      ACSC_WAITBLOCK* _wait);
    BOOL      GetDecel(       /*int _axis,*/      double *_decel,     ACSC_WAITBLOCK* _wait);
    BOOL      SetJerk (       /*int _axis,*/      /*double _djerk,*/      ACSC_WAITBLOCK* _wait);
    BOOL      GetJerk(        /*int _axis,*/      double *_djerk,     ACSC_WAITBLOCK* _wait);
    BOOL      SetKillDecel(   /*int _axis,*/      /*double _dkilldecel,*/ ACSC_WAITBLOCK* _wait);
	BOOL      GetKillDecel(   /*int _axis,*/      double *_dkilldecel, ACSC_WAITBLOCK* _wait);

	BOOL      SetJogVelocity(    /*int _axis,*/   /*double _velocity,*/   ACSC_WAITBLOCK* _wait);
	BOOL      GetJogVelocity(    /*int _axis,*/   double *_velocity,  ACSC_WAITBLOCK* _wait);
	BOOL      SetJogAccel(       /*int _axis,*/   /*double _accel,*/      ACSC_WAITBLOCK* _wait);
	BOOL      GetJogAccel(       /*int _axis,*/   double *_accel,     ACSC_WAITBLOCK* _wait);
	BOOL      SetJogDecel(       /*int _axis,*/   /*double _decel,*/      ACSC_WAITBLOCK* _wait);
	BOOL      GetJogDecel(       /*int _axis,*/   double *_decel,     ACSC_WAITBLOCK* _wait);
	BOOL      SetJogJerk (       /*int _axis,*/   /*double _djerk,*/      ACSC_WAITBLOCK* _wait);
	BOOL      GetJogJerk(        /*int _axis,*/   double *_djerk,     ACSC_WAITBLOCK* _wait);
	BOOL      SetJogKillDecel(   /*int _axis,*/   /*double _dkilldecel,*/ ACSC_WAITBLOCK* _wait);
	BOOL      GetJogKillDecel(   /*int _axis,*/   double *_dkilldecel, ACSC_WAITBLOCK* _wait);

    BOOL      SetFPos(        /*int _axis,*/      double _fPos,       ACSC_WAITBLOCK* _wait);
    BOOL      GetFPos(        /*int _axis,*/      double *_fPos,      ACSC_WAITBLOCK* _wait);
    BOOL      SetRPos(        /*int _axis,*/      double _fPos,       ACSC_WAITBLOCK* _wait);
    BOOL      GetRPos(        /*int _axis,*/      double *_fPos,      ACSC_WAITBLOCK* _wait);
    BOOL      GetFVelo(       /*int _axis,*/      double *_fVelo,     ACSC_WAITBLOCK* _wait);
	BOOL      GetRVelo(       /*int _axis,*/      double *_rVelo,     ACSC_WAITBLOCK* _wait);
	BOOL      SetActualPos(						double dPos);

    //모터 초기화
    BOOL      Commut(             /*int _axis,*/      ACSC_WAITBLOCK* _wait);
    BOOL      Motion_Enable(      /*int _axis,*/      ACSC_WAITBLOCK* _wait);
    BOOL      Motion_Disable(     /*int _axis,*/      ACSC_WAITBLOCK* _wait);
    BOOL      Motion_Go(          /*int _axis,*/      ACSC_WAITBLOCK* _wait);
    BOOL      Motion_Stop(        /*int _axis,*/      ACSC_WAITBLOCK* _wait);
    BOOL      Motion_Kill(        /*int _axis,*/      ACSC_WAITBLOCK* _wait);
    BOOL      Motion_Break(       /*int _axis,*/      ACSC_WAITBLOCK* _wait);
    BOOL      Motion_ToPoint(     int _flags,         /*int _axis,*/          double _point,      ACSC_WAITBLOCK* _wait);
    BOOL      Motion_ExtToPoint(  int _flags,         /*int _axis,*/          double _point,
                                            double _velo,       double _end_velo,       ACSC_WAITBLOCK* _wait);
    BOOL      Motion_Track(       int _flags,         /*int _axis,*/          ACSC_WAITBLOCK* _wait);
    BOOL      Motion_SetTargetPos(/*int _axis,*/      double _taget_pos,      ACSC_WAITBLOCK* _wait);
    BOOL      Motion_GetTargetPos(/*int _axis,*/      double *_taget_pos,     ACSC_WAITBLOCK* _wait);
    BOOL      Motion_Jog(         int _flags,         /*int _axis,*/          double _velo,       ACSC_WAITBLOCK* _wait);

    BOOL      Motion_SetMaster(   /*int _axis,*/      char* _formula,         ACSC_WAITBLOCK* _wait);
    BOOL      Motion_Slave(       int _flags,         /*int _axis,*/          ACSC_WAITBLOCK* _wait);
    BOOL      Motion_Slave_Stalled(int _flags,        /*int _axis,*/          double _left,
                                                double _right,  ACSC_WAITBLOCK* _wait);

    BOOL      Motion_MultiPoint(int _flags, /*int _axis,*/ double _dwell, ACSC_WAITBLOCK* _wait);

    BOOL      Motion_AddPoint(/*int _axis,*/ double _point , ACSC_WAITBLOCK* _wait);
    BOOL      Motion_ExtAddPoint(/*int _axis,*/ double _point, double _rate, ACSC_WAITBLOCK* _wait);


    BOOL      Motion_EndSequence(/*int _axis,*/ ACSC_WAITBLOCK* _wait);
    BOOL      Motion_GetMotorState(ACSC_WAITBLOCK* _wait);
    BOOL      Motion_GetAxisState(/*int _axis,*/ int* _state , ACSC_WAITBLOCK* _wait);
    BOOL      Motion_GetIndexState(/*int _axis,*/ int* _state , ACSC_WAITBLOCK* _wait);
    BOOL      Motion_ResetIndexState(/*int _axis,*/ int _mask , ACSC_WAITBLOCK* _wait);

	BOOL	  Motion_GetEncoderFault(/*int _axis,*/ int* _fault, ACSC_WAITBLOCK* _wait);
    BOOL      Motion_GetFault(/*int _axis,*/ int* _fault, ACSC_WAITBLOCK* _wait);
    BOOL      Motion_SetFaultMask(/*int _axis,*/ int _mask, ACSC_WAITBLOCK* _wait);
    BOOL      Motion_GetFaultMask(/*int _axis, int* _mask,*/ ACSC_WAITBLOCK* _wait);
    BOOL      Motion_EnableFault(/*int _axis,*/ int _fault , ACSC_WAITBLOCK* _wait);
    BOOL      Motion_DisableFault(/*int _axis,*/ int _fault , ACSC_WAITBLOCK* _wait);
    BOOL      Motion_SetResponseMask(/*int _axis,*/ int _mask, ACSC_WAITBLOCK* _wait);
    BOOL      Motion_GetResponseMask(/*int _axis,*/ int* _mask, ACSC_WAITBLOCK* _wait);
    BOOL      Motion_EnableResponse(/*int _axis,*/ int _response, ACSC_WAITBLOCK* _wait);
    BOOL      Motion_DisableResponse(/*int _axis,*/ int _response, ACSC_WAITBLOCK* _wait);
    BOOL      Motion_GetSafetyInput(/*int _axis,*/ int _input, int* _value, ACSC_WAITBLOCK* _wait);
    BOOL      Motion_GetSafetyInputPort(/*int _axis,*/ int* _value, ACSC_WAITBLOCK* _wait);
    BOOL      Motion_GetSafetyInputPortInv(/*int _axis,*/ int* _value, ACSC_WAITBLOCK* _wait);
    BOOL      Motion_SetSafetyInputPortInv(/*int _axis,*/ int _value, ACSC_WAITBLOCK* _wait);
    BOOL      Motion_FaultClear(/*int _axis,*/ ACSC_WAITBLOCK* _wait);

    BOOL      Motion_WaitMotionEnd(/*int _axis,*/ int _timeout);
    BOOL      Motion_WaitLogicalMotionEnd(/*int _axis,*/ int _timeout);

    BOOL      Motion_WaitMotorEnabled(/*int _axis,*/ int _state, int _timeout);
    BOOL      Motion_WaitMotorCommutated(/*int _axis,*/ int _state, int _timeout);

    BOOL      Motion_GetMotorError(/*int _axis,*/ int* _error, ACSC_WAITBLOCK* _wait);
    BOOL      Motion_GetMotionError(/*int _axis,*/ int* _error, ACSC_WAITBLOCK* _wait);
//    BOOL      Motion_GetEtherCATSlaveIndex(int _vendor_id, int _product_id, int _count, int* _slave_index, ACSC_WAITBLOCK* _wait);

    BOOL      Motion_PegInc(int _flags, /*int _axis,*/ double _width, double _first_point,
    double _interval, double _last_point, int _tb_number, double _tb_period, ACSC_WAITBLOCK* _wait);

    BOOL      Motion_PegRandom(int _flags, /*int _axis,*/ double _width, char* _point_array,
    char* _state_array, int _tb_number, double _tb_period, ACSC_WAITBLOCK* _wait);
    BOOL      Motion_AssignPins(/*int _axis,*/ unsigned short _mask, ACSC_WAITBLOCK* _wait);
    BOOL      Motion_StopPeg(/*int _axis,*/ ACSC_WAITBLOCK* _wait);
    BOOL      Motion_AssignPegNT(/*int _axis,*/ int _eng_to_enc_bit_code, int _gp_outs_bit_code, ACSC_WAITBLOCK* _wait);
    BOOL      Motion_AssignPegOutputsNT(/*int _axis,*/ int _output_index, int _bit_code, ACSC_WAITBLOCK* _wait);
    BOOL      Motion_AssignFastInputsNT(/*int _axis,*/ int _input_index, int _bit_code, ACSC_WAITBLOCK* _wait);
    BOOL      Motion_PegIncNT(int _flags, /*int _axis,*/ double _width, double _first_point,
    double _interval, double _last_point, int _tb_number, double _tb_period, ACSC_WAITBLOCK* _wait);
    BOOL      Motion_PegRandomNT(int _flags, /*int _axis,*/ double _width, int _mode, int _first_index,
    int _last_index, char* _point_array, char* _state_array, int _tb_number, double _tb_period, ACSC_WAITBLOCK* _wait);
    BOOL      Motion_WaitPegReadyNT(/*int _axis,*/ int _timeout);
    BOOL      Motion_StartPegNT(/*int _axis,*/ ACSC_WAITBLOCK* _wait);
    BOOL      Motion_StopPegNT(/*int _axis,*/ ACSC_WAITBLOCK* _wait);


    BOOL	Motion_Save_Momory(ACSC_WAITBLOCK* _wait);

    BOOL	GetSystemFault(void);
	BOOL	GetEncoderSystemFault(void);
	BOOL	GetSystemInv(void);
    BOOL	IsAlarm(int nValue);
	BOOL	IsEncAxisAlarm(int nValue);
    void	GetMotorError(void);
	BOOL	IsError(void);
	BOOL	IsMoving();
	BOOL	IsAccelerating();
	BOOL	IsInPosition();
	BOOL	IsEnable();

	BOOL	MoveAbs(int nFlags, double dTarget, ACSC_WAITBLOCK* nWait);
    BOOL	MoveRel(int nFlags, double dTarget, ACSC_WAITBLOCK* nWait);
	BOOL	MoveJog(int nFlags, double dVelo, ACSC_WAITBLOCK* nWait);

    void	GetHomeFlag();
    void	SetHomeFlag(int nFlag);
	int		PEG_Prepare();
	//int           PEG_OutState(std::vector<double> vPos, string strPosName, string strStateName, double dPulse_Width =0.5 );
	int		PEG_SetPos(double dWidth, double dFirstPos, double dLastPos, double dFreq);
    int		PEG_SetPos_Single(double dWidth, double dFirstPos, double dLastPos, double dFreq);    
	BOOL	GetCurrFeedBackVel(double *dRefVel);
	BOOL	GetCmdRefVel(double *dRefVel);


};
//---------------------------------------------------------------------------

#endif
