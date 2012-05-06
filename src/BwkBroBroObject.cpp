/**
 * @file    BwkMarbleObject.cpp
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

#include "boost/foreach.hpp"

#include "BwkBroBroObject.hpp"
#include "BwkObject.hpp"
#include "BwkPlayer.hpp"
#include "BwkLevel.hpp"
	
/**
 * CTOR
 */
BwkBroBroObject::BwkBroBroObject(BwkLevel * level)
: BwkObject( level, BROBRO )
{
	// Start in the down direction so we see BroBro's face
    setImage(BwkSlots::BWK_BMP_BROBRO_DOWN);
	setPushStrength(HEAVY_PUSH);
	setPushResistance(NO_PUSH);	
}

/**
 *  Walk towards the player when Bwock and this BroBro are parallel.
 */
void BwkBroBroObject::act()
{
	// If already moving, make sure this BroBro is animating
	if( isMoving() ) 
	{
		if( !isAnimating() ) 
		{
			beginAnimation(20);
		}		
	}
	// If not moving, evaluate whether we should
	else 
	{
		// Stop any animation that may be going on
		if( isAnimating() ) 
		{
			stopAnimation();
		}
		// Never follow the Bwock if he's flying
		if(_level->player()->flying()) 
		{
			return;
		}
		// Handle the player being aligned on the X axis
		if( _level->player()->x() == x() ) 
		{
			if( _level->player()->y() < y() ) 
			{
				setImage(BwkSlots::BWK_BMP_BROBRO_UP);
				goDir(UP_DIR);
			}
			else 
			{
				setImage(BwkSlots::BWK_BMP_BROBRO_DOWN);			
				goDir(DOWN_DIR);
			}
		}
		// Handle the player being aligned on the Y axis		
		else if( _level->player()->y() == y() ) 
		{
			if( _level->player()->x() < x() ) 
			{
				setImage(BwkSlots::BWK_BMP_BROBRO_LEFT);
				goDir(LEFT_DIR);
			}
			else 
			{
				setImage(BwkSlots::BWK_BMP_BROBRO_RIGHT);
				goDir(RIGHT_DIR);
			}
		}		
	}
}

