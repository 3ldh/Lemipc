/*
** print_map.c for lemipc in /home/blanch_p/rendu/Semestre3/Unix/PSU_2016_lemipc
**
** Made by Alexandre BLANCHARD
** Login   <blanch_p@epitech.net>
**
** Started on  Fri Mar 24 14:59:30 2017 Alexandre BLANCHARD
** Last update Mon Mar 27 16:01:44 2017 Alexandre BLANCHARD
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lemipc.h"

int	*recup_empty_places(int *map)
{
  int	i;
  int	j;
  int	*empty;

  if ((empty = malloc((WIDTH * HEIGHT + 1) * sizeof(int))) == NULL)
    exit(1);
  i = -1;
  j = 0;
  while (++i < WIDTH * HEIGHT + 1)
    empty[i] = -1;
  i = 0;
  /* memset(map, 0, WIDTH * HEIGHT); */
  /* printf("%d\n", empty[0]); */
  while (i < WIDTH * HEIGHT)
    {
      if (map[i] == 0)
	{
	  empty[j] = i;
	  j++;
	}
      i++;
    }
  return (empty);
}

int	intlen(int *str)
{
  int	i;

  i = 0;
  while (str[i] >= 0)
    {
      /* printf("str[%d] = %d\n", i, str[i]); */
      i++;
    }
  /* printf("Il reste %d places\n", i); */
  return (i);
}

void	put_player_on_map(t_player *player, int *map)
{
  int	*empty;
  int	empty_len;
  int	pos;

  empty = recup_empty_places(map);
  if ((empty_len = intlen(empty)) == 0)
    return ;
  pos = rand() % empty_len;
  map[empty[pos]] = player->team_nb;
  player->x = empty[pos] % WIDTH;
  player->y = empty[pos] / WIDTH;
  free(empty);
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
