#pragma once
#include "Stack.h"
namespace CommonUtilities
{
	/*
			NODE
	*/
	template<class T>
	class BSTSet;

	template <class T>
	class BSTSetNode
	{
	public:
		~BSTSetNode();
		BSTSetNode(const BSTSetNode &) = delete;
		BSTSetNode &operator=(const BSTSetNode &) = delete;

		const T &GetData() const;
		const BSTSetNode<T> *GetLeft() const;
		const BSTSetNode<T> *GetRight() const;

	private:
		void ReplaceWith(BSTSetNode<T>* aNode);
		void SetConnectedNodeLinksTo(BSTSetNode<T>* aNode);
		BSTSetNode<T>() {}
		friend class BSTSet<T>;
		T myData;
		BSTSetNode* myLeft = nullptr;
		BSTSetNode* myRight = nullptr;
	};

	template<class T>
	inline BSTSetNode<T>::~BSTSetNode()
	{
		delete myLeft;
		delete myRight;
		myLeft = nullptr;
		myRight = nullptr;
	}

	template<class T>
	inline const T & BSTSetNode<T>::GetData() const
	{
		return myData;
	}

	template<class T>
	inline const BSTSetNode<T>* BSTSetNode<T>::GetLeft() const
	{
		return myLeft;
	}

	template<class T>
	inline const BSTSetNode<T>* BSTSetNode<T>::GetRight() const
	{
		return myRight;
	}

	template<class T>
 	inline void BSTSetNode<T>::ReplaceWith(BSTSetNode<T>*aNode)
 	{
		SetConnectedNodeLinksTo(aNode);
		if (aNode != nullptr)
		{
			aNode->SetConnectedNodeLinksTo(this);
		}
 
		BSTSetNode<T> * myOldLeft = myLeft;
		BSTSetNode<T> * myOldRight = myRight;
 		myLeft = aNode->myLeft;
 		myRight = aNode->myRight;
		aNode->myLeft = myOldLeft;
		aNode->myRight = myOldRight;
 	}

	template<class T>
	inline void BSTSetNode<T>::SetConnectedNodeLinksTo(BSTSetNode<T>* aNode)
	{
		if (myRight != nullptr)
		{
			myRight->myParent = aNode;
		}
		if (myLeft != nullptr)
		{
			myLeft->myParent = aNode;
		}
		if (myParent != nullptr)
		{
			if (myParent->myLeft == this)
			{
				myParent->myLeft = aNode;
			}
			else
			{
				myParent->myRight = aNode;
			}
		}
	}

	/*
			SET
	*/
	template <class T>
	class BSTSet
	{
	public:
		BSTSet();
		~BSTSet();

		const BSTSetNode<T> *GetRoot() const;
		bool HasElement(const T &aData) const;
		void Insert(const T &aData);
		void Remove(const T &aData);
		void DSWBalance();
		int Count() const;
		int GetDepth();
		int GetWidth(int aDepth);
		void GetSetList(T * aListPtr) const;

	private:
		void AddToList(const BSTSetNode<T>* aNode, T* aListPtr, unsigned & aIndex) const;
		int Count(const BSTSetNode<T>*aNode) const;
		void Compact(int aN);
		void BalanceBackbone(int aN);
		void RotateRight(BSTSetNode<T>* aNode);
		void RotateLeft(BSTSetNode<T>* aNode);
		BSTSetNode<T>* Find(const T& aData, BSTSetNode<T>* aNode);

		BSTSetNode<T>* GetParent(BSTSetNode<T>* aNode);
		BSTSetNode<T>* GetParent(BSTSetNode<T>* aNode, BSTSetNode<T>* aSearchNode);
		const BSTSetNode<T>* GetParent(const BSTSetNode<T>* aNode) const;
		const BSTSetNode<T>* GetParent(const BSTSetNode<T>* aNode, const BSTSetNode<T>* aSearchNode) const;

