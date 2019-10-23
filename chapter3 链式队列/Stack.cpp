#include "Stack.h"
template<class T>
Stack<T>::Stack() :S_size(0), head(nullptr) {}
template<class T>
Stack<T>::~Stack()
{
	clear();
}
template<class T>
void Stack<T>::push(T Val)
{
	ListNode<T> *pnew = new ListNode<T>(Val);
	if (head == nullptr)
	{
		head = pnew;
		pnew->pNext = nullptr;
	}
	else
	{
		pnew->pNext = head;
		head = pnew;
	}
	S_size++;
}
template<class T>
T Stack<T>::pop()
{
	if (S_size == 0 && head == nullptr)
	{
		cout << "Stack is empty!" << endl;
		return -1;
	}
	T _Val = head->Val;
	ListNode<T> *ptemp = head;
	head = head->pNext;
	delete ptemp;
	ptemp = nullptr;
	S_size--;
	return _Val;
}
template<class T>
bool Stack<T>::empty()
{
	return head == nullptr;
}
template<class T>
int Stack<T>::size()
{
	return S_size;
}
template<class T>
void Stack<T>::clear()
{
	if (head == nullptr)
	{
		cout << "Stack is empty!" << endl;
		return;
	}
	/*ListNode<T> *p1, *p2;
	p1 = head;
	while (p1 != nullptr)
	{
	p2 = p1->pNext;
	delete p1;
	p1 = p2;
	}
	head = nullptr;*/

	while (!empty())
	{
		pop();
	}

	S_size = 0;
}