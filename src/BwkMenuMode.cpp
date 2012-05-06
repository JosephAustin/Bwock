/**
 * @file    BwkMenuMode.cpp
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

#include "BwkMenuMode.hpp"
#include "BwkGameMode.hpp"
#include "BwkPlayer.hpp"

#include "BwkApplication.hpp"

// Singleton initialization
BwkMenuMode * BwkMenuMode::_instance = NULL;

/**
 *  CTOR
 */
BwkMenuMode::BwkMenuMode()
{
	_bg = bwk_fetch(BwkSlots::BWK_IMG_MENU_BG);
	_bgScrollHorz = _bgScrollVert = 0;
	_currentOption = 0;
	_queuedReturn = this;
	_bwock = new BwkPlayer(NULL);
	_bwock->beginAnimation(50);
	
	_mainOptions.push_back(BwkSlots::BWK_IMG_MENU_START);
	//_mainOptions.push_back(BwkSlots::BWK_IMG_MENU_GRAPHICS);
	//_mainOptions.push_back(BwkSlots::BWK_IMG_MENU_SOUND);
	_mainOptions.push_back(BwkSlots::BWK_IMG_MENU_QUIT);
	//_gfxOptions.push_back(BwkSlots::BWK_IMG_MENU_RES);
	//_gfxOptions.push_back(BwkSlots::BWK_IMG_MENU_FS);
	//_gfxOptions.push_back(BwkSlots::BWK_IMG_MENU_BACK);
	//_soundOptions.push_back(BwkSlots::BWK_IMG_MENU_SFX);
	//_soundOptions.push_back(BwkSlots::BWK_IMG_MENU_MUSIC);
	//_soundOptions.push_back(BwkSlots::BWK_IMG_MENU_BACK);
	
	_curOptions = &_mainOptions;
}

/**
 * This recieves delegation from the application's update function. Then it can
 * either delegate to an overlay or pass control to the gameUpdate() function.
 *
 * @return next mode to be updated. To persist, return a "this" pointer.
 */
BwkMode * BwkMenuMode::update()
{
	_bwock->update();
	
	_bgScrollHorz = _bgScrollHorz + 0.005;
	_bgScrollVert = _bgScrollVert + 0.005;
	
	if( (int)_bgScrollHorz >= 1.0 ) {
		_bgScrollHorz = 0;
	}
	if( (int)_bgScrollVert >= 1.0 ) {
		_bgScrollVert = 0;
	}
	
	if( _queuedReturn == this ) {
		if( !bwk_input()->down(Gosu::kbReturn) ) {
			_queuedReturn = NULL;
		}
	}
	else if( !_queuedReturn ) {
		if( bwk_input()->down(Gosu::kbReturn) ) {
			switch( (*_curOptions)[_currentOption] ) {
				case BwkSlots::BWK_IMG_MENU_START:
					_queuedReturn = BwkGameMode::instance();
					break;
				case BwkSlots::BWK_IMG_MENU_QUIT:
					return NULL;
				case BwkSlots::BWK_IMG_MENU_GRAPHICS:
					_curOptions = &_gfxOptions;
					_currentOption = 0;
					break;
				case BwkSlots::BWK_IMG_MENU_SOUND:
					_curOptions = &_soundOptions;
					_currentOption = 0;
					break;
				case BwkSlots::BWK_IMG_MENU_BACK:
					_curOptions = &_mainOptions;
					_currentOption = 0;
					_queuedReturn = this;
					break;
				default:
					break;						
			}
		}
	}
	else if( !bwk_input()->down(Gosu::kbReturn) ) {
		BwkMode * return_mode = _queuedReturn;
		_queuedReturn = this;
		return return_mode;
	}
	
	return this;
}

/**
 *  Handler for all draw events delegated to this mode
 */
void BwkMenuMode::draw()
{
	const int NUM_OPTIONS = _curOptions->size();
	int x_tiles = BwkApplication::VIRTUAL_HEIGHT / _bg->height();
	int y_tiles = BwkApplication::VIRTUAL_WIDTH / _bg->width();
	int x_offset = _bgScrollHorz * _bg->width();
	int y_offset = _bgScrollVert * _bg->height();
	
	// Draw the background
	for( int y = -1; y < (x_tiles + y_offset + 1); y++ ) {
		for( int x = -1 - x_offset; x < (y_tiles + 1); x++ ) {
			_bg->draw(	(x + _bgScrollHorz) * _bg->width(),
						(y - _bgScrollVert) * _bg->height(), 
						0);
		}
	}
	
	// Draw the options
	for( int i = 0; i < NUM_OPTIONS; i++ ) {
		Gosu::Image * image = bwk_fetch((*_curOptions)[i]);
		const int pillow = 50;

		int total_height = (image->height() * NUM_OPTIONS) + (pillow * NUM_OPTIONS);
		int start_x = (BwkApplication::VIRTUAL_HEIGHT / 2) - (total_height / 2);
		
		int x = (BwkApplication::VIRTUAL_WIDTH / 2) - (image->width() / 2);
		int y = start_x + (( image->height() + pillow ) * i);
		
		if( _currentOption == i ) {
			_bwock->setPosition(x - _bwock->image()->width() - 10, y);
			_bwock->image()->draw(_bwock->x(), _bwock->y(), 2);
			bwk_video()->drawQuad(x, y, Gosu::Color::WHITE, 
				x + image->width(), y, Gosu::Color::GRAY, 
				x + image->width(), y + image->height(), Gosu::Color::WHITE, 
				x, y + image->height(), Gosu::Color::GRAY, 
				1);
		}
		image->draw(x, y, 1);
	}
}

/**
 *  When a key is pressed...
 *
 *  @param button   The button pressed
 */
void BwkMenuMode::buttonDown(Gosu::Button btn)
{
	if( (btn.id() == Gosu::kbUp)  &&  (_currentOption > 0)) {
		_currentOption--;
	}
	else if( (btn.id() == Gosu::kbDown) && (_currentOption < (_curOptions->size() - 1)) ) {
		_currentOption++;
	}
}

/**
 *  When any key is released...
 *
 *  @param button The button pressed
 */
void BwkMenuMode::buttonUp(Gosu::Button)
{
}
