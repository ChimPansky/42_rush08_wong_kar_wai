#include "2048.h"

int	main(void)
{
	t_game	game = {};

	game_init(&game);
	grid_spawn_random_nr(&game);
	grid_spawn_random_nr(&game);
	while (game.status == PLAYING)
	{
		game_draw(&game);
		game_wait_for_input(&game);
		game_update(&game);
		grid_spawn_random_nr(&game);
	}
	game_destroy(&game);
	return (SUCCESS);
}
