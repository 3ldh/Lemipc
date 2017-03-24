/*
** print_map.c for lemipc in /home/blanch_p/rendu/Semestre3/Unix/PSU_2016_lemipc
**
** Made by Alexandre BLANCHARD
** Login   <blanch_p@epitech.net>
**
** Started on  Fri Mar 24 14:59:30 2017 Alexandre BLANCHARD
** Last update Fri Mar 24 16:46:15 2017 Sauvau Mathieu
*/

#include <stdio.h>
#include "lemipc.h"

void	print_map(char *map)
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
      printf("%c", map[y]);
    }
  printf("\n");
}
