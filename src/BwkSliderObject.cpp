/**
 * @file    BwkSliderObject.cpp
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
#include "BwkSliderObject.hpp"
#include "BwkObject.hpp"
#include "BwkPlayer.hpp"
#include "BwkLevel.hpp"

BwkSliderObject::BwkSliderObject(BwkLevel * level, direction_flag_t dir)
: BwkObject(level, SLIDER)
{	
    if( dir == HORZ_DIR ) {
        setImage(BwkSlots::BWK_IMG_SLIDER_HORZ);
    }
    else {
        setImage(BwkSlots::BWK_IMG_SLIDER_VERT);
    }

	setPushStrength(LIGHT_PUSH);
	setPushResistance(LIGHT_PUSH);
	
    _dir = dir;
}

void BwkSliderObject::act()
{
    /** doesnt act **/
}

/**
 *	Marbles can be pushed by anything that tries to push, but in a specific
 *  direction.
 */
int BwkSliderObject::pushableDirections()
{
	return _dir;
}

