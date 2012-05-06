/**
 * @file    BwkObject.hpp
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

#ifndef __BWK_OBJECT_DEFINED__
#define __BWK_OBJECT_DEFINED__

#include <vector>
#include <ctime>

#include "Gosu/Gosu.hpp"

#include "BwkSlots.hpp"

class BwkLevel;

/**
 *  An object which appears in a BwkLevel. They are updated and drawn with each game loop.
 *  The game relies heavily upon these guys, since their dynamics and interactions with one
 *  another make things happen in the game world.
 */
class BwkObject
{

public:
	// Simple directional flags, for a multitude of uses. 
    enum direction_flag_t {
		NO_DIR		= 0x01,
		UP_DIR 		= 0x02,
		DOWN_DIR	= 0x04,
		LEFT_DIR	= 0x08,
		RIGHT_DIR	= 0x10,
		HORZ_DIR	= 0x20,
		VERT_DIR	= 0x40
	};

    // Identifiers for these objects. They may be strung together as bitwise flags for
	// a variety of purposes ( see unblockedObjects() ).
    enum object_type_t {
        UNDEFINED   = 0x0000001,
        PLAYER      = 0x0000002,
        BURNIE      = 0x0000004,
        ITCHI       = 0x0000008,
        BOULDER     = 0x0000010,
        BOULDERBUG  = 000000020,
        MARBLE      = 0x0000040,
        TIMERBLOCK  = 0x0000080,
        SLIDER      = 0x0000100,
        PUSHER      = 0x0000200,
        DOOR        = 0x0000400,
        KEY         = 0x0000800,
        SWITCH      = 0x0001000,
        SPRING      = 0x0082000,
        WEEDS       = 0x0004000,
        WALL        = 0x0008000,
        WATER       = 0x0010000,
        WIZARD      = 0x0020000,
        PUDDINI     = 0x0040000,
        SCORCHER    = 0x0080000,
        SIRSQUEAK   = 0x0100000,
        BROBRO      = 0x0200000,
        FASTATTACK  = 0x0400000,
        SLOWATTACK  = 0x0800000
    };
	
	// This enumerated type defines push rules for an object. This entails both the object's
	// push strength and push resistance. For example, an object with LIGHT_PUSH strength 
	// cannot push an object with HEAVY_PUSH resistance. By default, objects are NO_PUSH
	// for both their strength and resistance, i.e. they won't budge except on their own.
    enum push_type_t {
		NO_PUSH,
		LIGHT_PUSH,
		HEAVY_PUSH
    };

protected:
	// A simple structure for holding x/y coordinates
    struct pos_t {
        int x;
        int y;
    };
	
public:
    BwkObject(BwkLevel * level, object_type_t);

public:
    void setPosition( int x, int y );
	int x() const { return  _position.x; }
    int y() const { return  _position.y; }
	
	void setLayer( int layer ) { _layer = layer; }
	int layer() const { return	_layer; }
	
	void setDestination( int x, int y );
	void setDestination( direction_flag_t dir );
	int destX() const { return  _destination.x; }
    int destY() const { return  _destination.y; }
	
	void stopMovement();
	
	void setSpeed(int speed) { _speed = speed; }
	
    object_type_t type() const { return _type; }
	
    void setImage(BwkSlots::Bwk_Data_Img_Slot slot);
    void setImage(BwkSlots::Bwk_Data_Bmp_Slot slot);
    Gosu::Image * image() const { return _image; }

    void setFrame(unsigned int frame);
	int curFrame() const { return _cur_frame; }
	
    void beginAnimation(int rate);
	void stopAnimation() { _animating = false; }
	bool isAnimating() const { return _animating; }
	
    void update();
    virtual void act();
    void move();
    bool isMoving();
	void goDir( direction_flag_t dir );

	bool blocked(BwkObject * obj) const;
	bool blocked(direction_flag_t dir, BwkObject * object);
    virtual int unblockedObjects();
	
    bool resists(BwkObject * other);
    bool resists(object_type_t type);
    virtual bool resistsFlight();
	
    virtual void cover(BwkObject * other);
	
	push_type_t pushStrength() const { return _push_strength; }
	push_type_t pushResistance() const { return _push_resistance; }
	void setPushStrength(push_type_t strength) { _push_strength = strength; }
	void setPushResistance(push_type_t resistance) { _push_resistance = resistance; }

	virtual int pushableDirections();
    virtual bool push(BwkObject * pusher, direction_flag_t dir);

protected:
    BwkLevel * _level;				// The current level this object exists within
    
private:
    pos_t _position;				// Position of this object in the play area
    pos_t _destination;				// Current destination for this object's movement	
    int _layer;             		// Layer the object currently resides in
	object_type_t _type;    		// The object's type
	push_type_t _push_strength;		// The type of push this object creates when moving
	push_type_t _push_resistance;	// How stoic this object is to a push from another object	
	Gosu::Image * _image;   		// The image/sprite associated with this object.
	int _speed;						// Current speed of the object's motions
	
	unsigned long _time;			// Used in timing events in order to smooth animation
	int _msRoundOff;				// Carry-over of millisecs when doing timing events

	std::vector<Gosu::Image*> _frames;  // All the frames in the animation sequence.
	int _anim_rate;						// The animation speed, determined at animation start
	bool _animating;					// Whether this object is currently animating
	unsigned int _cur_frame;            // Current frame of the animation
};

/**
 *  Sets the initial position of this object on screen( in pixels )
 */
inline void BwkObject::setPosition( int x, int y )
{
    _position.x = x;
    _position.y = y;
}

/**
 *  Sets a destination. Every update, the object will move towards this position
 */
inline void BwkObject::setDestination( int x, int y )
{
    _destination.x = x;
    _destination.y = y;
}

/**
 *  Sets the current destination to the current position, effectively halting
 *  any movement.
 */
inline void BwkObject::stopMovement()
{
    setDestination( x(), y() );
}

/**
 *  An object is moving if the destination is different than the current location.
 */
inline bool BwkObject::isMoving()
{
    return ( destX() != x() || destY() != y() );
}

/**
 *  Starts up and animation and calculates a play rate
 */
inline void BwkObject::beginAnimation(int rate ) {
    _animating = true;
    _anim_rate = rate * (_frames.size() * _frames.size() );
}

/**
 *  Called whenever another object is in the EXACT same space as this one. This handles
 *  objects which are collected, pressed, etc.
 */
inline void BwkObject::cover(BwkObject * other)
{
    // Do nothing by default - override to use
}

/**
 *  Convenience function, see resists(object_type_t)
 */
inline bool BwkObject::resists(BwkObject * other)
{
    return resists(other->type());
}

/**
 * Returns whether a queried object type is resisted by this one, meaning that
 * it cannot enter into the same space without attempting a push.
 */
inline bool BwkObject::resists(object_type_t type)
{
    return !(unblockedObjects() & type);
}

/**
 *  Whether a flying object is able to pass over this object. Overload to change
 *  the rule for this situation.
 */
inline bool BwkObject::resistsFlight()
{
    return false;
}

/**
 *  Overload this to return which object types are unblocked by this object
 */
inline int BwkObject::unblockedObjects()
{
    return UNDEFINED;
}

/**
 *	Returns the directions this object can be pushed, if it can be pushed
 *  at all. By default, it can be pushed either horizontal or vertical, 
 *  meaning there is no real restriction. Overload to change this.
 */
inline int BwkObject::pushableDirections()
{
	return HORZ_DIR | VERT_DIR;
}

#endif // __BWK_OBJECT_DEFINED__
