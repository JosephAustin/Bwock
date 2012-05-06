/**
 * @file    BwkApplication.hpp
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

#ifndef __BWK_APPLICATION_DEFINED__
#define __BWK_APPLICATION_DEFINED__

#include "Gosu/Gosu.hpp"

class BwkMode;
namespace irrklang{ class ISoundSource; }

/**
 *  Main application class for Bwock. Delegates to Game Modes so that the
 *  control loop is shared throughout the various game states.
 */
class BwkApplication : public Gosu::Window
{
public:
    static const int VIRTUAL_WIDTH  = 800;  // The virtual resolution width
    static const int VIRTUAL_HEIGHT = 600;  // The virtual resolution height

public:
    BwkApplication();

public:
    void update();
    void draw();
    void buttonDown(Gosu::Button);
    void buttonUp(Gosu::Button);

private:
	Gosu::Bitmap * _loadBitmap( std::wstring file );
    Gosu::Image * _loadImage( std::wstring file );
    irrklang::ISoundSource * _loadSound( std::string file );
    irrklang::ISoundSource * _loadSong( std::string file );

private:
    BwkMode * _current_mode;    //  Current game mode to delegate to.
};

#endif // __BWK_APPLICATION_DEFINED__
