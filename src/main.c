/*
** main.c for  in /home/sauvau_m/rendu/PSU_2016_lemipc
**
** Made by Sauvau Mathieu
** Login   <mathieu.sauvau@epitech.eu>
**
** Started on  Fri Mar 24 14:14:25 2017 Sauvau Mathieu
** Last update Wed Mar 29 15:14:36 2017 Sauvau Mathieu
*/

#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include "lemipc.h"

t_vector2	g_dir_to_vector2[5] =
  {
    {0, 0},
    {0, -1},
    {0, 1},
    {-1, 0},
    {1, 0}
  };

struct sembuf getsem_op(int sem_num, int op_value)
{
  struct sembuf sops;

  sops.sem_num = sem_num;
  sops.sem_op = op_value;
  sops.sem_flg = 0;
  return sops;
}

void		lock(int sem_id)
{
  struct sembuf sops;

  sops = getsem_op(0, -1);
  semop(sem_id, &sops, 1);
}

void		unlock(int sem_id)
{
  struct sembuf sops;

  sops = getsem_op(0, 1);
  semop(sem_id, &sops, 1);
}

t_vector2	diff_vector(t_vector2 a, t_vector2 b)
{
  t_vector2	res;

  res.x = a.x - b.x;
  res.y = a.y - b.y;
  return (res);
}

float		distance_vector2(t_vector2 a, t_vector2 b)
{
  t_vector2	vec;

  vec = diff_vector(a, b);
  return (sqrt(vec.x * vec.x + vec.y * vec.y));
}

t_vector2	get_vector2(int x, int y)
{
  t_vector2	vec;

  vec.x = x;
  vec.y = y;
  return (vec);
}

int		find_nearest_enemy(t_player *player, int *map)
{
  int		i;
  int		pos;
  t_vector2	current;
  t_vector2	nearest;
  t_vector2	player_pos;

  i = -1;
  pos = -1;
  nearest = get_vector2(0, 0);
  player_pos = get_vector2(player->x, player->y);
  while (++i < WIDTH * HEIGHT)
    {
      current = get_vector2(i % WIDTH, i / WIDTH);
      if (abs(player->x - current.x) <= FIND_RANGE && abs(player->y - current.y) <= FIND_RANGE &&
	  map[i] != player->team_nb && map[i] != 0 &&
	  abs(distance_vector2(player_pos, nearest)) > abs(distance_vector2(player_pos, current)))
	{
	  nearest = current;
	  pos = i;
	}
    }
  return (pos);
}

bool		can_move_direction(int x, int y, int *map,
				   direction dir)
{
  t_vector2	vec;

  vec = g_dir_to_vector2[dir];
  if ((y + vec.y) * WIDTH + x + vec.x >= 0 &&
      (y + vec.y) * WIDTH + x + vec.x < WIDTH * HEIGHT)
      return (map[(y + vec.y) * WIDTH + x + vec.x] == 0);
  return (false);
}

bool		next_to_enemy(t_player *player, int pos_enemy)
{
  return (abs(pos_enemy % WIDTH - player->x) <= 1
	  && abs(pos_enemy / WIDTH - player->y) <= 1);
}

direction	get_direction(t_player *player, int *map, int pos)
{
  int		x;
  int		y;
  int		diff_x;
  int		diff_y;
  direction	dir;

  x = pos % WIDTH;
  y = pos / WIDTH;
  dir = NONE;
  diff_x = (int)(x - player->x);
  diff_y = (int)(y - player->y);
  if (!next_to_enemy(player, pos))
    {
      if (diff_x != 0)
	{
	  (diff_x < 0) ? (dir = LEFT) : (dir = RIGHT);
	  if (dir != NONE && can_move_direction(player->x, player->y, map, dir))
	    return (dir);
	}
      if (diff_y != 0)
	{
	  (diff_y < 0) ? (dir = UP) : (dir = DOWN);
	  if (dir != NONE && can_move_direction(player->x, player->y, map, dir))
	    return (dir);
	}
    }
  else
    printf("Not moving next to enemy\n");
  return (NONE);
}

bool		is_target_alive(t_player *player, int pos_target, int *map)
{
  printf("pos target received %d\n", pos_target);
  return (map[pos_target] != 0 && map[pos_target] != player->team_nb);
}

