#include <stdint.h>
#include <stdlib.h>
#include "gba.h"
#include "drawable.h"
#include "input.h"
#include "tiles.h"
#include "font.h"
#include "text.h"


// The entry point for the game.
int main()
{
	// Set display options.
	// DCNT_MODE0 sets mode 0, which provides four tiled backgrounds.
	// DCNT_OBJ enables objects.
	// DCNT_OBJ_1D make object tiles mapped in 1D (which makes life easier).
	REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_BG1 | DCNT_BG2 | DCNT_BG3 | DCNT_OBJ | DCNT_OBJ_1D;
	
	// Set background 0 options.
	// BG_CBB sets the charblock base (where the tiles come from).
	// BG_SBB sets the screenblock base (where the tilemap comes from).
	// BG_8BPP uses 8bpp tiles.
	// BG_REG_32x32 makes it a 32x32 tilemap.
	REG_BG0CNT = BG_CBB(0) | BG_SBB(30) | BG_8BPP | BG_REG_32x32;
	
	// Set background 1 options.
	REG_BG1CNT = BG_CBB(0) | BG_SBB(29) | BG_8BPP | BG_REG_32x32;
	REG_BG1HOFS = 0;
	REG_BG1VOFS = 0;
	
	// Set background 2 options.
	REG_BG2CNT = BG_CBB(0) | BG_SBB(28) | BG_8BPP | BG_REG_32x32;
	REG_BG2HOFS = 0;
	REG_BG2VOFS = 0;
	
	// Set background 3 options.
	REG_BG3CNT = BG_CBB(0) | BG_SBB(27) | BG_8BPP | BG_REG_32x32;
	REG_BG3HOFS = 0;
	REG_BG3VOFS = 0;
	
	
	
	// Set up the object palette.
	SetPaletteObj(0, RGB(0, 0, 0)); // blank
	SetPaletteObj(1, RGB(0, 0, 0)); // black
	SetPaletteObj(2, RGB(31, 31, 31)); // white
	SetPaletteObj(3, RGB(31, 31, 0)); // yellow
	SetPaletteObj(4, RGB(31, 0, 0)); // red
	SetPaletteBG(0, RGB(0, 0, 0)); // blank
	SetPaletteBG(1, RGB(0, 0, 0)); // black
	SetPaletteBG(2, RGB(31, 31, 31)); // white
	SetPaletteBG(3, RGB(31, 31, 0)); // bright yellow
	SetPaletteBG(4, RGB(31, 0, 0)); // red
	SetPaletteBG(5, RGB(30, 0, 15)); // magenta
	SetPaletteBG(6, RGB(23, 3, 5)); // pink?
	SetPaletteBG(7, RGB(1, 4, 28)); // blueIhope
	SetPaletteBG(8, RGB(2, 25, 2)); // greenish
	SetPaletteBG(9, RGB(10, 10, 0)); // yellow?
	SetPaletteBG(10, RGB(31, 31, 31)); // white
	SetPaletteBG(11, RGB(20, 20, 31)); // pale blue (sky)
	SetPaletteBG(12, RGB(25, 25, 25)); // grey (cloud)
	SetPaletteBG(13, RGB(20, 10, 0)); // brown (brick)
	
	
	
	// Alphabet tile counter.
	int tile_num = 0;
	// Loads the font tile-map to charblock 1.
	for (tile_num = 0; tile_num < 129; tile_num++)
	{
		LoadTile8(1, tile_num, font_bold[tile_num]);
	}
	
	// Load the tile data above into video memory, putting it in charblock 0.
	LoadTile8(0, 1, sky_tile);
	LoadTile8(0, 2, cloud_tile);
	LoadTile8(0, 3, brick_tile);
	LoadTile8(0, 4, build_tile);
	LoadTile8(0, 5, blank_tile); // tile number 0 = blank
	LoadTile8(0, 6, red_box_tile); // tile number 1 = red box
	LoadTile8(0, 7, LSD_box_tile); // my own tile 2
	
	// Load the tiles for the objects into charblock 4.
	// (Charblocks 4 and 5 are for object tiles;
	// 8bpp tiles 0-255 are in CB 4, tiles 256-511 in CB 5.)
	LoadTile8(4, 1, LSD_box_tile);
	
	// set sky background and load cloud tiles
	for (int y = 0; y < 32; y++)
	{
		for (int x = 0; x < 32; ++x)
		{
			SetTile(27, x, y, 1);
		}
	}
	
	// clouds to screenblock 28.
	for (int cl = 0; cl < 24; cl++) // cloudcounter
	{
		int clx = rand()%32; // generates a random position x for the clouds between numbers 1-32
		int cly = rand()%14; // generates a random position y for the clouds between numbers 1-16
		SetTile(28, clx, cly, 2); // puts down the actual tiles in the above positions
	}
	
	// Make sure no objects are on the screen, but why should they be?
	ClearObjects();
	
	// Initial object parameters
	int smilex = 116;
	int smiley = 76;
	
	// Set up object 0 as a char in the middle of the screen.
	SetObject(0,
		ATTR0_SHAPE(0) | ATTR0_8BPP | ATTR0_REG | ATTR0_Y(smiley),
		ATTR1_SIZE(0) | ATTR1_X(smilex),
		ATTR2_ID8(1));
	
	SetObjectX(0, 1);
	SetObjectY(0, 1);
		
	// Input handle
	Input input;
	
	// Initialize a frame counter.
	int frames = 0;
	
	int curbgOffSetX = 0;
	int curbgOffSetY = 0;

	
	while (true)
	{
		frames++;
		
		Text::DrawText(22, 1, "Score:");
		
		input.UpdateInput();
		int dirx = input.GetInput().xdir;
		int diry = input.GetInput().ydir;
		input.ResetInput();
		
		
		if (diry != 0)
		{
			smiley += diry;
			SetObjectY(0, smiley);
		}
	
		if (dirx != 0)
		{
			smilex += dirx;
			SetObjectX(0, smilex);
		}
	
		if (smilex >= SCREEN_WIDTH - 9)
		{
			smilex = SCREEN_WIDTH - 9;
		}
	
		if (smilex <= 0 + 1)
		{
			smilex = 0 + 1;
		}
		
		if (smiley >= SCREEN_HEIGHT - 9)
		{
			smiley = SCREEN_HEIGHT - 9;
		}
		
		if (smiley <= 0 + 1)
		{
			smiley = 0 + 1;
		}
		
		WaitVSync();
		UpdateObjects();
	}
	
	return 0;
}

