/**
 * @file    BwkTimerBlockObject.hpp
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


#ifndef __BWK_TIMER_BLOCK_OBJECT_DEFINED__
#define __BWK_TIMER_BLOCK_OBJECT_DEFINED__

#include "BwkObject.hpp"

class BwkLevel;

/**
 *  This object is a simple pushable square that counts down from some
 *  specified number ( 1-9 ) for every tile it is pushed. A full tile
 *  is considered as two push events. Once it reaches zero, the block becomes
 *  static.
 */
class BwkTimerBlockObject : public BwkObject
{
public:
    BwkTimerBlockObject(BwkLevel * level, int timer );

public:
    bool push(BwkObject * other, direction_flag_t dir);

private:
	int _timer; // The number of ticks left before the object is unpushable
};


#endif // __BWK_TIMER_BLOCK_OBJECT_DEFINED__
