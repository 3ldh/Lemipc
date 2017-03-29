/*
** lemipc.h for  in /home/sauvau_m/rendu/PSU_2016_lemipc
**
** Made by Sauvau Mathieu
** Login   <mathieu.sauvau@epitech.eu>
**
** Started on  Fri Mar 24 14:15:27 2017 Sauvau Mathieu
** Last update Wed Mar 29 15:13:23 2017 Sauvau Mathieu
*/

#ifndef LEMIPC_H_

# define LEMIPC_H_

# define WIDTH 20
# define HEIGHT 20
# define FIND_RANGE 20

# include <stdbool.h>
# include <stddef.h>
# include <sys/ipc.h>
# include <sys/shm.h>

typedef struct	s_msg
{
  long		mtype;
  char		mtext[10];
}		t_msg;

typedef struct	s_vector2
{
  int		x;
  int		y;
}		t_vector2;

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
  int		msg_id;
  bool		is_first;
  size_t	x;
  size_t	y;
  int		team_nb;
}		t_player;

extern t_vector2	g_dir_to_vector2[5];
extern void		(*move_fct[5])(t_player *, int *);

struct sembuf	getsem_op(int sem_num, int op_value);
void		lock(int sem_id);
void		unlock(int sem_id);
void		send_msg(t_player *player, int pos);
int		wait_msg(t_player *player, t_msg *msg);

void		move_up(t_player *, int *);
void		move_down(t_player *, int *);
void		move_left(t_player *, int *);
void		move_right(t_player *, int *);
void		print_map(int *map);
void		put_player_on_map(t_player *, int *);
void		move_random(t_player *, int *);
bool		is_alive(t_player *, int *);

void		call_to_arms(t_player *player, int *map);
bool		listen_to_team(t_player *player, int *map, t_msg *msg);
bool		is_target_alive(t_player *player, int pos_target, int *map);
direction	get_direction(t_player *player, int *map, int pos);
int		find_nearest_enemy(t_player *player, int *map);
bool		is_winner(int *);

#endif /* ! LEMIPC_H_ */
