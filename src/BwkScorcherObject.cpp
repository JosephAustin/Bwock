/**
 * @file    BwkScorcherObject.cpp
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
#include "BwkScorcherObject.hpp"
#include "BwkPlayer.hpp"
#include "BwkProjectileObject.hpp"
#include "BwkManager.hpp"
#include "BwkLevel.hpp"

/**
 *  CTOR
 */
BwkScorcherObject::BwkScorcherObject(BwkLevel * level, direction_flag_t dir)
: BwkObject(level, SCORCHER)
{
	_flame = NULL;
    _dir = dir;
    _awake = false;

    setImage(BwkSlots::BWK_BMP_SCORCHER_ASLEEP);

	// Go to the appropriate frame
	switch( dir ) {
		case UP_DIR:
			setFrame(0);
			break;
		case DOWN_DIR:
			setFrame(1);
			break;
		case LEFT_DIR:
			setFrame(2);
			break;
		case RIGHT_DIR:
			setFrame(3);
			break;
	}
	
}

void BwkScorcherObject::act()
{
    if( !_awake ) {
        if( _level->allKeys().size() == 0 ) {
            setImage(BwkSlots::BWK_BMP_SCORCHER_AWAKE);
            setFrame( (int)_dir );
            _awake = true;
        }
    }
    else {
        if( _flame ) {
            if( _flame->finished() ) {
                if( _flame->gotPlayer() ) {
                    _level->player()->lose();
                }
                _level->addToDeathRow(_flame);
                _flame = NULL;
            }
        }
        else if( !_level->player()->flying() ) {
            // If the player is completely in sight either way, attack!
            if( (_level->player()->x() == x()) || (_level->player()->y() == y()) ) {
                _attack();
            }
        }
    }
}

void BwkScorcherObject::_attack()
{
    bool success = true;        // Whether the player is in attack range
    BwkPlayer * player;         // For convenience

    player = _level->player();

    if( player->x() == x() ) {
        if( _dir == UP_DIR ) {
            if( player->y() > y() ) {
                success = false;
            }
        }
        else if( _dir == DOWN_DIR ) {
            if( player->y() < y() ) {
                success = false;
            }
        }
        else {
            success = false;
        }
    }
    else if( player->y() == y() ) {
        if( _dir == LEFT_DIR ) {
            if( player->x() > x() ) {
                success = false;
            }
        }
        else if( _dir == RIGHT_DIR ) {
            if( player->x() < x() ) {
                success = false;
            }
        }
        else {
            success = false;
        }
    }


    // Try to kill player
    if( success ) {
		_flame = new BwkProjectileObject(_level, _dir, SLOWATTACK, BwkSlots::BWK_BMP_FIREBALL );

		switch( _dir ) {
			case BwkObject::RIGHT_DIR:
				_flame->setPosition( x() + _level->tileSize() , y());
				break;
			case BwkObject::LEFT_DIR:
				_flame->setPosition( x() - _level->tileSize() , y());
				break;
			case BwkObject::DOWN_DIR:
				_flame->setPosition( x(), y() + _level->tileSize());
				break;
			case BwkObject::UP_DIR:
				_flame->setPosition( x(), y() - _level->tileSize());
				break;
            case BwkObject::NO_DIR:
                break;
		}


		_flame->setLayer(BwkLevel::GROUND);
		_level->addObject(_flame);
		_flame->stopMovement();
		
		BwkManager::instance()->playSound(BwkSlots::BWK_SOUND_SHOOT);
    }
}

