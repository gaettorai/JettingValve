
// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이 
// 들어 있는 포함 파일입니다.

#pragma once

// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이 
// 들어 있는 포함 파일입니다.

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 일부 CString 생성자는 명시적으로 선언됩니다.

// MFC의 공통 부분과 무시 가능한 경고 메시지에 대한 숨기기를 해제합니다.
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 핵심 및 표준 구성 요소입니다.
#include <afxext.h>         // MFC 확장입니다.


#include <afxdisp.h>        // MFC 자동화 클래스입니다.



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 공용 컨트롤에 대한 MFC 지원입니다.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows 공용 컨트롤에 대한 MFC 지원입니다.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC의 리본 및 컨트롤 막대 지원


#include <vector>
#include <list>
#include <locale.h>
#include <string.h>

#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "bgapi2_genicam.hpp"

using namespace BGAPI2;
using namespace cv;
using namespace std;
//#include "BOM.h"

#define CamWidth 2448
#define CamHeight 2048

#define WIDTHBYTES(bits) (((bits)+31)/32*4)

#define WindowWidth 1685
#define	WindowHeight 950

#define MotorCount	3

#define CamCount	2

#define CamName1		_T("UPPER")
#define CamName2		_T("SIDE")

#define resizeMagni	2

#define ColorBasic		RGB(240,240,240)
#define ColorGreen		RGB(0,255,0)
#define ColorRed		RGB(255,0,0)

#define PORT 50000
#define PACKET_SIZE 1024
#define CLIENT_IP	"192.168.0.230"
#define SERVER_IP	"192.168.0.255"
#define GAP_IP		"169.254.0.11"
#define GAP_PORT	5011

#define SHM_DISPL_VALUE	0x1F0
#define	MEM_READ	0x30
#define	MEM_READ_REPLY	(0x30+0x80)

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

#define _CRT_SECURE_NO_DEPRECATE


//#include "Define.h"
#include "ACSC.h"
//#include "vld.h"
// //////////////////////////////////////////////////////////////////////////
// Type Definitions
// //////////////////////////////////////////////////////////////////////////
typedef unsigned int LedState;

// //////////////////////////////////////////////////////////////////////////
// Name Spaces
// //////////////////////////////////////////////////////////////////////////

namespace
{
	/** Predefined initial Led State as "Off" state. */
	const LedState LED_BUTTON_STATE_OFF = 0;

	/** Predefined "On" Led State. */
	const LedState LED_BUTTON_STATE_ON = 1;

	/** Predefined activity duration in msec. */
	const int LED_BUTTON_DEFAULT_ACTIVITY_DURATION = 150;

	/** Predefined Led States Number. */
	const int LED_BUTTON_PREDEFINED_STATES_NUMBER = 2;

};

//각 축별로 홈을 다 잡은 후
#define INIT_HOME_NOT               0
#define INIT_HOME_OK                1
#define INIT_HOME_ING               2
#define INIT_HOME_ERR               3
#define INIT_HOME_FUNC_ERROR        4


//각 축별 홈관련
#define MOTION_HOME_NOT             0
#define MOTION_HOME_OK              1
#define MOTION_HOME_ING             2
#define MOTION_HOME_ERR             -1
#define MOTION_HOME_FUNC_ERROR      4


//typedef Set<PROCESS_STATUS, ps_ERROR, ps_PAUSE>  TPROCESS_STATUS;

enum AUTO_PROC_KIND
{
	apk_NONE = 0,
	apk_START = 1,
	apk_CHECK_INIT_HOME = 2,
	apk_CHECK_IN_OUT = 3,
	apk_INIT_POS = 4,
	apk_INIT_POS_COMP = 5,
	apk_FIRST_MOVE = 6,
	apk_FIRST_MOVE_COMP = 7,
	apk_SECOND_MOVE = 8,
	apk_SECOND_MOVE_COMP = 9,
	apk_CHECK_REPEAT = 10,
	apk_ALL_MOVE_COMP_INIT_POS_MOVE = 11,
	apk_ALL_MOVE_COMP_INIT_POS_MOVE_COMP = 12,
	apk_CHECK_STATUS = 13,

