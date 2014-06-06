#ifndef _ENHANCED_GRAPHICS_H_
#define _ENHANCED_GRAPHICS_H_

#include "Core.h"
#include "Vector2.h"
#include "Color.h"
#include "GraphicsFilter.h"
#include "Timer.h"
#include <cmath>
#include <string>
#include <vector>

using Core::Graphics;
using std::vector;

namespace Engine {

	class EnhancedGraphics {
		const int WIDTH, HEIGHT;
		int* bitmapBuffer;
		int curColor;
		bool hasChanged;
		Timer timer;
		//vector<Vector2> * changes;

		inline void swap(float& f1, float& f2) const {
			float temp = f1;
			f1 = f2;
			f2 = temp;
		}

		inline void swap(int& f1, int& f2) const {
			int temp = f1;
			f1 = f2;
			f2 = temp;
		}

		inline void clearBuffer() {
			std::fill(bitmapBuffer, bitmapBuffer + WIDTH*HEIGHT, 0);
		}

		inline void plot(Graphics& g, const Vector2& p) {
			g.DrawLine(p.x, p.y, p.x+1, p.y+1);
		}

		void operator=(EnhancedGraphics e) { e; }

		inline void change() {
			if (!hasChanged) {
				clearBuffer();
				hasChanged = true;
			}
		}

		inline void resetChanges() {
			hasChanged = false;
			//changes->clear();
		}

		inline bool isOnScreen(const Vector2& p) const {
			return p.x >= 0 && p.x < WIDTH && p.y >= 0 && p.y < HEIGHT;
		}

	public:
		EnhancedGraphics(int w, int h) : WIDTH(w), HEIGHT(h) {
			bitmapBuffer = new int[WIDTH * HEIGHT];
			curColor = RGB(255,255,255);
			timer.start();
			//changes = new vector<Vector2>();
		}

		//inline void draw(Graphics& g, GraphicsFilter& gf) {
		//	gf.filter(bitmapBuffer, WIDTH, HEIGHT);
		//	draw(g);
		//}

		inline void draw(Graphics& g, GraphicsFilter& gf) {
			int count = 0;

			//for (unsigned int i = 0; i < changes->size(); i++) {
			//	Vector2 p = changes->at(i);
			//	int color = bitmapBuffer[((int)p.y * WIDTH) + (int)p.x];

			//	if (color != 0) {
			//		g.SetColor(color);
			//		gf;
			//		//g.SetColor(x < WIDTH / 10 && y < HEIGHT / 3 ? gf.filterPx(color) : color);
			//		plot(g, p);
			//		count++;
			//	}
			//}

			for (int y = 0; y < HEIGHT; y++) {
				for (int x = 0; x < WIDTH; x++) {
					int color = bitmapBuffer[(y * WIDTH) + x];

					if (color != 0) {
						g.SetColor(color);
						gf;
						//g.SetColor(x < WIDTH / 10 && y < HEIGHT / 3 ? gf.filterPx(color) : color);
						plot(g, Vector2((float)x, (float)y));
						count++;
					}
				}
			}

			float time = timer.interval();
			int frames = (int)floorf(1.0f / time);


			g.SetColor(RGB(255,255,255));
			g.DrawString(20,HEIGHT - 65,std::to_string(frames).c_str());
			g.DrawString(20,HEIGHT - 45,std::to_string((int)(time * 1000)).c_str());
			g.DrawString(20,HEIGHT - 25,std::to_string(count).c_str());

			g.SetColor(RGB(255,155,0));
			g.DrawString(60,HEIGHT - 65,"fps");
			g.DrawString(60,HEIGHT - 45,"ms/frame");
			g.DrawString(60,HEIGHT - 25,"px/frame");

			g.SetColor(RGB(255,255,255));
			resetChanges();
		}

		void drawBitmap(const Vector2& start, int width, int height, int* data) {
			for (int y = 0; y < height; y++) {
				for (int x = 0; x < width; x++) {
					setColor(data[(y * width) + x]);
					drawPoint(start + Vector2((float)x,(float)y));
				}
			}
		}

		inline void drawPoint(const Vector2& p) {
			if (isOnScreen(p)) {
				float a = (255 - GetAValue(curColor)) / 255.0f;

				if (a != 0) {
					int coor = ((int)p.y * WIDTH) + (int)p.x;
					int c = bitmapBuffer[coor];
					float na = 1 - a;

					bitmapBuffer[coor] = RGB(
						min((GetRValue(c) * na) + (GetRValue(curColor) * a),255),
						min((GetGValue(c) * na) + (GetGValue(curColor) * a),255),
						min((GetBValue(c) * na) + (GetBValue(curColor) * a),255)
						);

					//if (c == 0)
						//changes->push_back(p);
					
					change();
				}
			}
		}

		inline void setColor(const int& c) {
			curColor = c;
		}

		void drawLine(const Vector2& p1, const Vector2& p2) {
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