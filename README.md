# KnightFall
C++ terminal-based game involving a chess piece Knight, that can freely move in al L shaped pattern, trying to reach a square with a flag planted on it. In its way, there are squares with planted bombs, which can dynamically increase and size and reallocate when the player reaches a flag. Every time a flag is generated, there's also another chess figure that is generated with it, and placed on a random square on the board. Player must avoid all mines, which are visible, as well as avoid all squares that would typically be covered by the enemy figure on the chess board. Player has an option to take the enemy figure, and eliminate its threats until the flag is reached, at which point, a new figure generates. Player's score is the number of flags reached, where after each flag, it is randomly generated in another previously unoccupied square. The game is ended under next curcumstances: 1. score reacher 100, 2. player steps on a mine, 3. player enters 3 incorrect inputs in a row, 4. player steps on a square defended by the enemy figure. 
Game modes available:
1.tutorial -> player must reach 1 flag  within 10 moves
2.easy     -> player must reach 3 flags within 20 moves
3.medium   -> player must reach 10 flags within 50 moves
4.survival -> player can reach up to 100 and the number of moves isn't limited
5.multigame -> player can play 2 separate survival games on 2 separate boards for added challenge
