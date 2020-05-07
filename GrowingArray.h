#pragma once
namespace CommonUtilities
{
	template<typename ObjectType, typename SizeType = unsigned>
	class GrowingArray
	{
	public:
		GrowingArray();
		GrowingArray(SizeType aNrOfRecommendedItems, bool aUseSafeModeFlag = true);
		GrowingArray(SizeType aNumItems, const ObjectType* aItems, bool aIseSafeModeFlag = true);
		GrowingArray(const GrowingArray& aGrowingArray);
		GrowingArray(GrowingArray&& aGrowingArray);

		~GrowingArray();

		GrowingArray& operator=(const GrowingArray& aGrowingArray);
		GrowingArray& operator=(GrowingArray&& aGrowingArray);

		void Init(SizeType aNrOfRecomendedItems, bool aUseSafeModeFlag = true);
		void Init(SizeType aNumItems, const ObjectType* aItems, bool aUseSafeModeFlag = true);

		inline ObjectType& operator[](const SizeType& aIndex);
		inline const ObjectType& operator[](const SizeType& aIndex) const;

		inline void Add(const ObjectType& aObject);
		inline void Add(ObjectType&& aObject);
		inline void Add(const GrowingArray<ObjectType>& aOtherArray);
		inline void Add(const ObjectType* aObjects, SizeType aNumObjects);
		inline void AddUnique(const ObjectType& aObject);
		inline void AddUnique(ObjectType&& aObject);

		template <typename ... Args>
		inline void AddInplace(Args...aArgs);
		inline void Insert(SizeType aIndex, const ObjectType& aObject);
		inline void Insert(SizeType aIndex, const GrowingArray<ObjectType>& aOtherArray);
		inline void Swap(SizeType aIndex1, SizeType aIndex2);
		inline void DeleteCyclic(ObjectType& aObject);
		inline void DeleteCyclicAtIndex(SizeType aItemNumber);
		inline void DeleteAtIndex(SizeType aItemNumber);
		inline void DeletePreserveOrder(ObjectType& aObject);
		inline void RemoveCyclic(const ObjectType& aObject);
		inline void RemoveCyclicAtIndex(SizeType aItemNumber);
		inline void RemoveAtRange(SizeType aStartIndex, SizeType aEndIndex);
		inline void RemoveAtIndex(SizeType aItemNumber);
		inline void RemovePreserveOrder(const ObjectType& aObject);
		inline SizeType Find(const ObjectType& aObject) const;

		inline ObjectType& GetLast();
		inline const ObjectType& GetLast() const;
		inline void RemoveLast();
		inline void DeleteLast();
		inline SizeType GetLastIndex() const;

		typedef ObjectType* iterator;
		typedef const ObjectType* const_iterator;
		iterator begin() { return myData; }
		const_iterator begin() const { return myData; }
		iterator end() { return &(myData[mySize]); }
		const_iterator end() const { return &(myData[mySize]); }

		inline const bool Empty() const;


		static const SizeType FoundNone = static_cast<SizeType>(-1);

		inline void RemoveAll();
		__forceinline void DeleteAll();
		inline ObjectType* GetPureData() const;
		inline ObjectType* GetBuffer() const { return myData; }

		void Optimize();
		__forceinline SizeType Size() const;
		__forceinline SizeType Capacity() const;
		inline void Reserve(SizeType aNewSize);
		inline void Resize(SizeType aNewSize);

	private:
		SizeType mySize;
		SizeType myCapacity;
		ObjectType* myData;
		bool myUseSafeMode;
	};

	template<typename ObjectType, typename SizeType>
	inline GrowingArray<ObjectType, SizeType>::GrowingArray()
	{
		myData = nullptr;
		myCapacity = 0;
		mySize = 0;
		myUseSafeMode = true;
	}

