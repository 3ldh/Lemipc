/*
** main.c for  in /home/sauvau_m/rendu/PSU_2016_lemipc
**
** Made by Sauvau Mathieu
** Login   <mathieu.sauvau@epitech.eu>
**
** Started on  Fri Mar 24 14:14:25 2017 Sauvau Mathieu
** Last update Fri Mar 24 16:35:50 2017 Sauvau Mathieu
*/

#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdio.h>
#include "lemipc.h"


int		main(int ac, char **av)
{
  t_player	player;
  char		**map;

  if (ac != 3)
    {
      printf("Usage : ./lemipc path_to_key team_nb\n");
      return (1);
    }
  player.key = ftok(av[1], 0);
  player.team_nb = atoi(av[2]);
  player.first_player = 0;
  printf("key %d\n", player.key);
  if ((player.shm_id = shmget(player.key, WIDTH * HEIGHT, SHM_W | SHM_R)) == -1)
    {
      player.shm_id = shmget(player.key, WIDTH * HEIGHT, IPC_CREAT |  SHM_W | SHM_R);
      printf("Creating shm :%d\n", player.shm_id);
      player.first_player = 1;
    }
  if ((player.sem_id = semget(player.key, 1, SHM_W | SHM_R)) == -1)
    {
      player.sem_id = semget(player.key, 1, IPC_CREAT | SHM_W | SHM_R);
      printf("Creating semaphore :%d\n", player.sem_id);
    }
  map = shmat(player.shm_id, NULL, 0);
  memset(map, '0', WIDTH * HEIGHT);
  shmctl(player.shm_id, IPC_RMID, NULL);
  return (0);
}
