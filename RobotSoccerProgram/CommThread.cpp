#include "StdAfx.h"
#include "CommThread.h"


CCommThread::CCommThread(void)
{
	m_hComm = NULL;
}


CCommThread::~CCommThread(void)
{
}




// open port sPortName at buadrate of dwBaud.
// if any thing read from function ThreadWatchComm  alert MainWnd
// ���� WM_COMM_READ�޽����� ������ ���� ���� wPortID���� ���� �޴´�.when send "wm...read" message receive the wportid value 
BOOL CCommThread::OpenPort(CString sPortName, DWORD dwBaud, WORD wPortID, BYTE parity, BYTE stopbits)
{
	// Local ����.variables
	COMMTIMEOUTS	timeouts;
	DCB				dcb;
//	DWORD			dwThreadID;

	// ���� �ʱ�ȭ 
	m_bConnected = FALSE;
	m_wPortID	= wPortID; // COM1-> 0, COM2->1,,,,,

	// overlapped structure ���� �ʱ�ȭ.
	m_osRead.Offset = 0;
	m_osRead.OffsetHigh = 0;
	if (! (m_osRead.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL)))	
		return FALSE;
	m_osWrite.Offset = 0;
	m_osWrite.OffsetHigh = 0;
	if (! (m_osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL)))
		return FALSE;
	
	// ��Ʈ ���� open port
	m_sPortName = sPortName;
	m_hComm = CreateFile( m_sPortName, 
		GENERIC_READ | GENERIC_WRITE, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 
		NULL);
	if (m_hComm == (HANDLE) -1){
		//MessageBox( NULL, _T("COM port error."), _T("comm Error!"), MB_ICONEXCLAMATION | MB_OK ) ;
		return FALSE;
	}

	// ��Ʈ ���� ����. setting port status

	// COM Port���� �߻��ϴ� �̺�Ʈ�� ����� �̺�Ʈ ���� chooseing events to use from generated events from com port
	// EV_RXCHAR event ����setting
	SetCommMask( m_hComm, EV_RXCHAR);	

	// InQueue, OutQueue ũ�� ����. size setting
	SetupComm( m_hComm, IN_BUFF_SIZE, OUT_BUFF_SIZE);	

	// ��Ʈ ����.erase port
	// TXABORT : Overlapped �����۾��� ���cancel overlapped transfer operations  RXABORT : Overlapped �����۾��� ��� cancel overlapped received oprations
	// TXCLEAR : ��� ���۸� Ŭ���� clear output buffer        RXCLEAR : �Է� ���۸� Ŭ���� input buffer clear
	PurgeComm( m_hComm,					
		PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR);

	// timeout ����.settings
	timeouts.ReadIntervalTimeout = 0xFFFFFFFF;
	timeouts.ReadTotalTimeoutMultiplier = 0;
	timeouts.ReadTotalTimeoutConstant = 0;
	timeouts.WriteTotalTimeoutMultiplier = 2*CBR_38400 / dwBaud;
	timeouts.WriteTotalTimeoutConstant = 0;
	SetCommTimeouts( m_hComm, &timeouts);

	//��Ʈ�� ���� �ӵ�, ������ ��Ʈ��, �и�Ƽ, ���� ��Ʈ��, XON/XOOF Flow Control����
	// dcb ����
	dcb.DCBlength = sizeof(DCB);
	GetCommState( m_hComm, &dcb);	// ���� ���� ����.
	dcb.BaudRate = dwBaud;
	dcb.ByteSize = 8;
//	dcb.Parity = 0;
	// 2002.5.4 �����̰� ����.
	dcb.Parity = parity;		// 0-4 = no, odd, even, mark, space

	dcb.StopBits = stopbits;
//	dcb.fInX = dcb.fOutX = 1;		// Xon, Xoff ���.
	// �����̰� ����. 2002.5.9.
	dcb.fInX = dcb.fOutX = 0;		// Xon, Xoff ���.
	dcb.XonChar = ASCII_XON;
	dcb.XoffChar = ASCII_XOFF;
	dcb.XonLim = 100;
	dcb.XoffLim = 100;
	if (! SetCommState( m_hComm, &dcb))	return FALSE;  // �� ����

	// ��Ʈ ���� ������ ����.
	m_bConnected = TRUE;
/*
	m_hThreadWatchComm = CreateThread( NULL, 0, 
		(LPTHREAD_START_ROUTINE)ThreadWatchComm, this, 0, &dwThreadID);
	if (! m_hThreadWatchComm)
	{
		MessageBox( NULL, "Failed to create event for thread!", "comm Error!",
                  MB_ICONEXCLAMATION | MB_OK ) ;
		ClosePort();
		return FALSE;
	}
*/
	return TRUE;
}
	
// ��Ʈ�� �ݴ´�.
void CCommThread::ClosePort()
{
	if( m_hComm == NULL ) return;

	m_bConnected = FALSE;
	SetCommMask( m_hComm, 0);
	PurgeComm( m_hComm,					
		PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR);
	CloseHandle( m_hComm);

	m_hComm = NULL;
}

void CCommThread::ClearPort()
{
	PurgeComm( m_hComm,					
		PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR);
}