	template<typename ObjectType, typename SizeType>
	inline GrowingArray<ObjectType, SizeType>::GrowingArray(SizeType aNrOfRecommendedItems, bool aUseSafeModeFlag)
	{
		myCapacity = aNrOfRecommendedItems;
		mySize = 0;
		myUseSafeMode = aUseSafeModeFlag;
		myData = (ObjectType*)malloc(sizeof(ObjectType) * myCapacity);
	}

	template<typename ObjectType, typename SizeType>
	GrowingArray<ObjectType, SizeType>::GrowingArray(SizeType aNumItems, const ObjectType* aItems, bool aIseSafeModeFlag /*= true*/)
	{
		Init(aNumItems, aItems, aIseSafeModeFlag);
	}

	template<typename ObjectType, typename SizeType>
	inline GrowingArray<ObjectType, SizeType>::GrowingArray(const GrowingArray& aGrowingArray)
	{
		myCapacity = aGrowingArray.myCapacity;
		mySize = aGrowingArray.mySize;
		myUseSafeMode = aGrowingArray.myUseSafeMode;
		myData = (ObjectType*)malloc(sizeof(ObjectType) * myCapacity);

		if (myUseSafeMode == true)
		{
			for (SizeType i = static_cast<SizeType>(0); i < mySize; ++i)
			{
				::new (&(myData[i])) ObjectType(aGrowingArray.myData[i]);
			}
		}
		else
		{
			std::memcpy(myData, aGrowingArray.myData, sizeof(ObjectType)*mySize);
		}
	}

	template<typename ObjectType, typename SizeType>
	inline GrowingArray<ObjectType, SizeType>::GrowingArray(GrowingArray&& aGrowingArray)
	{
		myData = aGrowingArray.myData;
		aGrowingArray.myData = nullptr;
		myCapacity = aGrowingArray.myCapacity;
		mySize = aGrowingArray.mySize;
		myUseSafeMode = aGrowingArray.myUseSafeMode;
	}

	template<typename ObjectType, typename SizeType>
	inline GrowingArray<ObjectType, SizeType>::~GrowingArray()
	{
		if (myData != nullptr)
		{
			for (SizeType i = 0; i < mySize; ++i)
			{
				myData[i].~ObjectType();
			}
			free(myData);
			myData = nullptr;
		}
		myCapacity = 0;
		mySize = 0;
	}

	template<typename ObjectType, typename SizeType>
	inline GrowingArray<ObjectType, SizeType>& GrowingArray<ObjectType, SizeType>::operator=(const GrowingArray& aGrowingArray)
	{
		if (myData != nullptr)
		{
			for (SizeType i = 0; i < mySize; ++i)
			{
				myData[i].~ObjectType();
			}
			free(myData);
			myData = nullptr;
		}

		myCapacity = aGrowingArray.myCapacity;
		mySize = aGrowingArray.mySize;
		myUseSafeMode = aGrowingArray.myUseSafeMode;
		myData = (ObjectType*)malloc(sizeof(ObjectType) * myCapacity);

		if (myUseSafeMode)
		{
			for (SizeType i = 0; i < mySize; ++i)
			{
				new (&(myData[i])) ObjectType(aGrowingArray.myData[i]);
			}
		}
		else
		{
			std::memcpy(myData, aGrowingArray.myData, sizeof(ObjectType)*mySize);
		}
		return *this;
	}

	template<typename ObjectType, typename SizeType>
	inline GrowingArray<ObjectType, SizeType>& GrowingArray<ObjectType, SizeType>::operator=(GrowingArray&& aGrowingArray)
	{
		if (myData)
		{
			for (SizeType i = 0; i < mySize; ++i)
			{
				myData[i].~ObjectType();
			}
			free(myData);
		}
		myData = aGrowingArray.myData;
		aGrowingArray.myData = nullptr;
		myCapacity = aGrowingArray.myCapacity;
		mySize = aGrowingArray.mySize;
		myUseSafeMode = aGrowingArray.myUseSafeMode;
		return *this;
	}


