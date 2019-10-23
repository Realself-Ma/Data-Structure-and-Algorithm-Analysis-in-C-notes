#include <iostream>
using namespace std;
template<class T>
struct ListNode
{
	T Val;
	ListNode<T> *pNext;
	ListNode(T _Val):Val(_Val),pNext(nullptr){}
};
template<class T>
class Queue
{
public:
	Queue():Q_size(0),head(nullptr){}
	~Queue()
	{
		clear();
	}
	void Enqueue(T Val);
	T Dequeue();
	void clear();
	bool empty();
	int size();
private:
	int Q_size;
	ListNode<T> *head;
};
template<class T>
void Queue<T>::Enqueue(T Val)
{
	ListNode<T> *pnew = new ListNode<T>(Val);
	if (head == nullptr)
	{
		head = pnew;
		pnew->pNext = nullptr;
	}
	else
	{
		ListNode<T> *ptemp = head;
		while (ptemp->pNext != nullptr)
		{
			ptemp = ptemp->pNext;
		}
		/*************************************************************
		不管while循环是ptemp->pNext != nullptr 还是循环ptemp!=nullptr 
		只要是直接将pnew赋值给ptemp，就不能将 pnew 连接上链表
		*************************************************************/
		/*ptemp = pnew;
		pnew->pNext = nullptr;*/

		ptemp->pNext = pnew;
		pnew->pNext = nullptr;
	}
	Q_size++;
}
template<class T>
T Queue<T>::Dequeue()
{
	if (head == nullptr)
	{
		cout << "Queue is empty!" << endl;
		return -1;
	}
	T _Val = head->Val;
	ListNode<T> *ptemp = head;
	head = head->pNext;
	delete ptemp;
	ptemp = nullptr;
	Q_size--;
	return _Val;
}
template<class T>
void Queue<T>::clear()
{
	if (head == nullptr)
	{
		cout << "Queue is empty!" << endl;
		return;
	}
	while (head != nullptr)
	{
		Dequeue();
	}
	Q_size = 0;
}
template<class T>
bool Queue<T>::empty()
{
	return head == nullptr;
}
template<class T>
int Queue<T>::size()
{
	return Q_size;
}
void main1()
{
	Queue<int> q;
	q.Enqueue(10);
	q.Enqueue(20);
	q.Enqueue(30);
	cout << q.size() << endl;
	cout << q.Dequeue() << endl;
	cout << q.Dequeue() << endl;
	cout << q.size() << endl;
	q.clear();
	cout << q.size() << endl;
	cout << q.empty() << endl;
	cin.get();
}