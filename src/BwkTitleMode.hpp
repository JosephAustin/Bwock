/**
 * @file    BwkTitleMode.hpp
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

#ifndef __BWK_TITLE_MODE_DEFINED__
#define __BWK_TITLE_MODE_DEFINED__

#include "BwkMode.hpp"

/**
 * Shows the logos and actual title screen.
 */
class BwkTitleMode : public BwkMode
{
private:
    // Title screen states ( in order of appearance )
    enum state_t {
        VASILISA,
        GOSU,
        FMOD,
        TITLE
    };
private:
    static BwkTitleMode * _instance;     // Singleton instance.
public:
    static BwkTitleMode * instance();
private:
     BwkTitleMode();
public:
    BwkMode * update();
    void draw();

private:
	BwkMode * _queuedReturn;
    state_t _curState;     // Current state of the title screen
};

/**
 *  Instance Accessor
 *
 *  @return Singleton instance
 */
inline BwkTitleMode * BwkTitleMode::instance()
{
    if( _instance == NULL ) {
        _instance = new BwkTitleMode;
    }
    return _instance;
}

#endif //  __BWK_TITLE_MODE_DEFINED__
