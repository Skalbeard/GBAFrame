#include "text.h"

// Draw text function.
void Text::DrawText(int x, int y, const char string[])
{
	for(unsigned int q = 0; q <= strlen(string); q++)
	{
		SetTile(31, x+q, y, string[q]);
	}
}