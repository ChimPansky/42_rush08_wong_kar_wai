#include "2048.h"

void resizeHandler(int sig)
{
	(void)sig;
	sigResize = 1;
}

int main(void)
{
	t_game game = {};

	signal(SIGWINCH, resizeHandler);

	game_init(&game);
	grid_spawn_random_nr(&game.grid, game.size);
	grid_spawn_random_nr(&game.grid, game.size);
	while (game.status == PLAYING)
	{
		if (moves_are_possible(&game) == false)
		{
			int option = 0;

			WINDOW *lose_message = newwin(6, 40, (LINES - 5) / 2, (COLS - 40) / 2);
			box(lose_message, 0, 0);
			mvwprintw(lose_message, 2, 1, "NO MOVES POSSIBLE!");
			mvwprintw(lose_message, 3, 1, "Do you Wish to Restart? Press R");
			mvwprintw(lose_message, 4, 1, "To quit, Press Q");

			while (option != 'q' && option != 'Q' && option != 'r' && option != 'R')
				option = getch();

			if (option == 'q' || option == 'Q')
				game.status = ABORTED;
			else if (option == 'r' || option == 'R')
			{
				game_destroy(&game);
				game_init(&game);
				grid_spawn_random_nr(&game.grid, game.size);
				grid_spawn_random_nr(&game.grid, game.size);
			}

			delwin(lose_message);
		}
		game_draw(&game);
		game_wait_for_input_and_update(&game);
		grid_spawn_random_nr(&game.grid, game.size);
	}
	game_destroy(&game);
	return (SUCCESS);
}
