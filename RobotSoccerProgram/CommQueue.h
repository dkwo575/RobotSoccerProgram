#pragma once

#define	BUFF_SIZE		4096 // Thread와 부모 프로세스가 데이터를 주고 받을 버퍼 크기

class CCommQueue
{
public:
	BYTE	buff[BUFF_SIZE];        // Queue Buffer
	int		m_iHead, m_iTail;       // Queue Head Tail Position
	void	Clear();                // Queue의 내용을 지운다.       
	int		GetSize();              // Queue에 들어 있는 데이터의 길이를 리턴한다.
	BOOL	PutByte(BYTE b);		// Queue에 1 byte 넣기.
	BOOL	GetByte(BYTE *pb);		// Queue에 1 byte 꺼내기.

	CCommQueue(void);
	~CCommQueue(void);
};

