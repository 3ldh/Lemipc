/*
** main.c for  in /home/sauvau_m/rendu/PSU_2016_lemipc
**
** Made by Sauvau Mathieu
** Login   <mathieu.sauvau@epitech.eu>
**
** Started on  Fri Mar 24 14:14:25 2017 Sauvau Mathieu
** Last update Mon Mar 27 14:36:12 2017 Sauvau Mathieu
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdio.h>
#include <time.h>
#include "lemipc.h"

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
  semop(player.sem_id, &sops, 1);
}

int		main(int ac, char **av)
{
  t_player	player;
  void		*map;
  struct sembuf	sops;

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
  if ((player.shm_id = shmget(player.key, WIDTH * HEIGHT * sizeof(int), SHM_W | SHM_R)) == -1)
    {
      player.shm_id = shmget(player.key, WIDTH * HEIGHT * sizeof(int), IPC_CREAT |  SHM_W | SHM_R);
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
  printf("using shm_id :%d\n", player.shm_id);
  semctl(player.sem_id, 0, SETVAL, 1);
  map = shmat(player.shm_id, NULL, 0);
  player.x = rand() % WIDTH;
  player.y = rand() % HEIGHT;
  put_player_on_map(&player, map);
  (void)sops;
  while (is_alive(&player, map))
    {
      lock(player.sem_id);
      move_player(&player, map);
      if (player.is_first)
  	print_map(map);
      unlock(player.sem_id);
      sleep(2);
    }
  shmctl(player.shm_id, IPC_RMID, NULL);
  return (0);
}
