#include "2048.h"

static int	get_two_or_four(void)
{
	int random_nr = rand();

	if (random_nr % 10 < 9)
		return (2);
	return (4);
}
void	grid_spawn_random_nr(t_game *game)
{
	int	row, col;

	while (1)
	{
		row = rand() % game->size;
		col = rand() % game->size;
		if (game->grid[row][col] == 0)
			break;
	}
	game->grid[row][col] = get_two_or_four();
}

static void	try_slide(t_game *game, t_position src, t_position dst)
{
	if (dst.row < 0 || dst.row > game->size || dst.col < 0 || dst.col > game->size)
		return ;
	if (game->grid[dst.row][dst.col] != 0)
		return ;
	game->grid[dst.row][dst.col] = game->grid[src.row][src.col];
	game->grid[src.row][src.col] = 0;
}

void	grid_slide_left(t_game *game)
{
	t_position	src;
	t_position	dst;

	src.row = 0;
	while (src.row < game->size)
	{
		dst.row = src.row;
		src.col = 0;
		while (src.col < game->size)
		{
			dst.col = src.col - 1;
			if (game->grid[src.row][src.col] != 0)
				try_slide(game, src, dst);
			src.col++;
		}
		src.row++;
	}
}

void	grid_slide_right(t_game *game)
{
	t_position	src;
	t_position	dst;

	src.row = 0;
	while (src.row < game->size)
	{
		dst.row = src.row;
		src.col = game->size;
		while (src.col >= 0)
		{
			dst.col = src.col + 1;
			if (game->grid[src.row][src.col] != 0)
				try_slide(game, src, dst);
			src.col--;
		}
		src.row++;
	}
}

void	grid_slide_up(t_game *game)
{
	t_position	src;
	t_position	dst;

	src.row = 0;
	while (src.row < game->size)
	{
		dst.row = src.row - 1;
		src.col = 0;
		while (src.col < game->size)
		{
			dst.col = src.col;
			if (game->grid[src.row][src.col] != 0)
				try_slide(game, src, dst);
			src.col++;
		}
		src.row++;
	}
}

void	grid_slide_down(t_game *game)
{
	t_position	src;
	t_position	dst;

	src.row = game->size;
	while (src.row >= 0)
	{
		dst.row = src.row + 1;
		src.col = 0;
		while (src.col < game->size)
		{
			dst.col = src.col;
			if (game->grid[src.row][src.col] != 0)
				try_slide(game, src, dst);
			src.col++;
		}
		src.row--;
	}
}

void grid_check_for_collisions_and_merge(t_game *game)
{
	(void)game;
}
