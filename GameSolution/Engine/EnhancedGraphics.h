#ifndef _ENHANCED_GRAPHICS_H_
#define _ENHANCED_GRAPHICS_H_

#include "Core.h"
#include "Vector2.h"
#include <cmath>

using Core::Graphics;

namespace Engine {

	class EnhancedGraphics {
		const int WIDTH, HEIGHT;
		int* bitmapBuffer;
		int curColor;
		bool hasChanged;

		void swap(float& f1, float& f2) {
			float temp = f1;
			f1 = f2;
			f2 = temp;
		}

		void swap(int& f1, int& f2) {
			int temp = f1;
			f1 = f2;
			f2 = temp;
		}

		inline void clearBuffer() {
			std::fill(bitmapBuffer, bitmapBuffer + WIDTH*HEIGHT, 0);
		}

		inline void plot(Graphics& g, Vector2 p) {
			g.DrawLine(p.x, p.y, p.x+1, p.y+1);
		}

		inline int coord(int x, int y) {
			return (y * WIDTH) + x;
		}

		inline int coord(Vector2 v) {
			return coord((int)v.x,(int)v.y);
		}

		void operator=(EnhancedGraphics e) { e; }

		void inline change() {
			if (!hasChanged) {
				clearBuffer();
				hasChanged = true;
			}
		}

		void inline resetChanges() {
			hasChanged = false;
		}

	public:
		EnhancedGraphics(int w, int h) : WIDTH(w), HEIGHT(h) {
			bitmapBuffer = new int[WIDTH * HEIGHT];
			curColor = RGB(255,255,255);
		}

		void draw(Graphics& g) {
			if (!hasChanged)
				return;

			resetChanges();

			for (int y = 0; y < HEIGHT; y++) {
				for (int x = 0; x < WIDTH; x++) {

					g;
					int color = bitmapBuffer[coord(x,y)];
					if (color != 0) {
						g.SetColor(bitmapBuffer[coord(x,y)]);
						plot(g, Vector2((float)x, (float)y));
					}
				}
			}

			g.SetColor(RGB(255,255,255));
		}

		inline void drawPoint(Vector2 p) {
			if (bitmapBuffer[coord(p)] != curColor) {
				bitmapBuffer[coord(p)] = curColor;
				change();
			}
		}

		inline void setColor(int c) {
			curColor = c;
		}

		void drawLine(Vector2 p1, Vector2 p2) {
			int x0 = (int)p1.x;
			int x1 = (int)p2.x;
			int y0 = (int)p1.y;
			int y1 = (int)p2.y;
			bool isInOrder = x0 <= x1;
			if (!isInOrder) {
				swap(x0,x1);
				swap(y0,y1);
			}

			bool steep = abs(y1 - y0) > abs(x1 - x0);
			if (steep) {
				swap(x0, y0);
				swap(x1, y1);
			}
			if (x0 > x1) {
				swap(x0, x1);
				swap(y0, y1);
			}
			int deltax = x1 - x0;
			int deltay = abs(y1 - y0);
			int error = deltax / 2;
			int ystep;
			int y = y0;
			if (y0 < y1)
				ystep = 1;
			else
				ystep = -1;

			for (int x = x0; x < x1; x++) {
				if (steep) 
					drawPoint(Vector2((float)y,(float)x));
				else
					drawPoint(Vector2((float)x,(float)y));
				error = error - deltay;
				if (error < 0) {
					y = y + ystep;
					error = error + deltax;
				}
			}
		}

	};

}

#endif