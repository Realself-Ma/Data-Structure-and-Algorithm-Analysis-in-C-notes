#include <iostream>
using namespace std;
/**********************************************************************************************

选择排序是一种O(n^2)级别的交换排序算法
分析worst case，average case和best case之后，选择排序的缺点显而易见——交换次数与逆序数成正比，
比较次数始终是O(n^2)

**********************************************************************************************/
void SelectionSort(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (a[i] > a[j])
			{
				int temp = a[j];
				a[j] = a[i];
				a[i] = temp;
			}
		}
	}
}
void main()
{
	int a[] = { 34,8,64,51,32,21 };
	SelectionSort(a, 6);
	for (int i = 0; i < 6; ++i)
	{
		cout << a[i] << " ";
	}
	cin.get();
}