/**
 * @file    BwkGameMode.hpp
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

#ifndef __BWK_GAME_MODE_DEFINED__
#define __BWK_GAME_MODE_DEFINED__

#include <vector>
#include "BwkMode.hpp"

class BwkGameOverlay;
class BwkLevel;

/**
 * Most of runtime will be spent in this mode. This handles the period of time
 * spent actually pushing blocks around and solving puzzles.
 */
class BwkGameMode : public BwkMode
{
private:
    static BwkGameMode * _instance; // Singleton instance
public:
    static BwkGameMode * instance();

private:
    BwkGameMode();
    virtual ~BwkGameMode();

public:
    BwkMode * update();
    void draw();

private:
    int _loadLevel();
    void _displayLevelAuthor();
	void _unloadOverlays();
    BwkMode * _gameUpdate();
    void buttonDown(Gosu::Button);

private:
    std::vector<BwkGameOverlay*> _overlays;  //  The overlays currently running
    BwkLevel* _currentLevel;                 //  Current level being played
};

/**
 * Singleton accessor
 *
 * @return Singleton instance
 */
inline BwkGameMode * BwkGameMode::instance()
{
    if( _instance == NULL ) {
        _instance = new BwkGameMode;
    }
    return _instance;
}

#endif //  __BWK_GAME_MODE_DEFINED__
