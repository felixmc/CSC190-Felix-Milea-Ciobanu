#ifndef _DRAWVALUE_H_
#define _DRAWVALUE_H_

#include "Core.h"
#include "Vector2.h"
#include "Matrix3.h"
#include <sstream>
#include <cmath>
#include <string>

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

	void drawValue(Core::Graphics& g, int x, int y, Matrix3 m) {
		stringstream ss;
		int xSpace = 100;
		int ySpace = 25;

		drawValue(g, x, y, m.x1); drawValue(g, x + xSpace, y, m.x2); drawValue(g, x + xSpace + xSpace, y, m.x3);
		drawValue(g, x, y + ySpace, m.y1); drawValue(g, x + xSpace, y + ySpace, m.y2); drawValue(g, x + xSpace + xSpace, y + ySpace, m.y3);
		drawValue(g, x, y + ySpace + ySpace, m.z1); drawValue(g, x + xSpace, y + ySpace + ySpace, m.z2); drawValue(g, x + xSpace + xSpace, y + ySpace + ySpace, m.z3);

		g.DrawString( x, y, ss.str().c_str());
	}


}

#endif