#ifndef _INVERSE_FILTER_H
#define _INVERSE_FILTER_H

#include "GraphicsFilter.h"
#include "Vector2.h"
#include "Color.h"

namespace Engine {

	class InverseFilter : public GraphicsFilter {
		virtual void filter(int* buffer, const int w, const int h) {
			buffer;w;h;
			for (int i = 0; i < w * h; i++) {
				int c = buffer[i];
				buffer[i] = RGB(255-GetRValue(c),255-GetGValue(c),255-GetBValue(c));
			}
			/*for (int y = 0; y < h; y++) {
				for (int x = 0; x < w; x++) {
					int c = buffer[(y * w) + x];
					buffer[(y * w) + x] = RGB(255-GetRValue(c),255-GetGValue(c),255-GetBValue(c));
				}
			}*/
		}

		virtual inline int filterPx(int c) {
			return RGB(255-GetRValue(c),255-GetGValue(c),255-GetBValue(c));
			//return c;
		}
	};

}

#endif