/**
 * @file    BwkGameOverlay.cpp
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

#include "BwkLevel.hpp"
#include "BwkManager.hpp"
#include "BwkSlots.hpp"
#include "BwkPausedGameOverlay.hpp"

/**
 * CTOR
 */
BwkPausedGameOverlay::BwkPausedGameOverlay()
{
    // We're in the first push state
    _pushState = 0;
}

/**
 *  Count push states until the user presses 'P' a second time to exit the pause state
 */
bool BwkPausedGameOverlay::update(BwkLevel * level)
{
    // A super condensed way of handling the button pushing. All I'm doing is counting
    // push states - one release, one press, and another release before we leave this overlay.
    if( _pushState == 0 ) {
        _pushState += (int)(!bwk_input()->down(Gosu::kbP));
    }
    else if( _pushState == 1 ) {
        _pushState += (int)(bwk_input()->down(Gosu::kbP));
    }
    else if( !bwk_input()->down(Gosu::kbP) ) {
        return false;
    }
    return true;
}

/**
 *  Drop a paused message on top of the playing area, centered
 */
void BwkPausedGameOverlay::draw(BwkLevel * level)
{
    int x = ( 800 / 2 ) - ( bwk_fetch(BwkSlots::BWK_IMG_PAUSED)->width() / 2 );  // X offset
    int y = ( 600 / 2 ) - ( bwk_fetch(BwkSlots::BWK_IMG_PAUSED)->height() / 2 ); // y offset
    bwk_fetch(BwkSlots::BWK_IMG_PAUSED)->draw(x, y, 100);
}

/**
 *  This overlay should definately be modal to pause the game
 */
bool BwkPausedGameOverlay::isModal() 
{
	return true;
}
