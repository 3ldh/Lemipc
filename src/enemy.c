/*
** enemy.c for  in /home/sauvau_m/rendu/PSU_2016_lemipc
**
** Made by Sauvau Mathieu
** Login   <mathieu.sauvau@epitech.eu>
**
** Started on  Thu Mar 30 14:13:27 2017 Sauvau Mathieu
** Last update Fri Mar 31 14:31:26 2017 Sauvau Mathieu
*/

#include <stdio.h>
#include <stdlib.h>
#include "lemipc.h"

bool		is_target_alive(t_player *player, int pos_target, int *map)
{
  return (map[pos_target] != 0 && map[pos_target] != player->team_nb);
}

int		find_nearest_enemy(t_player *player, int *map)
{
  int		i;
  int		pos;
  t_vector2	current;
  t_vector2	nearest;
  t_vector2	player_pos;

  i = -1;
  pos = -1;
  nearest = get_vector2(player->x, player->y);
  player_pos = get_vector2(player->x, player->y);
  while (++i < WIDTH * HEIGHT)
    {
      current = get_vector2(i % WIDTH, i / WIDTH);
      if (abs(player->x - current.x) <= FIND_RANGE
	  && abs(player->y - current.y) <= FIND_RANGE &&
	  map[i] != player->team_nb && map[i] != 0 &&
	  (abs(distance_vector2(player_pos, nearest)) == 0 ||
	   abs(distance_vector2(player_pos, nearest)) >
	   abs(distance_vector2(player_pos, current))))
	{
	  nearest = current;
	  pos = i;
	}
    }
  return (pos);
}
