/**
 * @file    BwkGameSettings.hpp
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

#ifndef __BWK_GAME_SETTINGS_DEFINED__
#define __BWK_GAME_SETTINGS_DEFINED__

#include <queue>
#include <string>

/**
 * Stores, reads and writes all the graphics settings for Bwock
 */
class BwkGameSettings
{
public:
    static BwkGameSettings * instance();
private:
    static BwkGameSettings * _instance;

private:
    BwkGameSettings();
    ~BwkGameSettings();

public:
    bool loadSettingsFile();
    bool saveSettingsFile();

    bool importLevelFiles();

    void setResolution( int width, int height );
    void setFullScreenMode( bool fullScreen );
	void toggleMusicMute();
	void toggleSoundMute();

    int resolutionWidth() const;
    int resolutionHeight() const;
    bool fullScreenMode() const;

	bool isMusicMuted() const;
	bool isSoundMuted() const;

    std::string getCurrentLevel();
    bool advanceLevel();

private:
	void _muteSettingsChanged();

private:
    int _resX, _resY;                       // Resolution of the game
    bool _fullScreen;                       // Full screen mode setting
	bool _musicMuted;	                    // Whether music is muted
	bool _soundMuted;	                    // Whether sound effects are muted
    std::queue<std::string> _levelFiles;    // Names of the level files in order of appearance
};

/**
 *  Singleton accessor
 */
inline BwkGameSettings * BwkGameSettings::instance()
{
    if( !_instance ) {
        _instance = new BwkGameSettings();
    }

    return _instance;
}

/**
 *  Sets the screen resolution of the game
 */
inline void BwkGameSettings::setResolution( int width, int height )
{
    _resX = width;
    _resY = height;
}

/**
 *  Sets the full screen mode setting
 */
inline void BwkGameSettings::setFullScreenMode( bool fullScreen )
{
    _fullScreen = fullScreen;
}

/**
 *	Toggles muting for music off and on
 */
inline void BwkGameSettings::toggleMusicMute()
{
	_musicMuted = !_musicMuted;
	_muteSettingsChanged();
}

/**
 *	Toggles muting for sound off and on
 */
inline void BwkGameSettings::toggleSoundMute()
{
	_soundMuted = !_soundMuted;
	_muteSettingsChanged();
}

/**
 * Gets the width of the resolution
 */
inline int BwkGameSettings::resolutionWidth() const
{
    return _resX;
}

/**
 * Gets the height of the resolution
 */
inline int BwkGameSettings::resolutionHeight() const
{
    return _resY;
}

/**
 * Gets whether the game is full screen
 */
inline bool BwkGameSettings::fullScreenMode() const
{
    return _fullScreen;
}

/**
 *	Returns whether music is muted
 */
inline bool BwkGameSettings::isMusicMuted() const
{
	return _musicMuted;
}

/**
 *	Returns whether sound is muted
 */
inline bool BwkGameSettings::isSoundMuted() const
{
	return _soundMuted;
}


#endif // __BWK_GAME_SETTINGS_DEFINED__

