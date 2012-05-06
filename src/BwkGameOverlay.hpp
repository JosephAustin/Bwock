/**
 * @file    BwkGameOverlay.hpp
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

#ifndef __BWK_GAME_OVERLAY_DEFINED__
#define __BWK_GAME_OVERLAY_DEFINED__

class BwkLevel;

/**
 * Overlays are meant to draw on top of the main game mode, so that special 
 * situations like dialogs, animations and whatever else can be encapsulated 
 * and expandable. They contain their own update and draw loops. Modal and
 * non-modal overlays are both supported ( see isModal() )
 */
class BwkGameOverlay
{
public:
    /**
     *  Takes over in updating the level data
     *
     *  @param level the collected level data, which this takes control of.
     *  @return whether this overlay will persist for another iteration.
     */
    virtual bool update( BwkLevel * level ) = 0;

    /**
     *  Takes over in drawing the level data
     *
     *  @param level the collected level data, which this takes control of.
     */
    virtual void draw( BwkLevel * level ) = 0;
	
	/** 
	 * Returns whether this is a modal overlay. If it is modal, the game loop
	 * should NOT proceed to its own drawing and updating until the overlay
	 * is closed. Otherwise, the overlay will not pause gameplay.
	 */
	virtual bool isModal() = 0;
};

#endif // __BWK_GAME_OVERLAY_DEFINED__
