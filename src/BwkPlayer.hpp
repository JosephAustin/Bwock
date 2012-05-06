/**
 * @file    BwkPlayer.hpp
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


#ifndef __BWK_PLAYER__
#define __BWK_PLAYER__

#include "BwkObject.hpp"

class BwkLevel;

/**
 *  Bwock, his cute sausagy self.
 */
class BwkPlayer : public BwkObject
{
public:
    BwkPlayer(BwkLevel * level);
    ~BwkPlayer();

    void win();
    void lose();

    bool hasWon();
    bool hasLost();

    void act();

    void beginFlight();

    bool flying() const;

private:
    bool _has_won;      // True when player has beaten the level
    bool _has_lost;     // True when player has died
    bool _is_flying;	// True when the player is flying
};


/**
 *  Mark the player as victorious
 */
inline void BwkPlayer::win()
{
    _has_won = true;
}

/**
 *  Mark the player as *DEAD*
 */
inline void BwkPlayer::lose()
{
    _has_lost = true;
}

/**
 *  @return     Whether the player escaped the level
 */
inline bool BwkPlayer::hasWon()
{
    return _has_won;
}

/**
 *  @return     Whether the player is dead.
 */
inline bool BwkPlayer::hasLost()
{
    return _has_lost;
}

inline bool BwkPlayer::flying() const
{
    return _is_flying;
}


#endif //__BWK_PLAYER__
