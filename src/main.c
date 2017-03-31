/*
** main.c for  in /home/sauvau_m/rendu/PSU_2016_lemipc
**
** Made by Sauvau Mathieu
** Login   <mathieu.sauvau@epitech.eu>
**
** Started on  Thu Mar 30 13:12:21 2017 Sauvau Mathieu
** Last update Fri Mar 31 15:14:23 2017 Sauvau Mathieu
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
#include <signal.h>
#include "lemipc.h"

int		id_shm;
int		id_msg;
int		id_sem;

void		call_to_arms(t_player *player, int *map)
{
  int		pos_enemy;
  direction	move_dir;
  t_msg		msg;

  if (!listen_to_team(player, map, &msg))
    {
      if ((pos_enemy = find_nearest_enemy(player, map)) != -1)
	{
	  send_msg(player, pos_enemy);
	  if ((move_dir = get_direction(player, map, pos_enemy) )!= NONE)
	    move_fct[move_dir](player, map);
	}
      else
	  move_random(player, map);
    }
  else
    {
      if ((move_dir = get_direction(player, map, atoi(msg.mtext))) != NONE)
	move_fct[move_dir](player, map);
    }
}

void		init_sem_msg(t_player *player)
{
  if ((player->sem_id = semget(player->key, 1, SHM_W | SHM_R)) == -1)
    {
      player->sem_id = semget(player->key, 1, IPC_CREAT | SHM_W | SHM_R);
      id_sem = player->sem_id;
    }
  if ((player->msg_id = msgget(player->key, SHM_W | SHM_R)) == -1)
    {
      player->msg_id = msgget(player->key, IPC_CREAT | SHM_W | SHM_R);
      id_msg = player->msg_id;
    }
}

void		init_shm(t_player *player, int **map)
{
  if ((player->shm_id = shmget(player->key, WIDTH * HEIGHT *
			      sizeof(int), SHM_W | SHM_R)) == -1)
    {
      player->shm_id = shmget(player->key, WIDTH * HEIGHT *
			     sizeof(int), IPC_CREAT |  SHM_W | SHM_R);
      player->is_first = true;
      *map = shmat(player->shm_id, NULL, 0);
      memset(*map, 0, WIDTH * HEIGHT * sizeof(int));
      id_shm = player->shm_id;
    }
}

void		loop(t_player *player, int *map)
{
  signal(SIGINT, catch_sig_int);
  while (!check_launch(player, map));
  while ((player->alive = is_alive(player, map)) || player->is_first)
    {
      if (is_winner(map))
      	break;
      lock(player->sem_id);
      if (player->alive)
  	call_to_arms(player, map);
      if (player->is_first)
      	  print_map(map);
      unlock(player->sem_id);
      sleep(1);
    }
  if (player->is_first)
    {
      print_map(map);
      printf("\nAnd the winner is Team %d\n\n", who_win(map));
      shmctl(player->shm_id, IPC_RMID, NULL);
      msgctl(player->msg_id, IPC_RMID, NULL);
      semctl(player->sem_id, 1, IPC_RMID);
    }
}

int		main(int ac, char **av)
{
  t_player	player;
  int		*map;

  if (ac != 3)
    {
      printf("Usage : ./lemipc path_to_key team_nb\n");
      return (1);
    }
  srand(time(0));
  player.key = ftok(av[1], 0);
  player.alive = true;
  player.team_nb = atoi(av[2]);
  player.is_first = false;
  init_shm(&player, &map);
  init_sem_msg(&player);
  semctl(player.sem_id, 0, SETVAL, 1);
  if ((map = shmat(player.shm_id, NULL, 0)) == (void *)-1)
    return (1);
  if (!put_player_on_map(&player, map))
    {
      printf("No more places on the map\n");
      return (1);
    }
  loop(&player, map);
  return (0);
}
