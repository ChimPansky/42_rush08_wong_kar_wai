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

int game_menu(void)
{
	int option;

	clear();
	mvprintw(0, 1, "=========================");
	mvprintw(1, 1, "|Select an Option below:|");
	mvprintw(2, 1, "|1. Start 4x4 Game      |");
	mvprintw(3, 1, "|2. Start 5x5 Game      |");
	mvprintw(4, 1, "|3. Quit Game           |");
	mvprintw(5, 1, "=========================");

	option = 0;
	while (option != '1' && option != '2' && option != '3')
		option = getch();
		
	if (option == '1')
		return (4);
	else if (option == '2')
		return (5);
	else if (option == '3')
		return (0);		
	return (0);
}

int game_lose_menu()
{
	int option = 0;
	clear();
	WINDOW *lose_message = newwin(6, 40, (LINES - 5) / 2, (COLS - 40) / 2);
	mvwprintw(lose_message, 1, 1, "==================================");
	mvwprintw(lose_message, 2, 1, "|NO MOVES POSSIBLE!              |");
	mvwprintw(lose_message, 3, 1, "|Do you Wish to Restart? Press R |");
	mvwprintw(lose_message, 4, 1, "|To quit, Press Q Twice          |");
	mvwprintw(lose_message, 5, 1, "==================================");
	refresh();
	wrefresh(lose_message);

	while (option != 'q' && option != 'Q' && option != 'r' && option != 'R')
		option = getch();
			
	delwin(lose_message);
	if (option == 'q' || option == 'Q')
		return (1);
	else if (option == 'r' || option == 'R')
		return (0);
	return (0);
}

int main(void)
{
	int size = 0; 
	t_game game = {};

	initscr();
	cbreak();
	noecho();

	//Window Size
	signal(SIGWINCH, resizeHandler);

	while (true)
	{
		//Game Menu
		size = game_menu();
		if (size == 0)
			break ;


		//Window Size Checker
		if(!window_size_checker(size))
		{
			endwin();
			ft_printf("Terminal Window is too small to run the game\n");
			break ;
		}

		//Game Init and Random Number placement
		game_init(&game, size);
		grid_spawn_random_nr(&game.grid, game.size);
		grid_spawn_random_nr(&game.grid, game.size);

		//Game Loop
		while (game.status == PLAYING)
		{
			//Checks if their any moves (If not player can restart or quit)
			if (moves_are_possible(&game) == false)
			{
				if (game_lose_menu() == 0)
				{
					grid_reset_values(&game, &game.grid);
					break ;
				}
				else if (game_lose_menu() == 1)
				{
					game.status = ABORTED;
					break ;
				}
			}

		//Draws Game and Inputs Movement
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