// ��Ʈ�� pBuff�� ������ nToWrite��ŭ ����.
// ������ ������ Byte���� �����Ѵ�.
DWORD CCommThread::WriteComm(BYTE *pBuff, DWORD nToWrite)
{
	DWORD	dwWritten, dwError, dwErrorFlags;
	COMSTAT	comstat;

	if (! WriteFile( m_hComm, pBuff, nToWrite, &dwWritten, &m_osWrite))
	{
		if (GetLastError() == ERROR_IO_PENDING)
		{
			// ���� ���ڰ� ���� �ְų� ������ ���ڰ� ���� ���� ��� Overapped IO��
			// Ư���� ���� ERROR_IO_PENDING ���� �޽����� ���޵ȴ�.
			//timeouts�� ������ �ð���ŭ ��ٷ��ش�.
			while (! GetOverlappedResult( m_hComm, &m_osWrite, &dwWritten, TRUE))
			{
				dwError = GetLastError();
				if (dwError != ERROR_IO_INCOMPLETE)
				{
					ClearCommError( m_hComm, &dwErrorFlags, &comstat);
					break;
				}
			}
		}
		else
		{
			dwWritten = 0;
			ClearCommError( m_hComm, &dwErrorFlags, &comstat);
		}
	}

	return dwWritten;
}

// ��Ʈ�κ��� pBuff�� nToWrite��ŭ �д´�.
// ������ ������ Byte���� �����Ѵ�.
DWORD CCommThread::ReadComm(BYTE *pBuff, DWORD nToRead)
{
	DWORD	dwRead, dwError, dwErrorFlags;
	COMSTAT	comstat;

	//----------------- system queue�� ������ byte���� �̸� �д´�.
	ClearCommError( m_hComm, &dwErrorFlags, &comstat);
	dwRead = comstat.cbInQue;
	
	if (dwRead > 0)
	{
		if (! ReadFile( m_hComm, pBuff, nToRead, &dwRead, &m_osRead))
		{
			if (GetLastError() == ERROR_IO_PENDING)
			{
				//--------- timeouts�� ������ �ð���ŭ ��ٷ��ش�.
				while (! GetOverlappedResult( m_hComm, &m_osRead, &dwRead, TRUE))
				{
					dwError = GetLastError();
					if (dwError != ERROR_IO_INCOMPLETE)
					{
						ClearCommError( m_hComm, &dwErrorFlags, &comstat);
						break;
					}
				}
			}
			else
			{
				dwRead = 0;
				ClearCommError( m_hComm, &dwErrorFlags, &comstat);
			}
		}
	}

	return dwRead;
}

// ��Ʈ�� �����ϰ�, ���� ������ ������ 
// m_ReadData�� ������ �ڿ� MainWnd�� �޽����� ������ Buffer�� ������
// �о��� �Ű��Ѵ�.

DWORD	ThreadWatchComm(CCommThread* pComm)
{
	DWORD		dwEvent;
	OVERLAPPED	os;
	BOOL		bOk = TRUE;
	BYTE		buff[IN_BUFF_SIZE];	 // �б� ����
	DWORD		dwRead;	 // ���� ����Ʈ��.

	// Event, OS ����.
	memset( &os, 0, sizeof(OVERLAPPED));
	if (! (os.hEvent = CreateEvent( NULL, TRUE, FALSE, NULL)))
		bOk = FALSE;
	if (! SetCommMask( pComm->m_hComm, EV_RXCHAR))
		bOk = FALSE;
	if (! bOk)
	{
		AfxMessageBox(_T("Error while creating ThreadWatchComm, ") + pComm->m_sPortName);
		return FALSE;
	}

	// ��Ʈ�� �����ϴ� ����.
	while (pComm->m_bConnected)
	{
		dwEvent = 0;

		// ��Ʈ�� ���� �Ÿ��� �ö����� ��ٸ���.
		WaitCommEvent( pComm->m_hComm, &dwEvent, NULL);
		
		if ((dwEvent & EV_RXCHAR) == EV_RXCHAR)
		{
			// ��Ʈ���� ���� �� �ִ� ��ŭ �д´�.
			/*do	
			{
				dwRead = pComm->ReadComm( buff, IN_BUFF_SIZE);
				
				if (BUFF_SIZE - pComm->m_QueueRead.GetSize() > (int)dwRead)
				{
					for ( WORD i = 0; i < dwRead; i++)
						pComm->m_QueueRead.PutByte(buff[i]);
				}
				else
					AfxMessageBox("m_QueueRead FULL!");
			  
			} while (dwRead);*/

			dwRead = pComm->ReadComm( buff, IN_BUFF_SIZE);
				
				if (BUFF_SIZE - pComm->m_QueueRead.GetSize() > (int)dwRead)
				{
					for ( WORD i = 0; i < dwRead; i++)
						pComm->m_QueueRead.PutByte(buff[i]);
				}
				else
					//AfxMessageBox("m_QueueRead FULL!");
					pComm->m_QueueRead.Clear();
			//	�о� ������ �޽����� ������.
			if(dwRead){
			//::PostMessage(hCommWnd,WM_COMM_READ, pComm->m_wPortID, 0);}
				;
			}
			//SendMessage(hCommWnd, WM_COMM_READ, pComm->m_wPortID, 0);
			//::PostMessage(hCommWnd,WM_COMM_READ, pComm->m_wPortID, 0);
		}
	}	
	
	// ��Ʈ�� ClosePort�� ���� ������ m_bConnected �� FALSE�� �Ǿ� ����.

	CloseHandle(os.hEvent);
	pComm->m_hThreadWatchComm = NULL;

	return TRUE;
}

