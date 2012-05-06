/**
 * @file    BwkMenuMode.hpp
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

#ifndef __BWK_MENU_MODE_DEFINED__
#define __BWK_MENU_MODE_DEFINED__

#include <vector>

#include "BwkMode.hpp"
#include "BwkSlots.hpp"

class BwkPlayer;

/**
 * The Main Menu, where the user can change graphics settings, start new games, or
 * enter passwords to return to their save states.
 */
class BwkMenuMode : public BwkMode
{
private:
    static BwkMenuMode * _instance;     // Singleton instance.
public:
    static BwkMenuMode * instance();
    
private:
     BwkMenuMode();    
public:
    BwkMode * update();
    void draw();
    
public:
	void buttonDown(Gosu::Button);
	void buttonUp(Gosu::Button);
	
private:
	BwkMode * _queuedReturn;
	Gosu::Image * _bg;			// The background image to scroll
	double _bgScrollHorz;		// Background scroll offset, horizontal
	double _bgScrollVert;		// Background scroll offset, vertical
	int _currentOption;			// The index of the current selected option
	std::vector<BwkSlots::Bwk_Data_Img_Slot> _mainOptions;
	std::vector<BwkSlots::Bwk_Data_Img_Slot> _gfxOptions;
	std::vector<BwkSlots::Bwk_Data_Img_Slot> _soundOptions;
	std::vector<BwkSlots::Bwk_Data_Img_Slot> * _curOptions;
	BwkPlayer * _bwock;
};

/**
 *  Instance Accessor
 *
 *  @return Singleton instance
 */
inline BwkMenuMode * BwkMenuMode::instance() 
{
    if( _instance == NULL ) {
        _instance = new BwkMenuMode;
    }
    return _instance;
}

#endif //  __BWK_MENU_MODE_DEFINED__
