#include "2048.h"

static int	get_two_or_four(void)
{
	int random_nr = rand();

	if (random_nr % 10 < 9)
		return (2);
	return (4);
}
void	grid_spawn_random_nr(t_grid *grid, int size)
{
	int	row, col;

	while (1)
	{
		row = rand() % size;
		col = rand() % size;
		if (grid->values[row][col] == 0)
			break;
	}
	grid->values[row][col] = get_two_or_four();
}

static void	try_slide(t_game *game, t_grid *grid, t_position src, t_position dst)
{
	if (dst.row < 0 || dst.row > game->size || dst.col < 0 || dst.col > game->size)
		return ;
	if (position_is_equal(src, dst))
		return ;
	//Merge function (Its not perfect but it works)
	if (grid->values[dst.row][dst.col] == grid->values[src.row][src.col])
	{
		grid->values[dst.row][dst.col] *= 2;
		grid->values[src.row][src.col] = 0;
		grid->grid_changed_after_move = true;
		return ;
	}
	if (grid->values[dst.row][dst.col] == 0)
	{
		grid->values[dst.row][dst.col] = grid->values[src.row][src.col];
		grid->values[src.row][src.col] = 0;
		grid->grid_changed_after_move = true;
		return ;
	}
	if (grid->values[dst.row][dst.col] != 0)
	{
		position_shift_by_one(&dst, game->last_key);
		try_slide(game, grid, src, dst);
		return ;
	}
}

void	grid_slide_left(t_game *game, t_grid *grid)
{
	t_position	src;
	t_position	dst;

	src.row = 0;
	dst.col = 0;
	while (src.row < game->size)
	{
		dst.row = src.row;
		src.col = 1;
		while (src.col < game->size)
		{
			if (grid->values[src.row][src.col] != 0)
				try_slide(game, grid, src, dst);
			src.col++;
		}
		src.row++;
	}
}

void	grid_slide_right(t_game *game, t_grid *grid)
{
	t_position	src;
	t_position	dst;

	src.row = 0;
	dst.col = game->size - 1;
	while (src.row < game->size)
	{
		dst.row = src.row;
		src.col = game->size - 2;
		while (src.col >= 0)
		{
			if (grid->values[src.row][src.col] != 0)
				try_slide(game, grid, src, dst);
			src.col--;
		}
		src.row++;
	}
}

void	grid_slide_up(t_game *game, t_grid *grid)
{
	t_position	src;
	t_position	dst;

	src.row = 1;
	dst.row = 0;
	while (src.row < game->size)
	{
		src.col = 0;
		while (src.col < game->size)
		{
			dst.col = src.col;
			if (grid->values[src.row][src.col] != 0)
				try_slide(game, grid, src, dst);
			src.col++;
		}
		src.row++;
	}
}

void	grid_slide_down(t_game *game, t_grid *grid)
{
	t_position	src;
	t_position	dst;

	src.row = game->size - 2;
	dst.row = game->size - 1;
	while (src.row >= 0)
	{
		src.col = 0;
		while (src.col < game->size)
		{
			dst.col = src.col;
			if (grid->values[src.row][src.col] != 0)
				try_slide(game, grid, src, dst);
			src.col++;
		}
		src.row--;
	}
}

void grid_check_for_collisions_and_merge(t_game *game)
{
	(void)game;
}

void	grid_copy(t_game *game, int src[5][5], int dst[5][5])
{
	t_position	cur;

	cur.row = 0;
	cur.col = 0;

	while (cur.row < game->size)
	{
		cur.col = 0;
		while (cur.col < game->size)
		{
			dst[cur.row][cur.col] = src[cur.row][cur.col];
			cur.col++;
		}
		cur.row++;
	}
}
