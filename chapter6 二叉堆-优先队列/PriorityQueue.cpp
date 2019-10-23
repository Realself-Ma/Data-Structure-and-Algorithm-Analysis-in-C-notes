#include <iostream>
using namespace std;
const int Mindata = 0;
template<class T>
class PriorityQueue
{
public:
	void Initialize(int MaxSize);
	void Enqueue(T Val);
	T Dequeue();
	void BuildHeap(T a[],int n);
	void printQueue();
	void clear();
	bool isFull();
	bool isEmpty();
private:
	T *Vals;
	int Capacity;
	int Size;
	void PercolateDown(int pos);
};
template<class T>
void PriorityQueue<T>::Initialize(int MaxSize)
{
	Vals = new T[MaxSize + 1]{ 0 };
	Vals[0] = Mindata;
	this->Capacity = MaxSize;
	this->Size = 0;
}
template<class T>
void PriorityQueue<T>::Enqueue(T Val)
{
	int i;
	if (isFull())
	{
		cout << "PriorityQueue is Full" << endl;
		return;
	}
	/***************************************************
	****************复杂度更低的交换方法****************
	Vals[0]=Mindata 是一个标记，避免了循环终止的测试代码
	****************************************************/
	for (i = ++Size; Vals[i / 2] > Val; i /= 2)
	{
		/***** ++Size用的很巧妙 *****/
		Vals[i] = Vals[i / 2];
	}
	Vals[i] = Val;
}
template<class T>
T PriorityQueue<T>::Dequeue()
{
	int i, child;
	T Min, Last;
	if (isEmpty())
	{
		cout << "PriorityQueue is  Empty!" << endl;
		return -1;
	}
	Min = Vals[1];
	       /***** Size--用的很巧妙 *****/
	Last = Vals[Size--];
	for (i = 1; i * 2 < Size; i = child)
	{
		/***************************************************************
		i从1开始，leftchild= 2 * i;
		数组的界限是a[Size],所以child不能为Size，不然测试a[child+1]就会越界
		***************************************************************/
		child = 2 * i;
		if (child != Size&&Vals[child + 1] < Vals[child])
		{
			child++;
		}
		if (Last > Vals[child])
		{
			Vals[i] = Vals[child];
		}
		else
		{
			break;
		}
	}
	Vals[i] = Last;
	return Min;
}
template<class T>
void PriorityQueue<T>::PercolateDown(int pos)
{
	int i, child;
	T temp = Vals[pos];
	for (i = pos; i * 2 < Size; i = child)
	{
		child = i * 2;
		if (child != Size&&Vals[child + 1] < Vals[child])
		{
			child++;
		}
		if (temp > Vals[child])
		{
			Vals[i] = Vals[child];
		}
		else
		{
			break;
		}
	}
	Vals[i] = temp;
}
template<class T>
void PriorityQueue<T>::BuildHeap(T a[],int n)
{
	for (int i = 0; i < n; i++)
	{
		Vals[i + 1] = a[i];
		Size++;
	}

	for (int i = n / 2; i > 0; i--)
	{
		PercolateDown(i);
	}
}
template<class T>
void PriorityQueue<T>::printQueue()
{
	for (int i = 1; i <=Capacity; ++i)
	{
		cout << Vals[i] << " ";
	}
	cout << "\n";
}
template<class T>
void PriorityQueue<T>::clear()
{
	delete[]Vals;
	Size = Capacity = 0;
}
template<class T>
bool PriorityQueue<T>::isFull()
{
	return Size == Capacity;
}
template<class T>
bool PriorityQueue<T>::isEmpty()
{
	return Size == 0;
}
void main()
{
	PriorityQueue<int> pq;
	pq.Initialize(20);
	int a[]{ 150,80,40,30,10,70,110,100,20,90,60,50,120,140,130 };
	pq.BuildHeap(a, 15);
	pq.printQueue();
	cin.get();
}
void main1()
{
	PriorityQueue<int> pq;
	pq.Initialize(11);
	pq.Enqueue(13);
	pq.Enqueue(21);
	pq.Enqueue(16);
	pq.Enqueue(24);
	pq.Enqueue(31);
	pq.Enqueue(19);
	pq.Enqueue(68);
	pq.Enqueue(65);
	pq.Enqueue(26);
	pq.Enqueue(32);
	pq.printQueue();
	pq.Enqueue(14);
	pq.printQueue();
	cout << pq.Dequeue() << endl;
	cout << pq.Dequeue() << endl;
	cout << pq.Dequeue() << endl;
	pq.clear();
	pq.printQueue();
	cin.get();
}