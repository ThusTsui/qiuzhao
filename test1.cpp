// #include <iostream>
// #include<cmath>
// using namespace std;
// int N;
// bool func(int ans)
// {
//     int fun = 0, i = 1, n = ans;//i是数量，n是每个方块的格子数
//     while (n!=1||i!=n)
//     {
//         fun += (n+1) * i;
//         n--;
//         i++;
//     }
//     if (fun==N) return true;
//     else return false;
// }
// int main()
// {
//     while (cin >> N)
//     { // 注意 while 处理多个 case
//         int ans = sqrt(N);
//         while(!func(ans)){
//             ans--;
//         }
//         cout << ans;
//     }
// }

#include <iostream>
#include <map>
#include <string>

using namespace std;

int main()
{
    map<int, string> a;

    int N;
    cin >> N;
    while (N--)
    {
        string temp;
        char cp;
        cin >> temp;
        if (temp[0] == 'o')
        {
            for (int i = 4;; i++)
            {
                cp[i - 4] = temp[i];
                if (temp[i] == 0)
                    break;
            }
            int ap=cp-'0';
            if(a.find(ap)) return a.end(ap);
        }
    }
}