/**
 * @file    BwkTiles.hpp
 * @author  Joseph Austin <joseph.the.austin@gmail.com>
 * @date    2010
 *
 * @section LICENSE
 *
 * "The Brave Bwock" is distributed under the MIT License.
 * Copyright (c) 2010 Joseph Austin
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */


#ifndef __BWK_TILES_DEFINED__
#define __BWK_TILES_DEFINED__

/**
 *  When reading in a level file, use this namespace as a dictionary for
 *  determining what each tile means based on the associated ASCII character.
 */
namespace BwkTiles
{
    const unsigned int MAX_TILE_SIZE = 50;      // Maximum default tile size

    // ITEMS AVAILABLE TO MULTIPLE LAYERS
    const char  TILE_BLANK          = '.';      // Blank spacer

    // ITEMS AVAILABLE TO TERRAIN LAYER ONLY
    const char  TILE_START          = 'S';      // Bwock Start Position
    const char	TILE_EXIT    	    = 'X';      // The Exit Door
    const char	TILE_WATER 	    	= '~';      // Water
    const char	TILE_LOW_WALL  	    = '*';      // Low Wall
    const char	TILE_HIGH_WALL 	    = '#';      // High Wall
    const char  TILE_WEEDS          = '%';      // Weeds

    //  ITEMS AVAILABLE TO OBJECT LAYER ONLY
    const char	TILE_SWITCH  	    = '/';      // Kill Switch
    const char	TILE_BOULDER 	    = '@';      // Boulder
    const char  TILE_MARBLE         = 'o';      // Marble
    const char  TILE_LEFT_PUSHER    = '<';      // Pusher for the left direction
    const char  TILE_RIGHT_PUSHER   = '>';      // Pusher for the right direction
    const char  TILE_UP_PUSHER      = '^';      // Pusher for the upwards direction
    const char  TILE_DOWN_PUSHER    = 'v';      // Pusher for the downwards direction
    const char  TILE_VERT_SLIDER    = '|';      // Vertical-Only slider
    const char  TILE_HORZ_SLIDER    = '-';      // Horizontal-Only slider
    const char	TILE_SPRING  	    = '&';      // Spring to initiate flight
    const char	TILE_WIZARD  	    = 'w';      // Wizard Rat Enemy
    const char	TILE_PUDDINI_HORZ   = 'p';      // Moving pudding monster (horizontal)
    const char	TILE_PUDDINI_VERT   = 'P';      // Moving pudding monster (vertical)
    const char	TILE_EYENAPPLE      = 'e';      // Eyenapples
    const char	TILE_UP_SCORCHER    = 'u';      // Scorcher facing up (north)
    const char	TILE_DOWN_SCORCHER  = 'n';      // Scorcher facing down (south)
    const char	TILE_RIGHT_SCORCHER = '(';      // Scorcher facing left
    const char	TILE_LEFT_SCORCHER  = ')';      // Scorcher facing right
	const char  TILE_BROBRO			= 'b';		// The brobro enemy
    const char	TILE_KEY     	    = '!';      // Collectable Key
};

#endif // __BWK_TILES_DEFINED__

