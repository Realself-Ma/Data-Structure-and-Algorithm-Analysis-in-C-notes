#include <iostream>
using namespace std;
/******************************************************************************************************
如果数组的前i - 1个元素已经排好序，你要将第i个元素插入到其中，使得前i个元素变得有序。为了找到应该插入
的位置，我们从后向前扫描，直到找到合适的位置为止。扫描过程中还需要把每个检查的每个元素向后移动一位，
以便给新元素腾出位置。
不难发现在数组已经“接近有序”的时候（也就是逆序数很小的时候），需要的“移动”操作就很少了。
当数组完全有序时，插入排序的复杂度就降低到了O(n)。这中worst case和best case的明显效率差异，就是插入排序
比选择排序好的原因。尽管他们理论上复杂度都是O(n^2)。
******************************************************************************************************/
void InsertionSort(int a[], int n)
{
	int i, j;
	for (i = 1; i < n; i++)
	{
		int temp = a[i];
		for (j = i; j > 0 && a[j - 1] > temp; j--)
		{
			a[j] = a[j - 1];
		}
		a[j] = temp;
	}
}
void main()
{
	int a[] = { 34,8,64,51,32,21 };
	InsertionSort(a, 6);
	for (int i = 0; i < 6; ++i)
	{
		cout << a[i] << " ";
	}
	cin.get();
}