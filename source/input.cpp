#include "input.h"

void Input::UpdateInput()
{
	if ((REG_KEYINPUT & KEY_LEFT) == 0)
	{
		CurrentInput.xdir = -1;
	}
	
	else if ((REG_KEYINPUT & KEY_RIGHT) == 0)
	{
		CurrentInput.xdir = 1;
	}
	
	if ((REG_KEYINPUT & KEY_UP) == 0)
	{
		CurrentInput.ydir = -1;
	}
	
	else if ((REG_KEYINPUT & KEY_DOWN) == 0)
	{
		CurrentInput.ydir = 1;
	}
}

Input::InputState Input::GetInput()
{
	return CurrentInput;
}

void Input::ResetInput()
{
	CurrentInput.xdir = 0;
	CurrentInput.ydir = 0;
}