		void Insert(const T& aData, BSTSetNode<T>*& aNode);
		void Remove(BSTSetNode<T>* aNode);
		bool HasElement(const T & aData, const BSTSetNode<T>* aNode) const;
		int GetWidth(BSTSetNode<T>* aNode, int aDepth) const;
		int GetDepth(BSTSetNode<T>* aNode);

		BSTSetNode<T>* GetMin(BSTSetNode<T>* aNode);
		BSTSetNode<T>* GetMax(BSTSetNode<T>* aNode);
		BSTSetNode<T>* myRoot;
	};

	template<class T>
	inline BSTSet<T>::BSTSet()
	{
		myRoot = nullptr;
	}

	template<class T>
	inline BSTSet<T>::~BSTSet()
	{
		delete myRoot;
		myRoot = nullptr;
	}
	 
	template<class T>
	inline const BSTSetNode<T> * BSTSet<T>::GetRoot() const
	{
		return myRoot;
	}

	template<class T>
	inline bool BSTSet<T>::HasElement(const T & aData) const
	{
		return HasElement(aData, myRoot);
	}
	 
	template<class T>
	inline void BSTSet<T>::Insert(const T & aData)
	{
		Insert(aData, myRoot);
	}

	template<class T>
	inline void BSTSet<T>::Remove(const T & aData)
	{
		Remove(Find(aData, myRoot));
	}

	template<class T>
	inline void BSTSet<T>::DSWBalance()
	{
		BSTSetNode<T>* targetNode = myRoot;
		while (targetNode != nullptr)
		{
			while (targetNode->myLeft != nullptr)
			{
				RotateRight(targetNode);
				BSTSetNode<T>* parent = GetParent(targetNode);
				if (parent != nullptr)
				{
					targetNode = parent;
				}
			}
			targetNode = targetNode->myRight;
		}
		BalanceBackbone(Count());
	}

	template<class T>
	inline int BSTSet<T>::Count() const
	{
		return Count(myRoot);
	}

	template<class T>
	inline int BSTSet<T>::GetDepth()
	{
		return GetDepth(myRoot);
	}

	template<class T>
	inline int BSTSet<T>::GetWidth(int aDepth)
	{
		return GetWidth(myRoot, aDepth);
	}

	template<class T>
	inline void BSTSet<T>::GetSetList(T * aListPtr) const
	{
		unsigned index = 0;
		AddToList(myRoot, aListPtr, index);
	}

	template<class T>
	inline void BSTSet<T>::AddToList(const BSTSetNode<T>* aNode, T * aListPtr, unsigned & aIndex) const
	{
		if (aNode != nullptr)
		{
			aListPtr[aIndex] = aNode->myData;
			aIndex++;
			AddToList(aNode->myLeft, aListPtr, aIndex);
			AddToList(aNode->myRight, aListPtr, aIndex);
		}
	}

	template<class T>
	inline int BSTSet<T>::Count(const BSTSetNode<T>* aNode) const
	{
		if (aNode == nullptr)
		{
			return 0;
		}
		int count = 1;
		if (aNode->myLeft != nullptr)
		{
			count += Count(aNode->myLeft);
		}
		if (aNode->myRight != nullptr)
		{
			count += Count(aNode->myRight);
		}
		return count;
	}

	template<class T>
	inline void BSTSet<T>::Compact(int aN)
	{
		BSTSetNode<T>* targetNode = myRoot;
		for (int i = 0; i < aN; ++i)
		{
			if (targetNode == nullptr)
			{
				break;
			}
			RotateLeft(targetNode);
			targetNode = GetParent(targetNode)->myRight;
		}
	}

	template<class T>
	inline void BSTSet<T>::BalanceBackbone(int aN)
	{
		int leaves = aN + 1 - static_cast<int>(std::pow(2, std::floor(std::log2(aN + 1))));
		Compact(leaves);
		aN -= leaves;
		while (aN > 1)
		{
			Compact(aN);
			aN /= 2;
		}
	}

