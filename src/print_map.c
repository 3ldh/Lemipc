/*
** print_map.c for lemipc in /home/blanch_p/rendu/Semestre3/Unix/PSU_2016_lemipc
**
** Made by Alexandre BLANCHARD
** Login   <blanch_p@epitech.net>
**
** Started on  Fri Mar 24 14:59:30 2017 Alexandre BLANCHARD
** Last update Mon Mar 27 13:36:20 2017 Alexandre BLANCHARD
*/

#include <stdio.h>
#include "lemipc.h"

void	make_player_on_map(t_player *player, int *map)
{
  map[player->y * WIDTH + player->x] = player->team_nb;
}

void	print_map(int *map)
{
  int	x;
  int	y;

  y = -1;
  x = -1;
  while (++y < HEIGHT * WIDTH)
    {
      if (x == WIDTH - 1)
	{
	  x = -1;
	  printf("\n");
	}
      else if (x != -1)
	printf(" ");
      ++x;
      printf("%d", map[y]);
    }
  printf("\n----------------------------------------\n");
}
