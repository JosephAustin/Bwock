/**
 * @file    BwkGameMode.cpp
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
#include <Gosu/Input.hpp>

#include "BwkGameMode.hpp"
#include "BwkGameOverlay.hpp"
#include "BwkPausedGameOverlay.hpp"
#include "BwkTextGameOverlay.hpp"
#include "BwkLevel.hpp"
#include "BwkObject.hpp"
#include "BwkTitleMode.hpp"
#include "BwkMenuMode.hpp"
#include "BwkApplication.hpp"
#include "BwkPlayer.hpp"
#include "BwkTiles.hpp"
#include "BwkGameSettings.hpp"


// Singleton initialization
BwkGameMode * BwkGameMode::_instance = NULL;

/**
 * CTOR
 */
BwkGameMode::BwkGameMode()
{
    _currentLevel = NULL;
}

/**
 * DTOR
 */
BwkGameMode::~BwkGameMode()
{
    // Unload any queued overlays
    _unloadOverlays();

    // unload the current level
    if (_currentLevel) {
        delete _currentLevel;
    }
}

/**
 * This recieves delegation from the main application's update function. It will
 * either delegate to an overlay, or pass control to the gameUpdate() function.
 *
 * @return next game mode to be updated. To persist, return a "this" pointer.
 */
BwkMode * BwkGameMode::update()
{
	BwkMode * return_mode = this;	// The return value for this call
	bool modal_overlay = false;		// Whether a modal overlay exists in queue

    BwkManager::instance()->playMusic(BwkSlots::BWK_MUSIC_BG);

	// See if any overlays are modal
	for( int i = 0; i < _overlays.size(); i++ ) {
		if(_overlays.at(i)->isModal()) {
			modal_overlay = true;
			break;
		}
	}

	// Update if no overlays are modal
    if( !modal_overlay ) {
        // Ensure that the correct level stays loaded
        if (!_currentLevel ) {
			if(_loadLevel() < 0) {
				return NULL;
			}
        }
        // Allow the game update function to determine the return value
        else {
			return_mode = _gameUpdate();
		}
	}

	// Update the overlays. Stop if a modal overlay is reached.
	for( int i = 0; i < _overlays.size(); i++ ) {
		bool modal = _overlays.at(i)->isModal();	// Is this overlay modal?

		// Update the overlay and remove it if it returns false
		if(!_overlays.at(i)->update(_currentLevel)) {
			delete _overlays.at(i);
			_overlays.erase(_overlays.begin() + i);

			// Step back one index
			i--;
		}

		// Break if the deleted overlay was modal
		if( modal ) {
			break;
		}
	}

    // If switching to a different mode, stop the background music.
    if( return_mode != this ) {
        BwkManager::instance()->stopMusic();
    }

	// Return the decided mode
    return return_mode;
}

/**
 *  This picks up from update() when there are no modal overlays
 *
 *  @return the next game mode to be loaded. Return "this" to persist.
 */
BwkMode * BwkGameMode::_gameUpdate()
{
    BwkMode * ret = this; // Final return value.

    // Advance the level if the player has won
    if (_currentLevel->player()->hasWon() ) {

        // If there are no more levels, start over for now
        if ( !(BwkGameSettings::instance()->advanceLevel()) ) {
            BwkGameSettings::instance()->importLevelFiles();
        }

        // Try to load the current level
        if(_loadLevel() < 0) {
            return NULL;
        }
    }
    // Restart the level if the player has lost
    else if (_currentLevel->player()->hasLost() ) {
        if(_loadLevel() < 0) {
            return NULL;
        }
    }
    // 'P' pauses the game via overlay
    else if (bwk_input()->down(Gosu::kbP)) {
        _overlays.insert(_overlays.begin(), new BwkPausedGameOverlay);
    }
    // Backspace key resets the level
    else if (bwk_input()->down(Gosu::kbBackspace)) {
        if( _loadLevel() < 0 ) {
            return NULL;
        }
    }
    // Escape key goes to the menu screen
    else if (bwk_input()->down(Gosu::kbEscape)) {
        ret = BwkMenuMode::instance();

        // Return this class to its initial state.
        delete _currentLevel;
        _currentLevel = NULL;
        _unloadOverlays();
    }
    // Normal game play state
    else {
        // Update level
        _currentLevel->update();
    }

    return ret;
}

/**
 *  Recieves delegation from the BwkApplication's draw() function, and draws as
 *  needed depending on the overlay state. All the drawing is done here instead
 *  of within the level class so that it will be better contained.
 *
 *  @see update()
 */
