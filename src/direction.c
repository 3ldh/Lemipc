/*
** direction.c for  in /home/sauvau_m/rendu/PSU_2016_lemipc
**
** Made by Sauvau Mathieu
** Login   <mathieu.sauvau@epitech.eu>
**
** Started on  Thu Mar 30 14:11:10 2017 Sauvau Mathieu
** Last update Thu Mar 30 15:06:32 2017 Sauvau Mathieu
*/

#include <stdlib.h>
#include "lemipc.h"

bool		can_move_direction(int x, int y, int *map,
				   direction dir)
{
  t_vector2	vec;

  vec = g_dir_to_vector2[dir];
  if ((y + vec.y) * WIDTH + x + vec.x >= 0 &&
      (y + vec.y) * WIDTH + x + vec.x < WIDTH * HEIGHT)
    return (map[(y + vec.y) * WIDTH + x + vec.x] == 0);
  return (false);
}

bool		next_to_enemy(t_player *player, int pos_enemy)
{
  return (abs(pos_enemy % WIDTH - player->x) <= 1 &&
	  abs(pos_enemy / WIDTH - player->y) <= 1);
}

direction		get_direction(t_player *player, int *map, int pos)
{
  t_vector2		diff;
  direction		dir;
  static direction	prev_dir;

  dir = NONE;
  diff = get_vector((int)(pos % WIDTH - player->x),
		    (int)(pos / WIDTH - player->y));
  if (!next_to_enemy(player, pos))
    {
      if (prev_dir != LEFT)
	{
	  (diff.x < 0) ? (dir = LEFT) : (dir = RIGHT);
	  prev_dir = LEFT;
	  if (dir != NONE && can_move_direction(player->x, player->y, map, dir))
	    return (dir);
	}
      else
	{
	  prev_dir = UP;
	  (diff.y < 0) ? (dir = UP) : (dir = DOWN);
	  if (dir != NONE && can_move_direction(player->x, player->y, map, dir))
	    return (dir);
	}
    }
  return (NONE);
}
