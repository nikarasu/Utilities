#pragma once
#include "GrowingArray.h"

namespace CommonUtilities
{
	template <class T>
	class Heap
	{
	public:
		Heap();
		~Heap();
		int GetSize() const; //Returns element amount in heap
		void Enqueue(const T &aElement); //Adds element to heap
		const T &GetTop() const; //Returns largest element in heap
		T Dequeue(); //Returns largest element and removesit from the heap
		GrowingArray<T> & GetArray();

	private:
		GrowingArray<T> myArray;

		void BubbleUp(int aIndex);
		void BubbleDown(int aIndex);
	};

	template<class T>
	inline Heap<T>::Heap()
	{
		myArray.Init(4);
	}

	template<class T>
	inline Heap<T>::~Heap()
	{
		myArray.RemoveAll();
	}

	template<class T>
	inline int Heap<T>::GetSize() const
	{
		return myArray.Size();
	}

	template<class T>
	inline void Heap<T>::Enqueue(const T & aElement)
	{
		myArray.Add(aElement);
		BubbleUp(myArray.Size() - 1);
	}

	template<class T>
	inline const T & Heap<T>::GetTop() const
	{
		return myArray[0];
	}

	template<class T>
	inline T Heap<T>::Dequeue()
	{
		T top = myArray[0];
		myArray.RemoveCyclicAtIndex(0);
		BubbleDown(0);
		return top;
	}

	template<class T>
	inline GrowingArray<T>& Heap<T>::GetArray()
	{
		return myArray;
	}

	template<class T>
	inline void Heap<T>::BubbleUp(int aIndex)
	{
		if (aIndex > 0 && aIndex <= myArray.Size() - 1)
		{
			int parentIndex = (aIndex - 1) / 2;
			int mine = myArray[aIndex];
			int parents = myArray[parentIndex];
			if (myArray[parentIndex] < myArray[aIndex])
			{
				T temp = myArray[parentIndex];
				myArray[parentIndex] = myArray[aIndex];
				myArray[aIndex] = temp;
				BubbleUp(parentIndex);
			}
		}
	}

	template<class T>
	inline void Heap<T>::BubbleDown(int aIndex)
	{
		if (aIndex >= 0 && aIndex < myArray.Size() - 1)
		{
			int leftIndex = aIndex * 2 + 1;
			int rightIndex = aIndex * 2 + 2;
			
			if (leftIndex < myArray.Size())
			{
				if (rightIndex < myArray.Size() && myArray[leftIndex] < myArray[rightIndex] && myArray[aIndex] < myArray[rightIndex])
				{
					T temp = myArray[rightIndex];
					myArray[rightIndex] = myArray[aIndex];
					myArray[aIndex] = temp;
					BubbleDown(rightIndex);
				}
				else if (myArray[aIndex] < myArray[leftIndex])
				{
					T temp = myArray[leftIndex];
					myArray[leftIndex] = myArray[aIndex];
					myArray[aIndex] = temp;
					BubbleDown(leftIndex);
				}
			}
		}
	}

}