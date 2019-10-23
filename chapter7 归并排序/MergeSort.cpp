#include <iostream>
using namespace std;
/*************************************************************************************************

�鲢�����Ƿ��η���һ�������ӣ����ڻ��ڱȽϵ��ڲ�/�ⲿ�����㷨����ͨ�Ĺ鲢�㷨����O(n * log(n))��ʱ��
��O(n)�Ŀռ临�Ӷȡ��͵ع鲢�㷨�ܰ������Ͷ���ռ俪����ʹ�ù鲢�������Ч��
�鲢����֮���Կ�������Ӧ�õ��ⲿ�����ϣ�����Ϊ�鲢����Ĺ鲢������˳��ɨ��ģ�������������˳��洢��
�ļ�����·�鲢�������ö��̻߳��ǲ��м��������٣�����������ļ��ͷ����ˡ������������һ���ļ�����û��
ô���ˡ�
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