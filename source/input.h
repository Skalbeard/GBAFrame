/*
Input class.
 */

#include <stdint.h>
#include "gba.h"

#ifndef INPUT_H
#define DRAWABLE_H

class Input
{
	private:
		struct InputState
		{
			int xdir;
			int ydir;
		};
		InputState CurrentInput;
		
	
	public:
		Input() {};
		void UpdateInput();
		InputState GetInput();
		void ResetInput();
};

#endif
