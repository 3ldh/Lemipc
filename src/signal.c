/*
** signal.c for lemipc in /home/blanch_p/rendu/Semestre3/Unix/PSU_2016_lemipc
**
** Made by Alexandre BLANCHARD
** Login   <blanch_p@epitech.net>
**
** Started on  Fri Mar 31 11:32:56 2017 Alexandre BLANCHARD
** Last update Fri Mar 31 13:57:07 2017 Alexandre BLANCHARD
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
/* #include <unistd.h> */
#include <stdlib.h>
#include "lemipc.h"

extern int	id_shm;
extern int	id_msg;
extern int	id_sem;

void	catch_sig_int()
{
  shmctl(id_shm, IPC_RMID, NULL);
  msgctl(id_msg, IPC_RMID, NULL);
  semctl(id_sem, 1, IPC_RMID);
  exit(1);
}
