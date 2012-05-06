/**
 * @file    BwkLevel.cpp
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

#include <string>
#include "boost/foreach.hpp"
#include "boost/lexical_cast.hpp"

#include "BwkApplication.hpp"
#include "BwkLevel.hpp"
#include "BwkObject.hpp"
#include "BwkWallObject.hpp"
#include "BwkTiles.hpp"
#include "BwkPlayer.hpp"
#include "BwkManager.hpp"
#include "BwkBoulderObject.hpp"
#include "BwkMarbleObject.hpp"
#include "BwkSliderObject.hpp"
#include "BwkPusherObject.hpp"
#include "BwkKeyObject.hpp"
#include "BwkDoorObject.hpp"
#include "BwkWizardObject.hpp"
#include "BwkPuddiniObject.hpp"
#include "BwkScorcherObject.hpp"
#include "BwkBroBroObject.hpp"
#include "BwkSwitchObject.hpp"
#include "BwkSpringObject.hpp"
#include "BwkWaterObject.hpp"
#include "BwkWeedsObject.hpp"
#include "BwkTimerBlockObject.hpp"
#include "BwkGameSettings.hpp"

/**
 * CTOR
 *
 * @param level_index   The index of the current level.
 */
BwkLevel::BwkLevel()
{
    // Initialize pointers
    _player = NULL;
    _exit_door = NULL;
    _kill_switch = NULL;
	_surrogate = NULL;

	// Default author
	_author = "";
	_title = "";
}

/**
 * 	DTOR
 */
BwkLevel::~BwkLevel()
{
    // Just delete every object on destruction; no need to worry about the lists
    // since this object will be gone.
    BOOST_FOREACH( BwkObject * obj, _all_objects ) {
        delete obj;
    }
}


/**
 *	Load a level file into memory
 */
int BwkLevel::load(std::string * error)
{
    std::string filename;       // File to be loaded
	std::ifstream file;			// Actual file

	// Determine the location of the levels directory
#ifdef WIN32
	filename = ".\\resources\\levels\\";
#else
	filename = "./resources/levels/";
#endif

	// Build file name from the level index
    filename += BwkGameSettings::instance()->getCurrentLevel();
    filename += ".bwk";

    // Open the file
    file.open( filename.c_str() );

    // Load the file and crash on failure
	if( _loadFile(file, error) < 0 ) {
		return -1;
	}

    // Close the file
    file.close();

    // Make all objects stay put when starting
    BOOST_FOREACH( BwkObject * obj, _all_objects ) {
        obj->stopMovement();
    }

	// Success!
	return 0;
}

/**
 *	Level update loop
 */
void BwkLevel::update()
{
	// Update a surrogate if one exists. See the header for info on surrogates.
	if( _surrogate ) {
		_surrogate->update();
	}
	else {
		// Update all objects
		BOOST_FOREACH( BwkObject * object, _all_objects ) {
			object->update();
			if( _surrogate ) {
				break;
			}
		}
        // Empty out 'dead' objects
        executeDeathRow();
	}
}

/**
 *  Removes an object entirely from a single vector of some defined type
 */
template <typename Type> void BwkLevel::_removeFromVector( BwkObject * query, std::vector<Type> & vect )
{
    for( unsigned int i = 0; i < vect.size(); i++ ) {
        if( vect[i] == query ) {
            vect.erase( vect.begin() + i );
        }
    }
}

/**
 * Add an object to all objects. Not added to any of the other lists. This exists mostly so that
 * projectiles can load themselves in.
 */
void BwkLevel::addObject( BwkObject * obj )
{
	_all_objects.push_back(obj);
}

/**
 *  Loads tiles from a given file
 *
 *  @param file     File stream to open for data
 */
