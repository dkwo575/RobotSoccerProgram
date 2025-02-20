#pragma once

#define	BUFF_SIZE		4096 // Thread�� �θ� ���μ����� �����͸� �ְ� ���� ���� ũ��

class CCommQueue
{
public:
	BYTE	buff[BUFF_SIZE];        // Queue Buffer
	int		m_iHead, m_iTail;       // Queue Head Tail Position
	void	Clear();                // Queue�� ������ �����.       
	int		GetSize();              // Queue�� ��� �ִ� �������� ���̸� �����Ѵ�.
	BOOL	PutByte(BYTE b);		// Queue�� 1 byte �ֱ�.
	BOOL	GetByte(BYTE *pb);		// Queue�� 1 byte ������.

	CCommQueue(void);
	~CCommQueue(void);
};

