#ifndef _ENGINE_PROFILER_H_
#define _ENGINE_PROFILER_H_

#if PROFILING_ON
#include <cassert>
#include <fstream>
#include <ctime>
#include <cstring>
#endif

namespace Engine {

	class Profiler {
		Profiler() {}
		Profiler(const Profiler&);
		Profiler& operator=(const Profiler&);
		static Profiler instance;
#if PROFILING_ON
		static const unsigned int MAX_FRAME_SAMPLES = 1000;
		static const unsigned int MAX_PROFILE_CATEGORIES = 20;
		const char* file;
		int frameIndex;
		unsigned int categoryIndex;
		unsigned int numUsedCategories;

		std::ofstream fileStream;

		struct ProfileCategory {
			const char* name;
			float samples[MAX_FRAME_SAMPLES];
		} categories[MAX_PROFILE_CATEGORIES];

		void writeFrame(unsigned int frame) {
			for (unsigned int cat = 0; cat < numUsedCategories; cat++) {
				fileStream << categories[cat].samples[frame];
				fileStream << (cat + 1 < numUsedCategories ? ',' : '\n');
			}
		}

#endif
	public:
		static Profiler& getInstance() {
			return instance;
		}
#if PROFILING_ON
		void addEntry(const char* categoryName, float time) {
			categoryName;
			time;
			ProfileCategory& pc = categories[categoryIndex++];

			if (frameIndex == 0) {
				pc.name = categoryName;
				numUsedCategories++;
			} else {
				//assert(categoryName == pc.name && categoryName != NULL);
				//assert(categoryIndex < numUsedCategories);
			}

			pc.samples[frameIndex % MAX_FRAME_SAMPLES] = time;
		}

		void newFrame() {
			if (frameIndex > 0) {
				assert(categoryIndex == numUsedCategories);
			}

			frameIndex++;
			categoryIndex = 0;
		}

		void initialize(const char* filename) {
			file = filename;
			frameIndex = -1;
			categoryIndex = 0;
			numUsedCategories = 0;
		}
		
		void shutdown() {
			//time_t rawtime;
			//struct tm * timeinfo = 0;
			//char filename [80];

			//time (&rawtime);
			//localtime_s(timeinfo,&rawtime);

			//strftime(filename,80," %m-%d-%Y %H:%M:%S.csv",timeinfo);
			char filename[80];
			strcpy_s(filename,80,file);
			strcat_s(filename,80,".csv");
			fileStream.open(filename);

			for (unsigned int i = 0; i < numUsedCategories; i++) {
				fileStream << categories[i].name;
				fileStream << (i + 1 < numUsedCategories ? ',' : '\n');
			}

			bool wrapped = frameIndex >= MAX_FRAME_SAMPLES && frameIndex != -1;
			unsigned int startIndex, endIndex;
			
			if (wrapped) {
				endIndex = frameIndex % MAX_FRAME_SAMPLES;
				startIndex = (endIndex + 1) % MAX_FRAME_SAMPLES;
				while (startIndex != endIndex) {
					writeFrame(startIndex);
					startIndex = (startIndex + 1) % MAX_FRAME_SAMPLES;
				}
				if (categoryIndex == numUsedCategories)
					writeFrame(startIndex);
			} else {
				unsigned int numActualFrames = frameIndex;
				if (categoryIndex == numUsedCategories)
					numActualFrames++;
				startIndex = 0;
				endIndex = numActualFrames;
				while (startIndex < endIndex)
					writeFrame(startIndex++);
			}

			fileStream.close();
		}
#else
		void addEntry(const char* categoryName, float time) {time;categoryName;}
		void newFrame() {}
		void initialize(const char* filename) {filename;}
		void shutdown() {}
#endif
	};

}

#define PROFILER Profiler::getInstance()

#endif