	template<typename ObjectType, typename SizeType>
	inline void GrowingArray<ObjectType, SizeType>::Init(SizeType aNrOfRecomendedItems, bool aUseSafeModeFlag)
	{
		ASSERT(myData == nullptr && "Cannot init growing array twice!");
		myUseSafeMode = aUseSafeModeFlag;
		myCapacity = aNrOfRecomendedItems;
		mySize = 0;
		myData = (ObjectType*)malloc(sizeof(ObjectType) * myCapacity);
	}

	template<typename ObjectType, typename SizeType>
	void GrowingArray<ObjectType, SizeType>::Init(SizeType aNumItems, const ObjectType* aItems, bool aUseSafeModeFlag)
	{
		ASSERT(myData == nullptr && "Cannot init growing array twice!");
		myUseSafeMode = aUseSafeModeFlag;
		myCapacity = aNumItems;
		mySize = aNumItems;
		myData = (ObjectType*)malloc(sizeof(ObjectType) * myCapacity);
		for (SizeType i = 0; i < mySize; ++i)
		{
			::new (&(myData[i])) ObjectType(aItems[i]);
		}
	}

	template<typename ObjectType, typename SizeType>
	inline ObjectType& GrowingArray<ObjectType, SizeType>::operator[](const SizeType& aIndex)
	{
		ASSERT(myData != nullptr && "Tried to access index in uninitialized GrowingArray!");
		ASSERT(aIndex >= 0 && aIndex < mySize && "Tried to access index out of bounds!");
		return myData[aIndex];
	}

	template<typename ObjectType, typename SizeType>
	inline const ObjectType& GrowingArray<ObjectType, SizeType>::operator[](const SizeType& aIndex) const
	{
		ASSERT(myData != nullptr && "Tried to use uninitialized GrowingArray!");
		ASSERT(aIndex >= 0 && aIndex < mySize && "Tried to access index out of bounds!");
		return myData[aIndex];
	}

	template<typename ObjectType, typename SizeType>
	inline void GrowingArray<ObjectType, SizeType>::Add(const ObjectType& aObject)
	{
		ASSERT(myData != nullptr && "Tried to use uninitialized GrowingArray!");
		if (mySize == myCapacity)
		{
			//WARNING_LOG("Growing array grew!");
			Reserve(myCapacity * 2);
		}
		::new (&(myData[mySize])) ObjectType(aObject);
		mySize++;
	}

	template<typename ObjectType, typename SizeType>
	inline void GrowingArray<ObjectType, SizeType>::Add(ObjectType&& aObject)
	{
		ASSERT(myData != nullptr && "Tried to use uninitialized GrowingArray!");
		if (mySize == myCapacity)
		{
			//WARNING_LOG("Growing array grew!");
			Reserve(myCapacity * 2);
		}
		::new (&(myData[mySize])) ObjectType(std::move(aObject));
		mySize++;
	}

	template<typename ObjectType, typename SizeType>
	inline void GrowingArray<ObjectType, SizeType>::Add(const GrowingArray<ObjectType>& aOtherArray)
	{
		for (const ObjectType & obj : aOtherArray)
		{
			Add(obj);
		}
	}

	template<typename ObjectType, typename SizeType>
	void CommonUtilities::GrowingArray<ObjectType, SizeType>::Add(const ObjectType* aObjects, SizeType aNumObjects)
	{
		for (uint i = 0; i < aNumObjects; ++i)
		{
			Add(aObjects[i]);
		}
	}

	template<typename ObjectType, typename SizeType>
	inline void GrowingArray<ObjectType, SizeType>::AddUnique(const ObjectType& aObject)
	{
		if (Find(aObject) == FoundNone)
		{
			Add(aObject);
		}
	}

	template<typename ObjectType, typename SizeType>
	inline void GrowingArray<ObjectType, SizeType>::AddUnique(ObjectType&& aObject)
	{
		if (Find(aObject) == FoundNone)
		{
			Add(aObject);
		}
	}

