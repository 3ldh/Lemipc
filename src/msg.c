/*
** msg.c for  in /home/sauvau_m/rendu/PSU_2016_lemipc
**
** Made by Sauvau Mathieu
** Login   <mathieu.sauvau@epitech.eu>
**
** Started on  Thu Mar 30 14:15:17 2017 Sauvau Mathieu
** Last update Fri Mar 31 14:32:27 2017 Sauvau Mathieu
*/

#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "lemipc.h"

bool		listen_to_team(t_player *player, int *map, t_msg *msg)
{
  if (wait_msg(player, msg) > 0)
    {
      if (is_target_alive(player, atoi(msg->mtext), map))
	{
	  send_msg(player, atoi(msg->mtext));
	  return (true);
	}
    }
  return (false);
}

int		wait_msg(t_player *player, t_msg *msg)
{
  return (msgrcv(player->msg_id, msg, sizeof(t_msg),
		 player->team_nb, IPC_NOWAIT));
}

void		send_msg(t_player *player, int pos)
{
  t_msg		msg;

  bzero(&msg, sizeof(t_msg));
  msg.mtype = player->team_nb;
  sprintf(msg.mtext, "%d", pos);
  msgsnd(player->msg_id, &msg, sizeof(msg), IPC_NOWAIT);
}
