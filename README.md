# TugofWar
ENGR 103 Final Project

OBJECTIVE: Players compete against each other to "pull" the LED dot to their side of the board. Plays like real life tug of war except instead of pulling a rope you're pressing a button.

RULES: Players cannot make inputs until the countdown ends.

SCORING: At 6 seconds into the duration of the game, the inputs have double the impact on the score of the game. At 12 seconds in, inputs are 3 times as effective. Finally, at 30 seconds in, as a tiebreaking feature, inputs are 10 times as effective.

INPUTS: Each player uses one button. Pressing the button will help move the dot towards their side of the board. Players are intended to "spam" the buttons, leading to a faster win. The switch on the board is used to turn the volume on or off.

OUTPUTS: Position of the LED dot on the board indicates current score. Color of the LED dot on the board indicates input scaling, where inputs can do 1X (initially), 2X (after 6 seconds), 3X (after 12 seconds), and 10X (after 30 seconds). A high pitch tone indicates the dot has moved to the left, and a lower pitch tone indicates the dot has moved to the right. A sequence will play when a winner is decided.
