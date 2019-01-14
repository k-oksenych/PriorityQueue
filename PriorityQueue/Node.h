#pragma once

template <typename T>
class Node
{
public:
	Node(T value, int priority) :
		value(value),
		priority(priority)
	{
	}

	Node* GetNext() const
	{
		return next;
	}

	Node* GetPrev() const
	{
		return prev;
	}

	T GetValue() const
	{
		return value;
	}
	int GetPriority() const
	{
		return priority;
	}

	void SetNext(Node* const next)
	{
		this->next = next;
	}
	void SetPrev(Node* const prev)
	{
		this->prev = prev;
	}
private:
	Node* next = nullptr;
	Node* prev = nullptr;
	T value;
	int priority;
};