/**
 * @file    BwkWeedsObject.hpp
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


#ifndef __BWK_WEEDS_OBJECT_DEFINED__
#define __BWK_WEEDS_OBJECT_DEFINED__

#include "BwkObject.hpp"

class BwkLevel;

/**
 *  Weeds challenge the player by allowing Bwock to traverse them, but not most
 *  other objects like pushables. It is essentially a hedge that Bwock can walk
 *  across, but that provides an obstacle when manipulating other objects.
 */
class BwkWeedsObject : public BwkObject
{
public:
    BwkWeedsObject( BwkLevel * level);

	int unblockedObjects();
};


inline int BwkWeedsObject::unblockedObjects()
{
    return PLAYER | FASTATTACK | SLOWATTACK;
}


#endif //__BWK_WEEDS_OBJECT_DEFINED__
