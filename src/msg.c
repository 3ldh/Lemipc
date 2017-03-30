/*
** msg.c for  in /home/sauvau_m/rendu/PSU_2016_lemipc
**
** Made by Sauvau Mathieu
** Login   <mathieu.sauvau@epitech.eu>
**
** Started on  Thu Mar 30 14:15:17 2017 Sauvau Mathieu
** Last update Thu Mar 30 15:02:11 2017 Alexandre BLANCHARD
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
  printf("waiting msg\n");
  if (wait_msg(player, msg) > 0)
    {
      printf("Message received %ld %s\n", msg->mtype, msg->mtext);
      if (is_target_alive(player, atoi(msg->mtext), map))
	{
	  printf("target is alive send_msg\n");
	  send_msg(player, atoi(msg->mtext));
	  return (true);
	}
      else
	printf("but target is dead\n");
    }
  return (false);
}

int		wait_msg(t_player *player, t_msg *msg)
{
  int		r;

  r = msgrcv(player->msg_id, msg, sizeof(t_msg), player->team_nb, IPC_NOWAIT);
  if (r < 0)
    printf("error %s\n", strerror(errno));
  printf("return value msgrecv :%d\n", r);
  return (r);
}

void		send_msg(t_player *player, int pos)
{
  t_msg		msg;

  bzero(&msg, sizeof(t_msg));
  msg.mtype = player->team_nb;
  sprintf(msg.mtext, "%d", pos);
  printf("msg_id %d -> pos send to team :%ld %s\n",
	 player->msg_id, msg.mtype, msg.mtext);
  msgsnd(player->msg_id, &msg, sizeof(msg), IPC_NOWAIT);
}
