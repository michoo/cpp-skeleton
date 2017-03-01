
#ifndef OPENCV_TUTO_CRITICAL_H
#define OPENCV_TUTO_CRITICAL_H

#include "../Common.h"

class CriticalSection
{
public:
	CriticalSection();
	~CriticalSection();

	void enter();
	void enter(const std::string& name);
	void leave();
	
private:
	std::string errorToString(int error);
	CriticalSection(const CriticalSection& ) { /* NO COPYING */ }
	CriticalSection& operator = (const CriticalSection& ) { return * this; /* NO ASSIGNMENT */ }
	pthread_mutex_t m_handle;
};


#endif //OPENCV_TUTO_CRITICAL_H

