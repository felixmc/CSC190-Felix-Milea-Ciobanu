#include "WaveSound.h"
#include <string>

using Engine::WaveSound;

void WaveSound::play(char* file) {
	//f;
	//std::wstring soundfile(file);

	PlaySoundA(file, NULL, SND_FILENAME|SND_ASYNC);
}

//WaveSound::WaveSound(char * filename) {
//	ok = false;
//	buffer = 0;
//	HInstance = GetModuleHandle(0);
//
//	ifstream infile(filename, ios::binary);
//
//	if (!infile) {
//		return;
//	}
//
//	infile.seekg (0, ios::end);   // get length of file
//	int length = infile.tellg();
//	buffer = newtchar[length];    // allocate memory
//	infile.seekg (0, ios::beg);   // position to start of file
//	infile.read (buffer,length);  // read entire file
//
//	infile.close();
//	ok = true;
//}
//
//WaveSound::~WaveSound() {
//	PlaySound(NULL, 0, 0); // STOP ANY PLAYING SOUND
//	delete [] buffer;      // before deleting buffer.
//}
//
//void WaveSound::play(bool async) {
//	if (!ok)
//		return;
//
//	if (async)
//		PlaySound(buffer, HInstance, SND_MEMORY | SND_ASYNC);
//	else
//		PlaySound(buffer, HInstance, SND_MEMORY);
//}
//
//bool WaveSound::isok() {
//	return ok;
//}