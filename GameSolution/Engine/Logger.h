#ifndef _ENGINE_LOGGER_H_
#define _ENGINE_LOGGER_H_

#include "ExportHeader.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using std::vector;
using std::string;

namespace Engine {

	enum ENGINE_SHARED Severity { Info, Warning, Error, Severe };

#ifdef LOGGING
#define LOG( severity, message) Logger::Log( severity, message, __FILE__, __LINE__ );
#define SAVE_LOG Logger::shutDown();
#else
	#define LOG( severity, message)
	#define SAVE_LOG
#endif

#pragma warning ( disable : 4100)

	class ENGINE_SHARED Logger {
	public:
		Logger(void);
		~Logger(void);
		static void StringReplace(string& str, const string& from, const string& to);
		static string Sanitize(string str);
		static void Log( Severity severity, const char* message, const char * logFile, int logLine);
		static void shutDown();

	private:
		static void WriteFile();
	};

#pragma warning ( default : 4100)

}

#endif