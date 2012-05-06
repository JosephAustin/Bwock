/**
 * @file    BwkDoorObject.hpp
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

#include "BwkObject.hpp"

class BwkLevel;

/**
 *  The level's exit point, which opens once all keys are found.
 */
class BwkDoorObject : public BwkObject
{
public:
    BwkDoorObject(BwkLevel * level);

public:
    void reposition();
    void open();
    void cover(BwkObject * other);
    bool resistsFlight();
    int unblockedObjects();

private:

    bool _isOpen;   // Whether the door has opened
};

/**
 *  Resist flying Bwock at all times. Otherwise the player could block the door
 *  but still fly over and win the level, which doesn't make sense for a doorway.
 */
inline bool BwkDoorObject::resistsFlight()
{
    return true;
}

/**
 *  Doors block everything, but if they are open, the player may pass
 */
inline int BwkDoorObject::unblockedObjects()
{
    return ( _isOpen ? PLAYER : UNDEFINED );
}
