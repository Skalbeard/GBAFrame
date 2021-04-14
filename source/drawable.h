/*
Primitive drawable class for the pixel plotter.
 */

#include <stdint.h>
#include "gba.h"

#ifndef DRAWABLE_H
#define DRAWABLE_H

class Drawable
{
	private:
		int posx;
		int posy;
		int width;
		int height;
		int colour;
		int BGcol;
	
		bool CheckScreenEdge();
	
	public:
		Drawable(int _posx, int _posy, int _width, int _height, int _colour, int _BGcol)
			: posx(_posx), posy(_posy), width(_width), height(_height), colour(_colour), BGcol(_BGcol)
		{
		}
		
		void Draw();
		bool Move(int xdir, int ydir);
		void EraseTrace();
		void DrawCircle3(int xCenter, int yCenter, int radius, int color);
};

#endif