void BwkGameMode::draw()
{
    // Draw the level
    if (_currentLevel) {
        int tile_size = _currentLevel->tileSize(); // Capture the tile size of this level
        double stretch_factor = (double) tile_size / BwkTiles::MAX_TILE_SIZE; // How much to stretch/squeeze the images

        // Fill the entire screen with a background of walls
        for (int y = 0; y <= BwkApplication::VIRTUAL_HEIGHT / tile_size; y++) {
            for (int x = 0; x <= BwkApplication::VIRTUAL_WIDTH / tile_size; x++) {
                // Some tricky checking to make sure we only draw the needed bushes; BIG performance difference!
                if (	((x * tile_size) < (int)_currentLevel->xOffset()) ||
                        ((y * tile_size) < (int) _currentLevel->yOffset()) ||
                        (((x + 1) * tile_size) >= (int) (_currentLevel->xOffset() + (_currentLevel->mapWidth() * tile_size))) ||
                        (((y + 1) * tile_size) >= (int) (_currentLevel->yOffset() + (_currentLevel->mapHeight() * tile_size)))) {
                    bwk_fetch(BwkSlots::BWK_IMG_WALL_LOW_TOP)->draw((x * tile_size), (y * tile_size),
                            0, stretch_factor, stretch_factor);
                }
            }
        }

        // Fill the play area with a background of grass
        for (unsigned int y = 0; y < _currentLevel->mapHeight(); y++) {
            for (unsigned int x = 0; x < _currentLevel->mapWidth(); x++) {
                bwk_fetch(BwkSlots::BWK_IMG_GRASS)->draw(_currentLevel->xOffset() + (x * tile_size),
                        _currentLevel->yOffset() + (y * tile_size),
                        0, stretch_factor, stretch_factor);
            }
        }

        // Draw every object at its current position
        BOOST_FOREACH(BwkObject * obj, _currentLevel->allObjects())
        {
            Gosu::Color filter = Gosu::Colors::white; // Filter color for drawing a given imag

            // Draw flying objects above a shadow.
            if ((obj == _currentLevel->player()) && _currentLevel->player()->flying()) {
                // Shadow first
                bwk_fetch(BwkSlots::BWK_IMG_SHADOW)->draw(obj->x(), obj->y(),
                        obj->layer(), stretch_factor, stretch_factor);
                // Actual object
                obj->image()->draw(obj->x(), obj->y() - (tile_size / 2),
                        100, stretch_factor, stretch_factor, filter);
            }
            else {
                double layer = obj->layer(); // Layer to draw on

                // Draw Bwock one level higher since he walks on top of stuff on the same layer
                if (obj == _currentLevel->player()) {
                    layer++;
                }
                // If an player can currently fly over the current object, darken it on draw
                else if ((_currentLevel->player()->flying()) && !(obj->resistsFlight()) ) {
                    if ((obj->y()-(int) _currentLevel->yOffset()) > -1) {
                        filter = Gosu::Colors::gray;
                    }
                }
                // Draw every object in any case
                obj->image()->draw(obj->x(), obj->y(), layer, stretch_factor, stretch_factor, filter);
            }
        }
    }

    // If there are overlays, draw them. Stop if a modal overlay is reached.
	for( int i = 0; i < _overlays.size(); i++ ) {
		_overlays.at(i)->draw(_currentLevel);

		// Check for modality
		if( _overlays.at(i)->isModal() ) {
			break;
		}
	}

}

/**
 *  Button press check
 */
void BwkGameMode::buttonDown(Gosu::Button btn)
{
	// Cheat code ctrl-c skips levels
	if( (btn.id() == Gosu::kbC) && (bwk_input()->down(Gosu::kbLeftControl)) ) {
		_currentLevel->player()->win();
	    _unloadOverlays();
	}
	// Toggle muting for music
	else if( btn.id() == Gosu::kbM ) {
		BwkGameSettings::instance()->toggleMusicMute();
	}
	// Toggle muting for sound (this one may need a popup)
	else if( btn.id() == Gosu::kbS ) {
		BwkGameSettings::instance()->toggleSoundMute();
	}
}

/**
 * Briefly display the author of the level
 */
void BwkGameMode::_displayLevelAuthor()
{
	if( _currentLevel ) {
		std::string title_str = _currentLevel->title();
		std::string author_str = _currentLevel->author();
		std::wstring title_wstr(title_str.length(), L' ');
		std::wstring author_wstr(author_str.length(), L' ');

		if( (title_str.length() == 0) && (author_str.length() == 0) ) {
			return;
		}

		if( title_str.length() == 0 ) {
			title_str = "Level";
			title_wstr = std::wstring(title_str.length(), L' ');
		}

		copy(title_str.begin(),title_str.end(),title_wstr.begin());
		copy(author_str.begin(),author_str.end(),author_wstr.begin());

		if( author_str.size() == 0 ) {
			_overlays.push_back(new BwkTextGameOverlay(3000, title_wstr ));
		}
		else {
			_overlays.push_back(new BwkTextGameOverlay(3000, title_wstr + std::wstring(L" by ") + author_wstr));
		}
	}
}

/**
 *  Erases the current level (if any) and loads a new one.
 */
int BwkGameMode::_loadLevel()
{
	std::string error;

    if (_currentLevel) {
        delete _currentLevel;
    }

    _currentLevel = new BwkLevel();

    _unloadOverlays();
    srand(5);

	if( _currentLevel->load(&error) < 0 ) {
		printf( "Failed to load level due to the following error: %s\n", error.c_str() );
		return -1;
	}

    _displayLevelAuthor();

	return 0;
}

/**
 *  Deletes any overlays loaded
 */
void BwkGameMode::_unloadOverlays()
{
    while (!_overlays.empty()) {
        delete _overlays.back();
        _overlays.pop_back();
    }
}
