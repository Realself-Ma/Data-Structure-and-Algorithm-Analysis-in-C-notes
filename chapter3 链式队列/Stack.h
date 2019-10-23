#pragma once
#include <iostream>
using namespace std;
template<class T>
struct ListNode
{
	T Val;
	ListNode<T> *pNext;
	ListNode(T _Val) :Val(_Val), pNext(nullptr) {}
};
template<class T>
class Stack
{
public:
	Stack();
	~Stack();
	void push(T Val);
	T pop();
	bool empty();
	int size();
	void clear();
private:
	int S_size;
	ListNode<T> *head;
};

