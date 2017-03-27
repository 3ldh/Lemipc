/*
** move_player.c for lemipc in /home/blanch_p/rendu/Semestre3/PSU_2016_lemipc
**
** Made by Alexandre BLANCHARD
** Login   <blanch_p@epitech.net>
**
** Started on  Fri Mar 24 15:03:07 2017 Alexandre BLANCHARD
** Last update Mon Mar 27 13:32:40 2017 Alexandre BLANCHARD
*/

#include <stdio.h>

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
  map[player->y * WIDTH + player->x] = '0';
  player->y = player->y - 1;
  map[player->y * WIDTH + player->x] = player->team_nb;
}

void	move_down(t_player *player, int *map)
{
  map[player->y * WIDTH + player->x] = '0';
  player->y = player->y + 1;
  map[player->y * WIDTH + player->x] = player->team_nb;
}

void	move_left(t_player *player, int *map)
{
  map[player->y * WIDTH + player->x] = '0';
  player->x = player->x - 1;
  map[player->y * WIDTH + player->x] = player->team_nb;
}

void	move_right(t_player *player, int *map)
{
  map[player->y * WIDTH + player->x] = '0';
  player->x = player->x + 1;
  map[player->y * WIDTH + player->x] = player->team_nb;
}

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
  if (x > 0 && map[y * WIDTH + x - 1] == '0')
    {
      moves = xrealloc(moves, i + 1, LEFT, &i);
      printf("ONE\n");
    }
  if (x < WIDTH - 1 && map[y * WIDTH + x + 1] == '0')
    {
      moves = xrealloc(moves, i + 1, RIGHT, &i);
      printf("TWO\n");
    }
  if (y > 0 && map[(y - 1) * WIDTH + x] == '0')
    {
      moves = xrealloc(moves, i + 1, UP, &i);
      printf("THREE\n");
    }
  if (y < HEIGHT - 1 && map[(y + 1) * WIDTH + x] == '0')
    {
      moves = xrealloc(moves, i + 1, DOWN, &i);
      printf("FOUR\n");
    }
  moves = xrealloc(moves, i + 1, NONE, &i);
  return (moves);
}

void	move_player(t_player *player, int *map)
{
  char	*moves;
  int	go;

  if ((moves = check_can_move(map, player->x, player->y)) == NULL)
    return ;
  go = rand() % strlen(moves);
  printf("%lu\n", strlen(moves));
  printf("go = %d\n", moves[go]);
  move_fct[(direction)moves[go]](player, map);
}
