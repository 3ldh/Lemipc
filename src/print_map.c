/*
** print_map.c for lemipc in /home/blanch_p/rendu/Semestre3/Unix/PSU_2016_lemipc
**
** Made by Alexandre BLANCHARD
** Login   <blanch_p@epitech.net>
**
** Started on  Fri Mar 24 14:59:30 2017 Alexandre BLANCHARD
** Last update Fri Mar 24 15:54:53 2017 Alexandre BLANCHARD
*/

#include <stdio.h>
#include "lemipc.h"

void	print_map(char **map)
{
  int	x;
  int	y;

  y = 0;
  while (y < HEIGHT)
    {
      x = 0;
      while (x < WIDTH)
	{
	  printf("%c ", map[y][x]);
	  x++;
	}
      printf("\n");
      y++;
    }
}
