/**
 * @file    BwkKeyObject.cpp
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
#include "BwkKeyObject.hpp"
#include "BwkObject.hpp"
#include "BwkPlayer.hpp"
#include "BwkManager.hpp"
#include "BwkDoorObject.hpp"
#include "BwkSwitchObject.hpp"
#include "BwkLevel.hpp"

BwkKeyObject::BwkKeyObject(BwkLevel * level)
: BwkObject( level, KEY )
{
    setImage(BwkSlots::BWK_IMG_KEY);
}

/**
 *  When covered by the player, a key is collected.
 *
 *  @param other   Object covering this key
 */
void BwkKeyObject::cover(BwkObject * other )
{
    if( other == _level->player() ) {
		BwkManager::instance()->playSound(BwkSlots::BWK_SOUND_GET_KEY);

        // Open the exit and switch if this is the last
        if( _level->allKeys().size() == 1 ) {
            _level->exitDoor()->open();
            if( _level->killSwitch() ) {
                _level->killSwitch()->open();
            }
        }

        // Kill this item
        _level->addToDeathRow(this);
    }
}