	template<typename ObjectType, typename SizeType>
	inline void GrowingArray<ObjectType, SizeType>::Insert(SizeType aIndex, const ObjectType& aObject)
	{
		ASSERT(myData != nullptr && "Tried to use uninitialized GrowingArray!");
		ASSERT(aIndex <= mySize && "Invalid index!");
		if (mySize == myCapacity)
		{
			Reserve(myCapacity * 2);
		}
		if (aIndex != mySize)
		{
			for (SizeType i = mySize; i > aIndex; i--)
			{
				::new (&(myData[i])) ObjectType(std::move(myData[i - 1]));
			}
			myData[aIndex].~ObjectType();
		}
		::new (&(myData[aIndex])) ObjectType(aObject);
		mySize++;
	}

	template<typename ObjectType, typename SizeType /*= unsigned*/>
	void CommonUtilities::GrowingArray<ObjectType, SizeType>::Insert(SizeType aIndex, const GrowingArray<ObjectType>& aOtherArray)
	{
		for (SizeType i = 0; i < aOtherArray.Size(); ++i)
		{
			Insert(aIndex + i, aOtherArray[i]);
		}
	}

	template<typename ObjectType, typename SizeType>
	inline void GrowingArray<ObjectType, SizeType>::Swap(SizeType aIndex1, SizeType aIndex2)
	{
		ASSERT(aIndex1 >= 0 && aIndex1 < mySize && "Tried to access index out of bounds!");
		ASSERT(aIndex2 >= 0 && aIndex2 < mySize && "Tried to access index out of bounds!");
		ObjectType tempStorage = myData[aIndex1];
		myData[aIndex1] = myData[aIndex2];
		myData[aIndex2] = tempStorage;
	}

	template<typename ObjectType, typename SizeType>
	inline void GrowingArray<ObjectType, SizeType>::DeleteCyclic(ObjectType& aObject)
	{
		ASSERT(myData != nullptr && "Tried to use uninitialized GrowingArray!");
		for (SizeType i = 0; i < mySize; i++)
		{
			if (myData[i] == aObject)
			{
				delete myData[i];
				myData[i] = myData[mySize - 1];
				mySize--;
			}
		}
	}

	template<typename ObjectType, typename SizeType>
	inline void GrowingArray<ObjectType, SizeType>::DeleteCyclicAtIndex(SizeType aItemNumber)
	{
		ASSERT(myData != nullptr && "Tried to use uninitialized GrowingArray!");
		delete myData[aItemNumber];
		myData[aItemNumber] = nullptr;
		myData[aItemNumber] = myData[mySize - 1];
		mySize--;
	}

	template<typename ObjectType, typename SizeType>
	inline void GrowingArray<ObjectType, SizeType>::DeleteAtIndex(SizeType aItemNumber)
	{
		ASSERT(myData != nullptr && "GrowingArray is not initialized yet.");
		ASSERT(aItemNumber >= static_cast<SizeType>(0) && aItemNumber < mySize && "Index out of bounds");
		delete myData[aItemNumber];
		myData[aItemNumber] = nullptr;
		for (SizeType i = aItemNumber; i < Size() - 1; ++i)
		{
			myData[i] = myData[i + 1];
		}
		--mySize;
	}

	template<typename ObjectType, typename SizeType /*= unsigned*/>
	void CommonUtilities::GrowingArray<ObjectType, SizeType>::DeletePreserveOrder(ObjectType& aObject)
	{
		SizeType index = Find(aObject);
		if (index != FoundNone)
		{
			DeleteAtIndex(index);
		}
	}

	template<typename ObjectType, typename SizeType>
	inline void GrowingArray<ObjectType, SizeType>::RemoveCyclic(const ObjectType& aObject)
	{
		ASSERT(myData != nullptr && "Tried to use uninitialized GrowingArray!");
		for (SizeType i = 0; i < mySize; i++)
		{
			if (myData[i] == aObject)
			{
				myData[i] = myData[mySize - 1];
				mySize--;
			}
		}
	}

