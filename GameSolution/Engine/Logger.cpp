#include "Logger.h"
#include <ctime>

using Engine::Logger;
using Engine::Severity;

vector <std::string> logList;
vector <Severity> severityList;

Logger::Logger(void) {}
Logger::~Logger(void) {}

void Logger::StringReplace(string& str, const string& from, const string& to) {
	size_t pos = 0;
	do  {
		pos = str.find(from, pos);
		if( pos != string::npos ) {
			str.replace( pos, from.length(), to);
			pos += to.length();
		}
	} while (pos != string::npos);
}

string Logger::Sanitize(string str) {
	StringReplace( str, ">" , "&lt" );
	StringReplace( str, "<" , "&gt" );

	return str;
}

void Logger::Log( Severity severity, const char* message, const char * logFile, int logLine) {
	std::stringstream ss;
	ss << "<h2><a href=\"" << logFile << "#" << logLine << "\"><span class=\"file\">" << logFile << "</span><span class=\"line\">"
	   << logLine << "</span></a></h2><p class=\"message\"><time data-timestamp=\"" << std::time(0) << "\"></time>" << Sanitize(message) << "</p>"; 
	std::string logEntry;
	logEntry = ss.str();
	
	logList.insert(logList.begin(), logEntry);
	severityList.insert(severityList.begin(), severity);
}

void Logger::shutDown() {
	WriteFile();
}

void Logger::WriteFile() {
	std::ofstream myFile("log.html");
	
	myFile << "<!DOCTYPE html>" << std::endl << "<html>" 
		<< std::endl << "<head>" << std::endl << "<title>Log File</title>" 
		<< std::endl << "<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\">"
		<< "</head>"
		<< std::endl << "<body>" << std::endl << "<div class=\"container\">";

	for(unsigned int i = 0; i < logList.size(); i ++) {
		char* severity = "";
		switch (severityList[i]) {
			case Info:
				severity = "info";
				break;
			case Warning:
				severity = "warning";
				break;
			case Error:
				severity = "error";
				break;
			case Severe:
				severity = "severe";
				break;
		}
		myFile << "<div class=\"log "<< severity << "\">" << std::endl
			   << logList[i].c_str() << "</div>";
	}
	myFile << "</div><script src=\"main.js\"></script></body>" << std::endl << "</html>";	
	myFile.close();
}