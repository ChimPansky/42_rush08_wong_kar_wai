#ifndef FT_2048
# define FT_2048

# include <ncurses.h>
# include "libft.h"

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


typedef struct s_game
{
	t_game_status	status;
	int				grid[5][5];
	int				size;
}			t_game;

//game.c
void	game_init(t_game *game);
void	game_destroy(t_game *game);
void	game_draw(t_game *game);
void	game_update(t_game *game);
void	game_wait_for_input(t_game *game);

#endif
