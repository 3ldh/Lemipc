/*
** main.c for  in /home/sauvau_m/rendu/PSU_2016_lemipc
**
** Made by Sauvau Mathieu
** Login   <mathieu.sauvau@epitech.eu>
**
** Started on  Fri Mar 24 14:14:25 2017 Sauvau Mathieu
** Last update Mon Mar 27 15:16:40 2017 Alexandre BLANCHARD
*/

#include <time.h>
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
  t_player	player2;
  t_player	player3;
  int		*map;

  (void) map;
  (void) player2;
  (void) player3;
  srand(time(0));
  if (ac != 3)
    {
      printf("Usage : ./lemipc path_to_key team_nb\n");
      return (1);
    }
  player.key = ftok(av[1], 0);
  player.team_nb = atoi(av[2]);
  player.first_player = 0;
  player2.key = ftok(av[1], 0);
  player2.team_nb = atoi(av[2]);
  player2.first_player = 0;
  player3.key = ftok(av[1], 0);
  player3.team_nb = 3;
  player3.first_player = 0;

  printf("key %d\n", player.key);
  if ((player.shm_id = shmget(player.key,
			      WIDTH * HEIGHT * sizeof(int), SHM_W | SHM_R)) == -1)
    {
      player.shm_id = shmget(player.key, WIDTH * HEIGHT * sizeof(int),
			     IPC_CREAT |  SHM_W | SHM_R);
      printf("Creating shm :%d\n", player.shm_id);
      player.first_player = 1;
      map = shmat(player.shm_id, NULL, 0);
      memset(map, 0, WIDTH * HEIGHT * sizeof(int));
    }
  if ((player.sem_id = semget(player.key, 1, SHM_W | SHM_R)) == -1)
    {
      player.sem_id = semget(player.key, 1, IPC_CREAT | SHM_W | SHM_R);
      printf("Creating semaphore :%d\n", player.sem_id);
    }
  map = shmat(player.shm_id, NULL, 0);
  /* player.x = rand() % WIDTH; */
  /* player.y = rand() % HEIGHT; */

  player.x = 0;
  player.y = 1;
  /* player2.x = 0; */
  /* player2.y = 3; */
  /* player3.x = 0; */
  /* player3.y = 2; */

  put_player_on_map(&player, map);
  /* make_player_on_map(&player2, map); */
  /* make_player_on_map(&player3, map); */
  print_map(map);
  printf("is alive player3 = %d\n", is_alive(&player3, map));
  /* shmctl(player.shm_id, IPC_RMID, NULL); */
  return (0);
}