	template<typename ObjectType, typename SizeType>
	inline void GrowingArray<ObjectType, SizeType>::RemoveCyclicAtIndex(SizeType aItemNumber)
	{
		ASSERT(myData != nullptr && "Tried to use uninitialized GrowingArray!");
		myData[aItemNumber] = myData[mySize - 1];
		mySize--;
	}

	template<typename ObjectType, typename SizeType>
	inline void GrowingArray<ObjectType, SizeType>::RemoveAtRange(SizeType aStartIndex, SizeType aEndIndex)
	{
		ASSERT(myData != nullptr && "Tried to access index in uninitialized GrowingArray!");
		ASSERT(aStartIndex >= 0 && aStartIndex < mySize && "Tried to access index out of bounds!");
		ASSERT(aEndIndex >= 0 && aEndIndex < mySize && "Tried to access index out of bounds!");
		ASSERT(aStartIndex <= aEndIndex && "Invalid range specified!");

		SizeType rangeSize = (aEndIndex + 1) - aStartIndex;
		SizeType distToEnd = mySize - (aEndIndex + 1);
		mySize -= rangeSize;
		memcpy(&myData[aStartIndex], &myData[aEndIndex + 1], distToEnd * sizeof(ObjectType));
	}

	template<typename ObjectType, typename SizeType>
	inline void GrowingArray<ObjectType, SizeType>::RemoveAtIndex(SizeType aItemNumber)
	{
		ASSERT(myData != nullptr && "GrowingArray is not initialized yet.");
		ASSERT(aItemNumber >= static_cast<SizeType>(0) && aItemNumber < mySize && "Index out of bounds");
		for (SizeType i = aItemNumber; i < Size() - 1; ++i)
		{
			myData[i] = myData[i + 1];
		}
		--mySize;
	}

	template<typename ObjectType, typename SizeType>
	inline void GrowingArray<ObjectType, SizeType>::RemovePreserveOrder(const ObjectType& aObject)
	{
		SizeType index = Find(aObject);
		if (index != FoundNone)
		{
			RemoveAtIndex(index);
		}
	}

	template<typename ObjectType, typename SizeType>
	inline SizeType GrowingArray<ObjectType, SizeType>::Find(const ObjectType& aObject) const
	{
		for (SizeType i = 0; i < mySize; i++)
		{
			if (aObject == myData[i])
			{
				return i;
			}
		}
		return FoundNone;
	}

	template<typename ObjectType, typename SizeType>
	inline ObjectType& GrowingArray<ObjectType, SizeType>::GetLast()
	{
		ASSERT(myData != nullptr && "Tried to use uninitialized GrowingArray!");
		return myData[mySize - 1];
	}

	template<typename ObjectType, typename SizeType>
	inline const ObjectType & GrowingArray<ObjectType, SizeType>::GetLast() const
	{
		ASSERT(myData != nullptr && "Tried to use uninitialized GrowingArray!");
		return myData[mySize - 1];
	}

	template<typename ObjectType, typename SizeType>
	inline void GrowingArray<ObjectType, SizeType>::RemoveLast()
	{
		ASSERT(myData != nullptr && "Tried to use uninitialized GrowingArray!");
		if (mySize > 0)
		{
			mySize--;
		}
	}

	template<typename ObjectType, typename SizeType>
	inline void GrowingArray<ObjectType, SizeType>::DeleteLast()
	{
		ASSERT(myData != nullptr && "Tried to use uninitialized GrowingArray!");
		if (mySize > 0)
		{
			mySize--;
			delete myData[mySize];
			myData[mySize] = nullptr;
		}
	}

	template<typename ObjectType, typename SizeType>
	SizeType GrowingArray<ObjectType, SizeType>::GetLastIndex() const
	{
		return mySize - 1;
	}

	template<typename ObjectType, typename SizeType>
	inline const bool GrowingArray<ObjectType, SizeType>::Empty() const
	{
		return mySize == 0;
	}

