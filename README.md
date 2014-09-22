----------------------------------------------

_Jean-Francois Vienneau_
=================

These instructions are specifically very vague.  We must learn not only about your skills as a programmer, but also about your skills and knowledge as a developer.

----------------------------------------------

Your task: write a game in Cocos2d-x (please use version 3.1), that compiles for iOS and Android.  Please include the necessary Xcode, and Eclipse projects in this repository.

Please avoid using online tutorials, as much as possible, and outline whatever you do use.

----------------------------------------------

This test is based on one of our working products.  It's also the same test we gave our Lead Developer when he came on board.  Your instructions are as followed:

Included in the _resources folder_ of files are **8** images.

- pieces.png
- projectile.png
- sling.png
- bottom.png

and their corresponding retina graphics [which have -hd on them].

Your task - the game, which is for an iPhone-sized screen, is based around a target-shoot type deal.  The "bottom" goes on the very bottom of the screen, with the "sling" anchored to its top.  You pull back the "sling" and a "projectile" is in the sling and depending on the distance you pull back and the angle from the point you pull to and the sling's starting point, the projectile, correctly rotated and everything, flies in that direction a distance determined by how far it's pulled back.

The 'enemies', or "pieces", are 2 different "types", of 3 different colors.  Note in the "pieces" file that there are 3 circles, green, orange and red, and 3 triangles, the same color.

The enemies come down the screen, one at a time, every 15 seconds.  There is a 30% chance it will be a circle and a 70% chance to be a triangle.  Of that percent, there is a 45% chance of green, 30% chance of orange and 25% chance of red.

Green enemies move straight downward.  Orange enemies move at a 45 degree angle [randomly picking at their start] and bounce off all the walls, switching their angles all the way down.  Red enemies move exactly the same as orange enemies, except that every 3 seconds, they switch.

Have the enemy start off screen on the top, randomly spaced across the screen, and slowly drop down.

When a projectile hits an enemy, 1) the projectile is destroyed 2) the enemy is destroyed.

Every 25 seconds the enemies are generated 10% faster than last time.  So first they're every 15 seconds. Then after 25 seconds, they start to generate every 13.5 seconds. And then every 12.15 seconds and so on.

For any formulas or numbers that aren't included in this document, just play-test and find a reasonable number that will allow us to play and test the game.

For bonus points:  give the game a bit of your own flair.  Use particle emitters and/or add other simple features that a typical game may need [such as a pause screen]. {bonus points tasks are not required, but help show us that you're able to think on your feet and design features that aren't specifically written out for you}.

Create this game targeted for iPhone screens.  However, it should be designed in code such that running the game on any sized screen will scale/re-layout the items accordingly.

Please write your code in C++, using the cocos2d-x library. Please document your code and your setup!  If you use any online resources, you **_must_** include the URL in the comments of the code, as well as inside of an **external.txt** file.

Make sure to commit as you go, so that each feature or change has its own commit.

When complete, make sure you've pushed your work.