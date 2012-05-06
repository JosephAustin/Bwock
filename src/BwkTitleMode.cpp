/**
 * @file    BwkTitleMode.cpp
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

#include "BwkTitleMode.hpp"
#include "BwkMenuMode.hpp"

// Singleton initialization
BwkTitleMode * BwkTitleMode::_instance = NULL;

/**
 *  CTOR
 */
BwkTitleMode::BwkTitleMode()
{
    _curState = VASILISA;
	_queuedReturn = this;
}

/**
 * This recieves delegation from the application's update function.
 *
 * @return next mode to be updated. To persist, return a "this" pointer.
 */
BwkMode * BwkTitleMode::update()
{
	if( _queuedReturn == this ) {
		if( !(bwk_input()->down(Gosu::kbReturn)) && !(bwk_input()->down(Gosu::kbEscape)) ) {
			_queuedReturn = NULL;
		}
	}
	else if( !_queuedReturn ) {
		if( bwk_input()->down(Gosu::kbReturn) || bwk_input()->down(Gosu::kbEscape) ) {		
			if( bwk_input()->down(Gosu::kbReturn) ) {
				if( _curState == TITLE ) {
					_queuedReturn = BwkMenuMode::instance();
				}
				else {
					_queuedReturn = this;
				}				
			}
			else if( bwk_input()->down(Gosu::kbEscape) ) {
				if( _curState == TITLE ) {
					return NULL;
				}
				else {
					_queuedReturn = this;
				}
			}
			
			if( _curState != TITLE ) {
			 	_curState = (state_t)((int)_curState + 1);
#ifndef WIN32
				if( _curState == FMOD ) {
					_curState = (state_t)((int)_curState + 1);
				}
#endif			
			}
		}
	}
	else if( !(bwk_input()->down(Gosu::kbReturn)) && !(bwk_input()->down(Gosu::kbEscape)) ) {
		BwkMode * return_mode = _queuedReturn;
		_queuedReturn = this;
		return return_mode;
	}	

    return this;
}

/**
 *  Handler for all draw events delegated to this mode
 */
void BwkTitleMode::draw()
{
    // Draw the correct image based on the current state
    switch(_curState) {
        case VASILISA:
            bwk_fetch(BwkSlots::BWK_IMG_VASILISA)->draw(0, 0, 0);
            break;
        case GOSU:
            bwk_fetch(BwkSlots::BWK_IMG_GOSU)->draw(0, 0, 0);
            break;
        case FMOD:
            bwk_fetch(BwkSlots::BWK_IMG_FMOD)->draw(0, 0, 0);
            break;
        case TITLE:
            bwk_fetch(BwkSlots::BWK_IMG_TITLE_SCREEN)->draw(0, 0, 0);
            break;
    };
}

