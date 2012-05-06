/**
 * @file    BwkObject.cpp
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
#include <Gosu/Gosu.hpp>

#include "BwkObject.hpp"
#include "BwkPlayer.hpp"
#include "BwkManager.hpp"
#include "BwkTiles.hpp"
#include "BwkLevel.hpp"
#include "BwkDoorObject.hpp"
#include "BwkProjectileObject.hpp"

#ifndef WIN32
using namespace std;
#endif

/**
 *  Constructor
 */
BwkObject::BwkObject( BwkLevel * level, object_type_t obj_type)
{
    // Initialize all the member variables
    _level = level;
	_position.x = _position.y = 0;
	_destination.x = _destination.y = 0;
	_layer = BwkLevel::TERRAIN;
	_type = obj_type;
	_push_strength = NO_PUSH;
	_push_resistance = NO_PUSH;
    _image = NULL;
	_speed = 10;	
	_time = Gosu::milliseconds();
	_msRoundOff = 0;	
	_anim_rate = 0;
    _animating = false;
	_cur_frame = 0;
}

/**
 * Sets the non-animated image of this object.
 *
 * @param slot  Slot containing the image to set.
 */
void BwkObject::setImage(BwkSlots::Bwk_Data_Img_Slot slot)
{
    Gosu::Image * img = bwk_fetch(slot);    // The image class

	_image = img;
    _frames.clear();
    _frames.push_back(img);
}

/**
 * Sets the Animated image of this object.
 *
 * Bitmap is treated as a film roll and each tile will be turned into a frame for
 * animation purposes. In this case, the first image taken from this process will
 * become the current image. Note that each frame is NOT a seperate image. They
 * are portions of the same memory and should be treated as such.
 */
void BwkObject::setImage(BwkSlots::Bwk_Data_Bmp_Slot slot  )
{
	Gosu::Bitmap * bmp = bwk_fetch(slot);
    unsigned int pos = 0;   // Position in the image to extract the next tile

	_frames.clear();

	// Get as many frames as possible which fit into the tile size
	while( pos < bmp->width() ) {
		_frames.push_back( new Gosu::Image( *bwk_video(), *bmp, pos, 0,
			BwkTiles::MAX_TILE_SIZE, BwkTiles::MAX_TILE_SIZE ) );
		pos += BwkTiles::MAX_TILE_SIZE;
	}

	// Set a starting frame
    _image = _frames[0];
}


/**
 *  Advances the animation frame. This runs circular.
 */
void BwkObject::setFrame( unsigned int frame )
{
    _cur_frame = frame;
    if( _cur_frame >= _frames.size() ) {
        _cur_frame = 0;
    }
    // Set the image
    _image = _frames[_cur_frame];
}


/**
 *  Called every loop.
 */
void BwkObject::update()
{
	// Call the overloadable action function
    act();

	// Reset the timer if the object is not moving. Otherwise, a stationary object
	// would 'jump' instantly to its destination the moment it tries to move
	if( !isMoving() ) {
		_time = Gosu::milliseconds();
		_msRoundOff = 0;
	}

    // Handle sprite animation
    if( _animating ) {
        setFrame( (Gosu::milliseconds()%_anim_rate)/(_anim_rate/_frames.size()) );
    }

	if( !_level ) {
		return;
	}
    // Cover Check: The player should NOT do this check when flying
    if( (type() != PLAYER) || !(_level->player()->flying()) ) {

        // Trigger a cover event in any object sharing the same exact position as this one
        BOOST_FOREACH( BwkObject * other, _level->allObjects() ) {

            // Skip self
            if( other == this ) {
                continue;
            }

            // Position check
            if( other->x() == x() && other->y() == y() ) {
                other->cover(this);
            }
        }
    }

    // Control motion and animation
    if( isMoving() ) {
        move();
    }
}

/**
 *  If the destination is not equal to the current location, incrementally move towards it
 */
void BwkObject::move()
{
	int timePassed = (Gosu::milliseconds() - _time + _msRoundOff );	// Millisecs passed since last frame
	int stepsPassed = timePassed / _speed;							// Movements passed since last frame

	// Store milliseconds to be added next time, and reset the timer
	_msRoundOff = timePassed % _speed;
	_time = Gosu::milliseconds();

	if( !isMoving() || (stepsPassed < 1) ) {
		return;
	}

    // Figure out where to go next
    if( destX() > x() ) {
        setPosition( min(destX(),x() + stepsPassed), y() );
    }
    else if( destX() < x() ) {
        setPosition( max(destX(),x() - stepsPassed), y() );
    }
    else if( destY() > y() ) {
        setPosition( x(), min(destY(),y() + stepsPassed) );
    }
    else if( destY() < y() ) {
        setPosition( x(), max(destY(),y() - stepsPassed) );
    }

}

/**
 *  Head in a particular direction. This is a somewhat complex function that I've had to
 *  visit often. It handles all collision detection. Hopefully it's been organized in a
 *  simple manner now, but proceed with caution!
 */