	template<typename ObjectType, typename SizeType>
	inline void GrowingArray<ObjectType, SizeType>::RemoveAll()
	{
		for (SizeType i = 0; i < mySize; i++)
		{
			myData[i].~ObjectType();
		}
		mySize = 0;
	}

	template<typename ObjectType, typename SizeType>
	__forceinline void GrowingArray<ObjectType, SizeType>::DeleteAll()
	{
		if (myData != nullptr)
		{
			for (SizeType i = 0; i < mySize; i++)
			{
				delete myData[i];
				myData[i] = nullptr;
			}
		}
		mySize = 0;
	}

	template<typename ObjectType, typename SizeType>
	inline ObjectType * GrowingArray<ObjectType, SizeType>::GetPureData() const
	{
		return myData;
	}

	template<typename ObjectType, typename SizeType>
	inline void GrowingArray<ObjectType, SizeType>::Optimize()
	{
		if (mySize < myCapacity)
		{
			myCapacity = mySize;

			if (myCapacity <= 0)
			{
				free(myData);
				myData = nullptr;
				return;
			}

			ObjectType* optimizedData = nullptr;
			if (myCapacity > 0)
			{
				optimizedData = (ObjectType*)malloc(sizeof(ObjectType) * myCapacity);
				if (myUseSafeMode)
				{
					for (SizeType i = 0; i < mySize; ++i)
					{
						::new (&(optimizedData[i])) ObjectType(std::move(myData[i]));
					}
				}
				else
				{
					std::memcpy(optimizedData, myData, sizeof(ObjectType)*mySize);
				}
			}
			free(myData);
			myData = optimizedData;
		}
	}

	template<typename ObjectType, typename SizeType>
	inline SizeType GrowingArray<ObjectType, SizeType>::Size() const
	{
		return mySize;
	}

	template<typename ObjectType, typename SizeType>
	inline SizeType GrowingArray<ObjectType, SizeType>::Capacity() const
	{
		return myCapacity;
	}

	template<typename ObjectType, typename SizeType>
	inline void GrowingArray<ObjectType, SizeType>::Reserve(SizeType aNewCapacity)
	{
		if (aNewCapacity > myCapacity)
		{
			myCapacity = aNewCapacity;

			ObjectType* newData = (ObjectType*)malloc(sizeof(ObjectType) * myCapacity);

			if (myUseSafeMode)
			{
				for (SizeType i = 0; i < mySize; ++i)
				{
					::new (&(newData[i])) ObjectType(std::move(myData[i]));
				}
			}
			else
			{
				std::memcpy(newData, myData, sizeof(ObjectType)*mySize);
			}
			free(myData);
			myData = newData;
		}
	}

	template<typename ObjectType, typename SizeType>
	inline void GrowingArray<ObjectType, SizeType>::Resize(SizeType aNewSize)
	{
		if (aNewSize > mySize)
		{
			if (aNewSize > myCapacity)
			{
				Reserve(aNewSize);
			}
			for (SizeType i = mySize; i < aNewSize; ++i)
			{
				::new (&(myData[i])) ObjectType();
			}
		}
		else
		{
			SizeType sizeDif = mySize - aNewSize;
			for (SizeType index = 0; index < sizeDif; ++index)
			{
				myData[(mySize - 1)- index].~ObjectType();
			}
		}
		mySize = aNewSize;
	}
	template<typename ObjectType, typename SizeType>
	template<typename ...Args>
	inline void GrowingArray<ObjectType, SizeType>::AddInplace(Args ...aArgs)
	{
		ASSERT(myData != nullptr && "Tried to use uninitialized GrowingArray!");
		if (mySize == myCapacity)
		{
			//WARNING_LOG("Growing array grew!");
			Reserve(myCapacity * 2);
		}
		::new (&(myData[mySize])) ObjectType(aArgs...);
		mySize++;

	}
}

namespace CU = CommonUtilities;