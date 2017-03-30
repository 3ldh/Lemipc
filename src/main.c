/*
** main.c for  in /home/sauvau_m/rendu/PSU_2016_lemipc
**
** Made by Sauvau Mathieu
** Login   <mathieu.sauvau@epitech.eu>
**
** Started on  Thu Mar 30 13:12:21 2017 Sauvau Mathieu
** Last update Thu Mar 30 16:03:06 2017 Sauvau Mathieu
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
#include "lemipc.h"

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

void		init_sem_msg(t_player *player)
{
  if ((player->sem_id = semget(player->key, 1, SHM_W | SHM_R)) == -1)
    {
      player->sem_id = semget(player->key, 1, IPC_CREAT | SHM_W | SHM_R);
      printf("Creating semaphore :%d\n", player->sem_id);
    }
  if ((player->msg_id = msgget(player->key, SHM_W | SHM_R)) == -1)
    {
      player->msg_id = msgget(player->key, IPC_CREAT | SHM_W | SHM_R);
      printf("Creating msg_q :%d\n", player->msg_id);
    }
}

void		init_shm(t_player *player, int **map)
{
  if ((player->shm_id = shmget(player->key, WIDTH * HEIGHT *
			      sizeof(int), SHM_W | SHM_R)) == -1)
    {
      player->shm_id = shmget(player->key, WIDTH * HEIGHT *
			     sizeof(int), IPC_CREAT |  SHM_W | SHM_R);
      printf("Creating shm :%d\n", player->shm_id);
      player->is_first = true;
      *map = shmat(player->shm_id, NULL, 0);
      memset(*map, 0, WIDTH * HEIGHT * sizeof(int));
    }
}

void		loop(t_player *player, int *map)
{
  (void)map;
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
      usleep(6000);
    }
  if (player->is_first)
    {
      print_map(map);
      shmctl(player->shm_id, IPC_RMID, NULL);
      msgctl(player->msg_id, IPC_RMID, NULL);
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
  map = shmat(player.shm_id, NULL, 0);
  if (!put_player_on_map(&player, map))
    {
      printf("No more places on the map\n");
      return (1);
    }
  loop(&player, map);
  return (0);
}
