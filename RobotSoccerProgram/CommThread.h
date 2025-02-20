#pragma once

#include"CommQueue.h"

#define IN_BUFF_SIZE    2048 // 통신 포트 입출력 버퍼 크기
#define OUT_BUFF_SIZE   2048

// Stop bits
#define	COM_STOP1   0
#define	COM_STOP1_5 1
#define	COM_STOP2   2

// Parity bits
#define	COM_PARITY_NONE  0 // 'N'
#define	COM_PARITY_ODD   1 // 'O'
#define	COM_PARITY_EVEN  2 // 'E'
#define	COM_PARITY_MARK  3 // 'M'
#define	COM_PARITY_SPACE 4 // 'S'


#define	ASCII_LF		0x0a
#define	ASCII_CR		0x0d
#define	ASCII_XON		0x11
#define	ASCII_XOFF		0x13

class CCommThread
{
public:
	CCommThread(void);
	~CCommThread(void);



	HWND hCommWnd;

	//--------- 환경 변수 -----------------------------------------//
	HANDLE		m_hComm;				// 통신 포트 파일 핸들
	CString		m_sPortName;			// 포트 이름 (COM1 ..)
	BOOL		m_bConnected;			// 포트가 열렸는지 유무를 나타냄.
	OVERLAPPED	m_osRead, m_osWrite;	// 포트 파일 Overlapped structure
	HANDLE		m_hThreadWatchComm;		// Watch함수 Thread 핸들.
	WORD		m_wPortID;				// WM_COMM_READ와 함께 보내는 인수.
										// 여러개의 포트를 열었을 경우 어떤 포트인지 
	                                    // 식별하는 데 사용한다.

	//--------- 통신 버퍼 -----------------------------------------//
	CCommQueue	m_QueueRead;                // 스레드와 부모 프로세스간의 통신 버퍼

	//--------- 외부 사용 함수 ------------------------------------//
	// 시리얼 포트를 연다. 인자 : 포트명, String의 속도, 포트 번호
	BOOL	OpenPort(CString sPortName, DWORD dwBaud, WORD wParam, BYTE parity, BYTE stopbits);
	// 시리얼 포트를 닫는다.
	void	ClosePort();
	// 시리얼 포트에 데이터를 쓴다.
	DWORD	WriteComm(BYTE *pBuff, DWORD nToWrite);

	// comm port를 다시 연다.	2002.5.9. 국현 추가.
	void changeCOMMSET(int port, int bps);

	//--------- 내부 사용 함수 ------------------------------------//
	// 스레드가 메세지를 보내온 경우 이 함수를 이용해서 테이터를 읽는다.
	DWORD	ReadComm(BYTE *pBuff, DWORD nToRead);

	void ClearPort();

};

DWORD ThreadWatchComm(CCommThread* pComm);

