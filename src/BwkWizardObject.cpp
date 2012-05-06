/**
 * @file    BwkWizardObject.cpp
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
#include "BwkWizardObject.hpp"
#include "BwkPlayer.hpp"
#include "BwkProjectileObject.hpp"
#include "BwkManager.hpp"
#include "BwkLevel.hpp"

BwkWizardObject::BwkWizardObject(BwkLevel * level)
: BwkObject(level, WIZARD)
{
    setImage(BwkSlots::BWK_BMP_WIZARD);
	_fork = NULL;
}

/**
 *  The wizard stares at the player when Bwock gets close. This is a warning to the player that they
 *  are in danger of being shot by his magic. This requires exact knowledge of the frames that animate
 *  for the wizard, of course, but it's justifiable - easy to tell if we mess it up, and easy to fix!
 */
void BwkWizardObject::act()
{
	if( _fork ) {
		_fork->update();
		if( _fork->finished() ) {
			if( _fork->gotPlayer() ) {
                _level->player()->lose();
			}
			_level->addToDeathRow(_fork);
			_fork = NULL;
			_level->setSurrogate(NULL);
		}
	}
	else if( !_level->player()->flying() ) {
		// If the player is nearly or fully aligned, stop and stare at them so the player will be warned.
		if( (_level->player()->x() >= (x()-(int)(_level->tileSize()/2))) &&
			(_level->player()->x() <= (x()+(int)(_level->tileSize()/2))) )
		{
			stopMovement();
			setFrame(1);
			stopAnimation();
		}
		else if( (_level->player()->y() >= (y()-(int)(_level->tileSize()/2))) &&
				 (_level->player()->y() <= (y()+(int)(_level->tileSize()/2))) )
		{
			stopMovement();
			if( _level->player()->x() < x() ) {
				setFrame(2);
			}
			else {
				setFrame(0);
			}
			stopAnimation();
		}
		// Animate if no sign of the player
		else if( !isAnimating() ) {
			beginAnimation(160);
		}
		// If the player is completely in sight either way, attack!
		if( (_level->player()->x() == x()) || (_level->player()->y() == y()) ) {
			_attack();
		}
	}
}

/**
 *  If the player gets in the wizard's sights, he'll attempt to kill Bwock with a
 *  ball of fire. This will only be done if there is nothing in the way.
 */
void BwkWizardObject::_attack()
{
    bool success = true;        // Whether the player is in attack range
    BwkPlayer * player;         // For convenience

    player = _level->player();

    BOOST_FOREACH( BwkObject * obj, _level->allObjects() ) {
        // Exceptions to ignore
        if( obj == player || obj == this ) {
            continue;
        }
        if( !obj->resists(FASTATTACK) ) {
            continue;
        }

        // Figure out if the object in question is blocking the player. This check
        // depends on whether the player is Y or X aligned. An object need only be
        // 50% blocking to cancel the attack.
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
        else
        {
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

        // Cancel the moment anything fails.
        if( !success ) {
            break;
        }
    }

    // Kill player
    if( success ) {
		BwkObject::direction_flag_t aimDir = BwkObject::UP_DIR;

		if( player->x() > x() ) {
			aimDir = BwkObject::RIGHT_DIR;
		}
		else if( player->x() < x() ) {
			aimDir = BwkObject::LEFT_DIR;
		}
		else if( player->y() > y() ) {
			aimDir = BwkObject::DOWN_DIR;
		}
		else if( player->y() > y() ) {
			aimDir = BwkObject::UP_DIR;
		}

		_level->setSurrogate(this);
		_fork = new BwkProjectileObject(_level, aimDir, FASTATTACK, BwkSlots::BWK_BMP_FORK );

		switch( aimDir ) {
			case BwkObject::RIGHT_DIR:
				_fork->setPosition( x() + _level->tileSize() , y());
				break;
			case BwkObject::LEFT_DIR:
				_fork->setPosition( x() - _level->tileSize() , y());
				break;
			case BwkObject::DOWN_DIR:
				_fork->setPosition( x(), y() + _level->tileSize());
				break;
			case BwkObject::UP_DIR:
				_fork->setPosition( x(), y() - _level->tileSize());
				break;
            case BwkObject::NO_DIR:
                break;
		}


		_fork->setLayer(BwkLevel::GROUND);
		_level->addObject(_fork);
		_fork->stopMovement();
		
		BwkManager::instance()->playSound(BwkSlots::BWK_SOUND_SHOOT);
    }
}

