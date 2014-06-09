#ifndef _ENGINE_PROFILER_H_
#define _ENGINE_PROFILER_H_

#include <fstream>
#include <ctime>
#include <cstring>

namespace Engine {

	class Profiler {
		Profiler() {}
		Profiler(const Profiler&);
		Profiler& operator=(const Profiler&);
		static Profiler instance;

		static const unsigned int MAX_FRAME_SAMPLES = 1000;
		static const unsigned int MAX_PROFILE_CATEGORIES = 20;
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

	public:
		static Profiler& getInstance() {
			return instance;
		}

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
				//assert(categoryIndex == numUsedCategories);
			}

			frameIndex++;
			categoryIndex = 0;
		}

		void initialize() {
			frameIndex = -1;
			categoryIndex = 0;
			numUsedCategories = 0;
		}

		void shutdown() {
			time_t rawtime;
			struct tm timeinfo;
			char buffer [80];

			time (&rawtime);
			localtime_s (&timeinfo,&rawtime);
			strftime (buffer,80,"data/profiler/%m-%d-%Y %H-%M-%S.csv",&timeinfo);

			fileStream.open(buffer);

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
	};

}

#if PROFILING_ON
#define PROFILER_SAVE Profiler::getInstance().shutdown();
#define PROFILER_FRAME Profiler::getInstance().newFrame();
#define PROFILER_INIT Profiler::getInstance().initialize();
#else
#define PROFILER_SAVE
#define PROFILER_FRAME
#define PROFILER_INIT
#endif

#endif