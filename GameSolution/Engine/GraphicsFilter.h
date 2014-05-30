#ifndef _ENGINE_GRAPHICS_FILTER_H_
#define _ENGINE_GRAPHICS_FILTER_H_

namespace Engine {

	struct GraphicsFilter {
		virtual void filter(int* buffer, const int w, const int h) = 0;
		virtual int filterPx(int px) = 0;
	};

}

#endif