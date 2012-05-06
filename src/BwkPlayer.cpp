/**
 * @file    BwkPlayer.cpp
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

#include "BwkPlayer.hpp"
#include "BwkLevel.hpp"
#include "BwkManager.hpp"


/**
 *  Constructor
 */
BwkPlayer::BwkPlayer(BwkLevel * level)
: BwkObject(level, PLAYER)
{
    setImage(BwkSlots::BWK_BMP_BWOCK_DOWN);

    _has_won = false;
    _has_lost = false;
    _is_flying = false;
	
	setPushStrength(HEAVY_PUSH);
	setPushResistance(NO_PUSH);
}

/**
 *  Respond to user's controls
 */
void BwkPlayer::act()
{
    BwkObject::direction_flag_t dir = NO_DIR;

    // Go the pressed direction, if any. Also change the images to match.
    if( !isMoving() ) {
		if( flying() && bwk_input()->down(Gosu::kbSpace) ) {
			bool clearToLand = true;

			// Back up the current position
			pos_t position;
			position.x = x();
			position.y = y();


			BOOST_FOREACH( BwkObject * obj, _level->allObjects() ) {
				if( obj == this ) {
					continue;
				}

				// Test for blockage in all directions
				setPosition(position.x, position.y - (_level->tileSize()/2));
				clearToLand = ( clearToLand && !blocked(obj) );
				setPosition(position.x, position.y + (_level->tileSize()/2));
				clearToLand = ( clearToLand && !blocked(obj) );
				setPosition(position.x - (_level->tileSize()/2), position.y);
				clearToLand = ( clearToLand && !blocked(obj) );
				setPosition(position.x + (_level->tileSize()/2), position.y);
				clearToLand = ( clearToLand && !blocked(obj) );
			}

			// Restore position
			setPosition(position.x, position.y);

			// Land if possible
			if( clearToLand ) {
				_is_flying = false;
				setImage(BwkSlots::BWK_BMP_BWOCK_DOWN);
			}
		}
		else if(bwk_input()->down(Gosu::kbLeft)) {
            dir = BwkObject::LEFT_DIR;
            setImage(flying() ? BwkSlots::BWK_BMP_BWOCK_LEFT_FLYING : BwkSlots::BWK_BMP_BWOCK_LEFT);
        }
        else if(bwk_input()->down(Gosu::kbRight)) {
            dir = BwkObject::RIGHT_DIR;
            setImage(flying() ? BwkSlots::BWK_BMP_BWOCK_RIGHT_FLYING : BwkSlots::BWK_BMP_BWOCK_RIGHT);
        }
        else if(bwk_input()->down(Gosu::kbUp)) {
            dir = BwkObject::UP_DIR;
            setImage(flying() ? BwkSlots::BWK_BMP_BWOCK_UP_FLYING : BwkSlots::BWK_BMP_BWOCK_UP);
        }
        else if(bwk_input()->down(Gosu::kbDown)) {
            dir = BwkObject::DOWN_DIR;
            setImage(flying() ? BwkSlots::BWK_BMP_BWOCK_DOWN_FLYING : BwkSlots::BWK_BMP_BWOCK_DOWN);
        }

        goDir( dir );

        if( layer() == BwkLevel::GROUND ) {
            // Logic for player when in motion
            if( isMoving() ) {
                beginAnimation(32);
            }
            else {
                stopAnimation();
                setFrame(0);
            }
        }
    }
}

void BwkPlayer::beginFlight()
{
    if( flying() ) {
        return;
    }

    _is_flying = true;

    setImage( BwkSlots::BWK_BMP_BWOCK_DOWN_FLYING );
    beginAnimation(32);
}
