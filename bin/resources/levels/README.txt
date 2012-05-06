---------------
DESIGNING LEVELS
---------------

Introduction

  This is a guide to creating levels for "The Brave Bwock". It is currently a 

requirement that a specific set of levels exists. In other words, you'll have to 

actually existing levels with yours to test them, using the same file names. Bwock 

is not the smartest program yet, so expect segmentation faults if you cause one of

the existing files to go missing.


==== RECENT CHANGES ====

  As of version 0.2, only two layers exist in a level instead of three. There are also

new tiles to be aware of.

========================


1. Header Information

  The header describes a level's name and author. If present, these fields will display 

briefly when your level is played. Please be warned that the standard for Bwock includes 

names for every level. Your level will be renamed if you submit it nameless. As the author, 

however, you may remain anonymous if you wish.


EXAMPLE:
  AUTHOR   Mike Smith
  TITLE    Hot Cross Buns



2. Comments

  Comments are supported to help annotate these files. The format is to preface each 

line of comment with a semicolon(;). Here is an example:


  ; Header Data
  AUTHOR  me!
  TITLE   cool land  ; End of line comments are fine



3. Level Dimensions

  After defining the header data, you must define the level map. The number of tiles in 

the x and y directions must be known in order to parse the tiles correctly. When you begin

the map section, you must immediately give the dimensions of the map, in this format:


  ; Header data up here...

  ; Start the map
  MAP  10 x 8


  This will begin the map section for a map that is ten tiles horizontal, eight tiles

vertical. The MAP notation is needed to tell the parser not to look for header information

anymore. After this line, there should be absolutely no data in the file other than map

tiles. Comments are permitted throughout the entire file.


  It's recommended that you do not overthink this. Put in some dummy dimensions and

make your level as high and wide as you need. Then go back at the end and count the

rows and columns. 



4. The Layers

  Bwock levels have two layers:


   TERRAIN: Bushes, bricks, grass, start position and exit
   GROUND:  Objects of all kinds, such as opponents and keys

  Most tiles are only available for a particular layer. Putting a tile on an incorrect 

layer will cause it not to be considered. If you have the same tile on all three layers,

it is sure to be considered for the right one, and ignored for the others. This is an

advantage; it means you can safely use a tile on the wrong layer and keep it there as a

frame of reference.


  Layers do have a purpose, as you'll see shortly.



5. Designing a Level (Quick start!)

  The best way to start is with a basic map of empty spaces like this:

		. . . . .
		. . . . .
		. . . . .
		. . . . .
	
  Then fill it out with your basic concept for a map, like this

		. . X . .
		. . . . .
		. ! S ! .
		. . . . .

  Keys (!) aren't visible to the first layer, so they will be ignored. However, copy 

this map:

		. . X . .
		. . . . .
		. ! S ! .
		. . . . .

		. . X . .
		. . . . .
		. ! S ! .
		. . . . .

  And you can be sure everything will be seen. Now let's see how layers allow us to put

a key directly adjacent to an exit...


		. . X . .
		. . . . .
		. ! S ! .
		. . . . .

		. . ! . .	; <--- Exit has a key under it!
		. . . . .
		. ! S ! .
		. . . . .


  Exits do not actually appear in the space you place them. They are moved outward 

to the nearest border, preferring vertical over horizontal. That would mean, in a 

single-layer system, that the space adjacent to an exit would have to be empty. Thanks

to layers, it does not. This is a forward-looking design, as many things may potentially

stack in future versions.


  Now you can count the rows and columns and place the dimensions directly above the

level design. Here is our example in its finality, complete with header data.

		; Header
		TITLE   Test Level
		AUTHOR  You!

		; Map info
		MAP     5 x 4

		. . X . .
		. . . . .
		. ! S ! .
		. . . . .

		. . ! . .
		. . . . .
		. ! S ! .
		. . . . .


	Try it out and you'll quickly see how this all works.



6. The tiles

	This is a quick reference of all the tiles 

	I. Special Tile
		
		One tile is available to all layers: The 'blank' space. It means 
		nothing is there. :)

		BLANK SPACE:  	.


	II. Terrain - 	This is the layer where walls go, as well as the start
			and end point of the level. Remember, you need both a start
			and end point or your level will crash.

		START POINT:	S
		END POINT:	X
		HIGH WALL:	#	( These are brick walls )
		LOW WALL:	*	( These are hedges )
		WEEDS:		%
		WATER:		~

	III. Ground -	All enemies, keys, and obstacles go here.

		SWITCH:		/	( kills all enemies if all keys are collected )
		BOULDER:	@	( Pushable )
		MARBLE:		o	( Recursively Pushable )
		LPUSHER:	<	( Pushes boulders/marbles left )
		RPUSHER:	>	( right...)
		UPUSHER:	^	( up...)
		DPUSHER:	v	( down...)
		VSlider:	|	( Can be pushed up and down only )
		HSlider:	-	( Can be pushed left and right only )
		Spring:		&	( Allows Bwock to fly! )
		Key:		!	( Bwock must collect to win )

7. Legal

  When submitting a level, you are claiming that the level is your original design, or that

it was funished to you under terms which allow free redistribution. Please do not simply

copy levels out from Adventures of Lolo, Sokoban, or other commercial titles under the

guise of originality. 


  You also give the authors of Bwock and its community the write to add or change the 

level's title, but understand that it is forbidden for them to change the name of the

author. Any modifications to the level itself will require consulting with the author,

i.e. you.



