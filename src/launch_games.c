/*
** launch_games.c for lemipc in /home/blanch_p/rendu/Semestre3/Unix/PSU_2016_lemipc
**
** Made by Alexandre BLANCHARD
** Login   <blanch_p@epitech.net>
**
** Started on  Wed Mar 29 14:09:48 2017 Alexandre BLANCHARD
** Last update Thu Mar 30 13:51:58 2017 Sauvau Mathieu
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

bool	check_launch(t_player *player, int *map)
{
  int	i;
  int	nb_team;
  int	prev_team_nb;

  i = -1;
  prev_team_nb = 0;
  nb_team = 0;
  lock(player->sem_id);
  while (++i < WIDTH * HEIGHT)
    {
      if (map[i] != 0 && prev_team_nb != map[i])
	{
	  prev_team_nb = map[i];
	  printf("nb_player for team %d :%d\n", map[i], nb_players_team(map, map[i]));
	  if (nb_players_team(map, map[i]) < MIN_PLAYER)
	    {
	      unlock(player->sem_id);
	      return (false);
	    }
	  else
	    ++nb_team;
	}
    }
  unlock(player->sem_id);
  printf("nb_team :%d\n", nb_team);
  return (nb_team >= MIN_TEAM);
}
