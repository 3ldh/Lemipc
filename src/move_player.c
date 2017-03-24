/*
** move_player.c for lemipc in /home/blanch_p/rendu/Semestre3/PSU_2016_lemipc
**
** Made by Alexandre BLANCHARD
** Login   <blanch_p@epitech.net>
**
** Started on  Fri Mar 24 15:03:07 2017 Alexandre BLANCHARD
** Last update Fri Mar 24 16:34:00 2017 Alexandre BLANCHARD
*/

#include <stdlib.h>
#include <string.h>
#include "lemipc.h"

void	(*move_fct[4])(t_player *, char **) =
{
  &move_up,
  &move_down,
  &move_left,
  &move_right
};

void	move_up(t_player *player, char **map)
{
  map[player->y][player->x] = 0;
  player->y = player->y - 1;
  map[player->y][player->x] = player->team_nb;
}

void	move_down(t_player *player, char **map)
{
  map[player->y][player->x] = 0;
  player->y = player->y + 1;
  map[player->y][player->x] = player->team_nb;
}

void	move_left(t_player *player, char **map)
{
  map[player->y][player->x] = 0;
  player->x = player->x - 1;
  map[player->y][player->x] = player->team_nb;
}

void	move_right(t_player *player, char **map)
{
  map[player->y][player->x] = 0;
  player->x = player->x + 1;
  map[player->y][player->x] = player->team_nb;
}

char	*xrealloc(char *moves, size_t size, direction dir, int *i)
{
  if ((moves = realloc(moves, size)) == NULL)
    exit(1);
  moves[*i++] = dir;
  return (moves);
}

char	*check_can_move(char **map, int x, int y)
{
  char	*moves;
  int	i;

  i = 0;
  moves = NULL;
  if (x > 0 && map[y][x - 1] == '0')
    moves = xrealloc(moves, i + 1, LEFT, &i);
  if (x < WIDTH - 1 && map[y][x + 1] == '0')
    moves = xrealloc(moves, i + 1, RIGHT, &i);
  if (y > 0 && map[y - 1][x] == '0')
    moves = xrealloc(moves, i + 1, UP, &i);
  if (y > HEIGHT - 1 && map[y + 1][x] == '0')
    moves = xrealloc(moves, i + 1, DOWN, &i);
  moves = xrealloc(moves, i + 1, NONE, &i);
  return (moves);
}

void	move_player(t_player *player, char **map)
{
  char	*moves;
  int	go;

  if ((moves = check_can_move(map, player->x, player->y)) == NULL)
    return ;
  go = rand() % strlen(moves);

  move_fct[go](player, map);
}
