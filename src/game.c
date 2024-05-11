#include "2048.h"
#include <stdbool.h>
#include <threads.h>

void	game_init(t_game *game)
{
	game->status = PLAYING;
	game->size = 4;

	//int max_x, max_y;

	//setlocale(LC_ALL, "");
	game->win_main = initscr();
	//curs_set(0);
	noecho(); 				// for ncurses, don't echo any keypresses
	keypad(stdscr, TRUE); 	// for ncurses, enable special keys
	//timeout(0); 			// Set timeout for getch to non-blocking mode
	//start_color();
	//init_pair(1, COLOR_RED, COLOR_BLACK);
	//getmaxyx(this->getMainWin(), max_y, max_x);
	// if (max_y < (BATTLE_HEIGHT + STATS_HEIGHT) || max_x < SCREEN_WIDTH) {
	// 	endwin();
	// 	throw WrongWindowSizeException();
	// }
	// this->setStatsWin(subwin(this->getMainWin(), STATS_HEIGHT, SCREEN_WIDTH, 0, 0));
	// this->setBattleWin(subwin(this->getMainWin(), BATTLE_HEIGHT, SCREEN_WIDTH, STATS_HEIGHT, 0));

}

void	game_destroy(t_game *game)
{
	delwin(game->win_main);
	endwin();
}

void game_draw(t_game *game)
{
    int row, col;
    clear();

    box(game->win_main, 0, 0);

	row = col = 0;
    while (row < game->size)
    {
		col = 0;
        while (col < game->size)
        {
            int cell_x = 2 + col * 6;
            int cell_y = 2 + row * 3;

            mvwprintw(game->win_main, cell_y, cell_x, "+-----+");
            mvwprintw(game->win_main, cell_y + 1, cell_x, "|     |");
            mvwprintw(game->win_main, cell_y + 2, cell_x, "+-----+");

            if (game->grid[row][col] != 0)
                mvwprintw(game->win_main, cell_y + 1, cell_x + 2, "%2d", game->grid[row][col]);
			col++;
        }
		row++;
    }
    wrefresh(game->win_main);
}


bool checks_win_condition(t_game *game)
{
	int row;
	int col;

	row = 0;
	col = 0;
	while (row < game->size)
	{
		col = 0;
		while (col < game->size)
		{
			if (game->grid[row][col] == WIN_VALUE)
				return true;
			col++;
		}
		row++;
	}
	return (false);
}

void	game_update(t_game *game)
{
	if (game->last_key == 27)
	{
		game->status = ABORTED;
		return ;
	}

	if (game->last_key == KEY_LEFT)
		grid_slide_left(game);
	else if (game->last_key == KEY_RIGHT)
		grid_slide_right(game);
	else if (game->last_key == KEY_UP)
		grid_slide_up(game);
	else if (game->last_key == KEY_DOWN)
		grid_slide_down(game);
	
	if (checks_win_condition(game) == true)
	{
		game->status = ABORTED;
		return ;
	}
	grid_check_for_collisions_and_merge(game);
}

void	game_wait_for_input(t_game *game)
{
	bool	valid_input = false;

	while (!valid_input)
	{
		game->last_key = getch();
		if (game->last_key == KEY_LEFT || game->last_key == KEY_RIGHT
				|| game->last_key == KEY_UP || game->last_key == KEY_DOWN
				|| game->last_key == 27)
		valid_input = true;
	}
}
