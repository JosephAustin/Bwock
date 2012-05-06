/**
 * @file    BwkTimerBlockObject.cpp
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
#include "BwkTimerBlockObject.hpp"
#include "BwkLevel.hpp"
#include "BwkPlayer.hpp"

/**
 *  CTOR
 */
BwkTimerBlockObject::BwkTimerBlockObject(BwkLevel * level, int timer )
: BwkObject( level, TIMERBLOCK )
{
    setImage(BwkSlots::BWK_BMP_TIMER_BLOCK);

	setPushStrength(NO_PUSH);
	setPushResistance(HEAVY_PUSH);
	
    // Capture the timer
    _timer = timer;

    // Restrict the timer
    if( timer < 1 ) {
        _timer ++;
    }
    else if( timer > 9 ) {
        _timer --;
    }

    // Double the timer ( 2 push events = 1 full tile )
    _timer *= 2;

    // Set the current frame
    setFrame(_timer / 2);
}

/**
 *  Overloaded to inject counting for how many times this object gets pushed.
 */
bool BwkTimerBlockObject::push(BwkObject * other, direction_flag_t dir)
{
    bool pushable;  // Whether this object is ordinarily pushable

    // If the timer is at zero, forget it
    if( _timer == 0 ) {
        return false;
    }

    // Call the regular function
    pushable = BwkObject::push(other, dir);

    // If it is normally pushable, reduce the timer and change the image
    if( pushable ) {
        _timer--;
        if( _timer % 2 == 0 ) {
            setFrame(_timer / 2);
        }
    }

    // Return whether this could be pushed
    return pushable;
}


