#include "2048.h"

void resizeHandler(int sig)
{
	(void)sig;
	sigResize = 1;
}

bool  window_size_checker(int size) 
{
	int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);
	return (max_y >= (size * 3 + 2) && max_x >= (size * 6 + 2));
}

int main(void)
{
	int option = 0;
	int size = 0;

	t_game game = {};

	initscr();
	cbreak();
	noecho();

	signal(SIGWINCH, resizeHandler);

	while (true)
	{
		clear();
		mvprintw(1, 1, "Select an Option below:");
		mvprintw(2, 1, "1. Start 4x4 Game");
		mvprintw(3, 1, "2. Start 5x5 Game");
		mvprintw(4, 1, "3. Quit Game");
		refresh();

		while (option < '1' || option > '3')
			option = getch();
		
		if (option == '1')
			size = 4;
		else if (option == '2')
			size = 5;
		else if (option == '3')
		{
			endwin();
			return (0);		
		}

		if(!window_size_checker(size))
		{
			endwin();
			ft_printf("Terminal Window is too small to run the game\n");
			exit(1);
		}

		game_init(&game, size);
		grid_spawn_random_nr(&game.grid, game.size);
		grid_spawn_random_nr(&game.grid, game.size);

		while (game.status == PLAYING)
		{
			if (moves_are_possible(&game) == false)
			{
				int option = 0;
				clear();
				WINDOW *lose_message = newwin(6, 40, (LINES - 5) / 2, (COLS - 40) / 2);
				mvwprintw(game.win_main, 2, 1, "NO MOVES POSSIBLE!");
				mvwprintw(game.win_main, 3, 1, "Do you Wish to Restart? Press R");
				mvwprintw(game.win_main, 4, 1, "To quit, Press Q");
				wrefresh(lose_message);

				while (option != 'q' && option != 'Q' && option != 'r' && option != 'R')
					option = getch();
			
				delwin(lose_message);
				if (option == 'q' || option == 'Q')
				{
					game.status = ABORTED;
					break ;
				}
				else if (option == 'r' || option == 'R')
				{ 
					grid_reset_values(&game, &game.grid);
					break ;
				}
			}
		game_draw(&game);
		game_wait_for_input_and_update(&game);
		grid_spawn_random_nr(&game.grid, game.size);
		
		}

		if (game.status == ABORTED)
			break ;

	}
	game_destroy(&game);

	endwin();
	return (SUCCESS);
}
