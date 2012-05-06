/**
 * @file    BwkBoulderObject.cpp
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

#include "BwkBoulderObject.hpp"
#include "BwkLevel.hpp"
#include "BwkPlayer.hpp"

/**
 *  CTOR
 */
BwkBoulderObject::BwkBoulderObject(BwkLevel * level)
: BwkObject( level, BOULDER )
{
    setImage(BwkSlots::BWK_IMG_BOULDER);
	setPushStrength(NO_PUSH);
	setPushResistance(HEAVY_PUSH);	
}

/**
 *  This function is overloaded to handle an annoying bug. A boulder can be pushed onto a
 *  water tile to make a bridge, but if it is pushed between two water tiles, the 'cover' 
 *  event cannot trigger. There's no elegant way to handle this, so we simply won't allow it.
 */
bool BwkBoulderObject::push(BwkObject * other, direction_flag_t dir)
{
    int count = 0;  // How many un-bridged water tiles are blocking
	
	// Push events should never go through if the object is moving
    if( isMoving() ) 
	{
        return false;
    }

    // Count up water tiles blocking in the attempted direction
    BOOST_FOREACH(BwkObject * obj, _level->allObjects()) 
	{
        if( blocked(dir, obj) && (obj->type() == WATER) && !(obj->unblockedObjects() & PLAYER) ) 
		{
            count ++;
        }
    }

    // If two or more waters were found, resist the push
    if( count >= 2 ) 
	{
        return false;
    }
    // Otherwise, proceed as usual
    else 
	{
        return BwkObject::push(other, dir);
    }
}