void DrawRandomCircles()
{
	//WaitVSync();
	//x = rand() % 240;
	//y = rand() % 160;
	//r = rand() % 50 + 10;
	//uint16_t color = RGB(rand()%31, rand()%31, rand()%31);
	//DrawCircle3(x, y, r, color);
	//WaitVSync();
}

/// BG scroll and screen register switch
/*
		//if ((REG_KEYINPUT & KEY_LEFT) == 0)
		//{
		//	if (curbgOffSetX > 0)
		//		curbgOffSetX--;
		//}
		//
		//else if ((REG_KEYINPUT & KEY_RIGHT) == 0)
		//{
		//	if (curbgOffSetX < SCREEN_WIDTH)
		//		curbgOffSetX++;
		//}
		//
		//if ((REG_KEYINPUT & KEY_UP) == 0)
		//{
		//	if (curbgOffSetY > 0)
		//		curbgOffSetY--;
		//}
		//
		//else if ((REG_KEYINPUT & KEY_DOWN) == 0)
		//{
		//	if (curbgOffSetY < SCREEN_HEIGHT)
		//		curbgOffSetY++;
		//}
		//
		//
		//REG_BG0HOFS = curbgOffSetX;
		//REG_BG0VOFS = curbgOffSetY;
		
		//if ((REG_KEYINPUT & KEY_A) == 0)
		//{
		//	REG_BG0CNT = BG_CBB(0) | BG_SBB(30) | BG_8BPP | BG_REG_32x32;
		//}
		//
		//else if ((REG_KEYINPUT & KEY_B) == 0)
		//{
		//	REG_BG0CNT = BG_CBB(0) | BG_SBB(31) | BG_8BPP | BG_REG_32x32;
		//}
*/