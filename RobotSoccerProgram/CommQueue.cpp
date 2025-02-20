#include "StdAfx.h"
#include "CommQueue.h"


CCommQueue::CCommQueue(void)
{
	Clear();
}


CCommQueue::~CCommQueue(void)
{
}

// Queue reset
void CCommQueue::Clear()
{
	m_iHead = m_iTail = 0;
	memset(buff, 0, BUFF_SIZE);
}

// get Queue size.
int CCommQueue::GetSize()
{
	return (m_iHead - m_iTail + BUFF_SIZE) % BUFF_SIZE;
}

// Queue put 1 byte into Queue.
BOOL CCommQueue::PutByte(BYTE b)
{
	// Queue checking whether the q is full
	if (GetSize() == (BUFF_SIZE-1)) return FALSE;
	buff[m_iHead++] = b;
	m_iHead %= BUFF_SIZE;
	return TRUE;
}

// Queue¿¡¼­ 1 byte pop.
BOOL CCommQueue::GetByte(BYTE* pb)
{
	// check empty for Queue
	if (GetSize() == 0) return FALSE;
	*pb = buff[m_iTail++];
	m_iTail %= BUFF_SIZE;
	return TRUE;
}
