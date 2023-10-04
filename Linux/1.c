#include <func.h>
int main()
{
int semArrid = semget(1000,1,IPC_CREAT|0600);
ERROR_CHECK(semArrid,-1,"semget");
int ret = semctl(semArrid,0,SETVAL,1);
ERROR_CHECK(ret,-1,"semctl");
struct sembuf P;
P.sem_num = 0;//信号量值在集合中的下标
P.sem_op = -1;//信号量值修改
P.sem_flg = SEM_UNDO;//如果P操作被终止，会自动恢复
struct sembuf V;
V.sem_num = 0;
V.sem_op = 1;
