#include <iostream>
using namespace std;
/*************************************************************************************************

归并排序是分治法的一个好例子，属于基于比较的内部/外部排序算法。普通的归并算法具有O(n * log(n))的时间
和O(n)的空间复杂度。就地归并算法能帮助降低额外空间开销，使得归并排序更高效。
归并排序之所以可以轻松应用到外部排序上，是因为归并排序的归并过程是顺序扫描的，可以用来处理顺序存储的
文件，多路归并还可以用多线程或是并行计算来加速，这样处理大文件就方便了。而想随机访问一个文件，就没那
么快了。
*************************************************************************************************/
void Merge(int a[], int tempArray[], int Lstart, int Rstart, int Rend)
{
	int Lend = Rstart - 1;
	int Length = Rend - Lstart + 1;
	int temppos = Lstart;
	while (Lstart <= Lend&&Rstart <= Rend)
	{
		if (a[Lstart] <= a[Rstart])
		{
			tempArray[temppos++] = a[Lstart++];
		}
		else
		{
			tempArray[temppos++] = a[Rstart++];
		}
	}
	while (Lstart <= Lend)
	{
		tempArray[temppos++] = a[Lstart++];
	}
	while (Rstart <= Rend)
	{
		tempArray[temppos++] = a[Rstart++];
	}
	for (int i = 0; i < Length; i++, Rend--)
	{
		a[Rend] = tempArray[Rend];
	}
}
void Msort(int a[], int tempArray[], int left, int right)
{
	if (left < right)
	{
		int center = (left + right) / 2;
		Msort(a, tempArray, left, center);
		Msort(a, tempArray, center + 1, right);
		Merge(a, tempArray, left, center + 1, right);
	}
}
void MergeSort(int a[], int n)
{
	int *tempArray = new int[n];
	if (tempArray)
	{
		Msort(a, tempArray, 0, n - 1);
	}
	else
	{
		cout << "Out of Space!" << endl;
	}
}
void main( )
{
	int a[] = { 34,8,64,51,32,21 };
	MergeSort(a, 6);
	for (int i = 0; i < 6; ++i)
	{
		cout << a[i] << " ";
	}
	cin.get();
}