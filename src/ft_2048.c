#include "2048.h"

int	main(void)
{
	t_game	game = {};

	game_init(&game);
	while (game.status == PLAYING)
	{
		game_draw(&game);
		sleep(1);
		game_wait_for_input(&game);
		game_update(&game);
	}
	game_destroy(&game);
	return (SUCCESS);
}
