#include <iostream>
using namespace std;
/**********************************************************************************************

ѡ��������һ��O(n^2)����Ľ��������㷨
����worst case��average case��best case֮��ѡ�������ȱ���Զ��׼��������������������������ȣ�
�Ƚϴ���ʼ����O(n^2)

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