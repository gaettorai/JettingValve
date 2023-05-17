//---------------------------------------------------------------------------
#include "pch.h"

#pragma hdrstop

//#include <IniFiles.hpp>
//#include "stdafx.h"
#include "JettingVisionDlg.h"
#include "CriticalG.h"
#include "ACSMotion.h"
#include <vector>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#pragma comment(lib, "ACSCL_x64.lib")
BOOL					CACSM::m_bOpen;
CJettingVisionDlg*           CACSM::m_pDuasEotsDlg;
HANDLE                  CACSM::m_hComm =ACSC_INVALID;
int                     CACSM::m_nMotCnt=0;
CACSMotion*             CACSM::m_pACSMotion;
double*                 CACSM::m_dRefPos;
double*					CACSM::m_dInputCommandPos;
double*                 CACSM::m_dActualPos;
double*					CACSM::m_dTagetPos;
double*                 CACSM::m_dCommandPos;
double*                 CACSM::m_dLeft_SoftLimit;
double*                 CACSM::m_dRight_SoftLimit;
double*                 CACSM::m_dMaxSpeed;
//vector<Group_Info>      CACSM::m_vGroupInfo;
int                     CACSM::m_nMasterAxis;
int                     CACSM::m_nSlaveAxis;
int                     CACSM::m_nInitHomeBufferIdx;
int                     CACSM::m_nInitHomeDone;
int                     CACSM::m_nInitParameters;
CString					CACSM::m_strErrMsg;
int                     CACSM::REAL_MOTOR_CNT;
//int                     CACSM::m_nIoModuleCnt;
MODULE_STATES           CACSM::m_InputModule;
MODULE_STATES           CACSM::m_OutputModule;
vector<IO_STATES>       CACSM::m_vInputStates;
vector<IO_STATES>       CACSM::m_vOutputStates;

int                     CACSM::m_nCalibX;
int                     CACSM::m_nCalibY;
CCriticalG*				CACSM::m_pACSSyncData;

CACSM::CACSM(CJettingVisionDlg* pDuasEotsDlg)
{
    //m_hComm = NULL;
	m_pDuasEotsDlg	= pDuasEotsDlg;
    m_pACSMotion    = NULL;
    m_nInitHomeDone = INIT_HOME_NOT;
    //m_vGroupInfo.clear();
    m_vInputStates.clear();
    m_vOutputStates.clear();
}
CACSM::~CACSM()
{
	//delete []m_pACSMotion;

// 	for (int i=0; i<2; i++)
// 	{
// 		delete[i] m_pACSMotion;
// 	}
	delete []m_dInputCommandPos;
	delete []m_dRefPos;
    delete []m_dActualPos;
	delete []m_dCommandPos;
	delete []m_dTagetPos;
    delete []m_dLeft_SoftLimit;
    delete []m_dRight_SoftLimit;
    delete []m_dMaxSpeed;	
	delete m_pACSSyncData;
    CloseComm();

}

void    CACSM::InitOnce(int nMotCnt)
{
    CString  strErrMsg;

//	ReadBaseConfig();
//	MotorsReadMap();
//	ReadBaseIOConfig();
//    ReadIOConfig();

    if(nMotCnt <= 0)
        return;

	REAL_MOTOR_CNT = 4;// nMotCnt;

	if (m_pACSMotion == NULL)
	{
		m_pACSMotion = new CACSMotion[nMotCnt];
	}

	m_dRefPos           	= new double[REAL_MOTOR_CNT];
	m_dActualPos        	= new double[REAL_MOTOR_CNT];
	m_dTagetPos        		= new double[REAL_MOTOR_CNT];
	m_dCommandPos       	= new double[m_nMotCnt];
	m_dInputCommandPos      = new double[m_nMotCnt];
	m_dLeft_SoftLimit   	= new double[REAL_MOTOR_CNT];
	m_dRight_SoftLimit  	= new double[REAL_MOTOR_CNT];
	m_dMaxSpeed         	= new double[REAL_MOTOR_CNT];
    ZeroMemory(m_dCommandPos, sizeof(double)*m_nMotCnt);  
	m_pACSSyncData = new CCriticalG();
}

BOOL CACSM::InitOpen(ACS_COMM_CONFIG comm_conf)
{
	BOOL	bRet;
	CString  strErrMsg;

	if (!OpenComm(comm_conf))
	{
		strErrMsg = Motion_GetLastErrorMessage();
		//frmLog->Add(LVLOG_ERROR, "Can Not Open Comm", strErrMsg);
		bRet = FALSE;
		return bRet;
	}
	//pDuasEotsDlg.
	ApplyMotionParameter();
	bRet = TRUE;
	return bRet;
}

BOOL CACSM::IsOpen()
{
	return m_bOpen;
}

BOOL    CACSM::ApplyMotionParameter(void)
{
	BOOL bRet;

	if( CACSM::m_pACSMotion == NULL)
		bRet =  FALSE;

    for(int i=0; i<CACSM::m_nMotCnt; i++)
    {
        CACSM::m_pACSMotion[i].Motion_GetFaultMask(NULL);
		CACSM::m_pACSMotion[i].SetVelocity(NULL);
        CACSM::m_pACSMotion[i].SetAccel(NULL);
        CACSM::m_pACSMotion[i].SetDecel(NULL);
        CACSM::m_pACSMotion[i].SetKillDecel(NULL);
        CACSM::m_pACSMotion[i].SetJerk(NULL);
        CACSM::SetRightSoftLimit(i, CACSM::m_pACSMotion[i].m_dMaxPos);
        CACSM::SetLeftSoftLimit(i, CACSM::m_pACSMotion[i].m_dMinPos);

    }
	CACSM::SetHomeOffset();
	//SetHomeOffset();
	// SetHomeOffsetVel();
	//GetAllHomeStatus();
	//GetAllSystemFault();

	bRet = TRUE;
	return bRet;
 
}

