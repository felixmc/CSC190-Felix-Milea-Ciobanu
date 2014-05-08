#ifndef _DRAWVALUE_H_
#define _DRAWVALUE_H_

#include "Core.h"
#include "Vector2.h"
#include <sstream>

using std::stringstream;

namespace Engine {

	void drawValue(Core::Graphics& g, int x, int y, int v) {
		stringstream ss;
		ss << v;
		g.DrawString( x, y, ss.str().c_str());
	}

	void drawValue(Core::Graphics& g, int x, int y, float v) {
		stringstream ss;
		ss << v;
		g.DrawString( x, y, ss.str().c_str());
	}
	
	void drawValue(Core::Graphics& g, int x, int y, Vector2 v) {
		stringstream ss;
		ss << v;
		g.DrawString( x, y, ss.str().c_str());
	}

}

#endif