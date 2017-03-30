/*
** check_dead.c for lemipc in /home/blanch_p/Semestre3/Unix/PSU_2016_lemipc
**
** Made by Alexandre BLANCHARD
** Login   <blanch_p@epitech.net>
**
** Started on  Mon Mar 27 14:07:49 2017 Alexandre BLANCHARD
** Last update Wed Mar 29 17:44:59 2017 Sauvau Mathieu
*/

#include <stdio.h>
#include <stdio.h>
#include "lemipc.h"

bool	is_winner(int *map)
{
  int	i;
  int	team;

  i = 0;
  team = 0;
  while (i < WIDTH * HEIGHT)
    {
      if (map[i] != 0 && team != 0 && map[i] != team)
	return (false);
      if (team == 0 && map[i] != 0)
	team = map[i];
      i++;
    }
  return (true);
}

int	check_surronding(int *map, int x, int y,
			 int team_nb)
{
  int	val;
  int	count;
  int	i;
  int	j;

  count = 0;
  i = -2;
  while (++i < 2)
    {
      j = -2;
      while (++j < 2)
	{
	  val = (y + i) * WIDTH + x + j;
	  if (val >= 0 && val < HEIGHT * WIDTH &&
	      map[val] == team_nb)
	    ++count;
	}
    }
  return (count);
}

bool    is_alive(t_player *player, int *map)
{
  int   i;
  int   j;
  int   map_value;

  i = -2;
  if (!player->alive)
    return (false);
  while (++i < 2)
    {
      j = -2;
      while (++j < 2)
        {
          map_value = (player->y + i) * WIDTH + player->x + j;
          if (map_value >= 0 && map_value < HEIGHT * WIDTH
              && map[map_value] != player->team_nb
              && map[map_value] != 0)
            if (check_surronding(map, player->x, player->y,
                                 map[map_value]) >= 2)
              {
                map[player->y * WIDTH + player->x] = 0;
                return (false);
              }
        }
    }
  return (true);
}
