/*
** move_player.c for lemipc in /home/blanch_p/rendu/Semestre3/PSU_2016_lemipc
**
** Made by Alexandre BLANCHARD
** Login   <blanch_p@epitech.net>
**
** Started on  Fri Mar 24 15:03:07 2017 Alexandre BLANCHARD
** Last update Thu Mar 30 14:58:00 2017 Alexandre BLANCHARD
*/

#include <stdlib.h>
#include <string.h>
#include "lemipc.h"

void	(*move_fct[5])(t_player *, int *) =
{
  NULL,
  &move_up,
  &move_down,
  &move_left,
  &move_right
};

void	move_up(t_player *player, int *map)
{
  map[player->y * WIDTH + player->x] = 0;
  player->y = player->y - 1;
  map[player->y * WIDTH + player->x] = player->team_nb;
}

void	move_down(t_player *player, int *map)
{
  map[player->y * WIDTH + player->x] = 0;
  player->y = player->y + 1;
  map[player->y * WIDTH + player->x] = player->team_nb;
}

void	move_left(t_player *player, int *map)
{
  map[player->y * WIDTH + player->x] = 0;
  player->x = player->x - 1;
  map[player->y * WIDTH + player->x] = player->team_nb;
}

void	move_right(t_player *player, int *map)
{
  map[player->y * WIDTH + player->x] = 0;
  player->x = player->x + 1;
  map[player->y * WIDTH + player->x] = player->team_nb;
}
