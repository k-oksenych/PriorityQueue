#include <iostream>

#include "Queue.h"

using namespace std;

int main()
{
	PriorityQueue<int> queue;
	queue.Enqueue(5, 6);
	queue.Enqueue(8, 7);
	queue.Enqueue(10, 6);
	queue.Enqueue(4, 7);
	queue.Enqueue(3, 2);
	queue.Enqueue(2, 1);
	queue.Enqueue(9, 1);
	queue.Print();
	//queue.Clear();
	//queue.Dequeue();
	//queue.Print();
	cout << queue.GetSize() << endl;
	//cout << boolalpha << queue.IsEmpty() << endl;
	//queue.Clear();
	//cout << queue.IsEmpty() << endl;
	//cout << queue.Peek() << endl;
	//queue.Print();

	//PriorityQueue<int> queue2;
	//queue2 = queue;
	//queue2.Print();

	//PriorityQueue<int> queue3 = std::move(queue2);
	//queue3.Print();
	//queue2.Print();
}