#include <func.h>
int main()
{
    int semArrid = semget(1000, 2, IPC_CREAT | 0600);
    ERROR_CHECK(semArrid, -1, "semget");
    unsigned short arr[2] = {0, 10};
    int ret = semctl(semArrid, 0, SETALL, arr);
    ERROR_CHECK(ret, -1, "semctl");
    if (!fork())
    {
        // 子进程是消费者
        struct sembuf consume[2];
        consume[0].sem_num = 0; // 0表示商品 1表示空格
        consume[0].sem_op = -1; // 商品减1
        consume[0].sem_flg = SEM_UNDO;
        consume[1].sem_num = 1;
        consume[1].sem_op = 1; // 空格加1
        consume[1].sem_flg = SEM_UNDO;
        while (1)
        {
            sleep(2);
            printf("I am consumer, before consume, product = %d, space = %d\n",
                   semctl(semArrid, 0, GETVAL), semctl(semArrid, 1, GETVAL));
            // semop(semArrid,consume,2); 这种写法显示太快了
            semop(semArrid, &consume[0], 1);
            printf("Buy a product\n");
            semop(semArrid, &consume[1], 1);
            printf("I am consumer, after consume, product = %d, space = %d\n",
                   semctl(semArrid, 0, GETVAL), semctl(semArrid, 1, GETVAL));
        }
        exit(0);
    }
    else
    {
        // 父进程是生产者
        struct sembuf produce[2];
        produce[0].sem_num = 0; // 0表示商品 1表示空格
        produce[0].sem_op = 1;  // 商品加1
        produce[0].sem_flg = SEM_UNDO;
        produce[1].sem_num = 1;
        produce[1].sem_op = -1; // 空格减1
        produce[1].sem_flg = SEM_UNDO;
        while (1)
        {
            sleep(1);
            printf("I am producer, before produce, product = %d, space = %d\n",
                   semctl(semArrid, 0, GETVAL), semctl(semArrid, 1, GETVAL));
            // semop(semArrid,produce,2);
            semop(semArrid, &produce[1], 1);
            printf("Produce a product\n");
            semop(semArrid, &produce[0], 1);
            printf("I am producer, after produce, product = %d, space = %d\n",
                   semctl(semArrid, 0, GETVAL), semctl(semArrid, 1, GETVAL));
        }
        wait(NULL);
    }
    return 0;
}