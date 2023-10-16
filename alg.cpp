#include <cstdio>
#include <cmath>
#include <iostream>
using namespace std;

// bool isPerfectCube(int x)
// {
//     int y = cbrt(x);
//     return y * y * y == x;
// }

// int main()
// {
//     int n;
//     cin >> n;
//     for (int a = 2; a <= n; a++)
//     {
//         for (int b = 2; b < a; b++)
//         {
//             for (int c = b; c < a; c++)
//             {
//                 int d = a * a * a - b * b * b - c * c * c;
//                 if (c*c*c <= d  && isPerfectCube(d))
//                 {
//                     cout << "Cube = " << a << ", "
//                          << "Triple = (" << b << "," << c << "," << cbrt(d) << ")" << endl;
//                 }
//             }
//         }
//     }

//     return 0;
// }

// int main()
// {
//     int i = 7;
//     while (1)
//     {
//         if (i % 3 == 2 && i % 5 == 4 && i % 6 == 5)
//         {
//             cout << i << endl;
//             break;
//         }
//         i += 14;
//     }
// }

#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>

int s1[32]; // 初始状态的开关数组
int s2[32]; // 目标状态的开关数组
int press[32]; // 按钮按下的情况数组
int status[32]; // 当前状态的开关数组
char ss1[32]; // 输入的初始状态
char ss2[32]; // 输入的目标状态

using namespace std;

int main()
{
    // 初始化数组
    for (int i = 0; i < 32; ++i)
    {
        s1[i] = 0;
        s2[i] = 0;
        press[i] = 0;
        status[i] = 0;
    }

    // 输入初始状态和目标状态
    cin >> ss1;
    cin >> ss2;

    int n = strlen(ss1); // 初始状态的长度
    int len = n + 1; // 长度加 1 的值
    int flag = 0; // 标记变量，用于判断是否达到目标状态
    int ans = 0; // 记录按下的开关数量

    // 将字符转化为整型数组
    for (int i = 0; i < len; i++)
    {
        if (ss1[i] == '1')
        {
            s1[i + 1] = 1;
        }
        if (ss1[i] == '0')
        {
            s1[i + 1] = 0;
        }
        if (ss2[i] == '1')
        {
            s2[i + 1] = 1;
        }
        if (ss2[i] == '0')
        {
            s2[i + 1] = 0;
        }
    }

    // 遍历所有可能的按下开关的情况
    for (int i = 0; i < (1 << n); i++)
    {
        flag = 0; // 每次进入循环前重置 flag
        int temp = i; // 临时存储当前情况的值

        // 将当前情况转化为按下开关的状态
        for (int j = 1; j < len; j++)
        {
            press[j] = temp % 2;
            temp = temp / 2;
        }

        // 计算当前状态
        for (int k = 1; k < len; k++)
        {
            // 使用 XOR 运算来计算当前状态的开关
            status[k] = press[k - 1] ^ press[k] ^ press[k + 1] ^ s1[k];
        }

        // 检查当前状态是否与目标状态相等
        for (int k = 1; k < len; k++)
        {
            if (status[k] != s2[k])
            {
                flag = 1; // 若状态不相等，将 flag 置为 1
            }
        }

        // 若当前状态与目标状态相等，则计算按下的开关数量并输出结果，程序结束
        if (flag == 0)
        {
            for (int k = 1; k < len; k++)
            {
                if (press[k] == 1)
                {
                    ans += 1;
                }
            }
            cout << ans << endl;
            return 0;
        }
    }

    // 若遍历完所有情况后仍未找到相等的状态，则输出"impossible"表示无法从初始状态转换到目标状态
    cout << "impossible" << endl;
}