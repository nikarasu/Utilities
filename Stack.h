#pragma once
#include <cassert>

namespace CommonUtilities
{
	template <class T>
	class Stack
	{
	public:
		//Create empty stack
		Stack();
		~Stack();

		//Returns element amount in stack
		int GetSize() const;

		//Returns top element in stack. Crashes with assert if stack is empty.
		const T &GetTop() const;

		//Returns top element in stack. Crashes with assert if stack is empty.
		T &GetTop();

		//Adds new element on top of stack
		void Push(const T &aValue);

		//Removes top element from stack and removes it. Crashes with assert if stack is empty.
		T Pop();

		void Clear();

	private:
		int myCapacity;
		int mySize;

		T* myData;
	};
	template<class T>
	inline Stack<T>::Stack()
	{
		mySize = 0;
		myCapacity = 32;
		myData = new T[myCapacity];
	}
	template<class T>
	inline Stack<T>::~Stack()
	{
		delete[] myData;
	}
	template<class T>
	inline int Stack<T>::GetSize() const
	{
		return mySize;
	}
	template<class T>
	inline const T & Stack<T>::GetTop() const
	{
		assert(mySize > 0 && "Can't get top from empty stack!");
		return myData[mySize - 1];
	}

	template<class T>
	inline T & Stack<T>::GetTop()
	{
		assert(mySize > 0 && "Can't get top from empty stack!");
		return myData[mySize - 1];
	}

	template<class T>
	inline void Stack<T>::Push(const T & aValue)
	{
		if (mySize == myCapacity)
		{
			myCapacity *= 2;
			T* newData = new T[myCapacity];
			for (int index = 0; index < mySize; ++index)
			{
				newData[index] = myData[index];
			}
			delete[] myData;
			myData = newData;
		}
		myData[mySize++] = aValue;
	}

	template<class T>
	inline T Stack<T>::Pop()
	{
		assert(mySize > 0 && "Can't pop from empty stack!");
		return myData[--mySize];
	}
	template<class T>
	inline void Stack<T>::Clear()
	{
		mySize = 0;
	}
}

namespace CU = CommonUtilities;