#include "Stack.h"
#include "Stack.cpp"
template<class T>
class DoubleStack_Queue
{
public:
	DoubleStack_Queue():Q_size(0),s1(new Stack<T>),s2(new Stack<T>){}
	~DoubleStack_Queue()
	{
		clear();
	}
	void Enqueue(T Val);
	T Dequeue();
	int size();
	void clear();
	bool empty();
private:
	Stack<T> *s1;
	Stack<T> *s2;
	int Q_size;
};
template<class T>
void DoubleStack_Queue<T>::Enqueue(T Val)
{
	s1->push(Val);
	Q_size = s1->size();
}
template<class T>
T DoubleStack_Queue<T>::Dequeue()
{
	while (!s1->empty())
	{
		s2->push(s1->pop());
	}
	T _Val = s2->pop();
	Q_size = s2->size();
	return _Val;
}
template<class T>
int DoubleStack_Queue<T>::size()
{
	return Q_size;
}
template<class T>
void DoubleStack_Queue<T>::clear()
{
	if (!s1->empty())
	{
		s1->clear();
		Q_size = s1->size();
	}
	else
	{
		s2->clear();
		Q_size = s2->size();
	}

}
template<class T>
bool DoubleStack_Queue<T>::empty()
{
	if (!s1->empty())
	{
		return s1->empty();
	}
	else
	{
		return s2->empty();
	}
}
void main()
{
	DoubleStack_Queue<int> q;
	q.Enqueue(10);
	q.Enqueue(20);
	q.Enqueue(30);
	cout << q.size() << endl;
	cout << q.Dequeue() << endl;
	cout << q.Dequeue() << endl;
	cout << q.size() << endl;
	q.clear();
	cout << q.size() << endl;
	cin.get();
}