void BwkObject::goDir( BwkObject::direction_flag_t dir)
{
	// Set the destination
	setDestination(dir);

	// Exit if not moving, obviously
	if( !isMoving() ) {
		return;
	}
	
	// Make sure the proposed movement stays locked to the play area. The exception is
	// the door, because Bwock can walk through it, outside of the play area. For that,
	// we allow the door's own collision rules to take effect.
	if( (destX() < _level->xOffset()) || (destY() < _level->yOffset()) ||
		(destX() > ( _level->xOffset() + (_level->tileSize() * (_level->mapWidth()-1)) ) ) ||
		(destY() > ( _level->yOffset() + (_level->tileSize() * (_level->mapHeight()-1)) ) ) )
	{
		// If not blocked by the door, then the destination area is definately off limits
		if( !blocked(_level->exitDoor()) ) {
			stopMovement();
			return;
		}
		
		// If blocked by the door, still make sure that the door is directly parallel to us.
		else if( _level->exitDoor()->x() != x() && _level->exitDoor()->y() != y() ) {
			stopMovement();
			return;
		}
	}	
	
	// Now comes the hard part - test collision with all other objects in the level.
	BOOST_FOREACH( BwkObject * obj, _level->allObjects() ) 
	{
		// skip self, which would always be colliding
		if( obj == this ) {
			continue;
		}

		// Don't bother checking collision if not colliding with the object :)
		if( !blocked(obj) ) {
			continue;
		}

		// Ignore objects that do not resist
		if( !(obj->resists(this)) ) {
			continue;
		}
			
		// Some special collision handling for the Bwock when he's flying.
		if( ((type() == PLAYER) || (obj->type() == PLAYER)) && _level->player()->flying() ) {

			// If THIS is the player, ignore the direct object (obj) unless it resists flight
			if( type() == PLAYER ) {
				if ( !obj->resistsFlight() ) {
					continue;
				}
				else {
					stopMovement();
					return;
				}
			}
			// If the direct object is the player, ignore the player unless THIS object 
			// resists flight ( the reverse scenareo of above, essentially )
			else if( obj->type() == PLAYER ) {
				if( !resistsFlight() ) {
					continue;
				}
				else {
					stopMovement();
					return;
				}
			}
		}
		// Now for regular collision checking 
		else {		
			// Check for direct collision ( not when off by a half tile )
			if( ( destX() == obj->x() ) || ( destY() == obj->y() ) ) {

				// Check directional collision limitations ( horizontal )
				if( (dir == LEFT_DIR) || (dir == RIGHT_DIR) ) {
					if( !(obj->pushableDirections() & dir) &&
						!(obj->pushableDirections() & HORZ_DIR ) )
					{
						stopMovement();
						return;
					}
				}
				// Check directional collision limitations ( vertical )
				if( (dir == UP_DIR) || (dir == DOWN_DIR) ) {
					if( !(obj->pushableDirections() & dir) &&
						!(obj->pushableDirections() & VERT_DIR ) )
					{
						stopMovement();
						return;
					}
				}
				
				// Direct collision allows pushing, so attempt a push on the object
				if( !obj->push(this, dir) ) {
					stopMovement();
					return;
				}
			}
			// Indirect collision with resistant obstacles always blocks. Makes things
			// a bit simpler!
			else {
				stopMovement();
				return;
			}
		}
	}
}

/**
 *  Attempt a push in the given direction. This will be called recursively for objects which
 *  can be pushed in groups.
 */
bool BwkObject::push(BwkObject * pusher, direction_flag_t dir)
{
    // Stop now if this object is already moving - thats always a no-no
    if( isMoving() ) {
        return false;
    }
	
	// Make sure the pusher can actually send a push
	if( pusher->pushStrength() == NO_PUSH ) {
		return false;
	}
	
	// Make sure this object can actually recieve a push
	if( pushResistance() == NO_PUSH ) {
		return false;
	}
	
	// If this has a strong resistance, only a strong push can move it
	if( (pushResistance() == HEAVY_PUSH)  &&  (pusher->pushStrength() != HEAVY_PUSH) ) {
		return false;
	}	

    // Checks passed. Try to go the given direction and recurse that way.
    goDir( dir );

    // If we weren't stopped, success!
    return isMoving();
}

/**
 *  Checks whether this object's destination crosses another object's space or destination
 *
 *  @param obj  Object to check against
 */
bool BwkObject::blocked(BwkObject * obj) const
{
    const double distance = _level->tileSize() / 2.0;   	// Half a tile's distance
	double xCheck = obj->destX();	// The X position to check against
	double yCheck = obj->destY();	// The Y position to check against

	// Check against the xCheck and yCheck.
	if( (destY() + (int)(distance)) < yCheck ) {
		return false;
	}
	if( destY() > (yCheck + (int)(distance)) ) {
		return false;
	}
	if( (destX() + (int)(distance)) < xCheck ) {
		return false;
	}
	if( destX() > (xCheck + (int)(distance)) ) {
		return false;
	}

	// Checks passed, so we must be blocked by this object
    return true;
}


/**
 * Check if an object is blocking in a particular direction.
 */
bool BwkObject::blocked(BwkObject::direction_flag_t dir, BwkObject * obj)
{
	double oldX = destX();	// The original X Destination
	double oldY = destY();	// The original Y Destination
	bool ret_val = false;	// The value returned by this function
    const double distance = _level->tileSize() / 2.0;   // Move half a tile

	// Set a temporary destination
	setDestination(dir);

	// Check if we're blocked now by the given object
	ret_val = blocked(obj);

	// Restore the original destination
	setDestination(oldX, oldY);

	return ret_val;
}

void BwkObject::act()
{
    // Nothing by default.
}

/**
 * 	Set the destination of this object in some specific direction
 */
void BwkObject::setDestination( BwkObject::direction_flag_t dir )
{
    const double distance = _level->tileSize() / 2.0;   // Move half a tile

	// Figure out what the change in destination equates to
	switch( dir ) {
		case BwkObject::RIGHT_DIR:
			setDestination(x() + distance, y());
			break;
		case BwkObject::LEFT_DIR:
			setDestination(x() - distance, y());
			break;
		case BwkObject::DOWN_DIR:
			setDestination(x(), y() + distance);
			break;
		case BwkObject::UP_DIR:
			setDestination(x(), y() - distance);
			break;
        case NO_DIR:
            break;
	}
}
