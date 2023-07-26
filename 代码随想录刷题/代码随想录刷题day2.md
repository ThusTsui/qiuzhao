[209.长度最小的子数组](https://leetcode.cn/problems/minimum-size-subarray-sum/)

1. 暴力
两重for循环遍历，取满足的最小值
```C++
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int result = INT32_MAX; // 最终的结果
        int sum = 0; // 子序列的数值之和
        int subLength = 0; // 子序列的长度
        for (int i = 0; i < nums.size(); i++) { // 设置子序列起点为i
            sum = 0;
            for (int j = i; j < nums.size(); j++) { // 设置子序列终止位置为j
                sum += nums[j];
                if (sum >= s) { // 一旦发现子序列和超过了s，更新result
                    subLength = j - i + 1; // 取子序列的长度
                    result = result < subLength ? result : subLength;
                    break; // 因为我们是找符合条件最短的子序列，所以一旦符合条件就break
                }
            }
        }
        // 如果result没有被赋值的话，就返回0，说明没有符合条件的子序列
        return result == INT32_MAX ? 0 : result;
    }
};
```
2. 滑动窗口

只用一重for循环，将复杂度降到O(n)

```C++
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int result = INT32_MAX;
        int sum = 0; // 滑动窗口数值之和
        int i = 0; // 滑动窗口起始位置
        int subLength = 0; // 滑动窗口的长度
        for (int j = 0; j < nums.size(); j++) {
            sum += nums[j];
            // 注意这里使用while，每次更新 i（起始位置），并不断比较子序列是否符合条件
            while (sum >= s) {
                subLength = (j - i + 1); // 取子序列的长度
                result = result < subLength ? result : subLength;
                sum -= nums[i++]; // 这里体现出滑动窗口的精髓之处，不断变更i（子序列的起始位置）
            }
        }
        // 如果result没有被赋值的话，就返回0，说明没有符合条件的子序列
        return result == INT32_MAX ? 0 : result;
    }
};
```


- 滑动窗口的for循环永远是后面的指针，不然就跟暴力一样了
- 滑动窗口的关键在于前面的指针如何滑动前进


[59.螺旋矩阵II](https://leetcode.cn/problems/spiral-matrix-ii/)
模拟：
循环不变量原则：牢记区间固定，规则一致，要左闭右开就都左闭右开
奇偶只需最后判断最后一个数的值就好
```C++
class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> res(n, vector<int>(n, 0)); 
        int sx=0,sy=0;//每一圈的起始位置
        int x=1;
        int count=1;
        int loop=n/2;
        int i,j;
        while(loop--){
            i=sx;
            j=sy;
            for(j=sy;j<n-x;j++)//从左向右
                res[sx][j]=count++;
            for(i=sx;i<n-x;i++)//从上向下
                res[i][j]=count++;
            for(;j>sy;j--)//从右往左
                res[i][j]=count++;
            for(;i>sx;i--)
                res[i][j]=count++;

            //更新起始位置坐标
            sx++;
            sy++;
            //控制长度
            x++;
        }
        if(n%2) res[n/2][n/2] = count;
        return res;
    }
};
```