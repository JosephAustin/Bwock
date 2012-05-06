/**
 * @file    BwkGameSettings.cpp
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
#include <iostream>
#include <string>

#include "BwkGameSettings.hpp"
#include "BwkManager.hpp"

// Singleton initializer
BwkGameSettings * BwkGameSettings::_instance = NULL;

/**
 *  CTOR
 */
BwkGameSettings::BwkGameSettings()
{
    _resX = 800;
    _resY = 600;
    _fullScreen = false;
	_musicMuted = false;
	_soundMuted = false;
}

/**
 *  DTOR
 */
BwkGameSettings::~BwkGameSettings()
{
}

/**
 *  Loads the settings.txt file. If the file doesnt exist, this will try to create a new
 *  one. If THAT fails, a false gets returned to signify that this attempt failed.
 */
bool BwkGameSettings::loadSettingsFile()
{
    std::ifstream in;           // Parsable input stream for reading the settings file
	std::string buffer;         // A simple string buffer for reading in keywords

    // Try to find the settings file.
	in.open("./settings.txt");

    // If the file could not be found, make a new one
    if( !in.good() ) {
        // Close the file
        in.close();

        // Save the file. We do not need to check the flag, as we must be sure it re-opens here.
        saveSettingsFile();

        // Now re-open
        in.open("./settings.txt");

        // Good to go?
        if( !in.good() ) {
            return false;
        }
    }

    // It is not possible to hit this point with a bad file, so parse happily
    while( in.good() ) {
        in >> buffer;
        if( buffer == "FULL_SCREEN") {
            in >> buffer;
            _fullScreen = (buffer == "true" );
        }
        else if( buffer == "SCREEN_WIDTH") {
            in >> _resX;
        }
        else if( buffer == "SCREEN_HEIGHT") {
            in >> _resY;
        }
    }
    in.close();

    // We have loaded in settings successfully!
    return true;
}

/**
 *  Try to save out a settings.txt file, overwriting if needed. Returns false if this fails.
 */
bool BwkGameSettings::saveSettingsFile()
{
    std::ofstream out;      // The output stream for a new settings file

    // try to open
    out.open("./settings.txt");

    // Check that
    if( !out.is_open() ) {
        return false;
    }

    // Write
    out << "FULL_SCREEN    " << (_fullScreen ? "true" : "false") << std::endl;
    out << "SCREEN_WIDTH   " << _resX << std::endl;
    out << "SCREEN_HEIGHT  " << _resY << std::endl;

    // Save the file
    out.close();

    // Success
    return true;
}

/**
 *	When mute settings change, affect the manager which is playing the
 *  sound effects and music.
 */
void BwkGameSettings::_muteSettingsChanged()
{
	if(_musicMuted) {
		BwkManager::instance()->stopMusic();
	}
}

/**
 *  Open the levels.txt resource file to collect all the file names to be opened in
 *  their specific order. These are put in a queue. When the user inputs a password,
 *  all that is needed is to pop the queue to the desired level.
 */
bool BwkGameSettings::importLevelFiles()
{
    std::ifstream in;           // Parsable input stream for reading the levels file
	std::string buffer;         // A simple string buffer for reading in keywords

    // Try to find the levels file.
	in.open("./resources/levels/levels.txt");

    // If the file could not be found,return failure
    if( !in.good() ) {
        return false;
    }

    // Collect the file names
    while( in.good() ) {
        in >> buffer;
        if( in.good() ) {
            _levelFiles.push(buffer);
        }
    }
    in.close();

    return true;
}

/**
 *  Return the level at the front of the queue
 */
std::string BwkGameSettings::getCurrentLevel()
{
    if( _levelFiles.empty() ) {
        return "";
    }
    else {
        return _levelFiles.front();
    }
}

/**
 *  Pop the queue and return whether or not there are levels remaining
 */
bool BwkGameSettings::advanceLevel()
{
    _levelFiles.pop();

    return (!_levelFiles.empty());
}
