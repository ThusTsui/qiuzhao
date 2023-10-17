#include <iostream>
#include <vector>
using namespace std;

/*
插入排序分析：
分为已排序和未排序，初始已排序区间只有1个元素 就是数组第1个，遍历未排序的每一个元素在已排序区间里找到合适的位置插入并保证数据一直有序。

具体实现：
两层循环，保证外层循环遍历过的元素都是已经排好序的。
外层循环从第一个元素开始负责遍历整个数组，确定当前的待插入元素；
内层循环负责判断该元素具体应该插入到前面已排好序数组的哪个位置，具体思路就是：如果该元素比前一个元素大就将两者交换。
结论：
1. 元素集合越接近有序，直接插入排序算法的时间效率越高；
2. 时间复杂度：O(N^2)；
3. 空间复杂度：O(1)。
*/
void InsertSort(vector<int> &nums, int n)
{
    if (n <= 1)
        return;
    for (int i = 0; i < n; ++i)
    {
        for (int j = i; j > 0 && nums[j] < nums[j - 1]; --j)
        {
            swap(nums[j], nums[j - 1]);
        }
    }
}
/*
冒泡排序分析：
两两元素相比，前一个比后一个大就交换，直到将最大的元素交换到末尾位置。一共进行n-1趟这样的交换将可以把所有的元素排好。
具体实现：
1. ?较相邻的元素。如果第?个?第?个?，就交换它们两个；
2. 对每?对相邻元素作同样的?作，从开始第?对到结尾的最后?对，这样在最后的元素应该会是最?的数；
3. 针对所有的元素重复以上的步骤，除了最后?个；
4. 重复步骤 1~3，直到排序完成。

总结：
1. 时间复杂度：O(N^2)；
2. 空间复杂度：O(1)。
*/
void BubbleSort(vector<int> &nums, int n)
{
    if (n <= 1)
        return;
    bool is_swap;
    for (int i = 1; i < n; ++i)
    {
        is_swap = false;
        // 设定?个标记，若为false，则表示此次循环没有进?交换，也就是待排序列已经有序，排序已经完成。
        for (int j = 1; j < n - i + 1; ++j)
        {
            if (nums[j] < nums[j - 1])
            {
                swap(nums[j], nums[j - 1]);
                is_swap = true; // 表示有数据交换
            }
        }
        if (!is_swap)
            break; // 没有数据交集，提前退出
    }
}
int main()
{
    vector<int> nums;
    int i;
    cout << "请输入要排序的数组：" << endl;
    while (cin >> i)
    {
        nums.push_back(i);
        if (cin.get() == '\n')
            break;
    }
    // InsertSort(nums, nums.size());//执行插入排序
    BubbleSort(nums, nums.size()); // 执行冒泡排序
    for (auto e : nums)
        cout << e << " ";
    return 0;
}
