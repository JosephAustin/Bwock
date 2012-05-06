/**
 * @file    BwkProjectileObject.cpp
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
#include "BwkProjectileObject.hpp"
#include "BwkPlayer.hpp"
#include "BwkLevel.hpp"

/**
 *	CTOR
 */
BwkProjectileObject::BwkProjectileObject(BwkLevel *level,
										 BwkObject::direction_flag_t dir,
                                         BwkObject::object_type_t type,
                                         BwkSlots::Bwk_Data_Bmp_Slot imageSlot)
: BwkObject( level, type )
{
	// Use the image passed in
    setImage(imageSlot);

	// Determine speed based on type
    if( type == FASTATTACK ) {

        setSpeed( 2 );
    }
    else {
        setSpeed( 5 );
    }

	// Go to the appropriate frame
	switch( dir ) {
		case UP_DIR:
			setFrame(0);
			break;
		case DOWN_DIR:
			setFrame(1);
			break;
		case LEFT_DIR:
			setFrame(2);
			break;
		case RIGHT_DIR:
			setFrame(3);
			break;
	}
	
	// Capture the direction
	_dir = dir;
}

/**
 *  Called repeatedly until it returns true by whoever has fired it.
 */
bool BwkProjectileObject::finished()
{
	// Move forward
	goDir(_dir);
	
	// See if we reached something that is blocking
    return !isMoving();
}

/**
 *  Called after finished() returns true to see if it was Bwock that
 *  the projectile hit.
 */
bool BwkProjectileObject::gotPlayer()
{
    return (blocked(_dir, _level->player()));
}
