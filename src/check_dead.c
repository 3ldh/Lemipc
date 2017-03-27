/*
** check_dead.c for lemipc in /home/blanch_p/Semestre3/Unix/PSU_2016_lemipc
**
** Made by Alexandre BLANCHARD
** Login   <blanch_p@epitech.net>
**
** Started on  Mon Mar 27 14:07:49 2017 Alexandre BLANCHARD
** Last update Mon Mar 27 14:34:47 2017 Alexandre BLANCHARD
*/

#include "lemipc.h"

int	check_surronding(int *map, int x, int y,
			 int team_nb)
{
  int	count;
  int	i;
  int	j;

  count = 0;
  i = -2;
  while (++i < 2)
    {
      j = -2;
      while (++j < 2)
	if (map[(y + i) * WIDTH + x + j] == team_nb)
	  ++count;
    }
  return (count);
}

bool	is_alive(t_player *player, int *map)
{
  int	i;
  int	j;

  i = -2;
  while (++i < 2)
    {
      j = -2;
      while (++j < 2)
	if (map[(player->y + i) * WIDTH + player->x + j] != player->team_nb
	    && map[(player->y + i) * WIDTH + player->x + j] != 0)
	  if (check_surronding(map, player->x, player->y,
			       map[(player->y + i) * WIDTH + player->x + j]) >= 2)
	    return (false);
    }
  return (true);
}
