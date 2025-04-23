# Pixel Lance
-------------------------

A top-down 2D medieval wave-based arcade game. Survive until you die!!!!

------------------------------------
## Subsystems Implemented
---------------------------------
### AI Enemy(NPC) states
-------------------------------
Based on an FSM of 3-states:
1. Surround: Enemies automatically target the player on spawn, and move to a surround position. This position is based on a random radius and the enemies orbit the player
2. Attack: Enemies at a random interval after surrounding will move in to attack the player.
3. Retreat: Enemies, if hit, exhibit retreat behavior, returning to a surround state and resuming the orbit.

The behavior of enemies in this manner gives them a more dynamic and intelligent feel, as they exhibit attack strategy rather than piling in on the player. The randomness of their attacks can certainly overwhelm the player if they lack crowd control ability!
     
### Original Music and UI Features
------------------------------
"Pixel Lance"(the music you're hearing) is an original composition by Spencer Bowden. Transcribed in Musescore, the music interpolates (steals from) "Piano Phase" by Steve Reich, the "Bean Theme" from Stephen Sondheim's "Into the Woods" musical and "The Moon Song" from the SNES Ducktales soundtrack.


The Volume Slider in the bottom right corner is a node implemented in C++ with GDExtension, extending HSlider properties to control the decibel level of the music.


Other UI elements include: Settings Menu, Health Bar, Game Over Screen, and Score.

Gameplay
[Images/Gameplay]
