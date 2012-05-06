/**
 * @file    main.cpp
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

#include <cstdio>
#include "BwkGameSettings.hpp"
#include "BwkApplication.hpp"

/**
 * Start and execute our application instance
 */
int main()
{
	BwkApplication app; // The game's startup class
	
    // Load or generate the game settings file. If this fails, error out.
    if( !BwkGameSettings::instance()->loadSettingsFile() ) 
	{
        printf( "ERROR - Could not find or create a settings file. "
                "Check that the executable folder is not read-only.");
        return 1;
    }
	
    // Now load in levels
    if( !BwkGameSettings::instance()->importLevelFiles() ) 
	{
        printf( "ERROR - Could not find levels.txt.");
        return 1;
    }

	// Now run the app
	app.show();
    return 0;
}
