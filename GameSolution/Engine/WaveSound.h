#ifndef _WAV_SOUND_H_
#define _WAV_SOUND_H_

#include "ExportHeader.h"
#include <windows.h>
#include <mmsystem.h>

namespace Engine {

	struct ENGINE_SHARED WaveSound {
		//WaveSound(char * filename);
		//~WaveSound();
		//void play(bool async=true);
		//bool isok();
		static void play(char*);

	//private:
	//	char * buffer;
	//	bool ok;
	//	HINSTANCE HInstance;
	};

}

#endif