bool		listen_to_team(t_player *player, int *map, t_msg *msg)
{
  printf("waiting msg\n");
  if (wait_msg(player, msg) > 0)
    {
      printf("Message received %ld %s\n", msg->mtype, msg->mtext);
      if (is_target_alive(player, atoi(msg->mtext), map))
	{
	  printf("target is alive send_msg\n");
	  send_msg(player, atoi(msg->mtext));
	  return (true);
	}
      else
	printf("but target is dead\n");
    }
  return (false);
}

void		call_to_arms(t_player *player, int *map)
{
  int		pos_enemy;
  direction	move_dir;
  t_msg		msg;

  if (!listen_to_team(player, map, &msg))
    {
      if ((pos_enemy = find_nearest_enemy(player, map)) != -1)
	{
	  printf("Target aquired x:%d y:%d\n", pos_enemy % WIDTH, pos_enemy / WIDTH);
	  send_msg(player, pos_enemy);
	  if ((move_dir = get_direction(player, map, pos_enemy) )!= NONE)
	    move_fct[move_dir](player, map);
	}
      else
	{
	  printf("move random\n");
	  move_random(player, map);
	}
    }
  else
    {
      printf("Moving according to order\n");
      if ((move_dir = get_direction(player, map, atoi(msg.mtext))) != NONE)
	move_fct[move_dir](player, map);
    }
}

int		wait_msg(t_player *player, t_msg *msg)
{
  int		r;

  r = msgrcv(player->msg_id, msg, sizeof(t_msg), player->team_nb, IPC_NOWAIT);
  if (r < 0)
    printf("error %s\n", strerror(errno));
  printf("return value msgrecv :%d\n", r);
  return r;
}

void		send_msg(t_player *player, int pos)
{
  t_msg		msg;

  bzero(&msg, sizeof(t_msg));
  msg.mtype = player->team_nb;
  sprintf(msg.mtext, "%d", pos);
  printf("msg_id %d -> pos send to team :%ld %s\n", player->msg_id, msg.mtype, msg.mtext);
  msgsnd(player->msg_id, &msg, sizeof(msg), IPC_NOWAIT);
}

int		main(int ac, char **av)
{
  t_player	player;
  void		*map;

  srand(time(0));
  if (ac != 3)
    {
      printf("Usage : ./lemipc path_to_key team_nb\n");
      return (1);
    }
  srand(time(0));
  player.key = ftok(av[1], 0);
  player.team_nb = atoi(av[2]);
  player.is_first = false;
  printf("key %d\n", player.key);
  if ((player.shm_id = shmget(player.key, WIDTH * HEIGHT *
			      sizeof(int), SHM_W | SHM_R)) == -1)
    {
      player.shm_id = shmget(player.key, WIDTH * HEIGHT *
			     sizeof(int), IPC_CREAT |  SHM_W | SHM_R);
      printf("Creating shm :%d\n", player.shm_id);
      player.is_first = true;
      map = shmat(player.shm_id, NULL, 0);
      memset(map, 0, WIDTH * HEIGHT * sizeof(int));
    }
  if ((player.sem_id = semget(player.key, 1, SHM_W | SHM_R)) == -1)
    {
      player.sem_id = semget(player.key, 1, IPC_CREAT | SHM_W | SHM_R);
      printf("Creating semaphore :%d\n", player.sem_id);
    }
  if ((player.msg_id = msgget(player.key, SHM_W | SHM_R)) == -1)
    {
      player.msg_id = msgget(player.key, IPC_CREAT | SHM_W | SHM_R);
      printf("Creating msg_q :%d\n", player.msg_id);
    }
  printf("using shm_id :%d\n", player.shm_id);
  semctl(player.sem_id, 0, SETVAL, 1);
  map = shmat(player.shm_id, NULL, 0);
  /* player.x = rand() % WIDTH; */
  /* player.y = rand() % HEIGHT; */
  put_player_on_map(&player, map);
  while (is_alive(&player, map))
    {
      lock(player.sem_id);
      call_to_arms(&player, map);
      if (player.is_first)
  	  print_map(map);
      unlock(player.sem_id);
      printf("is winner = %d\n", is_winner(map));
      sleep(5);
    }
  //TODO if last team
  shmctl(player.shm_id, IPC_RMID, NULL);
  msgctl(player.msg_id, IPC_RMID, NULL);
  return (0);
}