	template<class T>
	inline void BSTSet<T>::RotateRight(BSTSetNode<T>* aNode)
	{
 		if (aNode != nullptr)
 		{
			BSTSetNode<T>* nodeParent = GetParent(aNode);
 			BSTSetNode<T>* pivot = aNode->myLeft;
 			if (pivot != nullptr)
 			{
 				aNode->myLeft = pivot->myRight;
 				pivot->myRight = aNode;
 				if (nodeParent != nullptr)
 				{
 					if (nodeParent->myLeft == aNode)
 					{
						nodeParent->myLeft = pivot;
 					}
 					else
 					{
						nodeParent->myRight = pivot;
 					}
 				}
 				else
 				{
 					myRoot = pivot;
 				}
 			}
 		}
	}

	template<class T>
	inline void BSTSet<T>::RotateLeft(BSTSetNode<T>* aNode)
	{
		if (aNode != nullptr)
		{
			BSTSetNode<T>* nodeParent = GetParent(aNode);
			BSTSetNode<T>* pivot = aNode->myRight;
			if (pivot != nullptr)
			{
				aNode->myRight = pivot->myLeft;
				pivot->myLeft = aNode;
				if (nodeParent != nullptr)
				{
					if (nodeParent->myLeft == aNode)
					{
						nodeParent->myLeft = pivot;
						return;
					}
					else if (nodeParent->myRight == aNode)
					{
						nodeParent->myRight = pivot;
						return;
					}
					else
					{

					}
				}
				else
				{
					myRoot = pivot;
				}
			}
		}
	}

	template<class T>
	inline BSTSetNode<T>* BSTSet<T>::Find(const T & aData, BSTSetNode<T>* aNode)
	{
		if (aNode == nullptr)
		{
			return nullptr;
		}
		else if (aData < aNode->myData)
		{
			return Find(aData, aNode->myLeft);
		}
		else if (aNode->myData < aData)
		{
			return Find(aData, aNode->myRight);
		}
		else return aNode;
	}
	template<class T>
	inline BSTSetNode<T>* BSTSet<T>::GetParent(BSTSetNode<T>* aNode)
	{
		return GetParent(aNode, myRoot);
	}

	template<class T>
	inline BSTSetNode<T>* BSTSet<T>::GetParent(BSTSetNode<T>* aNode, BSTSetNode<T>* aSearchNode)
	{
		if (aSearchNode != nullptr)
		{
			if (aSearchNode->myLeft == aNode)
			{
				return aSearchNode;
			}
			else if (aSearchNode->myRight == aNode)
			{
				return aSearchNode;
			}
			else
			{
				BSTSetNode<T>* leftSearch = GetParent(aNode, aSearchNode->myLeft);
				BSTSetNode<T>* rightSearch = GetParent(aNode, aSearchNode->myRight);
				if (leftSearch != nullptr)
				{
					return leftSearch;
				}
				else if (rightSearch != nullptr)
				{
					return rightSearch;
				}
				else return nullptr;
			}
		}
		return nullptr;
	}

	template<class T>
	inline const BSTSetNode<T>* BSTSet<T>::GetParent(const BSTSetNode<T>* aNode) const
	{
		return GetParent(aNode, myRoot);
	}

	template<class T>
	inline const BSTSetNode<T>* BSTSet<T>::GetParent(const BSTSetNode<T>* aNode, const BSTSetNode<T>* aSearchNode) const
	{
		if (aSearchNode != nullptr)
		{
			if (aSearchNode->myLeft == aNode)
			{
				return aSearchNode;
			}
			else if (aSearchNode->myRight == aNode)
			{
				return aSearchNode;
			}
			else
			{
				BSTSetNode<T>* leftSearch = GetParent(aNode, aSearchNode->myLeft);
				BSTSetNode<T>* rightSearch = GetParent(aNode, aSearchNode->myRight);
				if (leftSearch != nullptr)
				{
					return leftSearch;
				}
				else if (rightSearch != nullptr)
				{
					return rightSearch;
				}
				else return nullptr;
			}
		}
		return nullptr;
	}

