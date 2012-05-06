/**
 * @file    BwkSlots.hpp
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

#ifndef __BWK_SLOTS_DEFINED__
#define __BWK_SLOTS_DEFINED__

/**
 * These slots provide organization for media stored in the BwkManager class.
 * A MAX value must be provided in order to iterate over these slots effectively.
 */
namespace BwkSlots
{
    // Slots for storing image files that do not animate
    enum Bwk_Data_Img_Slot {
        BWK_IMG_VASILISA,
        BWK_IMG_FMOD,
        BWK_IMG_GOSU,
        BWK_IMG_TITLE_SCREEN,
		BWK_IMG_MENU_BG,
		BWK_IMG_MENU_START,
		BWK_IMG_MENU_RESTORE,
		BWK_IMG_MENU_GRAPHICS,
		BWK_IMG_MENU_SOUND,
		BWK_IMG_MENU_QUIT,
		BWK_IMG_MENU_RES,
		BWK_IMG_MENU_FS,
		BWK_IMG_MENU_SFX,
		BWK_IMG_MENU_MUSIC,		
		BWK_IMG_MENU_BACK,
        BWK_IMG_PAUSED,
        BWK_IMG_GRASS,
        BWK_IMG_WEEDS,
        BWK_IMG_WALL_LOW_TOP,
        BWK_IMG_WALL_LOW_BASE,
        BWK_IMG_WALL_LOW_ROSES,
        BWK_IMG_WALL_HIGH_TOP,
        BWK_IMG_WALL_HIGH_BASE,
        BWK_IMG_WALL_HIGH_VINES,
        BWK_IMG_WATER,
        BWK_IMG_KEY,
        BWK_IMG_BOULDER,
        BWK_IMG_BOULDER_SUNK,
        BWK_IMG_MARBLE,
        BWK_IMG_SLIDER_HORZ,
        BWK_IMG_SLIDER_VERT,
		BWK_IMG_SHADOW,
		BWK_IMG_MAX
    };

    // Slots for storing bitmap image files, which animate
	enum Bwk_Data_Bmp_Slot {
        BWK_BMP_BWOCK_DOWN,
        BWK_BMP_BWOCK_UP,
        BWK_BMP_BWOCK_LEFT,
        BWK_BMP_BWOCK_RIGHT,
        BWK_BMP_BWOCK_DOWN_FLYING,
        BWK_BMP_BWOCK_UP_FLYING,
        BWK_BMP_BWOCK_LEFT_FLYING,
        BWK_BMP_BWOCK_RIGHT_FLYING,
        BWK_BMP_DOOR,
        BWK_BMP_PUSHER,
        BWK_BMP_SWITCH,
        BWK_BMP_SPRING,
        BWK_BMP_WIZARD,
        BWK_BMP_PUDDINI,
        BWK_BMP_BROBRO_LEFT,
        BWK_BMP_BROBRO_RIGHT,
        BWK_BMP_BROBRO_UP,
        BWK_BMP_BROBRO_DOWN,
        BWK_BMP_SCORCHER_ASLEEP,
        BWK_BMP_SCORCHER_AWAKE,
		BWK_BMP_FORK,
        BWK_BMP_SLIME,
		BWK_BMP_FIREBALL,
		BWK_BMP_TIMER_BLOCK,
		BWK_BMP_MAX
	};

    // Slots for storing sound files
    enum Bwk_Data_Sound_Slot {
        BWK_SOUND_GET_KEY,
		BWK_SOUND_BOING,
		BWK_SOUND_PUSH,
		BWK_SOUND_SHOOT,
		BWK_SOUND_SPLASH,
        BWK_SOUND_MAX
    };

    // Slots for storing music files
    enum Bwk_Data_Music_Slot {
		BWK_MUSIC_BG,
        BWK_MUSIC_MAX
    };
};

#endif // __BWK_SLOTS_DEFINED__
