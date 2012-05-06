/**
 * @file    BwkApplication.cpp
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

#include <fstream>
#include <irrKlang.h>
#include "BwkApplication.hpp"
#include "BwkGameSettings.hpp"
#include "BwkTitleMode.hpp"
#include "BwkGameMode.hpp"
#include "BwkManager.hpp"


/**
 *  CTOR - Construct window using the graphics settings instance
 */
BwkApplication::BwkApplication()
    : Window(
        BwkGameSettings::instance()->resolutionWidth(),
        BwkGameSettings::instance()->resolutionHeight(),
        BwkGameSettings::instance()->fullScreenMode(),
        10 )
{
	// Caption for the window
    setCaption(L"The Brave Bwock");

    // Use the virtual resolution to keep things looking as expected
    graphics().setResolution(VIRTUAL_WIDTH, VIRTUAL_HEIGHT);

    // Store the application device pointers globally
    BwkManager::instance()->setVideo( &graphics() );
    BwkManager::instance()->setInput( &input() );

    // Load Sprite Images
    bwk_set(  BwkSlots::BWK_BMP_BWOCK_DOWN,         _loadBitmap( L"player_down.png"  ));
    bwk_set(  BwkSlots::BWK_BMP_BWOCK_UP,           _loadBitmap( L"player_up.png"    ));
    bwk_set(  BwkSlots::BWK_BMP_BWOCK_LEFT,         _loadBitmap( L"player_left.png"  ));
    bwk_set(  BwkSlots::BWK_BMP_BWOCK_RIGHT,        _loadBitmap( L"player_right.png"  ));
    bwk_set(  BwkSlots::BWK_BMP_BWOCK_DOWN_FLYING,  _loadBitmap( L"player_down_fly.png"  ));
    bwk_set(  BwkSlots::BWK_BMP_BWOCK_UP_FLYING,    _loadBitmap( L"player_up_fly.png"    ));
    bwk_set(  BwkSlots::BWK_BMP_BWOCK_LEFT_FLYING,  _loadBitmap( L"player_left_fly.png"  ));
    bwk_set(  BwkSlots::BWK_BMP_BWOCK_RIGHT_FLYING, _loadBitmap( L"player_right_fly.png"  ));
    bwk_set(  BwkSlots::BWK_BMP_DOOR,           	_loadBitmap( L"door.png"  ));
    bwk_set(  BwkSlots::BWK_BMP_PUSHER,             _loadBitmap( L"pusher.png" ));
    bwk_set(  BwkSlots::BWK_BMP_WIZARD,             _loadBitmap( L"wizard_idle.png"));
    bwk_set(  BwkSlots::BWK_BMP_PUDDINI,            _loadBitmap( L"puddini.png"));
    bwk_set(  BwkSlots::BWK_BMP_BROBRO_LEFT,        _loadBitmap( L"brobro_left.png"));
    bwk_set(  BwkSlots::BWK_BMP_BROBRO_RIGHT,       _loadBitmap( L"brobro_right.png"));
    bwk_set(  BwkSlots::BWK_BMP_BROBRO_UP,          _loadBitmap( L"brobro_up.png"));
    bwk_set(  BwkSlots::BWK_BMP_BROBRO_DOWN,        _loadBitmap( L"brobro_down.png"));
    bwk_set(  BwkSlots::BWK_BMP_SCORCHER_ASLEEP,    _loadBitmap( L"scorcher_asleep.png"));
    bwk_set(  BwkSlots::BWK_BMP_SCORCHER_AWAKE,     _loadBitmap( L"scorcher_awake.png"));
    bwk_set(  BwkSlots::BWK_BMP_SWITCH,             _loadBitmap( L"switch.png"));
    bwk_set(  BwkSlots::BWK_BMP_SPRING,             _loadBitmap( L"spring.png"));
    bwk_set(  BwkSlots::BWK_BMP_FORK,               _loadBitmap( L"fork.png"));
    bwk_set(  BwkSlots::BWK_BMP_SLIME,              _loadBitmap( L"slime.png"));
    bwk_set(  BwkSlots::BWK_BMP_FIREBALL,           _loadBitmap( L"fireball.png"));
    bwk_set(  BwkSlots::BWK_BMP_TIMER_BLOCK,        _loadBitmap( L"timer_block.png"));

    // Load Static Images
	bwk_set(  BwkSlots::BWK_IMG_MENU_BG,			_loadImage( L"menu_bg.png"));
	bwk_set(  BwkSlots::BWK_IMG_MENU_START,			_loadImage( L"menu_start.png"));
//	bwk_set(  BwkSlots::BWK_IMG_MENU_RESTORE,		_loadImage( L"menu_restore.png"));
	bwk_set(  BwkSlots::BWK_IMG_MENU_GRAPHICS,		_loadImage( L"menu_graphics.png"));
	bwk_set(  BwkSlots::BWK_IMG_MENU_SOUND,			_loadImage( L"menu_sound.png"));	
	bwk_set(  BwkSlots::BWK_IMG_MENU_QUIT,			_loadImage( L"menu_quit.png"));
	bwk_set(  BwkSlots::BWK_IMG_MENU_RES,			_loadImage( L"menu_resolution.png"));
	bwk_set(  BwkSlots::BWK_IMG_MENU_FS,			_loadImage( L"menu_fullscreen.png"));
	bwk_set(  BwkSlots::BWK_IMG_MENU_SFX,			_loadImage( L"menu_sfx.png"));
	bwk_set(  BwkSlots::BWK_IMG_MENU_MUSIC,			_loadImage( L"menu_music.png"));	
	bwk_set(  BwkSlots::BWK_IMG_MENU_BACK,			_loadImage( L"menu_back.png"));
    bwk_set(  BwkSlots::BWK_IMG_GRASS,              _loadImage( L"grass.png" ));
    bwk_set(  BwkSlots::BWK_IMG_WEEDS,              _loadImage( L"weeds.png" ));
    bwk_set(  BwkSlots::BWK_IMG_WALL_LOW_TOP,       _loadImage( L"bush_top.png" ));
    bwk_set(  BwkSlots::BWK_IMG_WALL_LOW_BASE,      _loadImage( L"bush_bottom.png" ));
    bwk_set(  BwkSlots::BWK_IMG_WALL_LOW_ROSES,     _loadImage( L"bush_bottom_roses.png" ));
    bwk_set(  BwkSlots::BWK_IMG_WALL_HIGH_TOP,      _loadImage( L"brick_top.png" ));
    bwk_set(  BwkSlots::BWK_IMG_WALL_HIGH_BASE,     _loadImage( L"brick_bottom.png" ));
    bwk_set(  BwkSlots::BWK_IMG_WALL_HIGH_VINES,    _loadImage( L"brick_bottom_vines.png" ));
    bwk_set(  BwkSlots::BWK_IMG_WATER,              _loadImage( L"water.png" ));
    bwk_set(  BwkSlots::BWK_IMG_BOULDER,            _loadImage( L"boulder.png" ));
    bwk_set(  BwkSlots::BWK_IMG_BOULDER_SUNK,       _loadImage( L"boulder_sunk.png" ));
    bwk_set(  BwkSlots::BWK_IMG_MARBLE,             _loadImage( L"marble.png" ));
    bwk_set(  BwkSlots::BWK_IMG_SLIDER_HORZ,        _loadImage( L"hslider.png" ));
    bwk_set(  BwkSlots::BWK_IMG_SLIDER_VERT,        _loadImage( L"vslider.png" ));
    bwk_set(  BwkSlots::BWK_IMG_KEY,                _loadImage( L"key.png"));
    bwk_set(  BwkSlots::BWK_IMG_SHADOW,             _loadImage( L"shadow.png"));
    bwk_set(  BwkSlots::BWK_IMG_VASILISA,           _loadImage( L"logo.png" ));
    bwk_set(  BwkSlots::BWK_IMG_GOSU,               _loadImage( L"gosu.png" ));
    bwk_set(  BwkSlots::BWK_IMG_FMOD,               _loadImage( L"fmod.png" ));
    bwk_set(  BwkSlots::BWK_IMG_TITLE_SCREEN,       _loadImage( L"title.png" ));
    bwk_set(  BwkSlots::BWK_IMG_PAUSED,             _loadImage( L"paused.png" ));

    // Load Sound Effects
    bwk_set(  BwkSlots::BWK_SOUND_GET_KEY,          _loadSound( "getkey.ogg"));
    bwk_set(  BwkSlots::BWK_SOUND_PUSH,             _loadSound( "push.wav"));
    bwk_set(  BwkSlots::BWK_SOUND_SHOOT,            _loadSound( "shot.wav"));
    bwk_set(  BwkSlots::BWK_SOUND_BOING,            _loadSound( "boing.ogg"));
    bwk_set(  BwkSlots::BWK_SOUND_SPLASH,           _loadSound( "splash.ogg"));

    // Load music
	bwk_set(  BwkSlots::BWK_MUSIC_BG,				_loadSong(  "BwocksSunnyStart.ogg" ));

    // Set the initial game mode to be the title screen.
    _current_mode = BwkTitleMode::instance();
}


