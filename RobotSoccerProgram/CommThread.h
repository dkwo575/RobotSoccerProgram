#pragma once

#include"CommQueue.h"

#define IN_BUFF_SIZE    2048 // ��� ��Ʈ ����� ���� ũ��
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

	//--------- ȯ�� ���� -----------------------------------------//
	HANDLE		m_hComm;				// ��� ��Ʈ ���� �ڵ�
	CString		m_sPortName;			// ��Ʈ �̸� (COM1 ..)
	BOOL		m_bConnected;			// ��Ʈ�� ���ȴ��� ������ ��Ÿ��.
	OVERLAPPED	m_osRead, m_osWrite;	// ��Ʈ ���� Overlapped structure
	HANDLE		m_hThreadWatchComm;		// Watch�Լ� Thread �ڵ�.
	WORD		m_wPortID;				// WM_COMM_READ�� �Բ� ������ �μ�.
										// �������� ��Ʈ�� ������ ��� � ��Ʈ���� 
	                                    // �ĺ��ϴ� �� ����Ѵ�.

	//--------- ��� ���� -----------------------------------------//
	CCommQueue	m_QueueRead;                // ������� �θ� ���μ������� ��� ����

	//--------- �ܺ� ��� �Լ� ------------------------------------//
	// �ø��� ��Ʈ�� ����. ���� : ��Ʈ��, String�� �ӵ�, ��Ʈ ��ȣ
	BOOL	OpenPort(CString sPortName, DWORD dwBaud, WORD wParam, BYTE parity, BYTE stopbits);
	// �ø��� ��Ʈ�� �ݴ´�.
	void	ClosePort();
	// �ø��� ��Ʈ�� �����͸� ����.
	DWORD	WriteComm(BYTE *pBuff, DWORD nToWrite);

	// comm port�� �ٽ� ����.	2002.5.9. ���� �߰�.
	void changeCOMMSET(int port, int bps);

	//--------- ���� ��� �Լ� ------------------------------------//
	// �����尡 �޼����� ������ ��� �� �Լ��� �̿��ؼ� �����͸� �д´�.
	DWORD	ReadComm(BYTE *pBuff, DWORD nToRead);

	void ClearPort();

};

DWORD ThreadWatchComm(CCommThread* pComm);

