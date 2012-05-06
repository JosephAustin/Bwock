/**
 * @file    BwkWaterObject.cpp
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

#include "BwkWaterObject.hpp"
#include "BwkLevel.hpp"
#include "BwkSlots.hpp"
#include "BwkBoulderObject.hpp"
#include "BwkMarbleObject.hpp"
#include "BwkManager.hpp"

/**
 *  Constructor
 *
 *  @param level    Level this object belongs to
 */
BwkWaterObject::BwkWaterObject(BwkLevel * level)
: BwkObject(level, WATER)
{
    setImage( BwkSlots::BWK_IMG_WATER );
	_bridged = false;
}

void BwkWaterObject::cover(BwkObject * other)
{
	if( _bridged ) {
		return;
	}
	BwkBoulderObject * boulder = dynamic_cast<BwkBoulderObject*>(other) ;
	if( boulder ) {
		_level->addToDeathRow(boulder);
		setImage( BwkSlots::BWK_IMG_BOULDER_SUNK );
		_bridged = true;
		BwkManager::instance()->playSound(BwkSlots::BWK_SOUND_SPLASH);
	}
}

inline int BwkWaterObject::unblockedObjects()
{
    int flags = MARBLE | BOULDER | FASTATTACK;

    if( _bridged ) {
        flags |= PLAYER;
        flags |= PUSHER;
        flags |= SLOWATTACK;
    }

    return flags;
}

