#ifndef _ENGINE_TIMER_H_
#define _ENGINE_TIMER_H_

#include <windows.h>
#include "Core.h"

//typedef union _LARGE_INTEGER {
//	struct {
//		DWORD LowPart;
//		LONG HighPart;
//	 };
//	 LONGLONG QuadPart; 
//} LARGE_INTEGER;

namespace Engine {

	//class Timer {

	//	typedef struct {
	//		LARGE_INTEGER start;
	//		LARGE_INTEGER interval;
	//		LARGE_INTEGER stop;
	//	 } stopWatch;

	//	stopWatch timer;
	//	LARGE_INTEGER frequency;

	//	inline float toSec(LARGE_INTEGER& L) const {
	//		return (float)((double)L.QuadPart /(double)frequency.QuadPart);
	//	}

	//public:
	//	Timer() {
	//		timer.start.QuadPart = 0;
	//		timer.stop.QuadPart = 0;
	//		timer.interval.QuadPart = 0;
	//		QueryPerformanceFrequency(&frequency) ;
	//	}

	//	void start() {
	//		QueryPerformanceCounter(&timer.start) ;
	//		timer.interval = timer.start;
	//	}

	//	float stop() {
	//		LARGE_INTEGER now;
	//		QueryPerformanceCounter(&now);
	//		LARGE_INTEGER result;
	//		result.QuadPart = (now.QuadPart - timer.start.QuadPart);
	//		return toSec(result);
	//	}

	//	float elapsed() {
	//		LARGE_INTEGER now;
	//		QueryPerformanceCounter(&now);
	//		LARGE_INTEGER result;
	//		result.QuadPart = (now.QuadPart - timer.start.QuadPart);
	//		return toSec(result);
	//	}

	//	float intervalElapsed() {
	//		LARGE_INTEGER now;
	//		QueryPerformanceCounter(&now);
	//		LARGE_INTEGER result;
	//		result.QuadPart = (now.QuadPart - timer.interval.QuadPart);
	//		return toSec(result);
	//	}

	//	float interval() {
	//		LARGE_INTEGER now;
	//		QueryPerformanceCounter(&now);
	//		LARGE_INTEGER result;
	//		result.QuadPart = (now.QuadPart - timer.interval.QuadPart);
	//		timer.interval = now;
	//		return toSec(result);
	//	}
	//};

	class Timer {
		ULONGLONG startTime;
		ULONGLONG intervalTime;

	public:
		void start() {
			startTime = GetTickCount64();
			intervalTime = startTime;
		}

		float stop() {
			ULONGLONG now = GetTickCount64();
			return (float)(now - startTime);
		}

		float elapsed() const {
			ULONGLONG now = GetTickCount64();
			return (float)(now - startTime);
		}

		float intervalElapsed() const {
			ULONGLONG now = GetTickCount64();
			return (float)(now - intervalTime);
		}

		float interval() {
			ULONGLONG now = GetTickCount64();
			float result = (float)(now - intervalTime);
			intervalTime = now;
			return result;
		}

	};
}

#endif