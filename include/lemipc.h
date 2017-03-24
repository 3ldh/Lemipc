/*
** lemipc.h for  in /home/sauvau_m/rendu/PSU_2016_lemipc
**
** Made by Sauvau Mathieu
** Login   <mathieu.sauvau@epitech.eu>
**
** Started on  Fri Mar 24 14:15:27 2017 Sauvau Mathieu
** Last update Fri Mar 24 16:39:34 2017 Sauvau Mathieu
*/

#ifndef LEMIPC_H_

# define LEMIPC_H_

# define WIDTH 20
# define HEIGHT 20

# include <stddef.h>
# include <sys/ipc.h>
# include <sys/shm.h>

typedef enum	direction
  {
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT,
  }		direction;

typedef	struct	s_player
{
  key_t		key;
  int		shm_id;
  int		sem_id;
  int		first_player;
  size_t	x;
  size_t	y;
  int		team_nb;
}		t_player;

extern void	(*move_fct[4])(t_player *, char **);

void		move_up(t_player *, char **);
void		move_down(t_player *, char **);
void		move_left(t_player *, char **);
void		move_right(t_player *, char **);
void		print_map(char *map);

#endif /* ! LEMIPC_H_ */
