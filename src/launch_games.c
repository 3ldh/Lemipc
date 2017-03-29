/*
** launch_games.c for lemipc in /home/blanch_p/rendu/Semestre3/Unix/PSU_2016_lemipc
**
** Made by Alexandre BLANCHARD
** Login   <blanch_p@epitech.net>
**
** Started on  Wed Mar 29 14:09:48 2017 Alexandre BLANCHARD
** Last update Wed Mar 29 16:21:41 2017 Alexandre BLANCHARD
*/

#include <stdio.h>
#include "lemipc.h"

int	nb_players_team(int *map, int team)
{
  int	i;
  int	nb_players;

  i = 0;
  nb_players = 0;
  while (i < WIDTH * HEIGHT)
    {
      if (map[i] == team)
	nb_players++;
      i++;
    }
  return (nb_players);
}

bool	check_launch(int *map)
{
  int	i;
  bool	two_in_team;
  int	nb_players;
  int	nb_team;

  i = 0;
  two_in_team = false;
  nb_players = 0;
  while (i < WIDTH * HEIGHT)
    {
      if (map[i] != 0)
	{
	  if (nb_players_team(map, map[i]) >= 2)
	    two_in_team = true;
	  nb_players++;
	}
      i++;
    }
  nb_team = is_two_teams(map);
  printf("is_two_teams ? -> %d\n", nb_team);
  /* printf("nb_players = %d\n", nb_players); */
  printf("two in team ? -> %d\n", two_in_team);
  if (nb_team == true && two_in_team == true)
    return (true);
  return (false);
}
