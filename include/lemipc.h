/*
** lemipc.h for  in /home/sauvau_m/rendu/PSU_2016_lemipc
**
** Made by Sauvau Mathieu
** Login   <mathieu.sauvau@epitech.eu>
**
** Started on  Fri Mar 24 14:15:27 2017 Sauvau Mathieu
** Last update Mon Mar 27 13:36:18 2017 Sauvau Mathieu
*/

#ifndef LEMIPC_H_

# define LEMIPC_H_

# define WIDTH 20
# define HEIGHT 20

# include <stdbool.h>
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
  bool		is_first;
  size_t	x;
  size_t	y;
  int		team_nb;
}		t_player;

extern void	(*move_fct[5])(t_player *, int *);

void		move_up(t_player *, int *);
void		move_down(t_player *, int *);
void		move_left(t_player *, int *);
void		move_right(t_player *, int *);
void		print_map(int *map);
void		put_player_on_map(t_player *, int *);
void		move_player(t_player *, int *);
bool		is_alive(t_player *, int *);

#endif /* ! LEMIPC_H_ */
