Bwock Readme File

- For Bwock's copyright information, see "COPYING"

- For all other copyright information, see the "licenses" folder


----------------------------------------------------------------

I. Contact Information

	If you have any ideas, patches, contributions, or opinions about 

the weather, please do not hesitate to use the following address:


		joseph.the.austin@gmail.com
	

----------------------------------------------------------------


II. Dependencies


	Dependencies are now included with Bwock's source code for quick

use. Special thanks to Nikolaus Gebhardt for allowing the distribution of 

the IrrKlang headers.


	Please look under the licenses folder for individual licenses 

regarding each dependency. Those licenses are to be respected.


	Note that the Boost library is not included. Boost is easy to

get, and a good idea to have regardless. Just push the shiny red 

button here: http://www.boost.org/


----------------------------------------------------------------


III. Building

	Building Bwock from source is something I've tried to make as 

easy as possible. There are two folders at the root called "WINDOWS"

and "LINUX", which respectively build for those two operating systems.

It would be nice to include something to build for Mac, but I do not 

own one and know little about that subject. That is one field in which 

contributions are most welcome.


----------------------------------------------------------------

IV. Windows Build


	The Gosu library requires Visual Studio in order to work on 

Windows. It's actually quite a pain, since you have to set specific 

settings up and really maintain a good project. So, I made a project 

for you. If the *.user file doesn't work for you, you may need to go 

into project settings and modify the debugging properties such that 

the working directory is ../../bin. Other than that, everything

should be taken care of for your Windows development!


----------------------------------------------------------------

V. Linux Build


1. Get CMAKE. You should already have it, but it can be acquired

   either via repository, or via the website (http://www.cmake.org)


2. Enter the LINUX folder and type this in a console:

   cmake .
   make

3. Then type this to run:

   cd ../bin
   ./bwock


NOTICE

  As far as I can tell, there is no way to make a makefile with

cmake that handles debug and release in one go. To specify one

or the other, add -DCMAKE_BUILD_TYPE="<build type>" when you run

cmake.

  cmake . -DCMAKE_BUILD_TYPE="Debug"
  cmake . -DCMAKE_BUILD_TYPE="Release"

----------------------------------------------------------------

VI. Using An IDE in Linux


  Check and see if your favorite IDE can have its project generated 

by CMAKE by running "cmake -help" from a console. The list of 

available generators are at the bottom. For example, CodeBlocks users

can run:

	cmake . -G "CodeBlocks - Unix Makefiles"

  Make sure to change the current build target to the binary file if

you do this. 

  
  Or, you can use virtually any IDE by loading a project with a 

custom makefile. For example, CodeLite has a "Custom Makefile"

project option. All you have to do is change the binary path and

working directory, import the "src" folder and voila.

