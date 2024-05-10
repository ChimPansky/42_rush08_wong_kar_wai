#include "2048.h"

void	game_init(t_game *game)
{
	game->status = PLAYING;
	game->size = 4;
}

void	game_destroy(t_game *game)
{
	(void)game;
}

void	game_draw(t_game *game)
{
	int	i, j;

	i = j = 0;

	while (i < game->size)
	{
		j = 0;
		while (j < game->size)
		{
			ft_printf(" % 5d ", game->grid[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
	ft_printf("\n");
}

void	game_update(t_game *game)
{
	(void)game;
}
void	game_wait_for_input(t_game *game)
{
	getch();
	(void)game;
}
