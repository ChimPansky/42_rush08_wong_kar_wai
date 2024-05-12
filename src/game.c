#include "2048.h"
#include <ncurses.h>
#include <stdbool.h>
#include <threads.h>

size_t sigResize = 0;

void custom_colors()
{
	init_pair(2, 1, COLOR_BLACK);
	init_pair(4, 2, COLOR_BLACK);
	init_pair(8, 3, COLOR_BLACK);
	init_pair(16, 4, COLOR_BLACK);
	init_pair(32, 5, COLOR_BLACK);
	init_pair(64, 6, COLOR_BLACK);
	init_pair(128, 7, COLOR_BLACK);
	init_pair(256, 1, COLOR_BLACK);
	init_pair(512, 2, COLOR_BLACK);
	init_pair(1024, 3, COLOR_BLACK);
	init_pair(2048, 4, COLOR_BLACK);
	init_pair(4096, 5, COLOR_BLACK);
	init_pair(8192, 6, COLOR_BLACK);
}

void	game_init(t_game *game, int size)
{
	game->status = PLAYING;
	game->size = size;
	start_color();
	custom_colors();
	game->win_main = initscr();
	noecho(); 				// for ncurses, don't echo any keypresses
	keypad(stdscr, TRUE); 	// for ncurses, enable special keys
	initscr();
	grid_create_windows(game, &game->grid);
}
void	grid_destroy_windows(t_game *game, t_grid *grid)
{
	int	row = 0;
	int	col = 0;

	while (row < game->size)
	{
		col = 0;
		while (col < game->size)
		{
			delwin(grid->squares[row][col].win);
			col++;
		}
		row++;
	}
}

void	game_destroy(t_game *game)
{
	grid_destroy_windows(game, &game->grid);
	endwin();
}

void	draw_square(t_square *square, int color_pair)
{
    werase(square->win);
	wattron(square->win, COLOR_PAIR(color_pair));
	wbkgd(square->win, COLOR_PAIR(color_pair));
    //box(square->win, 0, 0);
	mvwprintw(square->win, SQUARE_HEIGHT / 2, SQUARE_WIDTH / 2 - 1, "%d", square->value);
	wattroff(square->win, COLOR_PAIR(color_pair));
	refresh();
    wrefresh(square->win);
}

void game_draw(t_game *game)
{
    int row, col;
    clear();

    //box(stdscr, 0, 0);

	row = col = 0;
    while (row < game->size)
    {
		col = 0;
        while (col < game->size)
        {
          draw_square(&game->grid.squares[row][col]);
/*
            int cell_x = 2 + col * 6;
            int cell_y = 2 + row * 3;

            mvwprintw(game->win_main, cell_y, cell_x, "+-----+");
            mvwprintw(game->win_main, cell_y + 1, cell_x, "|     |");
            mvwprintw(game->win_main, cell_y + 2, cell_x, "+-----+");

			int value = game->grid.squares[row][col].value;

			if (value != 0)
			{
				wattron(game->win_main, COLOR_PAIR(value));
				mvwprintw(game->win_main, cell_y + 1, cell_x + 2, "%2d", value);
				wattroff(game->win_main, COLOR_PAIR(value));
			}
      */			
			col++;
        }
		row++;
    }
	row = col = 0;
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
			if (game->grid.squares[row][col].value  == WIN_VALUE)
				return true;
			col++;
		}
		row++;
	}
	return (false);
}

void handleResize(t_game *game)
{
	clear();
	game_draw(game);
	refresh();
}

static void	game_wait_for_input(t_game *game)
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
void	game_wait_for_input_and_update(t_game *game)
{
	static bool win_message_display = false;
	while (!game->grid.grid_changed_after_move)
	{
		game_wait_for_input(game);
		if (game->last_key == 27)
		{
			game->status = ABORTED;
			return ;
		}
		if (game->last_key == KEY_LEFT)
			grid_slide_left(game, &game->grid);
		else if (game->last_key == KEY_RIGHT)
			grid_slide_right(game, &game->grid);
		else if (game->last_key == KEY_UP)
			grid_slide_up(game, &game->grid);
		else if (game->last_key == KEY_DOWN)
			grid_slide_down(game, &game->grid);

		if (sigResize == 1)
		{
			handleResize(game);
			sigResize = 0;
		}
	}

  if (checks_win_condition(game) == true && !win_message_display)
	{
		int option = 0;

		WINDOW *win_message = newwin(6, 40, (LINES - 5) / 2, (COLS - 40) / 2);
		box(win_message, 0,0);
		mvwprintw(win_message, 2, 2, "Congrats You Achieved 2048!!");
		mvwprintw(win_message, 3, 2, "Press Q to quit or C to continue");
		wrefresh(win_message);

		while (option != 'q' && option != 'Q' && option != 'c' && option != 'C')
			option = getch();

		if (option == 'q' || option == 'Q')
			game->status = ABORTED;
		else if (option == 'c' || option == 'C')
			game->status = PLAYING;

		delwin(win_message);
		win_message_display = true;
	}
	game->grid.grid_changed_after_move = false;
	grid_reset_merged(game, &game->grid);
}


bool	moves_are_possible(t_game *game)
{
	grid_copy(game, game->grid.squares, game->check_grid.squares);
	game->check_grid.grid_changed_after_move = false;
	game->last_key = KEY_LEFT;
	grid_slide_left(game, &game->check_grid);
	game->last_key = KEY_RIGHT;
	grid_slide_right(game, &game->check_grid);
	game->last_key = KEY_UP;
	grid_slide_up(game, &game->check_grid);
	game->last_key = KEY_DOWN;
	grid_slide_down(game, &game->check_grid);
	if (game->check_grid.grid_changed_after_move)
		return (true);
	return (false);
}

/*
bool checks_win_condition(t_game *game)
{
	int row;
	int col;

	row = 0;
	col = 0;
	while (row < game->size)

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
}*/
