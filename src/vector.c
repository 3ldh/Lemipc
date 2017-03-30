/*
** vector.c for  in /home/sauvau_m/rendu/PSU_2016_lemipc
**
** Made by Sauvau Mathieu
** Login   <mathieu.sauvau@epitech.eu>
**
** Started on  Thu Mar 30 14:09:33 2017 Sauvau Mathieu
** Last update Thu Mar 30 14:52:25 2017 Sauvau Mathieu
*/

#include "lemipc.h"

t_vector2	g_dir_to_vector2[5] =
  {
    {0, 0},
    {0, -1},
    {0, 1},
    {-1, 0},
    {1, 0}
  };

t_vector2	diff_vector(t_vector2 a, t_vector2 b)
{
  t_vector2	res;

  res.x = a.x - b.x;
  res.y = a.y - b.y;
  return (res);
}

float		distance_vector2(t_vector2 a, t_vector2 b)
{
  t_vector2	vec;

  vec = diff_vector(a, b);
  return (vec.x + vec.y);
}

t_vector2	get_vector2(int x, int y)
{
  t_vector2	vec;

  vec.x = x;
  vec.y = y;
  return (vec);
}
