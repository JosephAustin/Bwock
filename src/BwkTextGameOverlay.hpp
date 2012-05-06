/**
 * @file    BwkTextGameOverlay.hpp
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

#ifndef __BWK_TEXT_GAME_OVERLAY_DEFINED__
#define __BWK_TEXT_GAME_OVERLAY_DEFINED__

#include <string>
#include "BwkGameOverlay.hpp"

/**
 *  A quick, non-modal text popup currently existing to put level authors on screen
 *  for a brief ti_expireTimeme.
 */
class BwkTextGameOverlay : public BwkGameOverlay
{
public:
    BwkTextGameOverlay(unsigned long timeLimit, std::wstring message);
    bool update(BwkLevel * level);
    void draw(BwkLevel * level);
	bool isModal();

private:
	unsigned long _expireTime;		// The time at which this popup expires
	Gosu::Font _font;
	std::wstring _message;	// The message to print
	int _position;
};

#endif // __BWK_PAUSED_GAME_OVERLAY_DEFINED__
