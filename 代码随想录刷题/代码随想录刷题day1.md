[704二分查找](https://leetcode.cn/problems/binary-search/solution/er-fen-cha-zhao-by-leetcode-solution-f0xw/)

1. 定好右区间的开闭，决定是while(l<=r或者l＜r),还有后面更新区间带不带±1；
2. mid的取法left + ((right - left) / 2)可以防止溢出

```C++
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l=0;
        int r=nums.size() - 1;
        while(l <= r){
            int mid = l + r >> 1;
            if(nums[mid] > target) r =mid-1;
            else if(nums[mid] < target) l = mid+1;
            else return mid;
        }
        return -1;
    }
};
```
补充：
左闭右开做法：
```C++
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l=0;
        int r=nums.size();//左闭右开
        while(l<r){
            int mid=l+r>>1;
            if(nums[mid]<target) l=mid+1;//更新左边时一样
            else if(nums[mid]>target) r=mid;//更新右边时，r已经找过，但因为是右开，所以只需令r=mid，不会再搜索r
            else return mid;
        }
        return -1;
    }
};
```


- 二分需要再加几道巩固一下



[27. 移除元素](https://leetcode.cn/problems/remove-element/)

1. 暴力

```C++
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int size = nums.size();
        for(int i=0;i<size;i++){
            if(nums[i]==val){
                for(int j=i;j<size-1;j++){
                    nums[j]=nums[j+1];
                }           
            i--;//移位后还要在这位计算，不能让i++，所以--抵消
            size--;
            }
        }
        return size;
    }
};
```

2. 双指针

- 快慢指针，快指针在前，碰到需移除的继续走，遇到不须移除的，将快指针赋值给慢指针
```C++
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int size = nums.size();
        int l=0;
        for(int r=0;r<size;r++){
            if(nums[r]!=val)
                nums[l++]=nums[r];
            }
        return l;
    }
};
```



[977. 有序数组的平方](https://leetcode.cn/problems/squares-of-a-sorted-array/)

1. 暴力
```C++
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int size = nums.size();
        for(int i=0;i<size;i++){
            nums[i]=nums[i]*nums[i];
        }
        sort(nums.begin(),nums.end());
        return nums;
    }
};
```


2. 双指针

```C++
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int size = nums.size();
        int i = 0,j = size-1;
        vector<int> temp(size);
        while(i <= j){// 注意这里要i <= j，因为最后要处理两个元素
            if(nums[i]*nums[i] < nums[j]*nums[j]) {
                temp[--size] = nums[j]*nums[j];
                j--;
            }
            else{
                temp[--size] = nums[i]*nums[i];
                i++;
            }
        }
        return temp;
    }
};
```

总结：
- 数组问题考虑开闭，考虑最后剩下两个元素时候合不合理
- 数组考虑双指针