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
