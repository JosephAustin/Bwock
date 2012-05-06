/**
 * @file    BwkLevel.hpp
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


#ifndef __BWK_LEVEL_DEFINED__
#define __BWK_LEVEL_DEFINED__

#include <fstream>
#include <vector>
#include <string>

class BwkObject;
class BwkPlayer;
class BwkWallObject;
class BwkBoulderObject;
class BwkMarbleObject;
class BwkSliderObject;
class BwkKeyObject;
class BwkDoorObject;
class BwkSwitchObject;

/**
 *  A level of Bwock, with all the objects needed to create a puzzle.
 */
class BwkLevel
{
public:
    // The layers a map may have
    enum layer_t {
		TERRAIN = 0,
		GROUND,
		LAYER_COUNT };

public:
    BwkLevel();
    ~BwkLevel();

public:
    unsigned int index() const;
    unsigned int tileSize() const;
    unsigned int mapWidth() const;
    unsigned int mapHeight() const;
    unsigned int xOffset() const;
    unsigned int yOffset() const;

    BwkPlayer * player() const;
    BwkDoorObject * exitDoor() const;
    BwkSwitchObject * killSwitch() const;

    std::vector<BwkObject*>        allObjects() const;
    std::vector<BwkObject*>         allEnemies() const;
    std::vector<BwkWallObject*>    allWalls() const;
    std::vector<BwkBoulderObject*> allBoulders() const;
    std::vector<BwkKeyObject*>     allKeys() const;
    std::vector<BwkDoorObject*>    allDoors() const;

    void addToDeathRow( BwkObject * obj);
	void executeDeathRow();
	void setSurrogate( BwkObject * surrogate);
	void update();
	void addObject( BwkObject * obj );

	std::string author() const;
	std::string title() const;

	int load(std::string * error);

private:
    template <typename Type> void _removeFromVector( BwkObject * query, std::vector<Type> & vect );

    int _loadFile(std::ifstream & file,  std::string * error );
    char _getNextCharacter(std::ifstream & file);
    void _generateObject( const char tile, int x, int y, int layer );
	void _readHeaderData(std::ifstream & file, std::string * data);

private:
    unsigned int _tile_size;        // The x/y dimension for each tile
    unsigned int _map_width;        // Width of the play area in tiles
    unsigned int _map_height;       // Height of the play area in tiles
    unsigned int _x_offset;         // Offset of map in pixels along the X
    unsigned int _y_offset;         // Offset of map in pixels along the Y

    BwkPlayer * _player;            // The player object
    BwkDoorObject * _exit_door;     // The door to exit this level
    BwkSwitchObject * _kill_switch; // The switch which kills all opponents

	BwkObject* _surrogate;			//  If set, this object's update() replaces all update calls.

    std::vector<BwkObject*>         _all_objects;   // All objects loaded
    std::vector<BwkObject*>          _all_enemies;   // All enemies loaded
    std::vector<BwkWallObject*>     _all_walls;     // All walls loaded
    std::vector<BwkBoulderObject*>  _all_boulders;  // All boulders loaded
    std::vector<BwkMarbleObject*>   _all_marbles;   // All marbles loaded
    std::vector<BwkSliderObject*>   _all_sliders;   // All sliders loaded
    std::vector<BwkKeyObject*>      _all_keys;      // All keys loaded

    std::vector<BwkObject*>         _death_row;		// Objects to be destroyed

	std::string _author;			// Author of the level
	std::string _title;
};

/**
 *  @return The size to draw each tile
 */
inline unsigned int BwkLevel::tileSize() const
{
    return _tile_size;
}

/**
 *  @return The map width in tiles
 */
inline unsigned int BwkLevel::mapWidth() const
{
    return _map_width;
}

/**
 *  @return The map height in tiles
 */
inline unsigned int BwkLevel::mapHeight() const
{
    return _map_height;
}

/**
 *  @return The X offset in pixels
 */
inline unsigned int BwkLevel::xOffset() const
{
    return _x_offset;
}

/**
 *  @return The Y offset in pixels
 */
inline unsigned int BwkLevel::yOffset() const
{
    return _y_offset;
}

/**
 *  @return The player object
 */
inline BwkPlayer * BwkLevel::player() const
{
    return _player;
}

/**
 *  @return The door object which exits this level
 */
inline BwkDoorObject * BwkLevel::exitDoor() const
{
    return _exit_door;
}

/**
 *  @return The switch to kill all enemies
 */
inline BwkSwitchObject * BwkLevel::killSwitch() const
{
    return _kill_switch;
}

/**
 *  @return All the objects owned by this level
 */
inline std::vector<BwkObject*> BwkLevel::allObjects() const
{
    return _all_objects;
}

/**
 *  @return All the objects which are enemies
 */
inline std::vector<BwkObject*> BwkLevel::allEnemies() const
{
    return _all_enemies;
}

/**
 *  @return All the objects which are walls
 */
inline std::vector<BwkWallObject*> BwkLevel::allWalls() const
{
    return _all_walls;
}

/**
 *  @return All the objects which are boulders
 */
inline std::vector<BwkBoulderObject*> BwkLevel::allBoulders() const
{
    return _all_boulders;
}

/**
 *  @return All the objects which are keys
 */
inline std::vector<BwkKeyObject*> BwkLevel::allKeys() const
{
    return _all_keys;
}

/**
 * @return The author of this level
 */
inline std::string BwkLevel::author() const
{
	return _author;
}

inline std::string BwkLevel::title() const
{
	return _title;
}


#endif // __BWK_LEVEL_DEFINED__
