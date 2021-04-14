/*
Text functions.
 */
#include <string.h>
#include "gba.h"

#ifndef TEXT_H
#define TEXT_H

#include <stdint.h>
class Text
{
	public:
		static void DrawText(int x, int y, const char string[]);
		
	private:
};

#endif
