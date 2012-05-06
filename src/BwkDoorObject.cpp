/**
 * @file    BwkDoorObject.cpp
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
#include "BwkDoorObject.hpp"
#include "BwkWallObject.hpp"
#include "BwkPlayer.hpp"
#include "BwkManager.hpp"
#include "BwkLevel.hpp"

/**
 *  CTOR
 */
BwkDoorObject::BwkDoorObject(BwkLevel * level)
: BwkObject(level, DOOR)
{
    setImage(BwkSlots::BWK_BMP_DOOR);
    _isOpen = false;
}

/**
 *  When this is called, the door opens,setting the image frame to 1.
 */
void BwkDoorObject::open()
{
    setFrame(1);
	BwkManager::instance()->playSound(BwkSlots::BWK_SOUND_PUSH);
    _isOpen = true;
}

/**
 *  The play area is not exactly where doors goe. Calling reposition moves the door
 *  out to the perimeter of the level, and deletes any wall it encounters.
 */
void BwkDoorObject::reposition()
{
    // Try to put the door along the perimeter of the level depending on its location.
    // This favors the top and bottom perimeter.
    if( y() == (int)( _level->yOffset() + ( _level->tileSize() * _level->mapHeight() ) ) ) {
        setPosition( x(), y() + _level->tileSize() );
    }
    else if( x() == (int)(_level->xOffset()) ) {
        setPosition( x() - _level->tileSize(), y() );
    }
    else if( x() == (int)(_level->xOffset() + (_level->tileSize() * (_level->mapWidth()-1) ) ) ) {
        setPosition( x() + _level->tileSize(), y() );
    }
    else {
        setPosition( x(), _level->yOffset() - _level->tileSize() );
    }

    // Delete any walls underneath
    BOOST_FOREACH( BwkWallObject * wall, _level->allWalls() ) {
         if( wall->x() == x() && wall->y() == y() ) {
			 _level->addToDeathRow(wall);
        }
    }
}

/**
 *  Sets victory for the player instantly, since it has to be open for Bwock to enter it.
 */
void BwkDoorObject::cover(BwkObject * other)
{
    if( other == _level->player() ) {
        _level->player()->win();
    }
}

