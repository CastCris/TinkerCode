# SnakeGame!
[Click here for simulate!](https://www.tinkercad.com/things/5SGD52oYjqc-snakegame)

## Preview
<img src="./Circuit.png">

## Drescription
This circuit simulates the popular Snake game.

Using a LED Matrix, the circuit displays the snake's body and the food that makes it grow!
However, due to limitations of TinkerCad and the ATmega328 microcontroller, the snake and body share the same color.
To solve this, in the playing mode, the LCD displays the snake's current direction, including clockwise and counterclockwise.

Using the two buttons, you can control the snake.
Pressing the left button makes the snake turn in the counterclockwise direction
and pressing the right button make the snake turn in the clockwise.

The game can also store scores and switch between levels.

See the table below of each game mode and a brief description about them for more data.
| (MAIN)GAME MODES | DESCRIPTION                                                                                                                                                              |
|------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| BOOTING          | Used only during game initializing.<br>When booting, the game displays a welcome message <br>with a simple animation of a snake showing its tongue<br>on the LCD display. |
| MENU             | As name the name suggest, it's the game menu.<br>In this mode, the user is able to browser between menu tab,<br>like SCORE, PLAY, LEVEL.                      |
| PLAYING          | The main game mode. Here is where the magic happens.                                                                                                                           |

| (MENU)GAME MODES | DESCRIPTION                                                                                                                                                                                                                                   |
|------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| PLAY             | Using this menu mode, the player is able to initialize the game.                                                                                                                                                                              |
| SCORE            | Here, the player can see theri scores.<br>The top twenty scores are stored and displayed in a<br>ascending order.                                                                                                                           |
| LEVEL            | For now, this game currently has only one level. However, if there ware more levels<br>the player should be able to select the desired level.<br>A level defines how the game goes behaves, but not much beyond that,<br>now it only sets the player's hp. |

<i>*Note that the Menu modes are circular, that is, when last menu is reached, the next one returns to the first.
The last menu is LEVEL and the first is PLAY.</i>

<hr>
The right and left push buttons have four function throughout game:

- <b>Select the next game menu mode</b>
- <b>Activate a game menu action</b>
- <b>Turn the snake in a clockwise direction</b>
- <b>Turn the snake in a counterclockwise direction</b>

See the following table for more informations about the buttons functions in each menu and in the PLAYING mode
| BUTTON | MENU PLAY            | MENU SCORE           | MENU LEVEL           | PLAYING                                        |
|--------|----------------------|----------------------|----------------------|------------------------------------------------|
| RIGHT  | Start the game.      | See the next score   | Set the next level   | Turn the snake clockwise        |
| LEFT   | Switch for next menu | Switch for next menu | Switch for next menu | Turn the snake counterclockwise |
