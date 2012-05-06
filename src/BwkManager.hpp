/**
 * @file    BwkManager.hpp
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

#ifndef __BWK_MANAGER_DEFINED__
#define __BWK_MANAGER_DEFINED__

// Macros for fetching / setting data slots
#define bwk_fetch(A)    BwkManager::instance()->fetch(A)    // Fetch a data item
#define bwk_set(A, B)   BwkManager::instance()->set(A, B)   // Set a data item

// Macros for acquiring the pointers neccessary to use Gosu
#define bwk_video()     BwkManager::instance()->video()     // Get the global Gosu Video class
#define bwk_input()     BwkManager::instance()->input()     // Get the global Gosu Input class

#include <irrKlang.h>

#include "Gosu/Gosu.hpp"
#include "BwkSlots.hpp"

/**
 * This is a custom data management class. It uses enumerated slots as storage containers for 
 * images and sounds. Using the macros above, it is easy to use this global class without having
 * to directly request an instance. I do this because media is frequently used throughout the
 * program.
 */
class BwkManager
{
private:
    static BwkManager * _instance;      //  Singleton instance of the data manager
public:
    static BwkManager * instance();
private:
    BwkManager();

public:
    Gosu::Image * fetch( BwkSlots::Bwk_Data_Img_Slot slot ) const;
    Gosu::Bitmap * fetch( BwkSlots::Bwk_Data_Bmp_Slot slot ) const;
    irrklang::ISoundSource * fetch( BwkSlots::Bwk_Data_Sound_Slot slot ) const;
    irrklang::ISoundSource * fetch( BwkSlots::Bwk_Data_Music_Slot slot ) const;

	void playSound(BwkSlots::Bwk_Data_Sound_Slot slot);
	void playMusic(BwkSlots::Bwk_Data_Music_Slot slot);
	void stopMusic();

    void set( BwkSlots::Bwk_Data_Img_Slot slot, Gosu::Image * media );
    void set( BwkSlots::Bwk_Data_Bmp_Slot slot, Gosu::Bitmap * media );
    void set( BwkSlots::Bwk_Data_Sound_Slot slot, irrklang::ISoundSource * media );
    void set( BwkSlots::Bwk_Data_Music_Slot slot, irrklang::ISoundSource * media );

    void setVideo( Gosu::Graphics * video );
    void setInput( Gosu::Input * input );

    Gosu::Graphics * video() const;
    Gosu::Input * input() const;
	irrklang::ISoundEngine * soundEngine() const;

private:
    // Stored data
    Gosu::Image * _image[BwkSlots::BWK_IMG_MAX];   		//  All the images used by this game
    Gosu::Bitmap * _bitmap[BwkSlots::BWK_BMP_MAX];  	//  All the bitmaps used by this game
    irrklang::ISoundSource* _sound[BwkSlots::BWK_SOUND_MAX]; //  All sound effects used by this game
	irrklang::ISoundSource* _song[BwkSlots::BWK_MUSIC_MAX];  //  All music used in the game

	irrklang::ISound * _songPlaying;					// Song currently playing, if any


    // Globalized Gosu data
    Gosu::Graphics * _video;                        //  Video class instance
    Gosu::Input * _input;                           //  Input class instance
	
	irrklang::ISoundEngine * _soundEngine;			// Irrklang sound engine
};

/**
 *  Singleton accessor
 */
inline BwkManager * BwkManager::instance()
{
    if( _instance == NULL ) {
        _instance = new BwkManager;
    }
    return _instance;
}

/**
 *  Getter for an image file, accessed by an image slot
 *
 *  @param  slot    An image slot
 *  @return Image associated with the slot parameter
 */
inline Gosu::Image * BwkManager::fetch( BwkSlots::Bwk_Data_Img_Slot slot ) const
{
    return _image[slot];
}

/** 
 *  Getter for a bitmap image file, accessed by a bitmap slot
 *
 *  @param  slot    A bitmap slot
 *  @return Bitmap associated with the slot parameter
 */
inline Gosu::Bitmap * BwkManager::fetch( BwkSlots::Bwk_Data_Bmp_Slot slot ) const
{
    return _bitmap[slot];
}

/**
 *  Getter for a sound file, accessed by a sound slot
 * 
 *  @param  slot    A sound slot
 *  @return Sound associated with the slot parameter
 */
inline irrklang::ISoundSource * BwkManager::fetch( BwkSlots::Bwk_Data_Sound_Slot slot ) const
{
    return _sound[slot];
}

/** 
 *  Getter for a song, accessed by an song slot
 *
 *  @param  slot    A song slot
 *  @return Song associated with the slot parameter
 */
inline irrklang::ISoundSource * BwkManager::fetch( BwkSlots::Bwk_Data_Music_Slot slot ) const
{
    return _song[slot];
}

/**
 *  Sets an image to a slot.
 *
 *  @param  slot    A slot to set media to
 *  @param  media   The media to assign to the slot
 */
inline void BwkManager::set( BwkSlots::Bwk_Data_Img_Slot slot, Gosu::Image * media )
{
    _image[slot] = media;
}

/**
 *  Sets a bitmap to a slot.
 *
 *  @param  slot    A slot to set media to
 *  @param  media   The media to assign to the slot
 */
inline void BwkManager::set( BwkSlots::Bwk_Data_Bmp_Slot slot, Gosu::Bitmap * media )
{
    _bitmap[slot] = media;
}

/**
 *  Sets a sound sample to a slot.
 *
 *  @param  slot    A slot to set media to
 *  @param  media   The media to assign to the slot
 */
inline void BwkManager::set( BwkSlots::Bwk_Data_Sound_Slot slot, irrklang::ISoundSource * media )
{
    _sound[slot] = media;
}

/**
 *  Sets a song to a slot.
 *
 *  @param  slot    A slot to set media to
 *  @param  media   The media to assign to the slot
 */
inline void BwkManager::set( BwkSlots::Bwk_Data_Music_Slot slot, irrklang::ISoundSource * media )
{
    _song[slot] = media;
}

/**
 *  Sets the global video class for the application.
 *
 *  @param video    Globalized video class from the actual application
 */
inline void BwkManager::setVideo( Gosu::Graphics * video )
{
    _video = video;
}

/**
 *  Sets the global input class for the application.
 *
 *  @param input    Globalized input class from the actual application
 */
inline void BwkManager::setInput( Gosu::Input * input )
{
    _input = input;
}

/**
 *  Accessor for the global video class
 *
 *  @return The global video class
 */
inline Gosu::Graphics * BwkManager::video() const
{
    return _video;
}

/**
 *  Accessor for the global input class
 *
 *  @return The global input class
 */
inline Gosu::Input * BwkManager::input() const
{
    return _input;
}

/**
 *  Accessor for the global audio engine class
 *
 *  @return The global audio engine class
 */
inline irrklang::ISoundEngine * BwkManager::soundEngine() const
{
	return _soundEngine;
}

#endif // __BWK_MANAGER_DEFINED__