	template<class T>
	inline void BSTSet<T>::Insert(const T & aData, BSTSetNode<T>*& aNode)
	{
		if (aNode == nullptr)
		{
			aNode = new BSTSetNode<T>();
			aNode->myData = aData;
		}
		else if (aData < aNode->myData)
		{
			Insert(aData, aNode->myLeft);
		}
		else if (aNode->myData < aData)
		{
			Insert(aData, aNode->myRight);
		}
		else return; //Duplicate, no insertion
	}

	template<class T>
	inline void BSTSet<T>::Remove(BSTSetNode<T>* aNode)
	{
		if (aNode != nullptr)
		{
			BSTSetNode<T>* nodeParent = const_cast<BSTSetNode<T>*>(GetParent(aNode));
			BSTSetNode<T>** parentLink = &myRoot;
			if (nodeParent != nullptr)
			{
				//Get parent link, else root
				if (nodeParent->myLeft == aNode)
				{
					parentLink = &nodeParent->myLeft;
				}
				else
				{
					parentLink = &nodeParent->myRight;
				}
			}

			//No children
			if (aNode->myLeft == nullptr && aNode->myRight == nullptr)
			{
				//Set link in parent to null
				*parentLink = nullptr;
			}
			else if (aNode->myLeft != nullptr && aNode->myRight != nullptr)
			{
				//Find rightmost in left sub-tree
				BSTSetNode<T>* rightmost = aNode->myLeft;
				BSTSetNode<T>** rightmostParentLink = &aNode->myLeft;
				while (rightmost->myRight != nullptr)
				{
					rightmostParentLink = &rightmost->myRight;
					rightmost = rightmost->myRight;
				}
				*parentLink = rightmost;
				*rightmostParentLink = rightmost->myLeft;
				rightmost->myLeft = aNode->myLeft;
				rightmost->myRight = aNode->myRight;
			}
			else //Single child
			{
				//Set link in parent to child
				if (aNode->myLeft != nullptr)
				{
					*parentLink = aNode->myLeft;
				}
				else
				{
					*parentLink = aNode->myRight;
				}
			}
			aNode->myLeft = nullptr;
			aNode->myRight = nullptr;
			delete aNode;
		}
	}
 
 	template<class T>
 	inline bool BSTSet<T>::HasElement(const T & aData, const BSTSetNode<T>* aNode) const
 	{
 		if (aNode == nullptr)
 		{
 			return false;
 		}
 		else if (aData < aNode->myData)
 		{
 			return HasElement(aData, aNode->myLeft);
 		}
 		else if (aNode->myData < aData)
 		{
 			return HasElement(aData, aNode->myRight);
 		}
 		else return true;
 	}

	template<class T>
	inline int BSTSet<T>::GetWidth(BSTSetNode<T>* aNode, int aDepth) const
	{
		if (aNode != nullptr)
		{
			if (aDepth == 0)
			{
				return 1;
			}
			else
			{
				return (GetWidth(aNode->myLeft, aDepth - 1) + GetWidth(aNode->myRight, aDepth - 1));
			}
		}
		else
		{
			return 0;
		}
	}

	template<class T>
	inline int BSTSet<T>::GetDepth(BSTSetNode<T>* aNode)
	{
		if (aNode != nullptr)
		{
			int leftDepth = GetDepth(aNode->myLeft);
			int rightDepth = GetDepth(aNode->myRight);
			if (leftDepth >= rightDepth)
			{
				return 1 + leftDepth;
			}
			else return 1 + rightDepth;
		}
		return 0;
	}

	template<class T>
	inline BSTSetNode<T>* BSTSet<T>::GetMin(BSTSetNode<T>* aNode)
	{
		if (aNode != nullptr)
		{
			while (aNode->myLeft != nullptr)
			{
				aNode = aNode->myLeft;
			}
		}
		else return nullptr;
	}

	template<class T>
	inline BSTSetNode<T>* BSTSet<T>::GetMax(BSTSetNode<T>* aNode)
	{
		if (aNode != nullptr)
		{
			while (aNode->myRight != nullptr)
			{
				aNode = aNode->myRight;
			}
		}
		else return nullptr;
	}
}