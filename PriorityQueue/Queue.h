#pragma once
#include <iostream>

#include "Node.h"

using namespace std;

template <typename T>
class PriorityQueue
{
public:
	PriorityQueue();
	PriorityQueue(const PriorityQueue& source);
	PriorityQueue(PriorityQueue&& source);
	~PriorityQueue();

	PriorityQueue& operator=(const PriorityQueue& right);
	PriorityQueue& operator=(PriorityQueue&& right);

	void Clear();
	T Dequeue();
	void Enqueue(const T item, const int priority);
	unsigned int GetSize() const;
	bool IsEmpty() const;
	T& Peek();
	const T& Peek() const;

	void Print() const;

private:
	Node<T>* head = nullptr;
	void Copy(const PriorityQueue& source);
	void Move(PriorityQueue&& source);
};

template <typename T>
PriorityQueue<T>::PriorityQueue()
{
}

template <typename T>
void PriorityQueue<T>::Copy(const PriorityQueue& source)
{
	if (source.head != nullptr)
	{
		Node<T>* head = new Node<T>(source.head->GetValue(), source.head->GetPriority());
		this->head = head;
	}

	Node<T>* new_node = this->head;
	Node<T>* old_node = source.head;

	while ((old_node = old_node->GetNext()) != nullptr)
	{
		Node<T>* node = new Node<T>(old_node->GetValue(), old_node->GetPriority());
		new_node->SetNext(node);
		if (new_node == this->head)
		{
			new_node->SetPrev(nullptr);
		}
		else
		{
			new_node->SetPrev(new_node);
		}
		new_node = node;
	}
}

template <typename T>
void PriorityQueue<T>::Move(PriorityQueue&& source)
{
	if (source.head != nullptr)
	{
		Node<T>* head = new Node<T>(source.head->GetValue(), source.head->GetPriority());
		head->SetNext(source.head->GetNext());
		head->SetPrev(nullptr);
		this->head = head;
	}

	source.head = nullptr;
}

template <typename T>
PriorityQueue<T>::PriorityQueue(const PriorityQueue& source)
{
	Copy(source);
}

template <typename T>
PriorityQueue<T>::PriorityQueue(PriorityQueue&& source)
{
	Move(std::move(source));
}

template <typename T>
PriorityQueue<T>::~PriorityQueue()
{
	if (head != nullptr)
	{
		Clear();
	}
}

template <typename T>
PriorityQueue<T>& PriorityQueue<T>::operator=(const PriorityQueue& right)
{
	Copy(std::move(right));

	return *this;
}

template <typename T>
PriorityQueue<T>& PriorityQueue<T>::operator=(PriorityQueue&& right)
{
	Move(right);

	return *this;
}

template <typename T>
void PriorityQueue<T>::Clear()
{
	if (head != nullptr)
	{
		Node<T>* current = head;

		if (current->GetNext() != nullptr)
		{
			Node<T>* next = current->GetNext();

			while (next != nullptr)
			{
				delete current;
				current = next;
				next = current->GetNext();
			}
		}
		delete current;
		head = nullptr;
	}
}

template <typename T>
T PriorityQueue<T>::Dequeue()
{
	T value = 0;

	if (head != nullptr)
	{
		Node<T>* newHead = head->GetNext();
		value = head->GetValue();
		delete head;
		head = newHead;
	}

	return value;
}

template <typename T>
void PriorityQueue<T>::Enqueue(const T item, const int priority)
{
	Node<T>* node = new Node<T>(item, priority);

	if (head == nullptr) //empty
	{
		head = node;
	}
	else //not empty
	{
		Node<T>* current = head;
		Node<T>* previous = nullptr;

		while (current->GetNext() != nullptr)
		{
			if (node->GetPriority() > current->GetPriority())
			{
				break;
			}

			previous = current;
			current = current->GetNext();
		}

		if (current->GetNext() == nullptr && current->GetPriority() >= node->GetPriority()) //last node
		{
			current->SetNext(node);
			node->SetPrev(current);
		}
		else if (current == head && node->GetPriority() >= current->GetPriority()) //first node
		{
			if (node->GetPriority() == current->GetPriority())
			{
				current->SetNext(node);
				node->SetPrev(current);
			}
			else
			{
				node->SetNext(current);
				current->SetPrev(node);
				head = node;
			}

		}
		else //others
		{
			if (current->GetPriority() == node->GetPriority())
			{
				while (node->GetPriority() < current->GetPriority() || current->GetNext() != nullptr)
				{
					previous = current;
					current = current->GetNext();
				}

				current->SetNext(node);
				node->SetPrev(current);

				if (current->GetNext() != nullptr)
				{
					node->SetNext(current->GetNext());
					current->GetNext()->SetPrev(node);
				}
			}
			if (previous != nullptr)
			{
				previous->SetNext(node);
				node->SetPrev(previous);
			}
			node->SetNext(current);
			current->SetPrev(node);
		}
	}
}

template <typename T>
unsigned int PriorityQueue<T>::GetSize() const
{
	unsigned int size = 0;

	if (head == nullptr)
	{
		return size;
	}
	else
	{
		Node<T>* current = head;
		++size;

		while (current->GetNext() != nullptr)
		{
			++size;
			current = current->GetNext();
		}
	}

	return size;
}

template <typename T>
bool PriorityQueue<T>::IsEmpty() const
{
	bool empty = false;

	if (head == nullptr)
	{
		empty = true;
	}

	return empty;
}

template <typename T>
T& PriorityQueue<T>::Peek()
{
	T value = 0;

	if (head != nullptr)
	{
		value = head->GetValue();
	}

	return value;
}

template <typename T>
const T& PriorityQueue<T>::Peek() const
{
	T value = 0;

	if (head != nullptr)
	{
		value = head->GetValue();
	}

	return value;
}

template <typename T>
void PriorityQueue<T>::Print() const
{
	Node<T>* node = head;
	while (node != nullptr)
	{
		cout << node->GetValue() << ' ';

		node = node->GetNext();
	}

	if (head == nullptr)
	{
		cout << "Queue is empty";
	}

	cout << endl;
}