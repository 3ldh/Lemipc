/*
** move.c for lemipc in /home/blanch_p/rendu/Semestre3/Unix/PSU_2016_lemipc
**
** Made by Alexandre BLANCHARD
** Login   <blanch_p@epitech.net>
**
** Started on  Thu Mar 30 14:56:57 2017 Alexandre BLANCHARD
** Last update Thu Mar 30 14:58:19 2017 Alexandre BLANCHARD
*/

#include <string.h>
#include <stdlib.h>
#include "lemipc.h"

char	*xrealloc(char *moves, size_t size, direction dir, int *i)
{
  if ((moves = realloc(moves, size)) == NULL)
    exit(1);
  moves[(*i)++] = dir;
  return (moves);
}

char	*check_can_move(int *map, int x, int y)
{
  char	*moves;
  int	i;

  i = 0;
  moves = NULL;
  if (x > 0 && map[y * WIDTH + x - 1] == 0)
    moves = xrealloc(moves, i + 1, LEFT, &i);
  if (x < WIDTH - 1 && map[y * WIDTH + x + 1] == 0)
    moves = xrealloc(moves, i + 1, RIGHT, &i);
  if (y > 0 && map[(y - 1) * WIDTH + x] == 0)
    moves = xrealloc(moves, i + 1, UP, &i);
  if (y < HEIGHT - 1 && map[(y + 1) * WIDTH + x] == 0)
    moves = xrealloc(moves, i + 1, DOWN, &i);
  moves = xrealloc(moves, i + 1, NONE, &i);
  return (moves);
}

void	move_random(t_player *player, int *map)
{
  char	*moves;
  int	go;

  if ((moves = check_can_move(map, player->x, player->y)) == NULL)
    return ;
  go = rand() % strlen(moves);
  move_fct[(direction)moves[go]](player, map);
}
