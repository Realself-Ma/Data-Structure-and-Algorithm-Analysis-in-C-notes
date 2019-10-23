#include <iostream>
using namespace std;
/*************************************************************************************************

希尔排序是插入排序的改进版。交换排序的目的，是通过交换，将逆序数降低为0。每交换一对相邻元素，逆序数
变化为1。如果交换的元素不相邻，则逆序数的变化可能就大于1。希尔排序的思路，就是通过交换离得更远的
两个元素，让逆序数更快地变为0（当然，并不总是管用）
关于希尔排序的复杂度，不一定是O(n^2)，要根据选取的间隔序列来分析

*************************************************************************************************/
void ShellSort(int a[], int n)
{
	int i, j, increment;
	for (increment = n / 2; increment > 0; increment /= 2)
	{
		for (i = increment; i < n; i++)
		{
			int temp = a[i];
			for (j = i; j >= increment; j -= increment)
			{
				if (a[j - increment]>temp)
				{
					a[j] = a[j - increment];
				}
				else
				{
					break;
				}
			}
			a[j] = temp;
		}
	}
}
void main()
{
	int a[] = { 34,8,64,51,32,21 };
	ShellSort(a, 6);
	for (int i = 0; i < 6; ++i)
	{
		cout << a[i] << " ";
	}
	cin.get();
}