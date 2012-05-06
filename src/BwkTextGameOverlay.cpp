/**
 * @file    BwkTextGameOverlay.cpp
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

#include "Gosu/Gosu.hpp"
#include "BwkTextGameOverlay.hpp"
#include "BwkManager.hpp"

/**
 *  CTOR
 *  @param timeLimit	The amount of time in milliseconds to show the text
 */
BwkTextGameOverlay::BwkTextGameOverlay(unsigned long timeLimit, std::wstring message)
: _font(*(BwkManager::instance()->video()), L"Arial", 25 )
{
	_expireTime = (Gosu::milliseconds()) + timeLimit;
	_message = message;
	_position = -10;
}

/**
 *	This overlay is done when the elapsed time goes over the time limit
 */
bool BwkTextGameOverlay::update(BwkLevel * level)
{
	// If time is left for this text overlay to show, move it into
	// view until this condition is false.
	if( Gosu::milliseconds() < _expireTime ) {
		// Move to the 10th pixel position down
		if( _position < 10 ) {
			_position += 1;
		}
	}
	else {
		// Move out of view
		if( _position > -10 ) {
			_position -= 1;
		}
		// Once out of view, destroy this overlay
		else {
			return false;
		}
	}

	// If it isnt, keep this overlay going
	return true;
}

/**
 *	Draw the text on the screen
 */
void BwkTextGameOverlay::draw(BwkLevel * level)
{
	_font.draw(_message, 10,_position, 100);
}

/**
 *  For now, this is never modal
 */
bool BwkTextGameOverlay::isModal()
{
	return false;
}
