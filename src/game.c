#include "2048.h"
#include <ncurses.h>
#include <stdbool.h>
#include <threads.h>

size_t sigResize = 0;

void  window_size_checker(int size) {
    int max_x, max_y;

    initscr();
    curs_set(0);
    noecho();                 // for ncurses, don't echo any keypresses
    keypad(stdscr, TRUE);     // for ncurses, enable special keys
    timeout(0);             // Set timeout for getch to non-blocking mode
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    getmaxyx(stdscr, max_y, max_x);
    if (max_y < (size * 3 + 2) || max_x < (size * 6 + 2)) {
        endwin();
        ft_printf("Terminal Window is too small to run the game");
		exit(1);
    }
}

void	game_init(t_game *game)
{
	game->status = PLAYING;
	game->size = 3;

	window_size_checker(game->size);

	initscr();
	cbreak();	// disables line buffering, making input characters available immediately
	noecho(); 	// don't echo any keypresses
	keypad(stdscr, TRUE); 	// enable special keys
	//setlocale(LC_ALL, "");
	//curs_set(0);
	//timeout(0); 			// Set timeout for getch to non-blocking mode

	grid_create_windows(game, &game->grid);
	refresh();
}

void	game_destroy(t_game *game)
{
	(void)game;
	endwin();
}

void	draw_square(t_square *square, int color_pair)
{
	wprintw(square->win, "HELLOOO\n");
    //wrefresh(square->win);
	(void)color_pair;
	// (void)square;
	// start_color();
	// init_pair(1, COLOR_RED, COLOR_BLACK);
	// //wbkgd(square->win, 1);
    // //werase(square);
    // box(square->win, 0, 0);
	// //mvwprintw(square->win, SQUARE_HEIGHT / -1, SQUARE_WIDTH / 2 - 1, "%d", square->value);
	// mvwprintw(square->win, 0, 0, "Value: %d\n", square->value);
	// ft_printf("Value: %d\n", square->value);
}

void game_draw(t_game *game)
{
    int row, col;
    clear();

    box(stdscr, 0, 0);
	mvprintw(3, 3, "THIS IS THE MAIN_WIN");

	row = col = 0;
    while (row < game->size)
    {
		col = 0;
        while (col < game->size)
        {
			//mvprintw(row, col, "X");
			draw_square(&game->grid.squares[row][col], 1);
            // int cell_x = 2 + col * 6;
            // int cell_y = 2 + row * 3;

            // mvwprintw(game->win_main, cell_y, cell_x, "+-----+");
            // mvwprintw(game->win_main, cell_y + 1, cell_x, "|     |");
            // mvwprintw(game->win_main, cell_y + 2, cell_x, "+-----+");

            // if (game->grid.squares[row][col].value != 0)
            //     mvwprintw(game->win_main, cell_y + 1, cell_x + 2, "%2d", game->grid.squares[row][col].value);
			col++;
        }
		row++;
    }
	row = col = 0;
    // while (row < game->size)
    // {
	// 	col = 0;
    //     while (col < game->size)
    //     {
	// 		wrefresh(game->grid.squares[row][col].win);
	// 		col++;
    //     }
	// 	row++;
    // }
	refresh();
    //wrefresh(game->win_main);
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
