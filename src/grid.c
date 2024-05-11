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
		if (grid->squares[row][col].value == 0)
			break;
	}
	grid->squares[row][col].value = get_two_or_four();
}

static void	merge_squares(t_grid *grid, t_position src, t_position dst)
{
	if (grid->squares[dst.row][dst.col].value == 0)
		grid->squares[dst.row][dst.col].value = grid->squares[src.row][src.col].value;
	else
		grid->squares[dst.row][dst.col].value *= 2;
	grid->grid_changed_after_move = true;
	grid->squares[src.row][src.col].value = 0;
}

static void	try_slide(t_game *game, t_grid *grid, t_position src)
{
	t_position	dst;

	dst.col = src.col;
	dst.row = src.row;
	position_shift_by_one(&dst, game->last_key);
	if (dst.row < 0 || dst.row >= game->size || dst.col < 0 || dst.col >= game->size)
		return ;
	if (grid->squares[dst.row][dst.col].value == 0)
	{
		merge_squares(grid, src, dst);
		try_slide(game, grid, dst);
		return ;
	}
	if (grid->squares[dst.row][dst.col].value != 0
		&& grid->squares[dst.row][dst.col].value == grid->squares[src.row][src.col].value
		&& grid->squares[dst.row][dst.col].merged == false)
	{
		merge_squares(grid, src, dst);
		grid->squares[dst.row][dst.col].merged = true;
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
			if (grid->squares[src.row][src.col].value != 0)
				try_slide(game, grid, src);
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
			if (grid->squares[src.row][src.col].value != 0)
				try_slide(game, grid, src);
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
			if (grid->squares[src.row][src.col].value != 0)
				try_slide(game, grid, src);
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
			if (grid->squares[src.row][src.col].value != 0)
				try_slide(game, grid, src);
			src.col++;
		}
		src.row--;
	}
}

// void 	check_neighbor_and_merge(t_game *game, t_grid *grid, t_position src, t_position dst)
// {
// 	position_shift_by_one(&dst, game->last_key);
// 	if (grid->squares[dst.row][dst.col].value == grid->squares[src.row][src.col].value)
// 	{
// 		grid->squares[dst.row][dst.col].value *= 2;
// 		grid->squares[src.row][src.col].value = 0;
// 		grid->grid_changed_after_move = true;
// 	}
// }

void	grid_copy(t_game *game, t_square src[5][5], t_square dst[5][5])
{
	t_position	cur;

	cur.row = 0;
	cur.col = 0;

	while (cur.row < game->size)
	{
		cur.col = 0;
		while (cur.col < game->size)
		{
			dst[cur.row][cur.col].value = src[cur.row][cur.col].value;
			dst[cur.row][cur.col].merged = false;
			cur.col++;
		}
		cur.row++;
	}
}

void	grid_reset_merged(t_game *game, t_grid *grid)
{
	t_position	cur;

	cur.row = 0;
	cur.col = 0;
	while (cur.row < game->size)
	{
		cur.col = 0;
		while (cur.col < game->size)
		{
			grid->squares[cur.row][cur.col].merged = false;
			cur.col++;
		}
		cur.row++;
	}
}
