#ifndef _ENGINE_ASSERT_H_
#define _ENGINE_ASSERT_H_

#include "Logger.h"
#include "Profiler.h"

#if ASSERT_ON
#define ASSERTM(c,msg) Engine::Assert::makeAssert(c,msg,__FILE__,__LINE__);
#define ASSERT(c) Engine::Assert::makeAssert(c,"An assertion has failed.",__FILE__,__LINE__);
#else
#define ASSERTM(c,msg)
#define ASSERT(c)
#endif

namespace Engine {

	struct ENGINE_SHARED Assert {

		static void makeAssert(bool condition, char* msg, char* file, int line) {
			if (!condition) {
				Engine::Logger::Log(Severe,msg,file,line);
				LOG_SAVE
				PROFILER_SAVE
				exit(1);
			}
		}

	};

}

#endif