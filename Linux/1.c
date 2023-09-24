void Daemon()
{
    const int MAXFD = 64;
    int i = 0;
    if (fork() != 0)
    {
        exit(0);
    }           // 父进程退出
    setsid();   // 成为新进程组组长和新会话领导，脱离控制终端
    chdir("/"); // 设置工作目录为根目录
    umask(0);   // 重设文件访问权限掩码
    for (; i < MAXFD; i++)
    {
        close(i); // 尽可能关闭所有从父进程继承来的文件
    }
}
int main()
{
    Daemon(); // 成为守护进程
    while (1)
    {
        sleep(1);
    }
    return 0;
}