int BwkLevel::_loadFile(std::ifstream& file, std::string * error )
{
	bool map_mode = false;	// True when entering the MAP section of the level file

	// Parse through the header data
	while( !map_mode && file.good() ) {
		char next = _getNextCharacter(file);	// The next available character

		// Skim over comments
		if( next == ';' ) {
			do {
				next = file.get();
			} while( next != '\n' && file.good() );
		}
		// Read header tags
		else {
			std::string str;	// The full tag string

			// Construct the tag string
			do {
				str += next;
				next = file.get();
			} while( (next != ' ') && (next != '\n') && (next != '\t') && (next != '\r') && file.good() );

			// Read header data for the tag
			if( str == "TITLE" ) {
				_readHeaderData(file, &_title);
			}
			else if( str == "AUTHOR" ) {
				_readHeaderData(file, &_author);
			}
			// If the tag begins the map section, this loop ends
			else if( str == "MAP" ) {
				map_mode = true;

				// Get the width
				file >> _map_width;

				// Skim the 'x'
				while (file.get() != 'x');

				// Get the height
				file >> _map_height;
			}
		}
	}

	// Error out if no map section is defined
	if( !map_mode ) {
		*error = "No MAP section defined";
		return -1;
	}

	// Error out if the heighth or width are zero
	if( (_map_height == 0) || (_map_width == 0) ) {
		*error = "No valid map dimensions entered. Format is WIDTH x HEIGHT after the 'MAP' tag.";
		return -1;
	}

    // The tile size for this level starts at the max size
    _tile_size = BwkTiles::MAX_TILE_SIZE;

    // Now we size down the tile size until the level fits neatly.
    while( (mapWidth() * tileSize()) >= (unsigned)BwkApplication::VIRTUAL_WIDTH - 75) {
        _tile_size -= 2;

        //  limit the size
        if( tileSize() == 6 ) {
            break;
        }
    }
    // Repeat for height
    while( (mapHeight() * tileSize()) >= (unsigned) BwkApplication::VIRTUAL_HEIGHT - 75) {
        _tile_size -= 2;

        // limit the size
        if( tileSize() == 6 ) {
            break;
        }
    }

    // Now calculate the x and y offsets
    _x_offset = (int)((BwkApplication::VIRTUAL_WIDTH - (int)(tileSize() * mapWidth()) ) / 2.0 );
    _y_offset = (int)((BwkApplication::VIRTUAL_HEIGHT - (int)(tileSize() * mapHeight()) ) / 2.0 );

    // Load the play area from the actual file
    for( int z = 0; z < LAYER_COUNT; z++ ) {
        for( unsigned int y = 0; y < mapHeight(); y++ ) {
            for( unsigned int x = 0; x < mapWidth(); x++ ) {
				char next = _getNextCharacter(file);	// The next available character

				// Skim over comments
				while( next == ';' ) {
					do {
						next = file.get();
					} while( next != '\n' && file.good() );
					next = _getNextCharacter(file);
				}

				// Error out if the number of tiles did not agree with the dimensions
				if( file.eof() ) {
					*error = "Not enough tiles present.";
					return -1;
				}

				// Create an object for the current tile
                _generateObject( next, x, y, z );
            }
        }
    }

    //  Add some walls on top of the map for a psuedo-3D look. By using actual
    //  objects, the tiles will correct themselves appropriately.
    for( unsigned int x = 0; x < mapWidth(); x++ ) {
        _generateObject(BwkTiles::TILE_LOW_WALL, x, -1, TERRAIN );
    }

    // Reposition the exit so that it's on the level perimeter
    exitDoor()->reposition();

    // Fix all the wall tiles so they'll look nicer
    BOOST_FOREACH( BwkWallObject * wall, allWalls() ) {
        wall->fixTiles();
    }

	return 0;
}


/**
 * 	Reads a string of header data
 */
void BwkLevel::_readHeaderData(std::ifstream & file, std::string * data)
{
	char next = _getNextCharacter(file);	// The next available character

	// Construct the data string out of characters in the file prior to the end of line
	do {
		*data += next;
		next = file.get();
		if( next == '\t' ) {
			next = ' ';
		}
	} while( (next != '\n') && (next != '\r') && file.good() );
}

/**
 *  Finds the next character in the file, skipping over newlines
 *
 *  @param file     File stream to read from
 */