//---------------------------------------------------------------------------
BOOL    CACSM::OpenComm(ACS_COMM_CONFIG comm_conf)
{
    BOOL    bRet;
    bRet = OpenCommTCP(comm_conf);
     return bRet;
}
//---------------------------------------------------------------------------
void CACSM::OpenTest(char* ch, int nPont)
{
	CString strErrMsg;
	m_hComm= acsc_OpenCommEthernetTCP(ch, nPont);
	if (m_hComm == ACSC_INVALID)
	{
		//strErrMsg = Motion_GetLastErrorMessage();
	}
}
BOOL    CACSM::OpenCommTCP(ACS_COMM_CONFIG comm_conf)
{
	char*	pchIP;
	int		nPort;
	int		nSize;
	if (m_hComm != ACSC_INVALID) return FALSE;

	nSize = comm_conf.str_ip.GetLength()+1;
	pchIP = new char[nSize];
	/*pchIP = */TranseCStringToCharPointer(comm_conf.str_ip, pchIP);
	nPort = comm_conf.n_port;
    m_hComm = acsc_OpenCommEthernetTCP(pchIP, nPort);
	if (m_hComm == ACSC_INVALID)
	{
		//g_StateData.m_readyState = ReadyState::rs_NOTREADY;
		m_bOpen = FALSE;
		delete pchIP;
        return FALSE;
    }
	//컨트롤러 접속 상태를 설정 함...
	g_StateData.m_readyState = ReadyState::rs_READY;
	m_bOpen = TRUE;
	delete[] pchIP;
	pchIP = NULL;
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL    CACSM::CloseComm()
{
    if( m_hComm == ACSC_INVALID ) return FALSE;

    if(!acsc_CloseComm(m_hComm))
        return FALSE;

	g_StateData.m_readyState = ReadyState::rs_NOTREADY;
    m_hComm= ACSC_INVALID;
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL    CACSM::GetConnectionInfo(ACSC_CONNECTION_INFO* _connection_info)
{

    if(!acsc_GetConnectionInfo(m_hComm, _connection_info))
        return FALSE;

    return TRUE;
}
//---------------------------------------------------------------------------

BOOL    CACSM::GetPCICardsInfo(ACSC_PCI_SLOT* _cards, int _nCnt, int* _nDetectedCardsCnt)
{

    if(!acsc_GetPCICards(_cards, _nCnt, _nDetectedCardsCnt))
        return FALSE;

    return TRUE;
}
//---------------------------------------------------------------------------

BOOL    CACSM::TerminateConnection(ACSC_CONNECTION_DESC* _connection)
{

    if(!acsc_TerminateConnection(_connection))
        return FALSE;

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL    CACSM::Motions_Enable(int *_axis, ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
	if (!acsc_EnableM(m_hComm, _axis, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
    return bRet;
}
//---------------------------------------------------------------------------
BOOL    CACSM::Motions_Disable(int *_axis, ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_DisableM(m_hComm, _axis, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------
BOOL    CACSM::Motions_Disable_All(ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_DisableAll(m_hComm, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------
BOOL    CACSM::Motion_Group(int *_axis, ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_Group(m_hComm, _axis, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motion_Split(int *_axis, ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_Split(m_hComm, _axis, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motion_Split_all(ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_SplitAll(m_hComm, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motions_Go(int *_axis, ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_GoM(m_hComm, _axis, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motions_Stop(int *_axis, ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_HaltM(m_hComm, _axis, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motions_Kill(int *_axis, ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_KillM(m_hComm, _axis, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------
BOOL    CACSM::Motion_Kill_all(ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_KillAll(m_hComm, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motions_Break(int *_axis, ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_BreakM(m_hComm, _axis, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motions_ToPoint(int _flags, int *_axis, double *_point, ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_ToPointM(m_hComm, _flags, _axis, _point, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motions_ExtToPoint(int _flags, int *_axis, double *_point,
 double _velo, double _end_velo, ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_ExtToPointM(m_hComm, _flags, _axis, _point, _velo, _end_velo, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motions_Jog(int _flags, int* _axis, int* _direction, double _velo, ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_JogM(m_hComm, _flags, _axis, _direction, _velo, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motions_MultiPoint(int _flags, int* _axis, double _dwell, ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_MultiPointM(m_hComm, _flags, _axis, _dwell, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------
/*
Function Name           : Motions_Segment
Function Discription    : 보간 동작 시작하는 함수.
Parameter Discription   : npAxis : 사용할 축의 배열의 포인터(1개나 2개), dpInitPoint : 초기 위치배열의 포인터(x,y 배열), pWait : 동기 비동기 설정
MonthDay                : 2018년 1월 10일
Editor                  : 한성민
*/
//---------------------------------------------------------------------------
BOOL    CACSM::Motions_Segment(int nFlags, int* npAxis, double* dpInitPoint , ACSC_WAITBLOCK* pWait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_Segment(m_hComm, nFlags, npAxis, dpInitPoint, pWait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------
/*
Function Name           : Motions_EndSequence
Function Discription    : 보간 동작 끝내는 함수.
Parameter Discription   : npAxis : 사용할 축의 배열의 포인터(1개나 2개), pWait : 동기 비동기 설정
MonthDay                : 2018년 1월 10일
Editor                  : 한성민
*/
//---------------------------------------------------------------------------
BOOL    CACSM::Motions_EndSequence(int* npAxis, ACSC_WAITBLOCK* pWait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_EndSequenceM(m_hComm, npAxis, pWait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------
/*
Function Name           : Motions_Line
Function Discription    : Line 보간 동작하는 함수.
Parameter Discription   : npAxis : 사용할 축의 배열의 포인터(1개나 2개), dpPoint : 움직일 지점의 포인터, pWait : 동기 비동기 설정
MonthDay                : 2018년 1월 10일
Editor                  : 한성민
*/
//---------------------------------------------------------------------------
BOOL    CACSM::Motions_Line(int* npAxis, double* dpPoint , ACSC_WAITBLOCK* pWait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_Line(m_hComm, npAxis, dpPoint, pWait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------
/*
Function Name           : Motions_ExtLine
Function Discription    : Line 보간 동작하는 함수. (Line 함수와 다른 점은 속도값 추가)
Parameter Discription   : npAxis : 축번호의 포인터, dpPoint : 움직일 지점의 포인터, dVelocity : 속도, pWait : 동기 비동기 설정
MonthDay                : 2018년 1월 10일
Editor                  : 한성민
*/
//---------------------------------------------------------------------------
BOOL    CACSM::Motions_ExtLine(int* npAxis, double* dpPoint, double dVelocity, ACSC_WAITBLOCK* pWait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_ExtLine(m_hComm, npAxis, dpPoint, dVelocity, pWait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motions_Arc1(int* npAxis, double* dpCenter, double* dpFinalPoint, int nRotation, ACSC_WAITBLOCK* pWait)
{
	return TRUE;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motions_ExtArc1(int* npAxis, double* dpCenter, double* dpFinalPoint, int nRotation, double dVelocity, ACSC_WAITBLOCK* pWait)
{
	return TRUE;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motions_Stopper(int* _axis, ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_Stopper(m_hComm, _axis, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motions_Projection(int* _axis, char* _matrix, ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_Projection(m_hComm, _axis, _matrix, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motions_AddPoint(int* _axis, double* _point , ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_AddPointM(m_hComm, _axis, _point, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motions_ExtAddPoint(int* _axis, double* _point , double _rate,  ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_ExtAddPointM(m_hComm, _axis, _point, _rate, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------
/*
함수명				:Motions_ExtendedSegmentedMotion
설  명				:다 축 XSEG 모션을 시작 함(다축 동시 구동)

파라메터
nFlags				: 0 (기본 매개 변수를 사용하여 세그먼트 모션 생성)
pAxis				: 축번호(0과 1 사용)
pPoint				: 시작 위치
dVel				: ACSC_NONE(벡터 속도를 사용하지 않음)
dEndVel				: ACSC_NONE(END 속도를 사용하지 않음)
dJunctionVel		: ACSC_NONE(Junction 속도를 사용하지 않음)
dAngle				: ACSC_NONE(교차 각도를 사용하지 않음)
dStarvationMargin	: ACSC_NONE(starvation margin을 초기 값(500msec)으로 설정)
pSegments			: NULL(내부 버퍼 사이즈 사용)
pMasks				: NULL(Waiting call)
*/
//---------------------------------------------------------------------------

BOOL    CACSM::Motions_ExtendedSegmentedMotion(int nFlags, int* pAxis, double* pPoint, double dVel, double dEndVel, double dJunctionVel, double dAngle,
	double dStarvationMargin, char* pSegments, ACSC_WAITBLOCK* pWait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_ExtendedSegmentedMotion(m_hComm, nFlags, pAxis, pPoint, dVel, dEndVel, dJunctionVel, dAngle, dStarvationMargin, pSegments, pWait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------
/*
함수명:Motions_SegmentLine
설  명:Line 그리는 함수
파라메터
nFlags			: 0 (초기값 사용)
pAxis			: 축번호(0과 1 사용)
pPoint			: 끝 위치
dVelocity		: ACSC_NONE(벡터 속도를 사용하지 않음)
dEndVelocity	: ACSC_NONE(END 속도를 사용하지 않음)
pValues			: NULL(값 배열을 사용 하지 않음)
pVariables		: NULL(변수 배열을 사용 하지 않음)
nIndex			: ACSC_NONE(인수를 사용 하지 않음)
pMasks			: NULL(Masks 배열을 사용 하지 않음)
*/
//---------------------------------------------------------------------------
BOOL   	CACSM::Motions_SegmentLine(int nFlags, int* pAxis, double* pPoint, double dVelocity, double dEndVelocity, char* pValues, char* pVariables,
	int nIndex, char* pMasks, ACSC_WAITBLOCK* pWait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
	if (!acsc_SegmentLine(m_hComm, nFlags, pAxis, pPoint, dVelocity, dEndVelocity, pValues, pVariables, nIndex, pMasks, pWait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------
/*
함수명			: Motions_SegmentArc2
설  명			: Arc 그리는 함수
파라메터
nFlags			: ACSC_AMF_VELOCITY(벡터 속도를 사용하는 Flags)
pAxis			: 축번호(0과 1 사용)
pCenter			: 원의 중심 위치
dAngle			: 3.141529(Semicircle)
dVelocity		: 25000(벡터 속도)
dEndVelocity	: ACSC_NONE(END 속도를 사용하지 않음)
pValues			: NULL(값 배열을 사용 하지 않음)
pVariables		: NULL(변수 배열을 사용 하지 않음)
nIndex			: ACSC_NONE(인수를 사용하지 않음)
pMasks			: NULL(Masks 배열을 사용 하지 않음)
pWait			: NULL(Waiting call)
*/
//---------------------------------------------------------------------------
static BOOL		  	Motions_SegmentArc2(int nFlags, int* pAxis, double* pCenter, double dAngle, double dVelocity, double dEndVelocity, char* pValues, char* pVariables,
	int nIndex, char* pMasks, ACSC_WAITBLOCK* pWait)
{
//	if (!acsc_SegmentArc2(m_hComm, ACSC_AMF_VELOCITY, pAxis, pCenter, dAngle/*3.141529*/, dVelocity(25000), ACSC_NONE, NULL, NULL, ACSC_NONE, NULL, NULL))
		//return FALSE;

	return TRUE;
}
//---------------------------------------------------------------------------
BOOL    CACSM::Motion_GetProgramState(int _buffer, int* _state , ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_GetProgramState(m_hComm, _buffer, _state, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motion_GetInput(int _port, int _bit, int* _value , ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_GetInput(m_hComm, _port, _bit, _value, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motion_GetInputPort(int _port, int* _value , ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_GetInputPort(m_hComm, _port, _value, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motion_GetOutput(int _port, int _bit, int* _value , ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_GetOutput(m_hComm, _port, _bit, _value, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motion_GetOutputPort(int _port, int* _value , ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_GetOutputPort(m_hComm, _port, _value, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motion_SetOutput(int _port, int _bit, int _value , ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_SetOutput(m_hComm, _port, _bit, _value, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motion_SetOutputPort(int _port, int _value , ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_SetOutputPort(m_hComm, _port, _value, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motion_GetAnalogInput(int _port, int* _value , ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_GetAnalogInput(m_hComm, _port, _value, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motion_GetAnalogOutput(int _port, int* _value , ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_GetAnalogOutput(m_hComm, _port, _value, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motion_SetAnalogOutput(int _port, int _value , ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_SetAnalogOutput(m_hComm, _port, _value, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motion_GetExtInput(int _port, int _bit, int* _value , ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_GetExtInput(m_hComm, _port, _bit, _value, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motion_GetExtInputPort(int _port, int* _value , ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_GetExtInputPort(m_hComm, _port, _value, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motion_GetExtOutput(int _port, int _bit, int* _value , ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_GetExtOutput(m_hComm, _port, _bit, _value, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motion_GetExtOutputPort(int _port, int* _value , ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_GetExtOutputPort(m_hComm, _port, _value, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motion_SetExtOutput(int _port, int _bit, int _value , ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_SetExtOutput(m_hComm, _port, _bit, _value, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motion_SetExtOutputPort(int _port, int _value , ACSC_WAITBLOCK* _wait)
{
    //acsc_SetExtOutput(m_hComm, _port, 4, 1, _wait);
    //acsc_SetOutput(m_hComm, _port, 4, 1, _wait);
    //acsc_SetOutputPort(m_hComm, _port, 4, _wait);
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_SetExtOutputPort(m_hComm, _port, _value, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motions_FaultClear(int* _axis, ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_FaultClearM(m_hComm, _axis, _wait) && !acsc_FaultClearM(m_hComm, _axis+1, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motions_WaitForAsyncCall(void* _buf, int* _received, ACSC_WAITBLOCK* _wait, int _timeout)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_WaitForAsyncCall(m_hComm, _buf, _received, _wait, _timeout))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motion_WaitProgramEnd(int _buffer, int _timeout)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_WaitProgramEnd(m_hComm, _buffer, _timeout))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motion_WaitInput(int _port, int _bit, int _state, int _timeout)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_WaitInput(m_hComm, _port, _bit, _state, _timeout))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motion_WaitUserCondition(ACSC_USER_CONDITION_FUNC _user_condition, int _timeout)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_WaitUserCondition(m_hComm, _user_condition, _timeout))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motion_DeclareVariable(int _type, char* _name, ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_DeclareVariable(m_hComm, _type, _name, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motion_ClearVariables(ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_ClearVariables(m_hComm, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motion_GetProgramError(int _buffer, int* _error, ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_GetProgramError(m_hComm, _buffer, _error, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motion_GetEtherCATError(int* _error, ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_GetEtherCATError(m_hComm, _error, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motion_GetEtherCATState(int* _state, ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_GetEtherCATState(m_hComm, _state, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motion_MapEtherCATInput(int _flags, int _offset, char* _variable_name, ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_MapEtherCATInput(m_hComm, _flags, _offset, _variable_name, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motion_MapEtherCATOutput(int _flags, int _offset, char* _variable_name, ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_MapEtherCATOutput(m_hComm, _flags, _offset, _variable_name, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motion_UnmapEtherCATInputsOutputs(ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_UnmapEtherCATInputsOutputs(m_hComm, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------
BOOL    CACSM::Motion_RegisterEmergencyStop()
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_RegisterEmergencyStop())
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motion_UnregisterEmergencyStop()
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_UnregisterEmergencyStop())
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motion_AnalyzeApplication(char* _file_name, ACSC_APPSL_INFO** _info, ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_AnalyzeApplication(m_hComm, _file_name, _info, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motion_LoadApplication(char* _file_name, ACSC_APPSL_INFO* _info, ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_LoadApplication(m_hComm, _file_name, _info, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motion_SaveApplication(char* _file_name, ACSC_APPSL_INFO* _info, ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_SaveApplication(m_hComm, _file_name, _info, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motion_FreeApplication(ACSC_APPSL_INFO* _info)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_FreeApplication(_info))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motion_ControllerReboot(int _timeout)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_ControllerReboot(m_hComm, _timeout))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motion_GetErrorString(int _error_code, char* _error_str, int _count, int* _received)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
	if(!acsc_GetErrorString(m_hComm, _error_code, _error_str, _count, _received))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------
BOOL    CACSM::Motion_Transaction(char* _out_buf, int _out_cnt, char* _in_buf, int _in_cnt, int* _received, ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
	if(!acsc_Transaction(m_hComm, _out_buf, _out_cnt, _in_buf, _in_cnt, _received, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}

//---------------------------------------------------------------------------

int    CACSM::Motion_GetLastError()
{
	int nVel;
	//m_pACSSyncData->Lock();
	nVel =  acsc_GetLastError();
	//m_pACSSyncData->UnLock();
	return nVel;
}

CString	CACSM::Motion_GetLastErrorMessage()
{
	int 		errorCode,received;
	CString		strErrorMsg;
	CString		strErrorCode;

	char*		m_chBuf;

	m_chBuf = new char[MAX_PATH];
	//m_pACSSyncData->Lock();
	errorCode = Motion_GetLastError();
	//m_pACSSyncData->UnLock();
	if( errorCode == 0)
		return m_strErrMsg;

	//m_chBuf = NULL;

	strErrorMsg.Format(_T("?%d:"),errorCode);
	Motion_GetErrorString(errorCode, m_chBuf, 255, &received);
	
	strErrorMsg = TranseCharPointerToCString(m_chBuf);
    strErrorMsg = strErrorCode + strErrorMsg;

	//m_chBuf = NULL;
	delete[] m_chBuf;
	m_chBuf = NULL;

	return strErrorMsg;

}
//---------------------------------------------------------------------------
CString    CACSM::Motion_GetLastErrorMessage(int *nErrCode)
{
	int 		received;
	CString		strErrorMsg;
	char*		m_chBuf;

	m_chBuf = new char;

	*nErrCode = Motion_GetLastError();
	if( *nErrCode == 0)
		return m_strErrMsg;
	//m_pACSSyncData->Lock();
	Motion_GetErrorString(*nErrCode, m_chBuf, 255, &received);
	//m_pACSSyncData->UnLock();
	strErrorMsg = TranseCharPointerToCString(m_chBuf);//CA2CT(m_chBuf);

	m_chBuf = NULL;
	delete m_chBuf;

	return strErrorMsg;

}
//---------------------------------------------------------------------------


int    CACSM::Motion_GetTimeout()
{
	int nVel;
	//m_pACSSyncData->Lock();
	nVel= acsc_GetTimeout(m_hComm);
	//m_pACSSyncData->UnLock();
	return nVel;
}
//---------------------------------------------------------------------------

int    CACSM::Motion_GetDefaultTimeout()
{
	//m_pACSSyncData->Lock();
    return acsc_GetDefaultTimeout(m_hComm);
	//m_pACSSyncData->UnLock();
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motion_SetIterations(int _iterations)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_SetIterations(m_hComm, _iterations))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motion_SetCommOptions(unsigned int _options)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_SetCommOptions(m_hComm, _options))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motion_SetTimeout(int _timeout)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_SetTimeout(m_hComm, _timeout))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motion_SetQueueOverflowTimeout(int _delay)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_SetQueueOverflowTimeout(m_hComm, _delay))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

int    CACSM::Motion_GetQueueOverflowTimeout()
{
	int nVel;
	//m_pACSSyncData->Lock();
    nVel =  acsc_GetQueueOverflowTimeout(m_hComm);
	//m_pACSSyncData->UnLock();
	return nVel;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motion_GetCommOptions(unsigned int* _Options)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_GetCommOptions(m_hComm, _Options))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motion_ReadInteger(int _nbuf, char* _var, int _from1, int _to1, int _from2,
int _to2, int* _values, ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
	if(!acsc_ReadInteger(m_hComm, _nbuf, _var, _from1, _to1, _from2, _to2, _values, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motion_WriteInteger(int _nbuf, char* _var, int _from1, int _to1, int _from2,
int _to2, int* _values, ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    //if( (HANDLER_TYPE)g_pProfile->m_Motion_Type == mt_ACS_NT )
    //{
        if(!acsc_WriteInteger(m_hComm, _nbuf, _var, _from1, _to1, _from2, _to2, _values, _wait))
			bRet = FALSE;
		else
			bRet = TRUE;
		//m_pACSSyncData->UnLock();
		return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSM::Motion_ReadReal(int _nbuf, char* _var, int _from1, int _to1, int _from2,
int _to2, double* _values, ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();

    if(!acsc_ReadReal(m_hComm, _nbuf, _var, _from1, _to1, _from2, _to2, _values, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL CACSM::Motion_WriteReal(int _nbuf, char* _var, int _from1, int _to1, int _from2,
int _to2, double* _values, ACSC_WAITBLOCK* _wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_WriteReal(m_hComm, _nbuf, _var, _from1, _to1, _from2, _to2, _values, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------
BOOL    CACSM::ReadBaseIOConfig()
{
//	bool    bRet;
	CString  strPath;
    CString  strTemp;
    CString  strSection;
    int     nTotalCnt=0;
//    int     i,j,l;
//    int     nPoint;
//  	strPath     = ExtractFilePath(Application->ExeName) + "Config\\io.ini";
//  	if( FileExists(strPath) == false) {
// 		return FALSE;
// 	}
// 
// 	TIniFile*   pIni    = new TIniFile(strPath);
// 
//     m_InputModule.nModuleCnt  = pIni->ReadInteger("IO_MODULE", "INPUT_MODULE_CNT", 0);
//     m_InputModule.vInfo.resize(m_InputModule.nModuleCnt);
// 
//     m_OutputModule.nModuleCnt  = pIni->ReadInteger("IO_MODULE", "OUTPUT_MODULE_CNT", 0);
//     m_OutputModule.vInfo.resize(m_OutputModule.nModuleCnt);
// 
// 
//     //input관련
//     for(i=0,l=0; i<m_InputModule.nModuleCnt; i++)
//     {
//         int nCnt;
//         strSection.sprintf("INPUT_%d", i+1);
// 
//         if( (MOTION_TYPE)g_pProfile->m_Motion_Type == mt_ACS_NT )
//             nPoint = pIni->ReadInteger(strSection, "INPUT_POINT_CNT", 16);
//         else if( (MOTION_TYPE)g_pProfile->m_Motion_Type == mt_ACS_OLD )
//             nPoint = 8;
// 
//         nTotalCnt += nPoint;
//         m_InputModule.vInfo[i].nPoints = nPoint;
// 
//         nCnt = m_InputModule.vInfo[i].nPoints/nPoint;
//         m_InputModule.vInfo[i].vModuleNo.resize(nCnt);
//         for(j=0; j < nCnt; j++, l++)
//         {
//             m_InputModule.vInfo[i].vModuleNo[j] = l;
//         }
//     }
// 
//     m_InputModule.nTotalPoints = nTotalCnt;
// 
//     //Output 관련
//     nTotalCnt = 0;
//     for(i=0,l=0; i<m_OutputModule.nModuleCnt; i++)
//     {
//         int nCnt;
//         strSection.sprintf("OUTPUT_%d", i+1);
// 
//         if( (MOTION_TYPE)g_pProfile->m_Motion_Type == mt_ACS_NT )
//             nPoint = pIni->ReadInteger(strSection, "OUTPUT_POINT_CNT", 16);
//         else if( (MOTION_TYPE)g_pProfile->m_Motion_Type == mt_ACS_OLD )
//             nPoint = 8;
// 
//         nTotalCnt += nPoint;
//         m_OutputModule.vInfo[i].nPoints = nPoint;
// 
//         nCnt = m_OutputModule.vInfo[i].nPoints/nPoint;
//         m_OutputModule.vInfo[i].vModuleNo.resize(nCnt);
//         for(j=0; j < nCnt; j++, l++)
//         {
//             m_OutputModule.vInfo[i].vModuleNo[j] = l;
//         }
//     }
// 
//     m_OutputModule.nTotalPoints = nTotalCnt;
// 
// 	delete pIni;
// 	pIni    = NULL;

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL    CACSM::ReadIOConfig()
{
//	bool    bRet;
//    int     nIoCnt;
// 	String  strPath;
//     String  strTemp;
//     String  strSection;
//     String  strIdnt;
//     int     nPoint;
// 
// 	strPath     = ExtractFilePath(Application->ExeName) + "Config\\ACS_IO.ini";
// 	if( FileExists(strPath) == false) {
// 		return FALSE;
// 	}
// 
// 	TIniFile*   pIni    = new TIniFile(strPath);
// 
//     if( (MOTION_TYPE)g_pProfile->m_Motion_Type == mt_ACS_NT )
//         nPoint = 16;
//     else if( (MOTION_TYPE)g_pProfile->m_Motion_Type == mt_ACS_OLD )
//         nPoint = 8;
// 
//     nIoCnt = m_InputModule.nTotalPoints / nPoint;
// 
//     m_vInputStates.resize(nIoCnt);
// 
//     for(int i=0, l=0; i<m_InputModule.nModuleCnt; i++)
//     {
//         strSection.sprintf("INPUT_%d", i+1);
//         int     nRoofCnt = m_InputModule.vInfo[i].nPoints/nPoint;
// 
//         for(int j=0, n=0; j< nRoofCnt; j++, l++)
//         {
//             for(int k=0; k < nPoint; k++, n++)
//             {
//                 strIdnt.sprintf("%d_%d",i+1, n+1);
//                 m_vInputStates[l].Names[k] = pIni->ReadString(strSection, strIdnt,"NOT USE");
// //                m_vInOutStates[l].NamesOutput[]
//             }
//         }
//     }
// 
//     //Output관련
// 
//     nIoCnt = m_OutputModule.nTotalPoints / nPoint;
// 
//     m_vOutputStates.resize(nIoCnt);
// 
//     for(i=0, l=0; i<m_OutputModule.nModuleCnt; i++)
//     {
//         strSection.sprintf("OUTPUT_%d", i+1);
//         int     nRoofCnt = m_OutputModule.vInfo[i].nPoints/nPoint;
// 
//         for(int j=0, n=0; j< nRoofCnt; j++, l++)
//         {
//             for(int k=0; k < nPoint; k++, n++)
//             {
//                 strIdnt.sprintf("%d_%d",i+1, n+1);
//                 m_vOutputStates[l].Names[k] = pIni->ReadString(strSection, strIdnt,"NOT USE");
// //                m_vInOutStates[l].NamesOutput[]
//             }
//         }
//     }
// 
// 
// 
// 	delete pIni;
// 	pIni    = NULL;

    return TRUE;

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
BOOL    CACSM::RunHome(int nBufferIdx, char* chLabel, ACSC_WAITBLOCK* Wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_RunBuffer(m_hComm, nBufferIdx, chLabel, Wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------
BOOL    CACSM::StopHome(int nBufferIdx, ACSC_WAITBLOCK* Wait)
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!acsc_StopBuffer(m_hComm, nBufferIdx, Wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------
void CACSM::MotorsApplayPara()
{
    if(m_pACSMotion == NULL)
        return;

    for(int i=0; i < m_nMotCnt; i++)
    {

     //ACSC_SAFETY_RL;
    }

}
//---------------------------------------------------------------------------
double     CACSM::GetCommandPos(int nMotidx)
{
	return m_dCommandPos[nMotidx];
}
double     CACSM::GetRefPos(int nMotidx)
{
	return m_dRefPos[m_pACSMotion[nMotidx].m_nAxis];
}
//---------------------------------------------------------------------------
double     CACSM::GetActualPos(int nMotidx)
{
	int nAxis;
	nAxis = m_pACSMotion[nMotidx].m_nAxis;
	double dVel;
	dVel = m_dActualPos[nAxis];
	return dVel;
}
//---------------------------------------------------------------------------
double     CACSM::GetTargetPos(int nMotidx)
{
	/*m_pSyncData->Lock();*/
	  return m_dTagetPos[m_pACSMotion[nMotidx].m_nAxis];
}
//---------------------------------------------------------------------------
void    CACSM::SetCommandPos(int nMotidx, double dCommandPos)
{

	m_dCommandPos[nMotidx] = dCommandPos;
}

//---------------------------------------------------------------------------
BOOL    CACSM::GetReferencePos()
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
    if(!Motion_ReadReal(ACSC_NONE, "RPOS", 0, REAL_MOTOR_CNT-1, ACSC_NONE, ACSC_NONE, m_dRefPos, NULL))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------
BOOL    CACSM::GetActualPos()
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
	if(!Motion_ReadReal(ACSC_NONE, /*"FPOS"*/"APOS", 0, REAL_MOTOR_CNT-1, ACSC_NONE, ACSC_NONE, m_dActualPos, NULL))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;

}
//---------------------------------------------------------------------------
BOOL    CACSM::GetTargetPos()
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
	if (!Motion_ReadReal(ACSC_NONE, "TPOS", 0, REAL_MOTOR_CNT-1, ACSC_NONE, ACSC_NONE, m_dTagetPos, NULL))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------
BOOL    CACSM::GetLeftSoftLimit()
{
	BOOL bRet;
	//m_pACSSyncData->Lock();
	if (!Motion_ReadReal(ACSC_NONE, "SLLIMIT", 0, REAL_MOTOR_CNT-1, ACSC_NONE, ACSC_NONE, m_dLeft_SoftLimit, NULL))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pACSSyncData->UnLock();
	return bRet;

}
//---------------------------------------------------------------------------

BOOL    CACSM::SetLeftSoftLimit(int nMotSelect, double dLeftSoftLimitPos)
{
    int nAxis;
    nAxis = m_pACSMotion[nMotSelect].m_nAxis;
    return Motion_WriteReal(ACSC_NONE, "SLLIMIT", nAxis, nAxis, ACSC_NONE, ACSC_NONE, &dLeftSoftLimitPos, NULL);

}
//---------------------------------------------------------------------------

BOOL    CACSM::GetRightSoftLimit()
{
    return Motion_ReadReal(ACSC_NONE, "SRLIMIT", 0, REAL_MOTOR_CNT-1, ACSC_NONE, ACSC_NONE, m_dRight_SoftLimit, NULL);

}
//---------------------------------------------------------------------------

BOOL    CACSM::SetRightSoftLimit(int nMotSelect, double dRightSoftLimitPos)
{
    int nAxis;
    nAxis = m_pACSMotion[nMotSelect].m_nAxis;
    return Motion_WriteReal(ACSC_NONE, "SRLIMIT", nAxis, nAxis, ACSC_NONE, ACSC_NONE, &dRightSoftLimitPos, NULL);
}
//---------------------------------------------------------------------------
BOOL    CACSM::GetMaxSpeed()
{
    return Motion_ReadReal(ACSC_NONE, "XVEL", 0, REAL_MOTOR_CNT-1, ACSC_NONE, ACSC_NONE, m_dMaxSpeed, NULL);

}
//---------------------------------------------------------------------------

void    CACSM::SetMaxSpeed(int nMotSelect, double dMaxSpeed)
{
    Motion_WriteReal(ACSC_NONE, "XVEL", nMotSelect, nMotSelect, ACSC_NONE, ACSC_NONE, &dMaxSpeed, NULL);

}
//---------------------------------------------------------------------------
//Sin 동작에 주파수 변수 셋팅 함수
void    CACSM::SetFreq(int nMotSelect, double dFreq)
{
	Motion_WriteReal(ACSC_NONE, "Frequency", ACSC_NONE, ACSC_NONE, ACSC_NONE, ACSC_NONE, &dFreq, NULL);

}
//---------------------------------------------------------------------------
//Sin 동작 변수 진폭 셋팅 함수
void	CACSM::SetPeriod(int nMotSelect, double dPeriod)
{
	Motion_WriteReal(ACSC_NONE, "Degree", ACSC_NONE, ACSC_NONE, ACSC_NONE, ACSC_NONE, &dPeriod, NULL);
}
//---------------------------------------------------------------------------
//Sin 동작 변수 주파수 변경 셋팅 함수
void	CACSM::SetFreqChange(int nMotSelect, double dChangeFreq)
{
	Motion_WriteReal(ACSC_NONE, "FREQ_CHANGE", ACSC_NONE, ACSC_NONE, ACSC_NONE, ACSC_NONE, &dChangeFreq, NULL);
}
//---------------------------------------------------------------------------
//Sin 동작 변수 시간 셋팅 함수
void	CACSM::SetRunTime(int nMotSelect, int nRunTime)
{
	Motion_WriteInteger(ACSC_NONE, "Run_time", ACSC_NONE, ACSC_NONE, ACSC_NONE, ACSC_NONE, &nRunTime, NULL);
}
//---------------------------------------------------------------------------
//축 설정
void CACSM::SetSinWaveAxis(int nMotSelect, int nAxis)
{
	Motion_WriteInteger(ACSC_NONE, "Axis", ACSC_NONE, ACSC_NONE, ACSC_NONE, ACSC_NONE, &nAxis, NULL);
}
//---------------------------------------------------------------------------
//버퍼프로그램 완료 체크 관련
BOOL CACSM::GetCompletSinMove()
{
	BOOL bRet;
	int	nValue;
	Motion_ReadInteger(ACSC_NONE, "PROC_END", ACSC_NONE, ACSC_NONE, ACSC_NONE, ACSC_NONE, &nValue, NULL);
	if (nValue == 0)
		bRet = FALSE;
	else
		bRet = TRUE;

	return bRet;
}
BOOL    CACSM::RunSinMove(int nBufferIdx, char* chLabel, ACSC_WAITBLOCK* Wait)
{
	if (!acsc_RunBuffer(m_hComm, nBufferIdx, chLabel, Wait))
		return FALSE;
	return TRUE;
}
//---------------------------------------------------------------------------
void    CACSM::StopSinMove(int nMotSelect)
{
	double dStopValue;
	dStopValue = 1;
	Motion_WriteReal(ACSC_NONE, "VIR_STOP", ACSC_NONE, ACSC_NONE, ACSC_NONE, ACSC_NONE, &dStopValue, NULL);
// 	if (!acsc_StopBuffer(m_hComm, nBufferIdx, Wait))
// 		return FALSE;
// 	return TRUE;
}
//---------------------------------------------------------------------------


void	CACSM::SetGroupMaster(int nAxis)
{
  
}
CString		CACSM::GetNameOfAxis(int nAxis)
{
    for(int i=0; i<CACSM::m_nMotCnt; i++)
    {
        if( CACSM::m_pACSMotion[i].m_nAxis == nAxis )
            return CACSM::m_pACSMotion[i].m_strMotorName;
    }
    return _T("");
}
//---------------------------------------------------------------------------
void        CACSM::SetGroupSlave(int nMasterAxis, int nSlaveAxis)
{
 
}
//---------------------------------------------------------------------------
void        CACSM::ReSetGroupMaster(int nAxis)
{

}
//---------------------------------------------------------------------------
void        CACSM::ReSetGroupSlave(int nMasterAxis, int nSlaveAxis)
{
 
}

//---------------------------------------------------------------------------

BOOL        CACSM::SetSyncGroup(int nMasterAxis, int nSlaveAxis)
{
// 	CString cmd;
// 
//     cmd.Format(_T("MFLAGS(%d).17=0;CONNECT RPOS(%d)=APOS(%d);DEPENDS %d,%d", nSlaveAxis, nSlaveAxis, nMasterAxis, nSlaveAxis, nMasterAxis));
// 
// 	if(!acsc_Command(m_hComm, cmd, cmd.GetLength(), NULL))
//         return FALSE;
// 
//     cmd.sprintf("SAFETYGROUP (%d,%d)", nMasterAxis, nSlaveAxis);
//     if(!acsc_Command(m_hComm, cmd.c_str(), cmd.Length(), NULL))
//             return FALSE;    

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL        CACSM::ReSetSyncGroup(int nSlaveAxis)
{
//     String cmd;
// 
//     cmd.sprintf("MFLAGS(%d).17=1;", nSlaveAxis);
// 
// 	if(!acsc_Command(m_hComm, cmd.c_str(), cmd.Length(), NULL))
//         return FALSE;
// 
//     cmd.sprintf("SAFETYGROUP %d", nSlaveAxis);
//     if(!acsc_Command(m_hComm, cmd.c_str(), cmd.Length(), NULL))
//         return FALSE;

    return TRUE;
}
BOOL     CACSM::AddDefaultAxisForGroup()
{
//     UnGroup();
// 
//     for(int i=0; i < (int)m_vGroupInfo.size(); i++)
//         m_vGroupInfo[i].vSlaveInfo.clear();
//     m_vGroupInfo.clear();
// 
//     SetGroupMaster(m_pACSMotion[KRF_POM_X].m_nAxis);
//     SetGroupSlave(m_pACSMotion[KRF_POM_X].m_nAxis, m_pACSMotion[KRF_STAGE_X].m_nAxis);
//     SetGroupMaster(m_pACSMotion[KRF_POM_Y].m_nAxis);
//     SetGroupSlave(m_pACSMotion[KRF_POM_Y].m_nAxis, m_pACSMotion[KRF_STAGE_Y].m_nAxis);
	return TRUE;
}
//---------------------------------------------------------------------------
BOOL     CACSM::Group()
{
//     String      strErrMsg;
// //    bool        bTest;
// 
// //    m_vGroupInfo.empty()
// 
//     for(int i=0; i < (int)m_vGroupInfo.size(); i++)
//     {
//         for(int j=0; j < (int)m_vGroupInfo[i].vSlaveInfo.size(); j++)
//         {
// //            bTest = m_vGroupInfo[i].vSlaveInfo[j].bGroup;
//             if(!m_vGroupInfo[i].vSlaveInfo[j].bGroup)
//             {
//                 if(!SetSyncGroup(m_vGroupInfo[i].nMasterAxis, m_vGroupInfo[i].vSlaveInfo[j].nSlaveAxis))
//                 {
//                     strErrMsg.sprintf("Can`t Grouping");
//                     return FALSE;
//                 }
//                 else
//                     m_vGroupInfo[i].vSlaveInfo[j].bGroup = true;
//             }
//         }
//     }
    return TRUE;
}
BOOL     CACSM::UnGroup()
{
//     String      strErrMsg;
// 
//     for(int i=0; i < (int)m_vGroupInfo.size(); i++)
//     {
//         for(int j=0; j < (int)m_vGroupInfo[i].vSlaveInfo.size(); j++)
//         {
//             if(m_vGroupInfo[i].vSlaveInfo[j].bGroup)
//             {
//                 if(!ReSetSyncGroup(m_vGroupInfo[i].vSlaveInfo[j].nSlaveAxis))
//                 {
//                     strErrMsg.sprintf("Can`t UnGrouping");
//                     return FALSE;
//                 }
//                 else
//                     m_vGroupInfo[i].vSlaveInfo[j].bGroup = false;
//             }
//         }
//     }
    return TRUE;
}
//---------------------------------------------------------------------------
int    CACSM::GetInitHomeStatus(void)
{
	GetInitHomeFlag();

	return m_nInitHomeDone;
}
//---------------------------------------------------------------------------
void     CACSM::GetInitHomeFlag()
{
    int nInitHomeFlag;

    if(!Motion_ReadInteger(ACSC_NONE, "Init_HomeDone", 0, 0, ACSC_NONE, ACSC_NONE, &nInitHomeFlag, NULL))
    {
        m_nInitHomeDone = INIT_HOME_FUNC_ERROR;
        return;
    }
    switch(nInitHomeFlag)
    {
    case INIT_HOME_NOT:
        m_nInitHomeDone = INIT_HOME_NOT;
        break;
    case INIT_HOME_OK:
        m_nInitHomeDone = INIT_HOME_OK;
        break;
    case INIT_HOME_ING:
        m_nInitHomeDone = INIT_HOME_ING;
        break;
    case INIT_HOME_ERR:
        m_nInitHomeDone = INIT_HOME_ERR;
        break;
    }

    return;

}
//---------------------------------------------------------------------------
void     CACSM::SetInitHomeFlag(int nFlag)
{

    if(!Motion_WriteInteger(ACSC_NONE, "Init_Home_Done", 8, 8, ACSC_NONE, ACSC_NONE, &nFlag, NULL))
    {
        m_nInitHomeDone = INIT_HOME_FUNC_ERROR;
        return;
    }

    return;

}
//---------------------------------------------------------------------------

int     CACSM::ReadInput()
{
    int                 nErrorCode;
    USHORT_DATA_32      nInputValue;
    int                 nPoint;

    //if((MOTION_TYPE)g_pProfile->m_Motion_Type == mt_ACS_NT)
	nPoint = 4;/*16*/;
    //else if((MOTION_TYPE)g_pProfile->m_Motion_Type == mt_ACS_OLD)
     //   nPoint = 8;





	for(int i=0, l=0; i < m_InputModule.nModuleCnt; i++)
	{

		int nCnt = m_InputModule.vInfo[i].nPoints/nPoint;

//        Motion_GetExtInputPort(i, &nInputValue.data, NULL);
		if(!Motion_ReadInteger(ACSC_NONE, /*"E_DIN"*/"IN", 0, i, ACSC_NONE, ACSC_NONE, &nInputValue.data, NULL))
		{
			nErrorCode = Motion_GetLastError();
			return nErrorCode;
		}
		for(int j=0; j < nCnt; j++, l++)
		{
			if(j==0)
				m_vInputStates[l].IO.data = (unsigned short)nInputValue.words.low;
			else
				m_vInputStates[l].IO.data = (unsigned short)nInputValue.words.high;
		}

    }
    return 1;

}
//---------------------------------------------------------------------------

BOOL    CACSM::ReadInputBit(int nIdx, int nBitNo)
{
    if(nIdx >= (int)m_vInputStates.size())
        return FALSE;

    if(ReadInput()!=1)
        return FALSE;

    if(nBitNo == 0)
        return m_vInputStates[nIdx].IO.bits.b_0;
    else if(nBitNo == 1)
        return m_vInputStates[nIdx].IO.bits.b_1;
    else if(nBitNo == 2)
        return m_vInputStates[nIdx].IO.bits.b_2;
    else if(nBitNo == 3)
        return m_vInputStates[nIdx].IO.bits.b_3;
    else if(nBitNo == 4)
        return m_vInputStates[nIdx].IO.bits.b_4;
    else if(nBitNo == 5)
        return m_vInputStates[nIdx].IO.bits.b_5;
    else if(nBitNo == 6)
        return m_vInputStates[nIdx].IO.bits.b_6;
	else if(nBitNo == 7)
        return m_vInputStates[nIdx].IO.bits.b_7;
    else if(nBitNo == 8)
        return m_vInputStates[nIdx].IO.bits.b_8;
    else if(nBitNo == 9)
        return m_vInputStates[nIdx].IO.bits.b_9;
    else if(nBitNo == 10)
        return m_vInputStates[nIdx].IO.bits.b_10;
    else if(nBitNo == 11)
        return m_vInputStates[nIdx].IO.bits.b_11;
    else if(nBitNo == 12)
        return m_vInputStates[nIdx].IO.bits.b_12;
    else if(nBitNo == 13)
        return m_vInputStates[nIdx].IO.bits.b_13;
    else if(nBitNo == 14)
        return m_vInputStates[nIdx].IO.bits.b_14;
    else if(nBitNo == 15)
        return m_vInputStates[nIdx].IO.bits.b_15;
    else
        return FALSE;
}
//---------------------------------------------------------------------------

BOOL    CACSM::ReadInputBit(int nBitNo)
{
	int idx,bitNo;
    int nPoint;

 //   if((MOTION_TYPE)g_pProfile->m_Motion_Type == mt_ACS_NT)
        nPoint = 4;
 //   else if((MOTION_TYPE)g_pProfile->m_Motion_Type == mt_ACS_OLD)
 //       nPoint = 8;


    idx = nBitNo/nPoint;
    bitNo = nBitNo%nPoint;


	return ReadInputBit(idx, bitNo);
}
//---------------------------------------------------------------------------
void    CACSM::SetOutput(int nModuleNo, int nIdx, unsigned short nValue)
{
    USHORT_DATA_32  nOutput;
    int nCnt;
    nCnt = m_OutputModule.vInfo[nModuleNo].vModuleNo.size();
    m_vOutputStates[nIdx].IO.data = nValue;

    for(int i=0; i < nCnt; i++)
    {
        if(i==0)
            nOutput.words.low = m_vOutputStates[m_OutputModule.vInfo[nModuleNo].vModuleNo[i]].IO.data;
        else
			nOutput.words.high = m_vOutputStates[m_OutputModule.vInfo[nModuleNo].vModuleNo[i]].IO.data;
	}

    if(!Motion_WriteInteger(ACSC_NONE, "E_DOUT", 0, nIdx, ACSC_NONE, ACSC_NONE, &nOutput.data, NULL))
    {
            return;
    }


}
//---------------------------------------------------------------------------

BOOL    CACSM::SetBit(int nIdx, int nBitNo, BOOL bOn)
{
 	BOOL                bFind=FALSE;
	int                 cnt,idx;
	USHORT_DATA_32      nOutput;
	if(nIdx >= (int)m_vOutputStates.size()) {
		m_strErrMsg.Format(_T("<<< SetBit >>> Module index Error"));
		return FALSE;
	}

	if(nBitNo >= 16) {
		m_strErrMsg.Format(_T("<<< SetBit >>> Module Bit Arrange Error"));
		return FALSE;
	}
	for(int i=0; i<(int)m_OutputModule.vInfo.size(); i++)
	{
		cnt = m_OutputModule.vInfo[i].vModuleNo.size();
		for( int j=0; j<cnt; j++)
		{
			if( m_OutputModule.vInfo[i].vModuleNo[j] == nIdx )
			{
				bFind   = TRUE;
				idx     = i;
				break;
			}
		}
	}
	if( !bFind )
	{
		m_strErrMsg.Format(_T("<<< SetBit >>> Module No Not Fonded"));
		CACSM::m_strErrMsg = m_strErrMsg;
		return FALSE;
	}

	unsigned short word = m_vOutputStates[nIdx].IO.data;
	unsigned short setbit = 0x0001 << nBitNo;

	if( bOn )
		word  =  word | setbit ;
	else
		word  =  word & ~setbit ;

	m_vOutputStates[nIdx].IO.data = word;


	for( int k=0; k<cnt; k++)
	{
		if( k == 0 )
			nOutput.words.low   = m_vOutputStates[m_OutputModule.vInfo[idx].vModuleNo[k]].IO.data;
		else
			nOutput.words.high   = m_vOutputStates[m_OutputModule.vInfo[idx].vModuleNo[k]].IO.data;
	}


	return Motion_WriteInteger(ACSC_NONE, "E_DOUT", 0, nIdx, ACSC_NONE, ACSC_NONE, &nOutput.data, NULL);//Motion_SetOutputPort(nIdx, nOutput.data, NULL);

}
//---------------------------------------------------------------------------
void    CACSM::SetBit(int nBitNo, BOOL bOn)
{
	int idx,bitNo;
    int nPoint;

    //if((MOTION_TYPE)g_pProfile->m_Motion_Type == mt_ACS_NT)
        nPoint = 16;
    //else if((MOTION_TYPE)g_pProfile->m_Motion_Type == mt_ACS_OLD)
    //    nPoint = 8;

	idx = nBitNo/nPoint;
	bitNo = nBitNo%nPoint;

	SetBit(idx,bitNo,bOn);

}


//---------------------------------------------------------------------------

void    CACSM::GetOutput()
{

    USHORT_DATA_32     nOutputValue;
    int nPoint;

    //if((MOTION_TYPE)g_pProfile->m_Motion_Type == mt_ACS_NT)
        nPoint = 16;
    //else if((MOTION_TYPE)g_pProfile->m_Motion_Type == mt_ACS_OLD)
     //   nPoint = 8;


    for(int i=0,l=0; i < m_OutputModule.nModuleCnt; i++)
    {
        int nCnt = m_OutputModule.vInfo[i].nPoints/nPoint;
        //수정Read_int
//        if(!Motion_GetOutputPort(i, &nOutputValue.data, NULL))
//            return;
        if(!Motion_ReadInteger(ACSC_NONE, "E_DOUT", 0, i, ACSC_NONE, ACSC_NONE, &nOutputValue.data, NULL))
            return;
        else
        {
            for(int j=0; j < nCnt; j++, l++)
            {
                if(j==0)
                    m_vOutputStates[l].IO.data = (unsigned short)nOutputValue.words.low;
                else
                    m_vOutputStates[l].IO.data = (unsigned short)nOutputValue.words.high;
            }
        }
    }




}
//---------------------------------------------------------------------------
BOOL    CACSM::ReadOutputBit(int nIdx, int nBitNo)
{
	if(nIdx >= (int)m_vOutputStates.size())
		return FALSE;

	GetOutput();

	if(nBitNo == 0)
		return m_vOutputStates[nIdx].IO.bits.b_0;
	else if(nBitNo == 1)
		return m_vOutputStates[nIdx].IO.bits.b_1;
	else if(nBitNo == 2)
		return m_vOutputStates[nIdx].IO.bits.b_2;
	else if(nBitNo == 3)
		return m_vOutputStates[nIdx].IO.bits.b_3;
	else if(nBitNo == 4)
		return m_vOutputStates[nIdx].IO.bits.b_4;
	else if(nBitNo == 5)
		return m_vOutputStates[nIdx].IO.bits.b_5;
	else if(nBitNo == 6)
		return m_vOutputStates[nIdx].IO.bits.b_6;
	else if(nBitNo == 7)
		return m_vOutputStates[nIdx].IO.bits.b_7;
	else if(nBitNo == 8)
		return m_vOutputStates[nIdx].IO.bits.b_8;
	else if(nBitNo == 9)
		return m_vOutputStates[nIdx].IO.bits.b_9;
	else if(nBitNo == 10)
		return m_vOutputStates[nIdx].IO.bits.b_10;
	else if(nBitNo == 11)
		return m_vOutputStates[nIdx].IO.bits.b_11;
	else if(nBitNo == 12)
		return m_vOutputStates[nIdx].IO.bits.b_12;
	else if(nBitNo == 13)
		return m_vOutputStates[nIdx].IO.bits.b_13;
	else if(nBitNo == 14)
		return m_vOutputStates[nIdx].IO.bits.b_14;
	else if(nBitNo == 15)
		return m_vOutputStates[nIdx].IO.bits.b_15;
	else
		return FALSE;
}
//---------------------------------------------------------------------------
BOOL    CACSM::ReadOutputBit(int nBitNo)
{
	int idx,bitNo;
    int nPoint;

 //   if((MOTION_TYPE)g_pProfile->m_Motion_Type == mt_ACS_NT)
        nPoint = 16;
 //   else if((MOTION_TYPE)g_pProfile->m_Motion_Type == mt_ACS_OLD)
  //      nPoint = 8;


    idx = nBitNo/nPoint;
    bitNo = nBitNo%nPoint;



	return ReadOutputBit(idx, bitNo);
}
//---------------------------------------------------------------------------
// Motion_WriteReal(ACSC_NONE, "SLLIMIT", nAxis, nAxis, ACSC_NONE, ACSC_NONE, &dLeftSoftLimitPos, NULL);

/*
char*	pchIP;
int		nPort;
int		nSize;
if (m_hComm != ACSC_INVALID) return FALSE;

nSize = comm_conf.str_ip.GetLength()+1;
pchIP = new char[nSize];
TranseCStringToCharPointer(comm_conf.str_ip, pchIP);
nPort = comm_conf.n_port;
m_hComm = acsc_OpenCommEthernetTCP(pchIP, nPort);
if (m_hComm == ACSC_INVALID)
{
	//g_StateData.m_readyState = ReadyState::rs_NOTREADY;
	m_bOpen = FALSE;
	delete pchIP;
	return FALSE;
}
//컨트롤러 접속 상태를 설정 함...
g_StateData.m_readyState = ReadyState::rs_READY;
m_bOpen = TRUE;
delete pchIP;
return TRUE;
*/

BOOL    CACSM::SetHomeOffset()
{
	int			nSize;
	char*		pchHomeOffsetVelName;
    CString		strHomeOffsetName;
    double		dHomeOffsetValue;

    for(int i=0, j=0; i<m_nMotCnt; i++)
    {
        strHomeOffsetName = m_pACSMotion[i].m_strHomeOffsetVarName;
		nSize = strHomeOffsetName.GetLength() + 1;
		pchHomeOffsetVelName = new char[nSize];
		TranseCStringToCharPointer(strHomeOffsetName, pchHomeOffsetVelName);
		//pchHomeOffsetVelName = CT2CA(strHomeOffsetName);
        dHomeOffsetValue  = m_pACSMotion[i].m_dHomeOffset;
        if(!Motion_WriteReal(ACSC_NONE, pchHomeOffsetVelName/*LPSTR(LPCTSTR(strHomeOffsetName))*/, j, j, ACSC_NONE, ACSC_NONE, &dHomeOffsetValue, NULL))
            return FALSE;
		delete[] pchHomeOffsetVelName;
		pchHomeOffsetVelName = NULL;
		j = j + 2;
    }
    return TRUE;
}

void    CACSM::GetAllHomeStatus()
{
    GetInitHomeStatus();

    for(int i=0; i< m_nMotCnt; i++)
    {
        m_pACSMotion[i].GetHomeFlag();
    }
}

void    CACSM::GetAllSystemFault()
{
    for(int i=0; i<m_nMotCnt; i++)
    {
        m_pACSMotion[i].GetSystemFault();
		m_pACSMotion[i].GetEncoderSystemFault();
    }
}

void CACSM::GetAllMotorStatus()
{
	for (int i = 0; i < m_nMotCnt; i++)
	{
		m_pACSMotion[i].Motion_GetMotorState(NULL);
	}
}

//---------------------------------------------------------------------------
BOOL    CACSM::SetHomeOffsetVel()
{
	int			nSize;
	char * pchHomeOffsetVelName;
    CString  strHomeOffsetVelName;
    double  dHomeOffsetVelValue;
    for(int i=0, j=0; i<m_nMotCnt; i++)
    {

		strHomeOffsetVelName = m_pACSMotion[i].m_strHomeOffsetVelVarName;
		nSize = strHomeOffsetVelName.GetLength() + 1;
		pchHomeOffsetVelName = new char[nSize];
		TranseCStringToCharPointer(strHomeOffsetVelName, pchHomeOffsetVelName); 
        dHomeOffsetVelValue  = m_pACSMotion[i].m_dHomeOffsetVel;
        if(!Motion_WriteReal(ACSC_NONE, pchHomeOffsetVelName, 0, 0, ACSC_NONE, ACSC_NONE, &dHomeOffsetVelValue, NULL))
            return FALSE;

		delete[] pchHomeOffsetVelName;
		pchHomeOffsetVelName = NULL;
		j = j + 2;
    }
    return TRUE;
}
//---------------------------------------------------------------------------

 CACSMotion::CACSMotion()
 :CACSM(/*pDuasEotsDlg*/CACSM::m_pDuasEotsDlg)
{
//    m_hComm = m_hComm;
 //   long  temp;
    m_nFault			= 0;
	m_nEncAxisFault		= 0;
    m_nSystemError      = 0;
    m_nMotorErrNum      = 0;
    m_strMotorErrMsg    = "";
    m_nHomeDone         = MOTION_HOME_NOT;
    m_bRepeatEnable     = false;
    m_nRepeatAct        = 0;
	//m_pSyncData		=	new CCriticalG();
//    MmodAlloc(0,0,0,&temp);

}
//---------------------------------------------------------------------------
   CACSMotion::~CACSMotion()
{
// 	   if (!m_pSyncData)
// 	   {
// 		   delete m_pSyncData;
// 		   m_pSyncData = NULL;
// 	   }
	       //CloseComm();
	   int a;
	   a = 0;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::SetVelocity(/*int _axis,*/ ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_SetVelocity(m_hComm, m_nAxis/*_axis*/, m_dVelocity, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL	CACSMotion::SetVelocityManual(/*int _axis,*/ ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
	if (!acsc_SetVelocity(m_hComm, m_nAxis/*_axis*/, m_manualVelocity, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}

BOOL	CACSMotion::SetVelocityMoving(/*int _axis,*/ ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
	if (!acsc_SetVelocity(m_hComm, m_nAxis/*_axis*/, m_movingVelocity, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}

BOOL	CACSMotion::SetVelocityJetting(/*int _axis,*/ ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
	if (!acsc_SetVelocity(m_hComm, m_nAxis/*_axis*/, m_jettingVelocity, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}

BOOL    CACSMotion::GetVelocity(/*int _axis,*/ double *_velocity, ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_GetVelocity(m_hComm, m_nAxis/*_axis*/, _velocity, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------
BOOL    CACSMotion::SetAccel( ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_SetAcceleration(m_hComm, m_nAxis/*_axis*/, m_dAccel, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::GetAccel(/*int _axis,*/ double *_accel, ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_GetAcceleration(m_hComm, m_nAxis/*_axis*/, _accel, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------
BOOL    CACSMotion::SetDecel( ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_SetDeceleration(m_hComm, m_nAxis/*_axis*/, m_dDecel, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::GetDecel(/*int _axis,*/ double *_decel, ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_GetDeceleration(m_hComm, m_nAxis/*_axis*/, _decel, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::SetJerk(ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_SetJerk(m_hComm, m_nAxis/*_axis*/, m_dJerk, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::GetJerk(/*int _axis,*/ double *_djerk, ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_GetJerk(m_hComm, m_nAxis/*_axis*/, _djerk, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::SetKillDecel( ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_SetKillDeceleration(m_hComm, m_nAxis/*_axis*/, m_dKillDecel, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::GetKillDecel(/*int _axis,*/ double *_dkilldecel, ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_GetKillDeceleration(m_hComm, m_nAxis/*_axis*/, _dkilldecel, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::SetJogVelocity(/*int _axis,*/ ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_SetVelocity(m_hComm, m_nAxis/*_axis*/, m_dVelocity, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::GetJogVelocity(/*int _axis,*/ double *_velocity, ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_GetVelocity(m_hComm, m_nAxis/*_axis*/, _velocity, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------
BOOL    CACSMotion::SetJogAccel( ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_SetAcceleration(m_hComm, m_nAxis/*_axis*/, m_dAccel, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::GetJogAccel(/*int _axis,*/ double *_accel, ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_GetAcceleration(m_hComm, m_nAxis/*_axis*/, _accel, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------
BOOL    CACSMotion::SetJogDecel( ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_SetDeceleration(m_hComm, m_nAxis/*_axis*/, m_dDecel, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::GetJogDecel(/*int _axis,*/ double *_decel, ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_GetDeceleration(m_hComm, m_nAxis/*_axis*/, _decel, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::SetJogJerk(ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_SetJerk(m_hComm, m_nAxis/*_axis*/, m_dJerk, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::GetJogJerk(/*int _axis,*/ double *_djerk, ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_GetJerk(m_hComm, m_nAxis/*_axis*/, _djerk, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::SetJogKillDecel( ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_SetKillDeceleration(m_hComm, m_nAxis/*_axis*/, m_dKillDecel, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::GetJogKillDecel(/*int _axis,*/ double *_dkilldecel, ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_GetKillDeceleration(m_hComm, m_nAxis/*_axis*/, _dkilldecel, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::SetFPos(/*int _axis,*/ double _fPos, ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_SetFPosition(m_hComm, m_nAxis/*_axis*/, _fPos, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::GetFPos(/*int _axis,*/ double *_fPos, ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
	if(!acsc_GetFPosition(m_hComm, m_nAxis/*_axis*/, _fPos, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------
BOOL       CACSMotion::SetActualPos(double dPos)
{
	CString cmd;

	BOOL	bRet;
	//m_pSyncData->Lock();
	cmd.Format(_T("SET APOS(%d)=%f"), m_nAxis, dPos);

	if(!acsc_Command(m_hComm, LPSTR(LPCTSTR(cmd)), cmd.GetLength(), NULL))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::SetRPos(/*int _axis,*/ double _rPos, ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
	if(!acsc_SetRPosition(m_hComm, m_nAxis/*_axis*/, _rPos, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::GetRPos(/*int _axis,*/ double *_rPos, ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
	if(!acsc_GetRPosition(m_hComm, m_nAxis/*_axis*/, _rPos, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

//BOOL    CACSMotion::GetAPos(/*int _axis,*/ double *_rPos, ACSC_WAITBLOCK* _wait)

//---------------------------------------------------------------------------

//BOOL    CACSMotion::SetAPos(/*int _axis,*/ double *_rPos, ACSC_WAITBLOCK* _wait)

//---------------------------------------------------------------------------

BOOL    CACSMotion::GetFVelo(/*int _axis,*/ double *_fVelo, ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_GetFVelocity(m_hComm, m_nAxis/*_axis*/, _fVelo, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::GetRVelo(/*int _axis,*/ double *_rVelo, ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_GetRVelocity(m_hComm, m_nAxis/*_axis*/, _rVelo, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------
BOOL    CACSMotion::Commut(/*int _axis,*/ ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_Commut(m_hComm, m_nAxis/*_axis*/, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------
BOOL    CACSMotion::Motion_Enable(/*int _axis,*/ ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	CString	strMsg;
	//m_pSyncData->Lock();
    if(!acsc_Enable(m_hComm, m_nAxis/*_axis*/, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_Disable(/*int _axis,*/ ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_Disable(m_hComm, m_nAxis/*_axis*/, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_Go(/*int _axis,*/ ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_Go(m_hComm, m_nAxis/*_axis*/, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_Stop(/*int _axis,*/ ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_Halt(m_hComm, m_nAxis/*_axis*/, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_Kill(/*int _axis,*/ ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_Kill(m_hComm, m_nAxis/*_axis*/, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_Break(/*int _axis,*/ ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_Break(m_hComm, m_nAxis/*_axis*/, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------
//여기
BOOL    CACSMotion::Motion_ToPoint(int _flags, /*int _axis,*/ double _point, ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_ToPoint(m_hComm, _flags, m_nAxis/*_axis*/, _point, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_ExtToPoint(int _flags, /*int _axis,*/ double _point,
 double _velo, double _end_velo, ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_ExtToPoint(m_hComm, _flags, m_nAxis/*_axis*/, _point, _velo, _end_velo, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_Track(int _flags, /*int _axis,*/ ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_Track(m_hComm, _flags, m_nAxis/*_axis*/, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_SetTargetPos(/*int _axis,*/ double _taget_pos, ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_SetTargetPosition(m_hComm, m_nAxis/*_axis*/, _taget_pos, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_GetTargetPos(/*int _axis,*/ double *_taget_pos, ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_GetTargetPosition(m_hComm, m_nAxis/*_axis*/, _taget_pos, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------
//여기
BOOL    CACSMotion::Motion_Jog(int _flags, /*int _axis,*/ double _velo, ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
	if (!acsc_Jog(m_hComm, _flags, m_nAxis/*_axis*/, _velo, _wait))
	{
		//strErrMsg.Format(_T("error: %d"), Motion_GetLastError());
		m_strErrMsg.Format(_T("<<< MOT >>>[%s][%d][ABS_FS]FUNC START FAIL !!!"), m_strMotorName, Motion_GetLastError());
		CACSM::m_strErrMsg = m_strErrMsg;
		bRet = FALSE;
	}
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_SetMaster(/*int _axis,*/ char* _formula, ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_SetMaster(m_hComm, m_nAxis/*_axis*/, _formula, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_Slave(int _flags, /*int _axis,*/ ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_Slave(m_hComm, _flags, m_nAxis/*_axis*/, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_Slave_Stalled(int _flags, /*int _axis,*/ double _left, double _right, ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_SlaveStalled(m_hComm, _flags, m_nAxis/*_axis*/, _left, _right, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_MultiPoint(int _flags, /*int _axis,*/ double _dwell, ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_MultiPoint(m_hComm, _flags, m_nAxis/*_axis*/, _dwell, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_AddPoint(/*int _axis,*/ double _point , ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_AddPoint(m_hComm, m_nAxis/*_axis*/, _point, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_ExtAddPoint(/*int _axis,*/ double _point, double _rate, ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_ExtAddPoint(m_hComm, m_nAxis/*_axis*/, _point, _rate, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_EndSequence(/*int _axis,*/ ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_EndSequence(m_hComm, m_nAxis/*_axis*/, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_GetMotorState(ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_GetMotorState(m_hComm, m_nAxis, &m_MotorState.Motor_Flags, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_GetAxisState(/*int _axis,*/ int* _state , ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_GetAxisState(m_hComm, m_nAxis/*_axis*/, _state, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_GetIndexState(/*int _axis,*/ int* _state , ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_GetIndexState(m_hComm, m_nAxis/*_axis*/, _state, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_GetFault(/*int _axis,*/ int* _fault, ACSC_WAITBLOCK* _wait)
{
    //int nAxis;
    //nAxis =
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_GetFault(m_hComm, m_nAxis/*_axis*/, _fault, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------
BOOL CACSMotion::Motion_GetEncoderFault(/*int _axis,*/ int* _fault, ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
	if (!acsc_GetFault(m_hComm, m_nEncAxisFault/*_axis*/, _fault, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}

BOOL    CACSMotion::Motion_SetFaultMask(/*int _axis,*/ int _mask, ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_SetFaultMask(m_hComm, m_nAxis/*_axis*/, _mask, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_GetFaultMask(/*int _axis, int* _mask, */ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    for(int j=0; j < 3; j++)
    {
    //if(!acsc_GetFaultMask(m_hComm, m_nAxis/*_axis*/, _mask, _wait))
		if (!acsc_GetFaultMask(m_hComm, m_nAxis/*_axis*/, &m_SafetyControlStates[j].Data, _wait))
		{
			bRet = FALSE;
			break;
		}
		else
			bRet = TRUE;
    }
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_EnableFault(/*int _axis,*/ int _fault , ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_EnableFault(m_hComm, m_nAxis/*_axis*/, _fault, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_DisableFault(/*int _axis,*/ int _fault , ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_DisableFault(m_hComm, m_nAxis/*_axis*/, _fault, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_SetResponseMask(/*int _axis,*/ int _mask, ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_SetResponseMask(m_hComm, m_nAxis/*_axis*/, _mask, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_GetResponseMask(/*int _axis,*/ int* _mask, ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_GetResponseMask(m_hComm, m_nAxis/*_axis*/, _mask, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_EnableResponse(/*int _axis,*/ int _response, ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_EnableResponse(m_hComm, m_nAxis/*_axis*/, _response, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_DisableResponse(/*int _axis,*/ int _response, ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_DisableResponse(m_hComm, m_nAxis/*_axis*/, _response, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_GetSafetyInput(/*int _axis,*/ int _input, int* _value, ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_GetSafetyInput(m_hComm, m_nAxis/*_axis*/, _input, _value, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_GetSafetyInputPort(/*int _axis,*/ int* _value, ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_GetSafetyInputPort(m_hComm, m_nAxis/*_axis*/, _value, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_GetSafetyInputPortInv(/*int _axis,*/ int* _value, ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_GetSafetyInputPortInv(m_hComm, m_nAxis/*_axis*/, _value, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_SetSafetyInputPortInv(/*int _axis,*/ int _value, ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_SetSafetyInputPortInv(m_hComm, m_nAxis/*_axis*/, _value, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_FaultClear(/*int _axis,*/ ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_FaultClear(m_hComm, m_nAxis/*_axis*/, _wait))
		bRet = FALSE;
	else
	{
		m_nFault = 0;
		m_nEncAxisFault = 0;
		m_nSystemError = 0;
		m_nMotorErrNum = 0;
		m_strMotorErrMsg = "";
		bRet = TRUE;
	}
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_WaitMotionEnd(/*int _axis,*/ int _timeout)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_WaitMotionEnd(m_hComm, m_nAxis/*_axis*/, _timeout))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_WaitLogicalMotionEnd(/*int _axis,*/ int _timeout)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_WaitLogicalMotionEnd(m_hComm, m_nAxis/*_axis*/, _timeout))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_WaitMotorEnabled(/*int _axis,*/ int _state, int _timeout)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_WaitMotorEnabled(m_hComm, m_nAxis/*_axis*/, _state, _timeout))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_WaitMotorCommutated(/*int _axis,*/ int _state, int _timeout)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_WaitMotorCommutated(m_hComm, m_nAxis/*_axis*/, _state, _timeout))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_GetMotorError(/*int _axis,*/ int* _error, ACSC_WAITBLOCK* _wait)
{
	int		nRet;
	BOOL	bRet;
	//m_pSyncData->Lock();
	if (!acsc_GetMotorError(m_hComm, m_nAxis/*_axis*/, _error, _wait))
	{
		nRet = acsc_GetLastError();
		bRet = FALSE;
	}

	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------
// bestmotion용 외부엔코더를 
// BOOL    CACSMotion::Motion_GetMotorError(/*int _axis,*/ int* _error, ACSC_WAITBLOCK* _wait)
// {
// 	BOOL	bRet;
// 	m_pSyncData->Lock();
// 	if (!acsc_GetMotorError(m_hComm, m_nAxis/*_axis*/, _error, _wait))
// 		bRet = FALSE;
// 	else
// 		bRet = TRUE;
// 	m_pSyncData->UnLock();
// 	return bRet;
// }
// ---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_GetMotionError(/*int _axis,*/ int* _error, ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_GetMotionError(m_hComm, m_nAxis/*_axis*/, _error, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

/*BOOL    CACSMotion::Motion_GetEtherCATSlaveIndex(int _vendor_id, int _product_id, int _count, int* _slave_index, ACSC_WAITBLOCK* _wait)
{
    if(!acsc_GetEtherCATSlaveIndex(m_hComm, _vendor_id, _product_id, _count, _slave_index, _wait))
        return FALSE;

    return TRUE;
} */
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_PegInc(int _flags, /*int _axis,*/ double _width, double _first_point,
 double _interval, double _last_point, int _tb_number, double _tb_period, ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_PegInc(m_hComm, _flags, m_nAxis/*_axis*/, _width, _first_point, _interval, _last_point, _tb_number, _tb_period , _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_PegRandom(int _flags, /*int _axis,*/ double _width, char* _point_array,
 char* _state_array, int _tb_number, double _tb_period, ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_PegRandom(m_hComm, _flags, m_nAxis/*_axis*/, _width, _point_array, _state_array, _tb_number, _tb_period , _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_AssignPins(/*int _axis,*/ unsigned short _mask, ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_AssignPins(m_hComm, m_nAxis/*_axis*/, _mask, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_StopPeg(/*int _axis,*/ ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_StopPeg(m_hComm, m_nAxis/*_axis*/, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_AssignPegNT(/*int _axis,*/ int _eng_to_enc_bit_code, int _gp_outs_bit_code, ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_AssignPegNT(m_hComm, m_nAxis/*_axis*/, _eng_to_enc_bit_code, _gp_outs_bit_code, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_AssignPegOutputsNT(/*int _axis,*/ int _output_index, int _bit_code, ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_AssignPegOutputsNT(m_hComm, m_nAxis/*_axis*/, _output_index, _bit_code, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_AssignFastInputsNT(/*int _axis,*/ int _input_index, int _bit_code, ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_AssignFastInputsNT(m_hComm, m_nAxis/*_axis*/, _input_index, _bit_code, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_PegIncNT(int _flags, /*int _axis,*/ double _width, double _first_point,
 double _interval, double _last_point, int _tb_number, double _tb_period, ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_PegIncNT(m_hComm, _flags, m_nAxis/*_axis*/, _width, _first_point, _interval, _last_point, _tb_number, _tb_period , _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_PegRandomNT(int _flags, /*int _axis,*/ double _width, int _mode, int _first_index,
int _last_index, char* _point_array, char* _state_array, int _tb_number, double _tb_period, ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_PegRandomNT(m_hComm, _flags, m_nAxis/*_axis*/, _width, _mode, _first_index, _last_index, _point_array, _state_array, _tb_number, _tb_period , _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_WaitPegReadyNT(/*int _axis,*/ int _timeout)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_WaitPegReadyNT(m_hComm, m_nAxis/*_axis*/, _timeout))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_StartPegNT(/*int _axis,*/ ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
    if(!acsc_StartPegNT(m_hComm,m_nAxis/*_axis*/, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_StopPegNT(/*int _axis,*/ ACSC_WAITBLOCK* _wait)
{
	BOOL	bRet;
	//m_pSyncData->Lock();
	if (!acsc_StopPegNT(m_hComm, m_nAxis/*_axis*/, _wait))
		bRet = FALSE;
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
    return bRet;
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::Motion_Save_Momory(ACSC_WAITBLOCK* _wait)
{
	int		nSize;
	char	*pChCmd;
	BOOL	bRet;
    CString  strCmd;
	CString  strErrMsg;
//    int     nStrLength;

//m_pSyncData->Lock();
    strCmd.Format(_T("#SAVEPAR %d\r"), m_nAxis);
	//여기도 바꿔야함
	pChCmd = CT2CA(strCmd);
	nSize = sizeof(pChCmd);
//    nStrLength = strCmd.Length();
    if(!acsc_Command(m_hComm, pChCmd, nSize/*strCmd.GetLength()*/, _wait))
    {
        strErrMsg.Format(_T("error: %d"), Motion_GetLastError());
		bRet =  FALSE;
    }
	else
		bRet = TRUE;
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------
BOOL CACSMotion::GetSystemFault(void)
{
	BOOL bRet;
	//m_pSyncData->Lock();
    if(Motion_GetFault(&m_nFault, NULL)) {
		bRet = TRUE;
    }
    else {
        m_strErrMsg.Format(_T("transaction error: %d\n"), Motion_GetLastError());
		bRet = FALSE;
    }
	//m_pSyncData->UnLock();

	return bRet;
}
//---------------------------------------------------------------------------
BOOL CACSMotion::GetEncoderSystemFault(void)
{
	BOOL bRet;
	//m_pSyncData->Lock();
	if (Motion_GetEncoderFault(&m_nEncAxisFault, NULL)) {
		bRet = TRUE;
	}
	else {
		m_strErrMsg.Format(_T("transaction error: %d\n"), Motion_GetLastError());
		bRet = FALSE;
	}
	//m_pSyncData->UnLock();

	return bRet;
}
//---------------------------------------------------------------------------
BOOL CACSMotion::GetSystemInv(void)
{
	BOOL bRet;
	//m_pSyncData->Lock();
    if(Motion_GetSafetyInputPortInv(&m_nInv, NULL))
	{
		bRet = TRUE;
    }
    else 
	{
        m_strErrMsg.Format(_T("transaction error: %d\n"), Motion_GetLastError());
		bRet = FALSE;
    }
	//m_pSyncData->UnLock();
	return bRet;
}
//---------------------------------------------------------------------------
BOOL CACSMotion::IsAlarm(int nValue)
{
//    if(m_nInv & nValue)
//    {
	BOOL bRet;
	//m_pSyncData->Lock();
	if(m_nFault & nValue)
	{
		GetMotorError();
		bRet = TRUE;
	}
	else
	{
		GetMotorError();
		bRet = FALSE;
	}
	//m_pSyncData->UnLock();
	return bRet;
//    }
/*    else
    {
        if(m_nFault & nValue)
        {
            m_nSystemError  = nValue;
            GetMotorError();
            return true;
        }
        else
        {
            return false;
        }
    }   */
}
//---------------------------------------------------------------------------
BOOL CACSMotion::IsEncAxisAlarm(int nValue)
{
	BOOL bRet;
	//m_pSyncData->Lock();
	if (m_nEncAxisFault & nValue)
	{
		GetMotorError();
		bRet = TRUE;
	}
	else
	{
		GetMotorError();
		bRet = FALSE;
	}
	//m_pSyncData->UnLock();
	return bRet;
	
}
//---------------------------------------------------------------------------
void     CACSMotion::GetMotorError(void)
{
//    int     nError;
	char*	pChBuf;
    CString  strErr;
    CString  strErrMsg;

    //strErrMsg.SetLength(256);

	pChBuf = new char[MAX_PATH];
	//m_pSyncData->Lock();
    if(Motion_GetMotorError(&m_nMotorErrNum, NULL))
    {
        if(m_nMotorErrNum > 0)
        {

            if(Motion_GetErrorString(m_nMotorErrNum, pChBuf, 255, NULL))
            {
				strErrMsg = TranseCharPointerToCString(pChBuf);//CA2CT(pChBuf);

                m_strMotorErrMsg.Format(_T("Motor error: %d (%s)\n"), m_nMotorErrNum, strErrMsg);
            }
        }
    }
    else
        m_strErrMsg.Format(_T("transaction error: %d\n"), Motion_GetLastError());
	//m_pSyncData->UnLock();
	//pChBuf = NULL;
	delete[] pChBuf;

}
//---------------------------------------------------------------------------
BOOL CACSMotion::IsError(void)
{
	BOOL bRet;

	bRet = FALSE;
	//m_pSyncData->Lock();
	if (m_nFault > 0 || m_nMotorErrNum > 0)
		bRet = TRUE;
	//m_pSyncData->UnLock();
    return bRet;
}
//---------------------------------------------------------------------------
BOOL CACSMotion::IsMoving()
{
	//m_pSyncData->Lock();
    Motion_GetMotorState(NULL);
	//m_pSyncData->UnLock();
    return m_MotorState.IsMoving();
}
//---------------------------------------------------------------------------
BOOL    CACSMotion::IsAccelerating()
{
	//m_pSyncData->Lock();
    Motion_GetMotorState(NULL);
	//m_pSyncData->UnLock();
    return m_MotorState.IsAccelerating();
}
//---------------------------------------------------------------------------

BOOL    CACSMotion::IsInPosition()
{
	//m_pSyncData->Lock();
    Motion_GetMotorState(NULL);
	//m_pSyncData->UnLock();
    return m_MotorState.IsInPosition();
}
//---------------------------------------------------------------------------
BOOL    CACSMotion::IsEnable()
{
	//m_pSyncData->Lock();
	Motion_GetMotorState(NULL);
	//m_pSyncData->UnLock();
    return m_MotorState.IsEnable();
}
//---------------------------------------------------------------------------

//여기
BOOL CACSMotion::MoveAbs(int nFlags, double dTarget, ACSC_WAITBLOCK* nWait)
{

    GetHomeFlag();
    GetSystemFault();
// 	if(!m_nTestMode)
// 	{
// 		//왜 release 모드에서는 home done이 안되지?? 내일 확인...
// 		if(m_nInitHomeDone != INIT_HOME_OK)
// 		{
// 			m_strErrMsg.Format(_T("<<< Init Home >>> [ABS] NOT INIT HOME DONE"));
// 			CACSM::m_strErrMsg = m_strErrMsg;
// 			return FALSE;
// 		}
// 	}
	if(m_nAxis < 0)
	{
		//m_strErrMsg.Format(_T("<<< MOT >>>[%s][ABS]Axis & Module Index < 0 !!!"),m_strMotorName);
		//CACSM::m_strErrMsg = m_strErrMsg;
		return FALSE;
	}
	//Home 동작이 완료했는지 확인
//	if(!m_nTestMode)
//	{
		if(m_nHomeDone != MOTION_HOME_OK)
		{
			//m_strErrMsg.Format(_T("<<< Init Home >>> [%s][ABS]NOT MOT HOME DONE"));
			//CACSM::m_strErrMsg = m_strErrMsg;
			return FALSE;
		}
//	}
	if(IsError() == TRUE)
	{
		//m_strErrMsg.Format(_T("<<< MOT >>>[%s][ABS]Ararm Signal Detected !!!"),m_strMotorName);
		//CACSM::m_strErrMsg = m_strErrMsg;
		return FALSE;
	}
	//동작 가능한지 판단...
	//추후 추가
	/*
   if(mpMoveCheck !=  && mpMoveCheck() == false)
	{
		mstr_Msg.sprintf("<<< MOT >>>[%s][ABS]Check Func Fail !!!",mstr_Name.c_str());
		return false;
	}
	*/
	m_strErrMsg = "";

	/*if(dTarget > m_dMaxAngle)
	{
		m_strErrMsg.Format(_T("<<< MOT >>>[%s][ABS]Max Pos Error !!!"),m_strMotorName);
		CACSM::m_strErrMsg = m_strErrMsg;
		return FALSE;
	}

	if(dTarget < m_dMinAngle)
	{
		m_strErrMsg.Format(_T("<<< MOT >>>[%s][ABS]Min Pos Error !!!"),m_strMotorName);
		CACSM::m_strErrMsg = m_strErrMsg;
		return FALSE;
	}*/
	//move 명령
	if(!Motion_ToPoint(nFlags, dTarget, nWait))
	{
		//m_strErrMsg.Format(_T("<<< MOT >>>[%s][ABS_FS]FUNC START FAIL !!!"),m_strMotorName);
		//CACSM::m_strErrMsg = m_strErrMsg;
		return FALSE;
	}

	//Debug mode시 처리...

	if(m_nDebugMode == 1)
	{
		//frmLog->Add(LVLOG_INFORMATION, "Move Abs", m_strErrMsg.sprintf("<<< MOT >>>[%s]ABS_START Pos(%f)Spd(%f)Acc(%f) !!!",m_strMotorName.c_str(),
		//dTarget,m_dVelocity,m_dAccel));
		CACSM::m_strErrMsg = m_strErrMsg;
	}

	return TRUE;


}
//---------------------------------------------------------------------------
BOOL CACSMotion::MoveRel(int nFlags, double dTarget, ACSC_WAITBLOCK* nWait)
{
    GetHomeFlag();
    GetSystemFault();
// 	if(!m_nTestMode)
// 	{
// 		if(m_nInitHomeDone != INIT_HOME_OK)
// 		{
// 			m_strErrMsg.Format(_T("<<< Init Home >>> [ABS] NOT INIT HOME DONE"));
// 			CACSM::m_strErrMsg = m_strErrMsg;
// 			return FALSE;
// 		}
// 	}
	if(m_nAxis < 0)
	{
		/*m_strErrMsg.Format(_T("<<< MOT >>>[%s][ABS]Axis & Module Index < 0 !!!"),m_strMotorName);
		CACSM::m_strErrMsg = m_strErrMsg;*/
		return FALSE;
	}
	//Home 동작이 완료했는지 확인
//	if(!m_nTestMode)
//	{
		if(m_nHomeDone != MOTION_HOME_OK)
		{
			/*m_strErrMsg.Format(_T("<<< Init Home >>> [%s][ABS]NOT MOT HOME DONE"));
			CACSM::m_strErrMsg = m_strErrMsg;*/
			return FALSE;
		}
//	}
	if(IsError() == TRUE)
	{
		/*m_strErrMsg.Format(_T("<<< MOT >>>[%s][ABS]Ararm Signal Detected !!!"),m_strMotorName);
		CACSM::m_strErrMsg = m_strErrMsg;*/
		return FALSE;
	}
	//동작 가능한지 판단...
	//추후 추가
	/*
   if(mpMoveCheck !=  && mpMoveCheck() == false)
	{
		mstr_Msg.sprintf("<<< MOT >>>[%s][ABS]Check Func Fail !!!",mstr_Name.c_str());
		return false;
	}
	m_bUserStop = false;        //사용자가 정지 명령 내리지 않는것을 처리..추후
	*/
	m_strErrMsg = _T("");

	if(!Motion_ToPoint(nFlags, dTarget, nWait))
	{
		/*m_strErrMsg.Format(_T("<<< MOT >>>[%s][ABS_FS]FUNC START FAIL !!!"), m_strMotorName);
		CACSM::m_strErrMsg = m_strErrMsg;*/
		return FALSE;
	}

	//Debug mode시 처리...
	if(m_nDebugMode == 1)
	{
		//frmLog->Add(LVLOG_INFORMATION, "Move Abs", m_strErrMsg.sprintf("<<< MOT >>>[%s]ABS_START Pos(%f)Spd(%f)Acc(%f) !!!",m_strMotorName.c_str(),
		//dTarget,m_dVelocity,m_dAccel));
		CACSM::m_strErrMsg = m_strErrMsg;
	}

	return TRUE;


}
//ACSC_AMF_VELOCITY
//플러스 방향은  +1도 설정 마이너스 방향은 -1도
BOOL CACSMotion::MoveJog(int nFlags, double dVelo, ACSC_WAITBLOCK* nWait)
{
	GetHomeFlag();
	GetSystemFault();
// 	if (!m_nTestMode)
// 	{
// 		if (m_nInitHomeDone != INIT_HOME_OK)
// 		{
// 			m_strErrMsg.Format(_T("<<< Init Home >>> [ABS] NOT INIT HOME DONE"));
// 			CACSM::m_strErrMsg = m_strErrMsg;
// 			return FALSE;
// 		}
// 	}
	if (m_nAxis < 0)
	{
		/*m_strErrMsg.Format(_T("<<< MOT >>>[%s][ABS]Axis & Module Index < 0 !!!"), m_strMotorName);
		CACSM::m_strErrMsg = m_strErrMsg;*/
		return FALSE;
	}
	//Home 동작이 완료했는지 확인
	//	if(!m_nTestMode)
	//	{
	if (m_nHomeDone != MOTION_HOME_OK)
	{
		/*m_strErrMsg.Format(_T("<<< Init Home >>> [%s][ABS]NOT MOT HOME DONE"));
		CACSM::m_strErrMsg = m_strErrMsg;*/
		return FALSE;
	}
	//	}
	if (IsError() == TRUE)
	{
		/*m_strErrMsg.Format(_T("<<< MOT >>>[%s][ABS]Ararm Signal Detected !!!"), m_strMotorName);
		CACSM::m_strErrMsg = m_strErrMsg;*/
		return FALSE;
	}
	//동작 가능한지 판단...
	//추후 추가
	/*
	if(mpMoveCheck !=  && mpMoveCheck() == false)
	{
	mstr_Msg.sprintf("<<< MOT >>>[%s][ABS]Check Func Fail !!!",mstr_Name.c_str());
	return false;
	}
	m_bUserStop = false;        //사용자가 정지 명령 내리지 않는것을 처리..추후
	*/
	m_strErrMsg = _T("");
	
	if (!Motion_Jog(nFlags, dVelo, nWait))
	{
		/*m_strErrMsg.Format(_T("<<< MOT >>>[%s][ABS_FS]FUNC START FAIL !!!"), m_strMotorName);
		CACSM::m_strErrMsg = m_strErrMsg;*/
		return FALSE;
	}

	//Debug mode시 처리...
	if (m_nDebugMode == 1)
	{
		//frmLog->Add(LVLOG_INFORMATION, "Move Abs", m_strErrMsg.sprintf("<<< MOT >>>[%s]ABS_START Pos(%f)Spd(%f)Acc(%f) !!!",m_strMotorName.c_str(),
		//dTarget,m_dVelocity,m_dAccel));
		CACSM::m_strErrMsg = m_strErrMsg;
	}

	return TRUE;
}
//---------------------------------------------------------------------------
void     CACSMotion::GetHomeFlag()
{
	int nHomeFlag;

 	char*	pChBuf;
 	pChBuf = new char[MAX_PATH];
	nHomeFlag = 0;
 	TranseCStringToCharPointer(m_strHomeRetVarName, pChBuf);
	//m_pSyncData->Lock();
  	if(!Motion_ReadInteger(ACSC_NONE, pChBuf, 0/*m_nAxis*/,  0/*m_nAxis*/, ACSC_NONE, ACSC_NONE, &nHomeFlag, NULL))
     {
 		//m_strHomeRetVarName = TranseCharPointerToCString(pChBuf);//CA2CT(pChBuf);
		m_nHomeDone = MOTION_HOME_ERR;
  
  		delete[] pChBuf;
  		pChBuf = NULL;
		//	m_pSyncData->UnLock();
		return;
	}
	//m_pSyncData->UnLock();
 	//m_strHomeRetVarName = TranseCharPointerToCString(pChBuf);
 
     switch(nHomeFlag)
     {
     case MOTION_HOME_NOT:
         m_nHomeDone = MOTION_HOME_NOT;
         break;
     case MOTION_HOME_OK:
         m_nHomeDone = MOTION_HOME_OK;
         break;
     case MOTION_HOME_ING:
         m_nHomeDone = MOTION_HOME_ING;
         break;
     case MOTION_HOME_ERR:
         m_nHomeDone = MOTION_HOME_ERR;
         break;
     }

 	delete[] pChBuf;
 	pChBuf = NULL;
	return;

}
//---------------------------------------------------------------------------
void     CACSMotion::SetHomeFlag(int nFlag)
{

	char*	pChBuf;

	pChBuf = new char[MAX_PATH];
	//m_pSyncData->Lock();
    if(!Motion_WriteInteger(ACSC_NONE, pChBuf, m_nHomeBufferIdx, m_nHomeBufferIdx, ACSC_NONE, ACSC_NONE, &nFlag, NULL))
    {
		m_strHomeRetVarName = TranseCharPointerToCString(pChBuf);
		pChBuf = NULL;
		delete[] pChBuf;
        m_nHomeDone = MOTION_HOME_FUNC_ERROR;
		//	m_pSyncData->UnLock();
        return;
    }
	//m_pSyncData->UnLock();
	m_strHomeRetVarName = TranseCharPointerToCString(pChBuf);
	
	delete[] pChBuf;
	pChBuf = NULL;
    return;

}
//---------------------------------------------------------------------------
int    CACSMotion::PEG_Prepare()
{

    if(m_hComm == ACSC_INVALID)
        return FALSE;
     //ACSPL : ASSIGNPEG   0, 0b000, 0b000	! 0 번축을 PEG 엔진 0번을 사용
    if(!Motion_AssignPegNT(0x00, 0x00, NULL)) //2,0
        return FALSE;
    // ACSPL : ASSIGNPOUTS 0, 0, 0b000		! 0 번축 PEG   출력 (pin : PEG X +)
    if(!Motion_AssignPegOutputsNT(0, 0x00, NULL))
        return FALSE;
    // ACSPL : ASSIGNPOUTS 0, 5, 0b000		! 0 번축 State 출력 (pin : X_STATE0 +)
//    if(!Motion_AssignPegOutputsNT(6, 3, NULL))
//        return FALSE;
    if(!Motion_AssignPegOutputsNT(2, 0, NULL))
        return FALSE;

    // PEG 출력를 지정하기 위한 배열 선언 (On, Off 로 사용하기 위한 2개 지점)
    if(!Motion_DeclareVariable(ACSC_REAL_TYPE, "PEG_POS_X(2)", NULL))
    {
        if(acsc_GetLastError()!= 2027)
            return FALSE;
    }

    if(!Motion_DeclareVariable(ACSC_INT_TYPE, "PEG_STATE_X(2)", NULL))
    {
        if(acsc_GetLastError()!= 2027)
            return FALSE;
    }

    return TRUE;
}

//현재 속도 얻어오는 함수.
BOOL CACSMotion::GetCurrFeedBackVel(double *dRefVel)
{
	BOOL bRef;
	//m_pSyncData->Lock();
	if (!Motion_ReadReal(ACSC_NONE, "FVEL", m_nAxis, m_nAxis, ACSC_NONE, ACSC_NONE, dRefVel, NULL))
	{
		//m_strHomeRetVarName = TranseCharPointerToCString(pChBuf);//CA2CT(pChBuf);
		bRef = FALSE;
	}
	else
		bRef = TRUE;
	
	//m_pSyncData->UnLock();
	return bRef;
}
//RACC FACC
//지령 속도 얻어오는 함수.
BOOL CACSMotion::GetCmdRefVel(double *dRefVel)
{
	BOOL bRef;
	//m_pSyncData->Lock();
	if (!Motion_ReadReal(ACSC_NONE, "RVEL", m_nAxis, m_nAxis, ACSC_NONE, ACSC_NONE, dRefVel, NULL))
	{
		//m_strHomeRetVarName = TranseCharPointerToCString(pChBuf);//CA2CT(pChBuf);
		bRef = FALSE;
	}
	else
		bRef = TRUE;

	//m_pSyncData->UnLock();
	return bRef;
}



//---------------------------------------------------------------------------
//2014-08-14
//한성민
// int    CACSMotion::PEG_OutState(std::vector<double> vPos, CString strPosName, String strStateName, double dPulse_Width)
// {
// 	int		i;
// 	int		nCnt, nStateCnt;
// 	int		* PEG_STATE;
// 	double	* lfPEG_Pos;
// 
// 	if(m_hComm == ACSC_INVALID)
// 		return FALSE;
// 
// 	nCnt 		= vPos.size();
// 	lfPEG_Pos	= new double[nCnt];
// 
// 	//배열 초기화
// 
// 	for(i=0; i<nCnt; i++)
// 	{
// 		lfPEG_Pos[i]=vPos[i];
// 	}
// 
// 	// State 처리 위한
// 	if(!strStateName.IsEmpty())
// 	{
// 		nStateCnt = nCnt * 2;
// 
// 		PEG_STATE = new int[nStateCnt];
// 
// 		for(int i=0,j=0; i<nStateCnt; i++, j+=2)
// 		{
// 			PEG_STATE[j]=1;
// 			PEG_STATE[j+1]=0;
// 		}
// 		if(!Motion_WriteInteger(-1, strStateName.c_str(), 0, nStateCnt, -1, -1, PEG_STATE, NULL))
// 		{
// 			delete []lfPEG_Pos;
// 			return FALSE;
// 		}
// 		delete []PEG_STATE;
// 	}
// 
// 
// // ON, OFF 처리를 위한 2개 지점 지정
// 	if(!Motion_WriteReal(-1, strPosName.c_str(), 0, nCnt, -1, -1, lfPEG_Pos, NULL))
// 	{
// 		delete []lfPEG_Pos;
// 		return FALSE;
// 	}
// 
// 	// PEG 출력을 위한 값 설정
// 	if(!Motion_PegRandomNT(ACSC_AMF_SYNCHRONOUS, dPulse_Width, X_PEG_OUTPUT_MODE, 0, nCnt, strPosName.c_str(), strStateName.c_str(), ACSC_NONE, ACSC_NONE, NULL))
// 	{
// 		delete []lfPEG_Pos;
// 		return FALSE;
// 	}
// 
// 	// PEG 엔진이 준비될 때 까지 대기함
// 	if(!Motion_WaitPegReadyNT(TIMEOUT_PEG_READY))
// 	{
// 		delete []lfPEG_Pos;
// 		return FALSE;
// 	}
// 
// 	delete []lfPEG_Pos;
// 
// 	return TRUE;
// }
//---------------------------------------------------------------------------
int    CACSMotion::PEG_SetPos(double dWidth, double dFirstPos, double dLastPos, double dFreq)
{
	// 갠트리 모드로 사용할 경우 위치 계산을 다시 하기 위한 변수
//     double dGentry_FirstPos = 0.0;
//     double dGentry_LastPos = 0.0;
//     double dGentry_Interval = 0.0;
//     double dArrEncoderOffset[11] = {0.0}; // 배열의 크기는 16축에 대해서만 읽기 위함 (실제 0, 2번 축만 사용할 경우 크기를 3 까지만 사용하면 됨)
//     String  strTemp;
//     if(m_hComm == ACSC_INVALID)
//         return FALSE;
// 
//     if(!Motion_ReadReal(ACSC_NONE, "EOFFS", 0, 10, -1, -1, dArrEncoderOffset, NULL))
//         return FALSE;
// //--------------------------------------------------------------------------------------------------------------------
// //                  ------------ 갠트리 모드에서 위치 지정을 위한 계산식 ------------
// //--------------------------------------------------------------------------------------------------------------------
//     dGentry_FirstPos = dFirstPos * 0.5 +  dArrEncoderOffset[4] * 0.5 + dArrEncoderOffset[6] * 0.25;
// 	dGentry_LastPos  = dLastPos  * 0.5 +  dArrEncoderOffset[4] * 0.5 + dArrEncoderOffset[6] * 0.25;
//     //Interval은 속도/주파수임
// //    if(dFirstPos > 0){
//     if(dFirstPos > dLastPos){
//         dGentry_Interval =  -(m_dVelocity / dFreq * 0.5);
//     }
//     else
//         dGentry_Interval =  m_dVelocity / dFreq * 0.5;
// 
// //--------------------------------------------------------------------------------------------------------------------
// 
// // PEG 출력을 위한 위치를 설정하고 준비 상태로 만들어 줌 (갠트리로 사용하기 때문에 0 번 축을 설정함)
//     if(!Motion_PegInc(ACSC_AMF_SYNCHRONOUS, dWidth, dGentry_FirstPos, dGentry_Interval, dGentry_LastPos, ACSC_NONE, ACSC_NONE, NULL))
//         return FALSE;
// 
// // 출력 준비가 모두 완료될 때 까지 대기함 (설정된 시간만큼)
// 	if(!Motion_WaitPegReadyNT(TIMEOUT_PEG_READY))
//         return FALSE;

    return TRUE;

}
//---------------------------------------------------------------------------

int    CACSMotion::PEG_SetPos_Single(double dWidth, double dFirstPos, double dLastPos, double dFreq)
{
    // 갠트리 모드로 사용할 경우 위치 계산을 다시 하기 위한 변수
//     double dGentry_FirstPos = 0.0;
//     double dGentry_LastPos = 0.0;
//     double dGentry_Interval = 0.0;
//     String  strTemp;
//     if(m_hComm == ACSC_INVALID)
//         return FALSE;
// 
// //--------------------------------------------------------------------------------------------------------------------
// //                  ------------ 갠트리 모드에서 위치 지정을 위한 계산식 ------------
// //--------------------------------------------------------------------------------------------------------------------
//     dGentry_FirstPos = dFirstPos;// * 0.5 +  dArrEncoderOffset[4] * 0.5 + dArrEncoderOffset[6] * 0.25;
// 	dGentry_LastPos  = dLastPos;//  * 0.5 +  dArrEncoderOffset[4] * 0.5 + dArrEncoderOffset[6] * 0.25;
//     //Interval은 속도/주파수임
//     if(dFirstPos > 0){
//         dGentry_Interval =  -(m_dVelocity / dFreq);
//     }
//     else
//         dGentry_Interval =  m_dVelocity / dFreq;
// 
// //--------------------------------------------------------------------------------------------------------------------
// 
// // PEG 출력을 위한 위치를 설정하고 준비 상태로 만들어 줌 (갠트리로 사용하기 때문에 0 번 축을 설정함)
//     if(!Motion_PegInc(ACSC_AMF_SYNCHRONOUS, dWidth, dGentry_FirstPos, dGentry_Interval, dGentry_LastPos, ACSC_NONE, ACSC_NONE, NULL))
//         return FALSE;
// 
// // 출력 준비가 모두 완료될 때 까지 대기함 (설정된 시간만큼)
// 	if(!Motion_WaitPegReadyNT(TIMEOUT_PEG_READY))
//         return FALSE;

    return TRUE;

}
//---------------------------------------------------------------------------

