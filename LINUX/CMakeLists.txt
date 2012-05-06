CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(bwock CXX)

# Relative path to source
SET(BWKSRC "../src")

# Headers and libs for GOSU
SET(GOSUHEADERS "../dependencies/Gosu/include")
SET(GOSULIBS "../dependencies/Gosu/lib")

# Headers and libs for IRRKLANG
SET(IRRKHEADERS "../dependencies/IrrKlang/include")
SET(IRRKLIBS "../dependencies/IrrKlang/lib")

# Set the include directories
INCLUDE_DIRECTORIES(${BWKSRC} ${GOSUHEADERS} ${IRRKHEADERS})

# Set the linking directories
# LINK_DIRECTORIES(${GOSULIBS} ${IRRKLIBS})

# On linux we need to use bwock_bin to specify that you execute with a script
IF(WIN32)
	SET(BWKEXECUTABLE "Bwock")
ELSE(WIN32)
	SET(BWKEXECUTABLE "bwock_bin")
ENDIF(WIN32)

# Debug build default
IF(NOT CMAKE_BUILD_TYPE)
	SET (CMAKE_BUILD_TYPE "Debug" CACHE STRING
	     "Type of build, one of: Debug|Release|RelWithDebInfo|MinSizeRel."
	     FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)

MESSAGE(STATUS "Build type set to `${CMAKE_BUILD_TYPE}'")

# Dependencies
SET(DEPS gosu IrrKlang
    CACHE STRING "List of the libraries we will link against.")

# Find full paths to the libraries and store them in the LIBRARIES variable
MESSAGE(STATUS "Checking for dependencies...")
FOREACH(dep ${DEPS})

	MESSAGE(STATUS "Searching library ${dep}")
	FIND_LIBRARY(PATH_${dep} ${dep} PATHS ${GOSULIBS} ${IRRKLIBS})

	IF(NOT PATH_${dep})
		MESSAGE(SEND_ERROR "Error: library ${dep} not found!")
	ENDIF(NOT PATH_${dep})

	MESSAGE(STATUS "  * ${dep}: ${PATH_${dep}}")
	SET(LIBRARIES ${LIBRARIES} ${PATH_${dep}})

ENDFOREACH(dep)

# Now for source
SET(BwkCode
    ${BWKSRC}/main.cpp
    ${BWKSRC}/BwkApplication.cpp    		${BWKSRC}/BwkApplication.hpp
    ${BWKSRC}/BwkManager.cpp			${BWKSRC}/BwkManager.hpp
     						${BWKSRC}/BwkMode.hpp
    ${BWKSRC}/BwkTitleMode.cpp    		${BWKSRC}/BwkTitleMode.hpp
    ${BWKSRC}/BwkMenuMode.cpp    		${BWKSRC}/BwkMenuMode.hpp
    ${BWKSRC}/BwkGameSettings.cpp    		${BWKSRC}/BwkGameSettings.hpp
    ${BWKSRC}/BwkPlayer.cpp    			${BWKSRC}/BwkPlayer.hpp
    ${BWKSRC}/BwkObject.cpp    			${BWKSRC}/BwkObject.hpp
    ${BWKSRC}/BwkBoulderObject.cpp		${BWKSRC}/BwkBoulderObject.hpp
    ${BWKSRC}/BwkTimerBlockObject.cpp		${BWKSRC}/BwkTimerBlockObject.hpp
    ${BWKSRC}/BwkMarbleObject.cpp		${BWKSRC}/BwkMarbleObject.hpp
    ${BWKSRC}/BwkDoorObject.cpp			${BWKSRC}/BwkDoorObject.hpp
    ${BWKSRC}/BwkKeyObject.cpp			${BWKSRC}/BwkKeyObject.hpp
    ${BWKSRC}/BwkProjectileObject.cpp		${BWKSRC}/BwkProjectileObject.hpp
    ${BWKSRC}/BwkPusherObject.cpp		${BWKSRC}/BwkPusherObject.hpp
    ${BWKSRC}/BwkSwitchObject.cpp		${BWKSRC}/BwkSwitchObject.hpp
    ${BWKSRC}/BwkSliderObject.cpp		${BWKSRC}/BwkSliderObject.hpp
    ${BWKSRC}/BwkSpringObject.cpp		${BWKSRC}/BwkSpringObject.hpp
    ${BWKSRC}/BwkWallObject.cpp			${BWKSRC}/BwkWallObject.hpp
    ${BWKSRC}/BwkWaterObject.cpp		${BWKSRC}/BwkWaterObject.hpp
    ${BWKSRC}/BwkWeedsObject.cpp		${BWKSRC}/BwkWeedsObject.hpp
    ${BWKSRC}/BwkWizardObject.cpp		${BWKSRC}/BwkWizardObject.hpp
    ${BWKSRC}/BwkPuddiniObject.cpp		${BWKSRC}/BwkPuddiniObject.hpp
    ${BWKSRC}/BwkScorcherObject.cpp		${BWKSRC}/BwkScorcherObject.hpp
    ${BWKSRC}/BwkBroBroObject.cpp		${BWKSRC}/BwkBroBroObject.hpp
    						${BWKSRC}/BwkTiles.hpp
    ${BWKSRC}/BwkLevel.cpp			${BWKSRC}/BwkLevel.hpp
    ${BWKSRC}/BwkGameMode.cpp			${BWKSRC}/BwkGameMode.hpp
    						${BWKSRC}/BwkGameOverlay.hpp
    ${BWKSRC}/BwkPausedGameOverlay.cpp		${BWKSRC}/BwkPausedGameOverlay.hpp
    ${BWKSRC}/BwkQuitGameOverlay.cpp		${BWKSRC}/BwkQuitGameOverlay.hpp
    ${BWKSRC}/BwkTextGameOverlay.cpp		${BWKSRC}/BwkTextGameOverlay.hpp
)

### The following should tell IDEs to group related files together
SOURCE_GROUP(Base  FILES ${BwkCode})

### Add the source group to the game executable
ADD_EXECUTABLE(${BWKEXECUTABLE} ${BwkCode})
TARGET_LINK_LIBRARIES(${BWKEXECUTABLE} ${LIBRARIES})

### Set the output directory to be the bin folder
SET(EXECUTABLE_OUTPUT_PATH  ../bin)



