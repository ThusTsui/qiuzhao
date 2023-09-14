## linux系统编程

写应用，需要调用操作系统帮忙

1. shell
2. 库函数(printf)：跨平台       //  ISOC规范
3. system calls 系统调用：直接使用操作系统内核功能   //POSIX规范

![](images/2023-09-10-09-45-32.png)


## 怎样学习系统编程
man 手册
![](images/2023-09-10-10-34-11.png)
- 安装库函数手册
sudo apt install manpages-posix-dev 

- man手册内容
  - 名字-声明-细节-返回值
- 阅读顺序
  - 1. 先阅读名字
  - 2. 看声明和返回值
    - 头文件
    - 指针类型的参数--**主调函数分配内存**
  （看有没有const）
    - 指针类型返回值--**主调函数是否要释放内存**
    ![](images/2023-09-10-10-45-59.png)
    void *malloc(size_t size);
    - 返回值不实现功能，只处理报错
  - 3. 细节：按需查看


## 文件

- 狭义：存储在外部存储介质上的数据集合
- 广义：慢、容量大、持久存储  ——— 万物皆文件

### 文件类型

普通文件 、目标文件、软连接
字符设备文件  (鼠标)  以字符为单位
块设备文件  (磁盘)     以块为单位
管道文件  (让两个文件之间彼此通信)
sorket文件(网络通信)

### 文件使用

![](images/2023-09-10-20-36-47.png)

## 通过man学习相关接口
### fopen

库函数
![](images/2023-09-10-20-44-44.png)

- FILE: 文件流/**用户态**文件缓冲区
- 参数1：字符串：路径
- 参数2：r只读打开，r+读写打开，w只写创建，w+读写创建

#### 写代码前的准备工作
- 43func.h
![](images/2023-09-13-16-59-07.png)
- 调用
![](images/2023-09-10-21-50-35.png)

#### 追加模式
"a" ：即append 只写追加————默认从文件结尾写入
"a+"           读写追加————打开时处于文件的开始,写入时(不管此时ptr处于什么位置)跳到文件的末尾

日志系统使用

文件流
![](images/2023-09-11-20-52-35.png)

#### 验证过程：

```C++
#include <43func.h>
int main(int argc, char *argv[])
{
    // 运行时执行./fopen file1
    ARGS_CHECK(argc, 2);//参数个数检查
    //FILE *fp=fopen(argv[1],"r");

    // FILE *fp=fopen(argv[1],"a");//追加模式
    // ERROR_CHECK(fp,NULL,"fopen");//fopen使用时不成功（没有该文件）检查
    // fwrite("howareyou",1,9,fp);//写入

    FILE *fp=fopen(argv[1],"a+");//
    ERROR_CHECK(fp,NULL,"fopen");//fopen使用时不成功（没有该文件）检查
    char buf[10]={0};
    fread(buf,1,9,fp);//a+可读
    puts(buf);
    printf("before fseek, loc = %ld\n",ftell(fp));
    fseek(fp,0,SEEK_SET);
    printf("after fseek, loc = %ld\n",ftell(fp));
    fwrite("howareyou",1,9,fp);//写入
    fclose(fp);
}
```

### 改变文件属性相关接口

#### 1. 用函数实现改变文件权限chmod    //man 2 chmod
```c++
#include<43func.h>
int main(int argc,char *argv[]){
    // ./chmod 777 dir1
    //执行chmod 将dir1文件权限改为777
    ARGS_CHECK(argc,3);
    //chmod(argv[2],argv[1]);///报错，第二个参数应该是八进制无符号整形
    __mode_t mode;
    sscanf(argv[1],"%o",&mode);
    int ret = chmod(argv[2],mode);
    ERROR_CHECK(ret,-1,"chmod");
}
```
#### 2. 获取当前目录getcwd

**学习目的**：了解指针作为参数和作为返回值的技巧
- man手册：
```C++
       #include <unistd.h>

       char *getcwd(char *buf, size_t size);
       //buf 传入传出参数

```

- 设计：

```C++
/*
返回值情况
1、 buf不为空，返回buf
*/
#include<43func.h>
int main(){
    char buf[1024] = {0};
    char *ret = getcwd(buf,sizeof(buf));
    //传入首地址，及长度信息(数组传入时长度信息丢失)
    
    ERROR_CHECK(ret,NULL,"getcwd");//报错检测，目录的数组太短可能目录输出越界就会报错
    printf("ret = %p,ret = %s\n",ret,ret);
    printf("ret = %p,ret = %s\n",buf,buf);
}
//2、buf微孔，返回一个堆空间的地址
#include<43func.h>
int main(){
    printf("cwd = %s\n",getcwd(NULL,0));
}

```

#### 3. 改变当前工作目录chdir
当前工作目录是一个进程的属性
- man手册
#include <unistd.h>
    int chdir(const char *path);

![](images/2023-09-13-17-23-47.png)
改成功了，但是只影响了子进程

#### 4. rmdir mkdir

- man 2 mkdir
 #include <sys/stat.h>
       #include <sys/types.h>

       int mkdir(const char *pathname, mode_t mode);
- man 2 rmdir
![](images/2023-09-13-17-29-08.png)

- 实现

1. mkdir

```C
#include<43func.h>
int main(int argc,char *argv[]){
    ARGS_CHECK(argc,2);
    int ret = mkdir(argv[1],0777);//需要8进制的777，所以写0777
    //所有创建文件的行为都会受到umask的影响
    ERROR_CHECK(ret,-1,"mkdir");

}
```

2. rmdir
只能删除空目录
```C
#include<43func.h>
int main(int argc,char *argv[]){
    ARGS_CHECK(argc,2);
    int ret = rmdir(argv[1]);
    ERROR_CHECK(ret,-1,"rmdir");

}
```



## 目录流
- 流
自动后移：用户可以不了解接口的情况下访问所有数据

例：C++迭代器

- 文件流回顾：见文件使用
- 目录流：

目录在磁盘中，以(带有ptr的)链表的形式进行存储
每一个**链表节点**(目录项，dirent:directory entry)，储存孩子的基本信息
![](images/2023-09-13-20-30-27.png)

- 目录流：是目录文件在内存中的缓冲区
每次除了取ptr所指地址，还会指针后移
![](images/2023-09-13-20-32-47.png)

### 目录流相关三个接口
![](images/2023-09-13-20-34-12.png)

### 1、opendir




### 2、readdir