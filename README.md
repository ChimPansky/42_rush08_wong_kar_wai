# FT_2048
(Rush #8 of the 42 Common Core)

# objective:
Recreate the 2048 game as a terminal game using C and the ncurses library.

# ncurses library:
Allows writing text-based user interfaces in terminal. Can create windows, panels, forms and menus.
It is used by many popular text-based tools like Vim, top and other command-line utilities.

Key features:
- Handling input (keypresses and mouse events)
- Window Management: Create multiple windows and sub-windows.
- Color Manipulation: Use color pairs to display text in various colors.
- Screen Refreshing: Efficiently update the screen to reflect changes.

# game analysis:
- the game is played on a 4*4 grid.
- the grid is represented by a 2-dimensional integer array (int [rows][cols], where rows=cols=4)
- each square on the grid either contains a single number (power of 2) or nothing
- the goal of the game is to create a square that contains the number 2048
- at game start 2 numbers (either 2 or 4) each spawn in a random (empty) square
- a player move consists of pressing one of the arrow keys (left, right, up, down) or the ESC key
- after a direction is read from player input, all the values in the grid "slide" over to the neighboring square in the given direction (if possible).
	That means:
	- for up: the row-index is decreased by one
	- for down: the row-index is increased by one
	- for left: the col-index is decreased by one
	- for right: the col-index is increased by one
- a move is only valid if at least one number in the grid can actually slide
- number merging: if after the sliding, 2 adjacent squares have the same number, they merge into one square with the new number having double the  original value (2-2 -> 4; 8-8 -> 16;...)
- the merging only happens if the neighboring direction matches the sliding direction; for left right its horizontal and for updown its vertical.
- per move and row/col only 1 merge can happen (?) (No mutilpe merges can happen)
- if after sliding, more than 2 adjacent squares have the same number, only the 2 "furthest away" in the sliding direction will merge
- after a valid move one new random number spawns in a random empty square
- throughout the game the chances for a 2 to appear are 90% compared to 10% for 4
- there are 2 conditions for the game to be over:
  - there are no valid moves left (clean_up and quit game)
  - one square has reached the value 2048 (or some lower power of 2 which can be defined in a enum: enum e_const{ WIN_VALUE = 2048};)
	in this case show a messagebox "Congratulations! You made it to 2048. Want to keep going? y/n"
	- if y: clear the messagebox and continue the game (game_draw(), game_read_input())
	- else: clean_up and quit game
  -
- the ESC key will show a messagebox ("Do you really want to quit? y/n")
  - then the game waits for input (only y/n possible).
    - if y: clean_up and quit game
    - else: clear the messagebox and continue the game (game_draw(), game_read_input())

# Bonus:
- colors: work with color pairs for each square (function square_draw).
  - dark grey for empty square
  - grey for 2
  - light grey for 4
  - 8+: shades of red getting more intens...
  - the color of the numbers is black for 2 and 4 and white for the rest
- game menu:
  - (1) new game (4x4)
  - (2) new game (5x5)
  - (3) quit game
  -  if there is a game in progress and the ESC button has been pressed, the menu will show with the following options:
  -  (1) resume game
  -  (2)
  -  (3) quit game
- ascii art for colors in function square_draw
- show scores during the game: current scores & top 5 scores. store scores in a highscores.txt:
  - TOM   42000
  - LILLY 34000
  - BOB   28000
  - ...
  -
# technical specifications:
- the executable name must be 2048
- the game must be written in C and compiled with -Wall -Wextra -Werror
- allowed libraries: ncurses and libft
- additional allowed functions
  - rand(), srand() from <stdlib.h>
  - time() from <time.h>
  - signal() from <signal.h>
- the source files must be compiled using a Makefile, which does not reling and should contain the following rules:
  - NAME, all, clean, fclean
- only one global variable is allowed to manage signals
