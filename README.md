# Bouble shooter - Game project in SFML

This is our midterm project for infromation engeneering. <br />
Game made in cpp and with SFML library.

### Team: <br />
Jakub Wesołowski --> https://github.com/kubuswes2003 <br />
Stanislaw Zalewski --> https://github.com/StanZalewski <br />

### Game Description / Info:

- End goal of the game:<br />
  The elimination of as many balls as possible without incoming balls touching the floor (red line in front of the main ball prepared to be shot).
Scoring as many points/balls shot as possible. Each ball equals 1 point.
  
- Challenge of the game: <br />
 Each time the player shoots down balls, the game difficulty intensifies - more and more colors appear on the screen, and fewer bombs are generated after each round.
  
- Single round description:<br />
  After each shot, the wall of balls moves one level down, and a new random stack is created on top. After the shot, a new ball appears in the queue with a random color.

- Game controls: <br />
  The game is controlled by the mouse (the pointer is moved by a cursor, and the balls are shot by a left click).
  
- Types of balls in the game: <br />

  - All colors apart from black <br />
    These are normal balls that appear in a random pattern on the screen, waiting to be shot down.
    
  - Only black balls with arrows - bombs <br />
    This type of ball serves as a bomb. They add a dynamic aspect to the game. Depending on which direction the arrows are pointing, the bomb will detonate through the whole map in the following possible scenarios:
    1. Verticaly
    2. Horizontaly
    3. Combination of above
  <br />
#### In game photo --> [Here]([#### Game Sketch --> [Here](https://github.com/StanZalewski/Project-Ball-Shooter/blob/main/INFO/In_game_photo.png)
#### Classes diagram --> [Here](https://github.com/StanZalewski/Project-Ball-Shooter/blob/main/INFO/Class_diagram.pdf)

### To play the game:
   1. Download the github repository <br />
   2. Download the SFML Library from --> [Here](https://www.sfml-dev.org/download/sfml/2.5.1/) or [Here](https://github.com/SFML/SFML.git) <br />
   3. That's all !!!
