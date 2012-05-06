/**
 * @file    BwkPuddiniObject.hpp
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

#ifndef __BWK_PUDDINI_OBJECT_DEFINED__
#define __BWK_PUDDINI_OBJECT_DEFINED__

#include "BwkObject.hpp"

class BwkProjectileObject;

/**
 *  Puddini moves back and forth in some given direction until he sees Bwock
 *  unblocked. Then he shoots unblockable slime at the player. Essentially, this
 *  is a wizard that moves.
 */
class BwkPuddiniObject : public BwkObject
{
public:
    BwkPuddiniObject(BwkLevel * level, direction_flag_t heading);
	
private:
    void act();
    void _attack();

private:
    direction_flag_t _dir;	// The current direction this object is going
    bool _gotPlayer;	// True when this object is in the state of killing Bwock
	BwkProjectileObject * _slime;	// Slime being fired at Bwock
};

#endif // __BWK_PUDDINI_OBJECT_DEFINED__
