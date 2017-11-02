/*
Author: Anthony Travisano
*/
#pragma once
#include <iostream>
#include <memory>

using namespace std;

template <class DataType>
struct Node
{
	DataType info;
	shared_ptr<Node<DataType>> next;
};

template <class DataType>
class PullQueue
{
	shared_ptr<Node<DataType>> front; //front and back pointers
	shared_ptr<Node<DataType>> back;

	void copy(const PullQueue<DataType> & original);
	void mv(PullQueue<DataType> && original);

public:
	PullQueue()
	{
		//PullQueue constructor
		front = nullptr;
		back = nullptr;
	}
	~PullQueue()
	{
		//destructor
		makeEmpty();
		front = nullptr;
		back = nullptr;
	}
	void enqueue(DataType & element);
	bool dequeue(DataType & element);
	bool peek(DataType & element);
	bool isEmpty();
	bool pull(DataType & item, DataType & pulled);
	void makeEmpty();
	PullQueue(const PullQueue<DataType> & ap)
	{
		//copy constructor
		copy(ap);
	}
	PullQueue<DataType> & operator =(const PullQueue<DataType> & right)
	{
		//copy assignment
		if (this == &right)
			return *this;
		makeEmpty();
		copy(right);
		return *this;
	}

	PullQueue(PullQueue<DataType> && ap)
	{
		//move constructor
		mv(move(ap));
	}

	PullQueue<DataType> & operator =(PullQueue<DataType> && right)
	{
		//move assignment
		if (this == &right)
			return *this;
		makeEmpty();
		mv(move(right));
		return *this;
	}
};

 template <class DataType>
void PullQueue<DataType>::enqueue(DataType & element)
{
	shared_ptr<Node<DataType>> newNode { new Node<DataType> };
	newNode->info = element;
	newNode->next = nullptr;
	if (back == nullptr)
	{
		//If nothing is in the PullQueue, then the newNode will become the front
		front = back = newNode;
	}
	else
	{
		//otherwise add it to end of PullQueue
		back->next = newNode;
		back = newNode;	 
	}

	//inserts element to end of PullQueue
}
 template <class DataType>
bool PullQueue<DataType>::dequeue(DataType & element)
{
	if (front == nullptr)
	{
		return false;
		//It cant remove anything if nothing is in PullQueue
	}
		element = front->info;	//saves the info of front before removal
		front = front->next;	//removes first node

		if (front == nullptr)
		{
			//used when dequeueing the last node
			back = nullptr;
		}
		
		return true;

}

 template <class DataType>
bool PullQueue<DataType>::peek(DataType & element)
 {
	//copies the first element in PullQueue
	if (front == nullptr)
	{
		return false;
	}
	element = front->info;
	return true;
 }

//Returns true if linked list is empty, otherwise returns false
 template <class DataType>
bool PullQueue<DataType>::isEmpty()
{
	if (front == nullptr)
	{
		return true;
	}
	return false;
}

//Pulls item from PullQueue if it meets the special condition
 template<class DataType>
bool PullQueue<DataType>::pull(DataType & item, DataType & pulled)
{
	if (front == nullptr)
	{
		return false;
	}
	shared_ptr<Node<DataType>> ptr( front );
	if (front != nullptr)
	{
		if (item == front->info)
		{
			//special case, for if its the first node
			pulled = front->info;
			front = front->next;	//pull item from queue
			if (front == nullptr)
			{
				back = front;
			}
			return true;
		}
	}
	for (; ptr->next != nullptr ; ptr = ptr->next)
	{
		if (item == ptr->next->info)
		{
			pulled = ptr->next->info;
			ptr->next = ptr->next->next;	//pull item from queue
			if (ptr->next == nullptr)
			{
				back = ptr;
			}
			return true;
		}
	}
	return false;
}

 template<class DataType>
 void PullQueue<DataType>::makeEmpty()
 {
	 //empties the Pull Queue
	 while (front != nullptr)
	 {
		 front = front->next;
	 }
	 back = nullptr;
 }

//makes copy of original
  template<class DataType>
  void PullQueue<DataType>::copy(const PullQueue<DataType> & original)
 {
	  //copy function
	  if (original.front == nullptr)
		  return;
	  shared_ptr<Node<DataType>> originalptr { original.front };
	  while (originalptr != nullptr)
	  {
		  enqueue(originalptr->info);
		  originalptr = originalptr->next;
	  }

 }

//moves the original
 template<class DataType>
 void PullQueue<DataType>::mv(PullQueue<DataType> && original)
 {
	 //move function
	 if (original.front == nullptr)
		 return;
	 shared_ptr<Node<DataType>> originalptr { original.front };
	 original.front = originalptr->next;
	 originalptr->next = nullptr;
	 front = move(originalptr);
	 shared_ptr<Node<DataType>> copyptr{ front };
	 while (original.front != nullptr)
	 {
		 originalptr = original.front;
		 original.front = originalptr->next;
		 originalptr->next = nullptr;
		 copyptr->next = move(originalptr);
		 copyptr = copyptr->next;
	 }
	 back = copyptr;
 }
