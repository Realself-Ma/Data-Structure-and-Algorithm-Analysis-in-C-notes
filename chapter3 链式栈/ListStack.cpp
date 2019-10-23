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
class Stack
{
public:
	Stack():S_size(0),head(nullptr){}
	~Stack()
	{
		clear();
	}
	void push(T Val);
	T pop();
	bool empty();
	int size();
	void clear();
private:
	int S_size;
	ListNode<T> *head;
};
/*
   push用头插法更轻松！！！！
*/
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
void main()
{
	Stack<int> s;
	s.push(10);
	s.push(20);
	s.push(30);
	cout << s.size() << endl;
	cout << s.pop() << endl;
	cout << s.pop() << endl;
	cout << s.size() << endl;
	s.clear();
	cout << s.size() << endl;
	cout << s.empty() << endl;
	cin.get();
}