/*
** team_nbr.c for lemipc in /home/blanch_p/rendu/Semestre3/Unix/PSU_2016_lemipc
**
** Made by Alexandre BLANCHARD
** Login   <blanch_p@epitech.net>
**
** Started on  Mon Mar 27 15:32:42 2017 Alexandre BLANCHARD
** Last update Thu Mar 30 14:54:49 2017 Alexandre BLANCHARD
*/

#include <stdlib.h>
#include "lemipc.h"

bool	is_present(int *team_nb, int num_team)
{
  int	i;

  i = 0;
  while (team_nb[i] != -1)
    {
      if (team_nb[i] == num_team)
	return (true);
      i++;
    }
  return (false);
}

bool	have_nb_teams(int *team_nb)
{
  int	i;

  i = 0;
  while (team_nb[i] >= 0)
    i++;
  if (i >= 2)
    {
      free(team_nb);
      return (true);
    }
  free(team_nb);
  return (false);
}

bool	is_two_teams(int *map)
{
  int	i;
  int	*team_nb;
  int	j;

  if ((team_nb = malloc(sizeof(int) * WIDTH * HEIGHT + 1)) == NULL)
    exit(1);
  i = -1;
  j = 0;
  while (++i < WIDTH * HEIGHT + 1)
    team_nb[i] = -1;
  i = 0;
  while (i < WIDTH * HEIGHT)
    {
      if (map[i] != 0)
	{
	  if (is_present(team_nb, map[i]) == false)
	    {
	      team_nb[j] = map[i];
	      j++;
	    }
	}
      i++;
    }
  return (have_nb_teams(team_nb));
}
