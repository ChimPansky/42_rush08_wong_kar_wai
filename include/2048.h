#ifndef FT_2048
# define FT_2048

# include <ncurses.h>
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

typedef struct s_position
{
	int	row;
	int	col;
}				t_position;

typedef struct s_game
{
	t_game_status	status;
	WINDOW			*win_main;
	int				grid[5][5];
	int				size;
	int				last_key;
}			t_game;

//game.c
void	game_init(t_game *game);
void	game_destroy(t_game *game);
void	game_draw(t_game *game);
void	game_update(t_game *game);
void	game_wait_for_input(t_game *game);

//grid.c
void	grid_spawn_random_nr(t_game *game);
void	grid_slide_left(t_game *game);
void	grid_slide_right(t_game *game);
void	grid_slide_up(t_game *game);
void	grid_slide_down(t_game *game);
void 	grid_check_for_collisions_and_merge(t_game *game);

#endif
