/**
 * @file    BwkPuddiniObject.cpp
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
#include "BwkPuddiniObject.hpp"
#include "BwkPlayer.hpp"
#include "BwkProjectileObject.hpp"
#include "BwkManager.hpp"
#include "BwkLevel.hpp"

// Note: its STILL possible to cheat these guys by moving just right when being attacked :P

/**
 *  CTOR
 */
BwkPuddiniObject::BwkPuddiniObject(BwkLevel * level, direction_flag_t heading)
: BwkObject(level, PUDDINI)
{
    // Set the image for this object
    setImage(BwkSlots::BWK_BMP_PUDDINI);

    // Initialize
	_slime = NULL;
    _gotPlayer = false;

    // Set the movement speed
    setSpeed(6);

    // Determine starting direction
    if( heading == HORZ_DIR ) {
        _dir = RIGHT_DIR;
    }
    else {
        _dir = DOWN_DIR;
    }
}

/**
 *  Puddini's act functionality
 */
void BwkPuddiniObject::act()
{
    if( !_gotPlayer ) {
        if( !isMoving() ) {
            goDir(_dir);
            if( !isMoving() ) {
                if( _dir == RIGHT_DIR ) {
                    _dir = LEFT_DIR;
                }
                else if( _dir == LEFT_DIR ) {
                    _dir = RIGHT_DIR;
                }
                else if( _dir == UP_DIR ) {
                    _dir = DOWN_DIR;
                }
                else if( _dir == DOWN_DIR ) {
                    _dir = UP_DIR;
                }
            }
        }
        else {
			// Go to the appropriate frame
			switch( _dir ) {
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
    }

	if( _slime ) {
		_slime->update();
		if( _slime->finished() ) {
			if( _slime->gotPlayer() ) {
                _level->player()->lose();
			}
			_level->addToDeathRow(_slime);
			_slime = NULL;
			_level->setSurrogate(NULL);
		}
	}
	else if( !_gotPlayer && !_level->player()->flying() ) {
		// If the player is completely in sight either way, attack!
		if( (_level->player()->x() == x()) ||
            (_level->player()->y() == y()) )
        {
			_attack();
		}
		else if((_level->player()->destX() == destX()) ||
                (_level->player()->destY() == destY()) )
        {
			_attack();
		}
	}
}

/**
 *  Unblockable attack on the player
 */
void BwkPuddiniObject::_attack()
{
    bool success = true;                            // Whether the player is in attack range
    BwkPlayer * player = _level->player();;         // For convenience

    BOOST_FOREACH( BwkObject * obj, _level->allObjects() ) {
        // Exceptions to ignore
        if( obj == player || obj == this ) {
            continue;
        }
        if( !obj->resists(FASTATTACK) ) {
            continue;
        }

        if( ( player->y() == y() ) ) {
            if( (( obj->x() < x() ) && (player->x() < obj->x())) ||
                (( obj->x() > x() ) && (player->x() > obj->x())) )
            {
                if( (obj->y() <= (y() + (int)(_level->tileSize()/2))) &&
                    (obj->y() >= (y() - (int)(_level->tileSize()/2))) )
                {
                    success = false;
                }
            }
        }
        else if( ( player->destY() == destY() ) ) {
            if( (( obj->x() < x() ) && (player->x() < obj->x())) ||
                (( obj->x() > x() ) && (player->x() > obj->x())) )
            {
                if( (obj->y() <= (destY() + (int)(_level->tileSize()/2))) &&
                    (obj->y() >= (destY() - (int)(_level->tileSize()/2))) )
                {
                    success = false;
                }
            }
        }
        else if( (player->x() == x() ) ) {
            if( (( obj->y() < y() ) && (player->y() < obj->y())) ||
                (( obj->y() > y() ) && (player->y() > obj->y())) )
            {
                if( (obj->x() <= (x() + (int)(_level->tileSize()/2))) &&
                    (obj->x() >= (x() - (int)(_level->tileSize()/2))) )
                {
                    success = false;
                }
            }
        }
        else if( (player->destX() == destX() ) ) {
            if( (( obj->y() < y() ) && (player->y() < obj->y())) ||
                (( obj->y() > y() ) && (player->y() > obj->y())) )
            {
                if( (obj->x() <= (destX() + (int)(_level->tileSize()/2))) &&
                    (obj->x() >= (destX() - (int)(_level->tileSize()/2))) )
                {
                    success = false;
                }
            }
        }
        else {
            success = false;
        }


        // Cancel the moment anything fails.
        if( !success ) {
            break;
        }
    }

    // Kill player
    if( success ) {
        if( ( player->destX() == destX() ) || ( player->destY() == destY() ) ) {
            player->setPosition(player->destX(), player->destY());
            setPosition(destX(), destY());
        }
        _gotPlayer = true;
		BwkObject::direction_flag_t aimDir = BwkObject::UP_DIR;
        if( ( player->y() == y() ) || (player->destY() == destY() ) ) {
            if( player->x() < x() ) {
                aimDir = LEFT_DIR;
            }
            else {
                aimDir = RIGHT_DIR;
            }
        }
        else if( (player->x() == x() ) || (player->destX() == destX() ) ) {
            if( player->y() < y() ) {
                aimDir = UP_DIR;
            }
            else {
                aimDir = DOWN_DIR;
            }
        }
		// Go to the appropriate frame
		switch( aimDir ) {
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

		_level->setSurrogate(this);
		_slime = new BwkProjectileObject(_level, aimDir, FASTATTACK, BwkSlots::BWK_BMP_SLIME );

		switch( aimDir ) {
			case BwkObject::RIGHT_DIR:
				_slime->setPosition( x() + _level->tileSize() , player->y());
				break;
			case BwkObject::LEFT_DIR:
				_slime->setPosition( x() - _level->tileSize() , player->y());
				break;
			case BwkObject::DOWN_DIR:
				_slime->setPosition( player->x(), y() + _level->tileSize());
				break;
			case BwkObject::UP_DIR:
				_slime->setPosition( player->x(), y() - _level->tileSize());
				break;
            case BwkObject::NO_DIR:
                break;
		}


		_slime->setLayer(BwkLevel::GROUND);
		_level->addObject(_slime);
		_slime->stopMovement();
		BwkManager::instance()->playSound(BwkSlots::BWK_SOUND_SHOOT);
    }
}

