/**
 * @file    BwkWallObject.cpp
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
#include "BwkWallObject.hpp"
#include "BwkLevel.hpp"
#include "BwkSlots.hpp"
/**
 *  Constructor
 *
 *  @param level    Level this object belongs to
 *  @param type     Type of wall this is
 */
BwkWallObject::BwkWallObject(BwkLevel * level, wallType type )
: BwkObject(level, WALL )
{
    if( type == HIGH_WALL ) {
        if( rand() % 100 < 25 ) {
            setImage(BwkSlots::BWK_IMG_WALL_HIGH_BASE);
        }
        else {
            setImage(BwkSlots::BWK_IMG_WALL_HIGH_VINES);
        }
    }
    else {
        if( rand() % 100 < 25 ) {
            setImage(BwkSlots::BWK_IMG_WALL_LOW_ROSES);
        }
        else {
            setImage(BwkSlots::BWK_IMG_WALL_LOW_BASE);
        }
    }

    _type = type;
}

void BwkWallObject::fixTiles()
{
    // The bottom-most walls always connect with the fake walls that surround the play area (low walls only)
    if( _type == LOW_WALL ) {
        if( y() == (int)( _level->yOffset() + (_level->tileSize() * (_level->mapHeight()-1)) ) ) {
            setImage(BwkSlots::BWK_IMG_WALL_LOW_TOP);
            return;
        }
    }
    // Make sure upper portions of walls have different images than lower portions by using the static
    // list of walls to determine which portion this one is. Only do this if the current tile is already
    // a base, as that is the default.
    BOOST_FOREACH(BwkWallObject * other, _level->allWalls()) {
        // Skip self
        if( other == this ) {
            continue;
        }

        // This only applies to walls of the same type
        if( other->_type != _type ) {
            continue;
        }

        // If a wall is in the tile adjacent to the south from this one, change the image so it will look neater.
        if( (other->x() == x())  && ((unsigned)other->y() == ( y() + _level->tileSize())) ) {
            if( _type == HIGH_WALL ) {
                setImage( BwkSlots::BWK_IMG_WALL_HIGH_TOP );
            }
            else {
                setImage(BwkSlots::BWK_IMG_WALL_LOW_TOP);
            }
        }
    }
}