/**
 *  Loads an image file from a file name.
 */
Gosu::Bitmap * BwkApplication::_loadBitmap( std::wstring file )
{
#ifdef WIN32
    return new Gosu::Bitmap(Gosu::quickLoadBitmap(L".\\resources\\images\\" + file));
#else
    return new Gosu::Bitmap(Gosu::quickLoadBitmap(L"./resources/images/" + file));
#endif
}


/**
 *  Loads an image file from a file name.
 */
Gosu::Image * BwkApplication::_loadImage( std::wstring file )
{
#ifdef WIN32
    return new Gosu::Image(graphics(), L".\\resources\\images\\" + file, true );
#else
    return new Gosu::Image(graphics(), L"./resources/images/" + file, true );
#endif
}


/**
 *  Loads an audio sample from a file name.
 */
irrklang::ISoundSource * BwkApplication::_loadSound( std::string file )
{
#ifdef WIN32
    return BwkManager::instance()->soundEngine()->
        addSoundSourceFromFile(std::string(".\\resources\\sound\\" + file).c_str());
#else
    return BwkManager::instance()->soundEngine()->
        addSoundSourceFromFile(std::string("./resources/sound/" + file).c_str());
#endif
}

/**
 *  Loads an audio file from a file name
 */
irrklang::ISoundSource * BwkApplication::_loadSong( std::string file )
{
#ifdef WIN32
    return BwkManager::instance()->soundEngine()->
        addSoundSourceFromFile(std::string(".\\resources\\music\\" + file).c_str());
#else
    return BwkManager::instance()->soundEngine()->
        addSoundSourceFromFile(std::string("./resources/music/" + file).c_str());
#endif
}

/**
 * Update the current mode to get the next one. The mode may change itself by
 * returning a pointer to a different mode, or NULL to end the program. It will
 * usually return itself in order to persist.
 */
void BwkApplication::update()
{
    if( _current_mode ) 
	{
        _current_mode = _current_mode->update();
    }
    else
	{
        close();
    }
}

/**
 *  Draw call. Pass this request to the current mode.
 */
void BwkApplication::draw()
{
    if( _current_mode ) 
	{
        _current_mode->draw();
    }
}

/**
 *  Pass button presses to the current application mode.
 */
void BwkApplication::buttonDown(Gosu::Button button)
{
    if( _current_mode ) 
	{
        _current_mode->buttonDown(button);
    }
}

/**
 *  Pass button releases to the current application mode.
 */
void BwkApplication::buttonUp(Gosu::Button button)
{
    if (_current_mode) 
	{
        _current_mode->buttonUp(button);
    }
}
