/**
 * @file    BwkWallObject.hpp
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


#ifndef __BWK_WALL_OBJECT_DEFINED__
#define __BWK_WALL_OBJECT_DEFINED__

#include "BwkObject.hpp"
#include "BwkPlayer.hpp"

class BwkLevel;

/**
 *  A wall which blocks the movement of objects. A high wall will block attacks
 *  and protect Bwock from harm, whereas a low wall only restricts movement. It
 *  is also impossible to fly over a high wall.
 */
class BwkWallObject : public BwkObject
{
public:
    enum wallType { LOW_WALL, HIGH_WALL };

public:
    BwkWallObject( BwkLevel * level, wallType type );
    void fixTiles();
    bool resistsFlight();
    int unblockedObjects();
	
private:
    wallType _type;
};

inline bool BwkWallObject::resistsFlight()
{
    return (_type == HIGH_WALL );
}

inline int BwkWallObject::unblockedObjects()
{
    return ( _type == HIGH_WALL ) ? UNDEFINED : (FASTATTACK | SLOWATTACK);
}

#endif //__BWK_WALL_OBJECT_DEFINED__
