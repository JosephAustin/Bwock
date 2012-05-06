/**
 * @file    BwkPusherObject.cpp
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

#include "BwkPusherObject.hpp"
#include "BwkObject.hpp"
#include "BwkPlayer.hpp"
#include "BwkLevel.hpp"

/**
 *  CTOR
 */
BwkPusherObject::BwkPusherObject(BwkLevel * level, BwkObject::direction_flag_t dir)
: BwkObject( level, PUSHER )
{
	// Set the image
    setImage(BwkSlots::BWK_BMP_PUSHER);
	
	setPushStrength(LIGHT_PUSH);
	setPushResistance(NO_PUSH);
	
	// Determine the frame to use
    switch( dir ) {
        case BwkObject::UP_DIR:
            setFrame(0);
            break;
        case BwkObject::DOWN_DIR:
            setFrame(1);
            break;
        case BwkObject::LEFT_DIR:
            setFrame(2);
            break;
        case BwkObject::RIGHT_DIR:
        default:
            setFrame(3);
            break;
    }

	// Capture the push direction
    _push_dir = dir;
}

/**
 *  Just push continuously
 */
void BwkPusherObject::act()
{
    if( !isMoving() ) {
        goDir(_push_dir);
    }
}

