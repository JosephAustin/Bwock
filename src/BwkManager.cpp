/**
 * @file    BwkManager.cpp
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

#include "BwkManager.hpp"
#include "BwkGameSettings.hpp"

// Singleton initialization
BwkManager * BwkManager::_instance = NULL;

/**
 * CTOR
 */
BwkManager::BwkManager()
{
    int i;  // Common iterator
    
	// Instantiate the engine 
	_soundEngine = irrklang::createIrrKlangDevice();
	
	// No song is playing
	_songPlaying = NULL;
	
    // Make every media item for every slot NULL
    for( i = 0; i < BwkSlots::BWK_IMG_MAX; i++ ) {
        _image[i] = NULL;
    }
    for( i = 0; i < BwkSlots::BWK_SOUND_MAX; i++ ) {
        _sound[i] = NULL;
    }
    for( i = 0; i < BwkSlots::BWK_MUSIC_MAX; i++ ) {
        _song[i] = NULL;
    }
}

void BwkManager::playSound(BwkSlots::Bwk_Data_Sound_Slot slot)
{
	if( !(BwkGameSettings::instance()->isSoundMuted()) ) {
		_soundEngine->play2D(bwk_fetch(slot));
	}
}

void BwkManager::playMusic(BwkSlots::Bwk_Data_Music_Slot slot)
{
	if( !_songPlaying && !(BwkGameSettings::instance()->isMusicMuted())) {
		_songPlaying = _soundEngine->play2D(bwk_fetch(slot), true, false, true);
		_songPlaying->setVolume(0.5);
	}
}

void BwkManager::stopMusic()
{
	if( _songPlaying ) {
		_songPlaying->stop();
		_songPlaying->drop();
		_songPlaying = NULL;
	}
}
