#include "2048.h"

int	main(void)
{
	t_game	game = {};

	game_init(&game);
	grid_spawn_random_nr(&game.grid, game.size);
	grid_spawn_random_nr(&game.grid, game.size);
	while (game.status == PLAYING)
	{
		if (moves_are_possible(&game) == false)
		{
			game.status = OVER;
			mvwprintw(game.win_main, 12, 0, "NO MOVES POSSIBLE!");
			sleep(3);
		}
		game_draw(&game);
		game_wait_for_input_and_update(&game);
		grid_spawn_random_nr(&game.grid, game.size);
	}
	game_destroy(&game);
	return (SUCCESS);
}