char BwkLevel::_getNextCharacter(std::ifstream& file)
{
    char ret;       // Discovered value

    // Ignore spaces and newlines entirely
    do {
        ret  = file.get();
    } while( ((ret == ' ') || (ret == '\n') || (ret == '\t') || (ret == '\r')) && file.good() );

	if( file.bad() ) {
		ret = '\n';
	}

    return ret;
}

/**
 *  Turn the tiles loaded into drawable objects. They are sorted into the many
 *  vectors kept by this class.
 *
 *  @param tile     Character-based tile to look up and generate
 *  @param x        X position of object in tiles without the offset.
 *  @param y        Y position of object in tiles without the offset.
 *  @param layer    Layer the object is on.
 */
void BwkLevel::_generateObject( const char tile, int x, int y, int layer )
{
    BwkObject * object = NULL;         // Object to be added

    // Terrain tiles
    if( layer == TERRAIN ) {
        switch( tile ) {
            case BwkTiles::TILE_WEEDS: {
				BwkWeedsObject * weeds = new BwkWeedsObject(this);
                object = weeds;
                break;
            }

			case BwkTiles::TILE_WATER: {
				BwkWaterObject * water = new BwkWaterObject(this);
                object = water;
                break;

			}
            case BwkTiles::TILE_LOW_WALL:
            case BwkTiles::TILE_HIGH_WALL:
            {
                BwkWallObject * wall;   // Wall to be added

                // Add either a low or high wall depending on the tile
                if( tile == BwkTiles::TILE_LOW_WALL ) {
                    wall = new BwkWallObject(this, BwkWallObject::LOW_WALL);
                }
                else {
                    wall = new BwkWallObject(this, BwkWallObject::HIGH_WALL);
                }
                _all_walls.push_back(wall);
                object = wall;
                break;
            }
            case BwkTiles::TILE_START: {
                if( player() ) {
                    return;
                }
                else {
                    object = _player = new BwkPlayer(this);
                }
                break;
            }
            case BwkTiles::TILE_EXIT: {
                if( exitDoor() ) {
                    return;
                }
                else {
                    object = _exit_door = new BwkDoorObject(this);
                }
                break;
            }
            default: break;
        }
    }
    // Ground tiles
    else if( layer == GROUND ) {
        switch( tile ) {
            case BwkTiles::TILE_BOULDER: {
                BwkBoulderObject * boulder = new BwkBoulderObject(this);
                _all_boulders.push_back(boulder);
                object = boulder;
                break;
            }
            case BwkTiles::TILE_MARBLE: {
                BwkMarbleObject * marble = new BwkMarbleObject(this);
                _all_marbles.push_back(marble);
                object = marble;
                break;
            }
            case BwkTiles::TILE_VERT_SLIDER: {
                BwkSliderObject * slider = new BwkSliderObject(this, BwkSliderObject::VERT_DIR);
                _all_sliders.push_back(slider);
                object = slider;
                break;
            }
            case BwkTiles::TILE_HORZ_SLIDER: {
                BwkSliderObject * slider = new BwkSliderObject(this, BwkSliderObject::HORZ_DIR);
                _all_sliders.push_back(slider);
                object = slider;
                break;
            }
            case BwkTiles::TILE_LEFT_PUSHER: {
                BwkPusherObject * pusher = new BwkPusherObject(this, BwkObject::LEFT_DIR);
                object = pusher;
                break;
            }
            case BwkTiles::TILE_RIGHT_PUSHER: {
                BwkPusherObject * pusher = new BwkPusherObject(this, BwkObject::RIGHT_DIR);
                object = pusher;
                break;
            }
            case BwkTiles::TILE_UP_PUSHER: {
                BwkPusherObject * pusher = new BwkPusherObject(this, BwkObject::UP_DIR);
                object = pusher;
                break;
            }
            case BwkTiles::TILE_DOWN_PUSHER: {
                BwkPusherObject * pusher = new BwkPusherObject(this, BwkObject::DOWN_DIR);
                object = pusher;
                break;
            }
            case BwkTiles::TILE_KEY: {
                BwkKeyObject * key = new BwkKeyObject(this);
                _all_keys.push_back(key);
                object = key;
                break;
            }
            case BwkTiles::TILE_WIZARD: {
                BwkWizardObject * wizard = new BwkWizardObject(this);
                _all_enemies.push_back(wizard);
                object = wizard;
                break;
            }
            case BwkTiles::TILE_RIGHT_SCORCHER: {
                BwkScorcherObject * scorcher = new BwkScorcherObject(this, BwkObject::RIGHT_DIR);
                _all_enemies.push_back(scorcher);
                object = scorcher;
                break;
            }
            case BwkTiles::TILE_LEFT_SCORCHER: {
                BwkScorcherObject * scorcher = new BwkScorcherObject(this, BwkObject::LEFT_DIR);
                _all_enemies.push_back(scorcher);
                object = scorcher;
                break;
            }
            case BwkTiles::TILE_UP_SCORCHER: {
                BwkScorcherObject * scorcher = new BwkScorcherObject(this, BwkObject::UP_DIR);
                _all_enemies.push_back(scorcher);
                object = scorcher;
                break;
            }
            case BwkTiles::TILE_DOWN_SCORCHER: {
                BwkScorcherObject * scorcher = new BwkScorcherObject(this, BwkObject::DOWN_DIR);
                _all_enemies.push_back(scorcher);
                object = scorcher;
                break;
            }

            case BwkTiles::TILE_PUDDINI_HORZ:
            {
                BwkPuddiniObject * puddini = new BwkPuddiniObject(this, BwkObject::HORZ_DIR);
                _all_enemies.push_back(puddini);
                object = puddini;
                break;
            }
            case BwkTiles::TILE_PUDDINI_VERT:
            {
                BwkPuddiniObject * puddini = new BwkPuddiniObject(this, BwkObject::VERT_DIR);
                _all_enemies.push_back(puddini);
                object = puddini;
                break;
            }
            case BwkTiles::TILE_BROBRO:
			{
				BwkBroBroObject * brobro = new BwkBroBroObject(this);
				_all_enemies.push_back(brobro);
				object = brobro;
				break;
			
			}			
            case BwkTiles::TILE_SWITCH: {
                if( killSwitch() ) {
                    return;
                }
                else {
                    object = _kill_switch = new BwkSwitchObject(this);
                }
                break;
            }
            case BwkTiles::TILE_SPRING: {
                object = new BwkSpringObject(this);
                break;
            }
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9': {
                object = new BwkTimerBlockObject(this, boost::lexical_cast<int>(tile));
                break;
            }
            default: break;
        }
    }

    // Position objects and add them to the object list
    if( object ) {
        object->setPosition(( x * tileSize()) + xOffset(), ( y * tileSize()) + yOffset() );

	    // Everything on the terrain and ground layer should be shoved up to the
	    // same layer. The terrain layer is imaginary.
#ifdef WIN32
		object->setLayer((layer_t)max(1,layer));
#else
		object->setLayer((layer_t)std::max(1,layer));
#endif

        _all_objects.push_back( object );
    }
}


/**
 *	Adds an object to be destroyed as soon as safely possible
 */
void BwkLevel::addToDeathRow( BwkObject * obj)
{
	_death_row.push_back(obj);
}


/**
 *	Destroy all objects on death row, and remove them appropriately
 */
void BwkLevel::executeDeathRow()
{
	if( !_death_row.empty() ) {
		BOOST_FOREACH( BwkObject * obj, _death_row ) {
			_removeFromVector<BwkObject*>( obj, _all_objects );
			_removeFromVector<BwkBoulderObject*>( obj, _all_boulders );
			_removeFromVector<BwkWallObject*>( obj, _all_walls );
			_removeFromVector<BwkKeyObject*>( obj, _all_keys );
			delete obj;
		}
		_death_row.clear();
	}
}

/**
 *  Set a surrogate to take over the update() operations
 */
void BwkLevel::setSurrogate( BwkObject * surrogate)
{
	_surrogate = surrogate;
}
