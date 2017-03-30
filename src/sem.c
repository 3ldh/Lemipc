/*
** sem.c for  in /home/sauvau_m/rendu/PSU_2016_lemipc
**
** Made by Sauvau Mathieu
** Login   <mathieu.sauvau@epitech.eu>
**
** Started on  Thu Mar 30 14:08:12 2017 Sauvau Mathieu
** Last update Thu Mar 30 15:17:24 2017 Alexandre BLANCHARD
*/

#include <sys/ipc.h>
#include <sys/sem.h>

struct sembuf	getsem_op(int sem_num, int op_value)
{
  struct sembuf sops;

  sops.sem_num = sem_num;
  sops.sem_op = op_value;
  sops.sem_flg = 0;
  return (sops);
}

void		lock(int sem_id)
{
  struct sembuf sops;

  sops = getsem_op(0, -1);
  semop(sem_id, &sops, 1);
}

void		unlock(int sem_id)
{
  struct sembuf sops;

  sops = getsem_op(0, 1);
  semop(sem_id, &sops, 1);
}
