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
class SingleLinkedList
{
public:
	SingleLinkedList():head(nullptr){}
	~SingleLinkedList()
	{
		clear();
	}
	void insertFront(T Val);
	void insertBack(T Val);
	void insertNode(int pos,T Val);
	void deleteNode(int pos);
	ListNode<T> * find(T Val);
	void update(int pos,T Val);
	void reverse();
	void clear();
	void printList();
private:
	ListNode<T> *head;
};
template<class T>
void SingleLinkedList<T>::insertFront(T Val)
{
	ListNode<T> *pnew = new ListNode<T>(Val);
	if (head == nullptr)
	{
		pnew->pNext = nullptr;
		head = pnew;
	}
	else
	{
		pnew->pNext = head;
		head = pnew;
	}
}
template<class T>
void SingleLinkedList<T>::insertBack(T Val)
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
		ptemp->pNext = pnew;
		pnew->pNext = nullptr;
	}
}
template<class T>
void SingleLinkedList<T>::insertNode(int pos, T Val)
{
	if (head == nullptr)
	{
		cout << "list is empty!" << endl;
		return;
	}
	ListNode<T> *pnew = new ListNode<T>(Val);
	if (pos == 1)
	{
		insertFront(Val);
	}
	else
	{
		ListNode<T> *ptemp1 = head;
		for (int i = 1; i < pos - 1; ++i)
		{
			ptemp1 = ptemp1->pNext;
		}
		ListNode<T> *ptemp2 = ptemp1->pNext;
		ptemp1->pNext = pnew;
		pnew->pNext = ptemp2;
	}
}
template<class T>
void SingleLinkedList<T>::deleteNode(int pos)
{
	if (head == nullptr)
	{
		cout << "list is empty!" << endl;
		return;
	}
	ListNode<T> *ptemp1 = head;
	if (pos == 1)
	{
		head = ptemp1->pNext;
		delete ptemp1;
		ptemp1 = nullptr;
	}
	else
	{
		for (int i = 1; i < pos-1; ++i)
		{
			ptemp1 = ptemp1->pNext;
		}
		ListNode<T> *ptemp2 = ptemp1->pNext;
		ptemp1->pNext = ptemp2->pNext;
		delete ptemp2;
		ptemp2 = nullptr;
	}
}
template<class T>
ListNode<T> * SingleLinkedList<T>::find(T Val)
{
	if (head == nullptr)
	{
		cout << "list is empty!" << endl;
		return nullptr;
	}
	ListNode<T> *ptemp = head;
	while (ptemp != nullptr)
	{
		if (ptemp->Val == Val)
		{
			return ptemp;
		}
		ptemp = ptemp->pNext;
	}
	return nullptr;
}
template<class T>
void SingleLinkedList<T>::update(int pos, T Val)
{
	if (head == nullptr)
	{
		cout << "list is empty!" << endl;
		return;
	}
	ListNode<T> *pnew = new ListNode<T>(Val);
	ListNode<T> *ptemp1 = head;
	if (pos == 1)
	{
		pnew->pNext = head->pNext;
		delete head;
		head = pnew;
	}
	else
	{
		for (int i = 1; i < pos - 1; ++i)
		{
			ptemp1 = ptemp1->pNext;
		}
		ListNode<T> *ptemp2 = ptemp1->pNext;
		ptemp1->pNext = pnew;
		pnew->pNext = ptemp2->pNext;
		delete ptemp2;
		ptemp2 = nullptr;
	}
}
template<class T>
void SingleLinkedList<T>::printList()
{
	/*if (head == nullptr)
	{
		cout << "list is empty!" << endl;
		return;
	}*/
	ListNode<T> *ptemp = head;
	while (ptemp != nullptr)
	{
		cout << ptemp->Val << " ";
		ptemp = ptemp->pNext;
	}
	cout << "\n";
}
template<class T>
void SingleLinkedList<T>::clear()
{
	if (head == nullptr)
	{
		cout << "list is empty!" << endl;
		return;
	}
	ListNode<T> *p1, *p2;
	p1 = head;
	while (p1 != nullptr)
	{
		p2 = p1->pNext;
		delete p1;
		p1 = p2;
	}
	head = nullptr;
}
template<class T>
void SingleLinkedList<T>::reverse()
{
	if (head == nullptr)
	{
		cout << "list is empty!" << endl;
		return;
	}
	ListNode<T> *p1, *p2, *p3;
	p1 = head;
	p2 = p1->pNext;
	while (p2 != nullptr)
	{
		/*
		每次实际连接的是 p3 和 p2 ,所以，p2->pNext = p1 不会出现双链
		（除初始化时，head 和 head->pNext 之间是双链）
		*/
		p3 = p2->pNext;
		p2->pNext = p1;/*在将链表逆转的同时，也将 p2 和 p3 之间的连接断开，使不会出现双链*/
		p1 = p2;
		p2 = p3;
	}
	/*所以，这里要断链，让head->pNext指向空指针*/
	head->pNext = nullptr;
	head = p1;/*此时，p1就是头指针*/
}
void main()
{
	SingleLinkedList<int> list;
	list.insertBack(10);
	list.insertBack(20);
	list.insertBack(30);
	list.insertFront(100);
	list.insertNode(2, 200);
	list.deleteNode(2);
	list.deleteNode(1);
	cout << list.find(10)->Val << endl;
	list.update(1, 50);
	list.printList();
	list.reverse();
	list.printList();
	list.clear();
	list.printList();
	cin.get();
}
