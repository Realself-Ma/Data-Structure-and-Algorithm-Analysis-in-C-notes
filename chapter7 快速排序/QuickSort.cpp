#include <iostream>
using namespace std;
#define CUTOFF 3
/*************************************************************************************************

����������ʵ��Ӧ�����Ļ����ڴ�Ĳ��ȶ��ıȽ�����ӵ��O(n * log(n))��ƽ�����ӶȺ�O(n ^ 2)��
����Ӷȡ����õ�˼·�Ƿ��η����ݹ�ʵ��

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
			++i,--j ���ܱ�֤��Swap��������i,jͣסλ�õ�����
			i++,j-- ���ܱ�֤����Ϊ����������������Swap��������
			�������a[i+1],a[j-1]
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
		�ݹ�Ķ�С����ŦԪ�ʹ�����ŦԪ��Ԫ�ؽ�������
		���ԣ���������ŦԪ���ڣ�i-1,i+1��;
		*******************************************/
		QSort(a, left, i - 1);
		QSort(a, i + 1, right);
	}
	else /* С��������������������ܸ��� */
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