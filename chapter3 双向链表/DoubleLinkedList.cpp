#include <iostream>
using namespace std;
template<class T>
struct ListNode
{
	T Val;
	ListNode<T> *prev;
	ListNode<T> *next;
	ListNode(T _Val):Val(_Val),prev(nullptr),next(nullptr){}
};
template<class T>
class DoubleLinkedList
{
public:
	DoubleLinkedList():size(0),head(nullptr),tail(nullptr){}
	~DoubleLinkedList()
	{
		clear();
	}
	void insertFront(T Val);
	void insertBack(T Val);
	void insertNode(int pos, T Val);
	void deleteNode(int pos);
	ListNode<T> *find(T Val);
	void updateNode(int pos,T Val);
	void clear();
	void print_headTotail();
	void print_tailTohead();
private:
	int size;
	ListNode<T> *head;
	ListNode<T> *tail;
};
template<class T> 
void DoubleLinkedList<T>::insertFront(T Val)
{
	ListNode<T> *pnew = new ListNode<T>(Val);
	if (head == nullptr&&tail == nullptr)
	{
		head = tail = pnew;
		pnew->prev = nullptr;
		pnew->next = nullptr;
	}
	else
	{
		head->prev = pnew;
		pnew->next = head;
		pnew->prev = nullptr;
		head = pnew;
	}
	size++;
}
template<class T>
void DoubleLinkedList<T>::insertBack(T Val)
{
	ListNode<T> *pnew = new ListNode<T>(Val);
	if (head == nullptr&&tail == nullptr)
	{
		head = tail = pnew;
		pnew->prev = nullptr;
		pnew->next = nullptr;
	}
	else
	{
		tail->next = pnew;
		pnew->prev = tail;
		pnew->next = nullptr;
		tail = pnew;
	}
	size++;
}
template<class T>
void DoubleLinkedList<T>::insertNode(int pos, T Val)
{
	if (size == 0 && head == nullptr)
	{
		cout << "list is empty!" << endl;
		return;
	}
	if (pos<1 || pos>size)
	{
		cout << "Out of Range!" << endl;
		return;
	}
	if (pos == 1)
	{
		insertFront(Val);
	}
	else
	{
		ListNode<T> *pnew = new ListNode<T>(Val);
		ListNode<T> *ptemp1, *ptemp2;
		ptemp1 = head;
		for (int i = 1; i < pos - 1; ++i)
		{
			ptemp1 = ptemp1->next;
		}
		ptemp2 = ptemp1->next;
		ptemp1->next = pnew;
		pnew->prev = ptemp1;
		pnew->next = ptemp2;
		ptemp2->prev = pnew;
	}
	size++;
}
template<class T>
void DoubleLinkedList<T>::deleteNode(int pos)
{
	if (size == 0 && head == nullptr)
	{
		cout << "list is empty!" << endl;
		return;
	}
	if (pos<1 || pos>size)
	{
		cout << "Out of Range!" << endl;
		return;
	}
	if (pos == 1)
	{
		ListNode<T> *ptemp1, *ptemp2;
		ptemp1 = head;
		ptemp2 = head->next;
		head = ptemp2;
		ptemp2->prev = nullptr;
		delete ptemp1;
		ptemp1 = nullptr;
	}
	else
	{
		ListNode<T> *ptemp1, *ptemp2;
		ptemp1 = head;
		for (int i = 1; i < pos - 1; ++i)
		{
			ptemp1 = ptemp1->next;
		}
		ptemp2 = ptemp1->next;
		ptemp1->next = ptemp2->next;
		if (ptemp2->next != nullptr)
		{
			ptemp2->next->prev = ptemp1;
			delete ptemp2;
			ptemp2 = nullptr;
		}
		else
		{
			delete ptemp2;
			ptemp2 = nullptr;
			tail = ptemp1;
		}
	}
	size--;
}
template<class T>
ListNode<T> *DoubleLinkedList<T>::find(T Val)
{
	if (size == 0 && head == nullptr)
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
		ptemp = ptemp->next;
	}
	return nullptr;
}
template<class T>
void DoubleLinkedList<T>::updateNode(int pos,T Val)
{
	if (size == 0 && head == nullptr)
	{
		cout << "list is empty!" << endl;
		return;
	}
	if (pos<1 || pos>size)
	{
		cout << "Out of Range!" << endl;
		return;
	}
	if (pos < size)
	{
		deleteNode(pos);
		insertNode(pos, Val);
	}
	else
	{
		deleteNode(pos);
		insertBack(Val);
	}
}
template<class T>
void DoubleLinkedList<T>::clear()
{
	if (size == 0 && head == nullptr)
	{
		cout << "list is empty!" << endl;
		return;
	}
	ListNode<T> *p1, *p2;
	p1 = head;
	while (p1 != nullptr)
	{
		p2 = p1->next;
		delete p1;
		p1 = p2;
	}
	size = 0;
	head = tail = nullptr;
}
template<class T>
void DoubleLinkedList<T>::print_headTotail()
{
	ListNode<T> *ptemp = head;
	while (ptemp != nullptr)
	{
		cout << ptemp->Val << " ";
		ptemp = ptemp->next;
	}
	cout << "\n";
}
template<class T>
void DoubleLinkedList<T>::print_tailTohead()
{
	ListNode<T> *ptemp = tail;
	while (ptemp != nullptr)
	{
		cout << ptemp->Val << " ";
		ptemp = ptemp->prev;
	}
	cout << "\n";
}
void main()
{
	DoubleLinkedList<int> list;
	list.insertBack(10);
	list.insertBack(20);
	list.insertBack(30);
	list.insertFront(200);
	list.insertNode(4, 500);
	cout << list.find(10)->next->Val << endl;
	list.updateNode(4, 800);
	list.deleteNode(4);
	//list.clear();
	list.print_headTotail();
	list.print_tailTohead();
	cin.get();
}