	apk_END_MOVE = 100,
	apk_PAUSE = 500,
	apk_ERROR = 5000,
	apk_SYSTEM_ERROR = 6000
};



CString getCurrentPath();

union BIT_DATA_8
{
	char  Data;

	struct BIT {        // Bit Field Structure
		unsigned b0 : 1;
		unsigned b1 : 1;
		unsigned b2 : 1;
		unsigned b3 : 1;
		unsigned b4 : 1;
		unsigned b5 : 1;
		unsigned b6 : 1;
		unsigned b7 : 1;
	} bit;

	void init()
	{
		ZeroMemory(this, sizeof(*this));
	}

	BIT_DATA_8()
	{
		init();
	}

	bool getBit(int nIdx)
	{
		return ((Data >> nIdx) & 0x0001);
	}

	void setBit(int nBitIdx, bool bOn)
	{
		if (bOn)
			Data = Data | (0x01 << nBitIdx);
		else
			Data = Data & ~(0x01 << nBitIdx);
	}
};

union WORD_DATA
{
	unsigned short int	nValue;
	short	int 		Value;
	struct _Ch
	{
		unsigned char low;
		unsigned char high;
	} Ch;

};

union DWORD_DATA
{
	int value;
	struct _word
	{
		unsigned short int low;
		unsigned short int high;
	} word;
	struct _ch
	{
		unsigned char _0;
		unsigned char _1;
		unsigned char _2;
		unsigned char _3;
	} ch;

};

union USHORT_DATA_32
{
	int data;
	struct WORDS
	{
		unsigned short low;
		unsigned short high;
	} words;

	void init()
	{
		ZeroMemory(this, sizeof(*this));
	}
	USHORT_DATA_32()
	{
		init();
	}
};

union USHORT_DATA_16
{
	unsigned short data;
	struct BITS
	{        // Bit Field Structure
		unsigned b_0 : 1;
		unsigned b_1 : 1;
		unsigned b_2 : 1;
		unsigned b_3 : 1;
		unsigned b_4 : 1;
		unsigned b_5 : 1;
		unsigned b_6 : 1;
		unsigned b_7 : 1;
		unsigned b_8 : 1;
		unsigned b_9 : 1;
		unsigned b_10 : 1;
		unsigned b_11 : 1;
		unsigned b_12 : 1;
		unsigned b_13 : 1;
		unsigned b_14 : 1;
		unsigned b_15 : 1;
	} bits;

	struct BYTES
	{
		unsigned char low;
		unsigned char high;
	} bytes;

	void init()
	{
		ZeroMemory(this, sizeof(*this));
	}

	USHORT_DATA_16()
	{
		init();
	}

	bool getBit(int nIdx)
	{
		return ((data >> nIdx) & 0x0001);
	}

	void setBit(int nBitIdx, bool bOn)
	{
		if (bOn)
			data = data | (0x01 << nBitIdx);
		else
			data = data & ~(0x01 << nBitIdx);
	}
};


typedef struct _ACS_COMM_CONFIG
{
	CString  str_ip;
	int     n_port;

	void init()
	{
		str_ip = "";
		n_port = 0;
	}

	_ACS_COMM_CONFIG()
	{
		init();
	}

}ACS_COMM_CONFIG, * PACS_COMM_CONFIG;



