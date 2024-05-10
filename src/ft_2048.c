#include "2048.h"

#include "game.c"

int	main(void)
{
	t_game	game = {};

	game_init(&game);

	while (game.status == PLAYING)
	{
		game_draw(&game);
		game_wait_for_input(&game);
		game_update(&game);
	}
	//endscreen_show(&game);
	game_destroy(&game);
	return (SUCCESS);
}
