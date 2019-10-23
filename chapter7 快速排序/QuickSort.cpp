#include <iostream>
using namespace std;
#define CUTOFF 3
/*************************************************************************************************

快速排序是实际应用最广的基于内存的不稳定的比较排序。拥有O(n * log(n))的平均复杂度和O(n ^ 2)的
最坏复杂度。采用的思路是分治法，递归实现

*************************************************************************************************/
void Swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}
int Median3(int a[], int left, int right)
{
	int center = (left + right) / 2;
	if (a[left] > a[center])
	{
		Swap(a[left], a[center]);
	}
	if (a[left] > a[right])
	{
		Swap(a[left], a[right]);
	}
	if (a[center] > a[right])
	{
		Swap(a[center], a[right]);
	}
	Swap(a[center], a[right - 1]);
	return a[right - 1];
}
void QSort(int a[],int left,int right)
{
	int i, j, pivot;
	if (left + CUTOFF <= right)
	{
		pivot = Median3(a, left, right);
		i = left;
		j = right - 1;
		for (;;)
		{
			/*****************************************************
			++i,--j 才能保证，Swap交换的是i,j停住位置的数据
			i++,j-- 则不能保证，因为是先引用再自增，Swap交换的是
			自增后的a[i+1],a[j-1]
			*****************************************************/
			while(a[++i]<pivot){}
			while(a[--j]>pivot){}
			if (i < j)
			{
				Swap(a[i], a[j]);
			}
			else
			{
				break;
			}
		}
		Swap(a[i], a[right - 1]);
		/*******************************************
		递归的对小于枢纽元和大于枢纽元的元素进行排序
		所以，不包括枢纽元在内（i-1,i+1）;
		*******************************************/
		QSort(a, left, i - 1);
		QSort(a, i + 1, right);
	}
	else /* 小数组的情况插入排序的性能更优 */
	{
		for (i = left+1; i <= right; i++)
		{
			int temp = a[i];
			for (j = i; j > left&&a[j - 1] > temp; j--)
			{
				a[j] = a[j - 1];
			}
			a[j] = temp;
		}
	}
}
void QuickSort(int a[], int n)
{
	QSort(a, 0, n - 1);
}
void main()
{
	int a[] = { 8,1,4,9,6,3,5,2,7,0 };
	QuickSort(a, 10);
	for (int i = 0; i < 10; ++i)
	{
		cout << a[i] << " ";
	}
	cin.get();
}