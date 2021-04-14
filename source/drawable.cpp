#include "drawable.h"

bool Drawable::CheckScreenEdge()
{
	bool result = false;
	
	// Defining borders of the screen
	if (posx > (SCREEN_WIDTH - 7))
	{
		result = true;
	}
	else if (posx < 1)
	{
		result = true;
	}
	else if (posy > (SCREEN_HEIGHT - 8))
	{
		result = true;
	}
	else if (posy < 1)
	{
		result = true;
	}
	
	return result;
}

void Drawable::Draw()
{
	for (int x = posx; x < posx + width; x++)
	{
		for (int y = posy; y < posy + height; y++)
		{
			PlotPixel8(x, y, colour);
		}
	}
}

bool Drawable::Move(int xdir, int ydir)
{
	if (!CheckScreenEdge())
	{
		posx += xdir;
		posy += ydir;
		return true;
	}
	return false;
}

void Drawable::EraseTrace()
{
	for (int x = posx - 5; x < posx + (width + 5); x++)
	{
		for (int y = posy - 5; y < posy + (height + 5); y++)
		{
			PlotPixel8(x, y, BGcol);
		}
	}
}

/////////////////////////////////////////////////////////////
// Function: DrawCircle3
// Bresenham's infamous circle algorithm
/////////////////////////////////////////////////////////////
void Drawable::DrawCircle3(int xCenter, int yCenter, int radius, int color)
{
	int x = 0;
	int y = radius;
	int p = 3 - 2 * radius;
	while (x <= y)
	{
		PlotPixel16(xCenter + x, yCenter + y, color);
		PlotPixel16(xCenter - x, yCenter + y, color);
		PlotPixel16(xCenter + x, yCenter - y, color);
		PlotPixel16(xCenter - x, yCenter - y, color);
		PlotPixel16(xCenter + y, yCenter + x, color);
		PlotPixel16(xCenter - y, yCenter + x, color);
		PlotPixel16(xCenter + y, yCenter - x, color);
		PlotPixel16(xCenter - y, yCenter - x, color);
		if (p < 0)
			p += 4 * x++ + 6;
		else
			p += 4 * (x++ - y--) + 10;
	}
}