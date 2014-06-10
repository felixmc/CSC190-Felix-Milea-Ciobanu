#ifndef _ENGINE_COLOR_H_
#define _ENGINE_COLOR_H_

#include "Core.h"
#include <cmath>

#define RGBA(r,g,b,a)			((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)|(((DWORD)(BYTE)(a))<<24)))
#define GetAValue(rgba)			(LOBYTE((rgba)>>24))
#define AFilter(c,a)			RGBA(GetRValue(c),GetGValue(c),GetBValue(c),a)
#define HSB(h,s,b)				Engine::Color::fromHSB(h,s,b,0)
#define HSBA(h,s,b,a)			Engine::Color::fromHSB(h,s,b,a)

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

		inline int fromHSB(int hi, int si, int vi, int alpha) {
			while (hi < 0) hi += 360;
			float s = si / 100.0f;
			float v = vi / 100.0f;
			float h = hi / 360.0f;
			float r = 0, g = 0, b = 0, f, p, q, t;
			int i = (int)floor(h * 6);
			f = (h * 6.0f) - i;
			p = v * (1.0f - s);
			q = v * (1.0f - f * s);
			t = v * (1.0f - (1.0f - f) * s);
			switch (i % 6) {
			case 0: r = v, g = t, b = p; break;
			case 1: r = q, g = v, b = p; break;
			case 2: r = p, g = v, b = t; break;
			case 3: r = p, g = q, b = v; break;
			case 4: r = t, g = p, b = v; break;
			case 5: r = v, g = p, b = q; break;
			}

			return RGBA(
				(int)floor(r * 255),
				(int)floor(g * 255),
				(int)floor(b * 255),
				alpha);

		}
	}
}

#endif