typedef struct _MOTION_CONFIGS
{
	short int           nAxis;
	//	CString             strMotorName;
	// 	unsigned char       chInpositionLevel;
	// 	//    unsigned char       chInpositionUse;
	// 	unsigned char       chAlarmLevel;
	// 	unsigned char       chNendLimitLevel;   //+limit 사용유무
	// 	unsigned char       chPendLimitLevel;   //-limit 사용유무
	// 	unsigned char       chZPhaseLevel;      //z상 사용 유무
	// 	unsigned char       chEncInputMethod;   //Encoder 체배 관련
	// 	unsigned char       chPulseOutMethod;   // 펼스 출력 방식
	// 	unsigned char       chStopMode;         //급정지, 감속정지 관련
	// 	unsigned char       chHomeLevel;        //홈센서 관련
	// 	unsigned char       chServoOnLevel;     //Servo On Level
	// 	unsigned char       chEMGLevel;         //EMG Level;

	//	double              dUnit;              //unit/pulse에서 쓰일 값
	//	double              dPulse;             //unit/pulse에서 쓰일 값
	//    double              dLowVelocity;
	//    double              dHightVelocity;
	//    double              dMaxVelocity;
	//    double              dStartPosition;
	//    double              dEndPosition;

	double              dVelocity;
	double              dAccelation;
	double              dDccelation;
	double              dSCurve;
	double              dJogVelocity;
	double              dJogAcclation;
	double              dJogDccelation;
	double              dJogSCurve;
	double              dNendLimitPos;
	double              dPendLimitPos;
	double              dHomeOffset;
	double              dHomeVel1;
	double              dHomeVel2;
	double              dHomeVel3;
	double              dHomeVel4;
	double              dInitPosition;
	bool                bUseSoftLimit;


	// 	_MOTION_CONFIGS()
	// 	{
	// 		nErrorCode = 0;
	// 		nAxis = 0;
	// 		strMotorName = "";
	// 		chInpositionLevel = 0;
	// 		chAlarmLevel = 0;
	// 		chNendLimitLevel = 0;
	// 		chPendLimitLevel = 0;
	// 		chZPhaseLevel = 0;
	// 		chEncInputMethod = 0;
	// 		chPulseOutMethod = 0;
	// 		chHomeLevel = 0;
	// 		dUnit = 0;
	// 		dPulse = 0;
	// 
	// 		dVelocity = 0;
	// 		dAccelation = 0;
	// 		dDccelation = 0;
	// 		dSCurve = 0;
	// 		dJogVelocity = 0;
	// 		dJogAcclation = 0;
	// 		dJogDccelation = 0;
	// 		dJogSCurve = 0;
	// 		dNendLimitPos = 0;
	// 		dPendLimitPos = 0;
	// 		dHomeOffset = 0;
	// 		chStopMode = 0;
	// 
	// 		dHomeVel1 = 0;
	// 		dHomeVel2 = 0;
	// 		dHomeVel3 = 0;
	// 		dHomeVel4 = 0;
	// 
	// 		chServoOnLevel = 0;
	// 		chEMGLevel = 0;
	// 		dInitPosition = 0;
	// 		bUseSoftLimit = false;

			//        chCoordinates       = 'C';

			//        dMaxVelocity        = 800;
			//        dLowVelocity        = 200;
			//        dHightVelocity      = 400;
			//        dStartPosition      = 0;
			//        dEndPosition        = 0;


}MOTION_CONFIGS, * PMOTION_CONFIGS;

typedef struct _USER_INFO
{
	CString		strUser;
	CString		strPass;

	_USER_INFO()
	{
		strUser = _T("");
		strPass = _T("1234");
	}
}USER_INFO, * PUSER_INFO;



//중간에 컨트롤러와 접속이 끊어지면....
namespace ReadyState
{
	enum READY_STATUS
	{
		rs_NONE = 0,
		rs_NOTREADY = 1,
		rs_READY = 2
	};
}

namespace ProcessState
{
	enum PROCESS_STATUS
	{
		ps_NONE = 0,
		ps_STOP = 1,
		ps_AUTO = 2,
		ps_MANUAL = 3,
		ps_PAUSE = 4,
		ps_ERROR = 5
	};
}

class StateData
{
public:
	StateData()
	{
		m_ProcState = ProcessState::ps_NONE;
		m_readyState = ReadyState::rs_NONE;
	}
public:
	ProcessState::PROCESS_STATUS m_ProcState;
	ReadyState::READY_STATUS m_readyState;
};

extern StateData g_StateData;
void TranseCStringToCharPointer(CString str, char retCh[]);
CString TranseCharPointerToCString(char* ch);
DWORD CreateNewFileAsUTF16(IN LPCTSTR lpszFilePath);
//double GetPrecisionTime(void);

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


