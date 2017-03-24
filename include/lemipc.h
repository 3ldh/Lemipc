/*
** lemipc.h for  in /home/sauvau_m/rendu/PSU_2016_lemipc
**
** Made by Sauvau Mathieu
** Login   <mathieu.sauvau@epitech.eu>
**
** Started on  Fri Mar 24 14:15:27 2017 Sauvau Mathieu
** Last update Fri Mar 24 15:44:08 2017 Sauvau Mathieu
*/

#ifndef LEMIPC_H_

# define LEMIPC_H_

# define WIDTH 20
# define HEIGHT 20

# include <stddef.h>
# include <sys/ipc.h>
# include <sys/shm.h>

typedef enum	Direction
  {
    UP,
    DOWN,
    LEFT,
    RIGHT,
  }

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

#endif /* ! LEMIPC_H_ */
