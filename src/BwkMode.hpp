/**
 * @file    BwkMode.hpp
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

#ifndef __BWK_MODE_DEFINED__
#define __BWK_MODE_DEFINED__

#include "BwkManager.hpp"

/**
 * A class for breaking up the different "modes" or game states of the main application.
 * All subclasses implement a singleton pattern to avoid memory leaks. Its unfortunate
 * that there's no way to enforce singleton patterns among derived classes, but maybe there's
 * a good reason.
 */
class BwkMode
{
public:
    /**
     * Called by each update in the main Gosu loop.
     * @return  Pointer to the next BwkAppMode to execute. We also return "this"
     *          to persist and NULL to quit.
     */
    virtual BwkMode * update() = 0;

    /**
     * Called by each draw function in the main Gosu loop.
     */
    virtual void draw() = 0;

    /**
     *  Events for buttons being pushed and released. Overload to handle input
     *  events effectively.
     */
    inline virtual void buttonDown(Gosu::Button) {};
    inline virtual void buttonUp(Gosu::Button) {};
};

#endif // __BWK_MODE_DEFINED__
