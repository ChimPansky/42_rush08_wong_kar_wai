#include <stdbool.h>
#include "2048.h"

bool	position_is_equal(t_position pos1, t_position pos2)
{
	if (pos1.row == pos2.row && pos1.col == pos2.col)
		return (true);
	return (false);
}

void	position_shift_by_one(t_position *pos, int direction)
{
	if (direction == KEY_LEFT)
		pos->col--;
	if (direction == KEY_RIGHT)
		pos->col++;
	if (direction == KEY_UP)
		pos->row--;
	if (direction == KEY_DOWN)
		pos->row++;
}

void	position_shift_by_one_reverse(t_position *pos, int direction)
{
	if (direction == KEY_LEFT)
		pos->col++;
	if (direction == KEY_RIGHT)
		pos->col--;
	if (direction == KEY_UP)
		pos->row++;
	if (direction == KEY_DOWN)
		pos->row--;
}
