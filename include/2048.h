#ifndef FT_2048
# define FT_2048

# include <ncurses.h>
#include <stdbool.h>
# include "libft.h"
# include "time.h"

# ifndef SUCCESS
  define SUCCESS 0
# endif
# ifndef FAILURE
  define  FAILURE !SUCCESS
# endif


typedef enum e_game_status
{
	PLAYING,
	PAUSED,
	ABORTED,
	OVER
}		t_game_status;

enum e_direction
{
	LEFT,
	RIGHT,
	UP,
	DOWN
  }

enum e_const
{
	WIN_VALUE = 2048

};

typedef struct s_position
{
	int	row;
	int	col;
}				t_position;

typedef struct s_grid
{
	int		values[5][5];
	bool	grid_changed_after_move;
}			t_grid;

typedef struct s_game
{
	t_game_status	status;
	WINDOW			*win_main;
	t_grid			grid;
	t_grid			check_grid;
	int				size;
	int				last_key;
}			t_game;

// game.c
void	game_init(t_game *game);
void	game_destroy(t_game *game);
void	game_draw(t_game *game);
void	game_wait_for_input_and_update(t_game *game);
void	game_wait_for_input(t_game *game);

// grid.c
void	grid_spawn_random_nr(t_grid *grid, int size);
void	grid_slide_left(t_game *game, t_grid *grid);
void	grid_slide_right(t_game *game, t_grid *grid);
void	grid_slide_up(t_game *game, t_grid *grid);
void	grid_slide_down(t_game *game, t_grid *grid);
void 	grid_check_for_collisions_and_merge(t_game *game);
void	grid_copy(t_game *game, int src[5][5], int dst[5][5]);
bool	moves_are_possible(t_game *game);

// position.c
bool	position_is_equal(t_position pos1, t_position pos2);
void	position_shift_by_one(t_position *pos, int direction);

#endif
