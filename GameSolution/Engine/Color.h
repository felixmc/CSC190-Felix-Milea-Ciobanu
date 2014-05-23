#ifndef _ENGINE_COLOR_H_
#define _ENGINE_COLOR_H_

#include "Core.h"
#include <cmath>

#define RGBA(r,g,b,a)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)|(((DWORD)(BYTE)(a))<<24)))
#define GetAValue(rgba)      (LOBYTE((rgba)>>24))

namespace Engine {
	namespace Color {
		const int RED	  = RGB(255,0,0);
		const int GREEN   = RGB(0,255,0);
		const int YELLOW  = RGB(255,255,0);
		const int CYAN    = RGB(0,255,255);
		const int CYAN2   = RGB(0,200,220);
		const int BLUE    = RGB(0,0,255);
		const int MAGENTA = RGB(255,0,128);
		const int ORANGE  = RGB(255,128,0);
		const int WHITE   = RGB(255,255,255);

		inline int interpolate(int c1, int c2, float mu) {
			mu = max(0,min(1,mu));
			int r = (int)(((1 - mu) * GetRValue(c1)) + (mu * GetRValue(c2)));
			int g = (int)(((1 - mu) * GetGValue(c1)) + (mu * GetGValue(c2)));
			int b = (int)(((1 - mu) * GetBValue(c1)) + (mu * GetBValue(c2)));
			int a = (int)(((1 - mu) * GetAValue(c1)) + (mu * GetAValue(c2)));
			return RGBA(r,g,b,a);
		}
	}
}

#endif