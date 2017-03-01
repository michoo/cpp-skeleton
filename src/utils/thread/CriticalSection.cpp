#include "CriticalSection.h"
#include "../Common.h"

CriticalSection::CriticalSection()
{
	int val = pthread_mutex_init(&m_handle, NULL);
	if (val != 0)
	{
		throw BasicException("Error initializing mutex: " + errorToString(val));
	}
}


CriticalSection::~CriticalSection()
{
	int val = pthread_mutex_destroy(&m_handle);
	if (val != 0)
	{
		throw BasicException("Error destroying mutex: " + errorToString(val));
	}
}

void CriticalSection::enter(const std::string& name)
{
	int val = pthread_mutex_lock(&m_handle);
	if (val != 0)
	{
		throw BasicException("Error locking mutex: " + errorToString(val));
	}
}

void CriticalSection::enter()
{
	int val = pthread_mutex_lock(&m_handle);
	if (val != 0)
	{
		throw BasicException("Error locking mutex: " + errorToString(val));
	}
}

void CriticalSection::leave()
{
	int val = pthread_mutex_unlock(&m_handle);
	if (val != 0)
	{
		throw BasicException("Error unlocking mutex: " + errorToString(val));
	}
}

std::string CriticalSection::errorToString(int error)
{
	std::string message;
	switch (error)
	{
	case EINVAL:
		message = "EINVAL";
		break;

	case EBUSY:
		message = "EBUSY";
		break;

	case EAGAIN:
		message = "EAGAIN";
		break;

	case EDEADLK:
		message = "EDEADLK";
		break;

	case EPERM:
		message = "EPERM";
		break;

	case EINTR:
		message = "EINTR";
		break;

	default:
		message = "UNKNOWN";
		break;
	}

	return message;
}

