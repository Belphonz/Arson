#ifndef	ARSON_CLASS_COLLECTION_ALLOCATOR_H
#define ARSON_CLASS_COLLECTION_ALLOCATOR_H

#include "../Common/Style.h"

namespace Arn
{
	template <typename T, typename STACK_MAX_SIZE = Arn::wideByte>
	class CollectionAllocator
	{
	private:
		T* _begin{};
		STACK_MAX_SIZE* _stack{};
		STACK_MAX_SIZE _head{};
		STACK_MAX_SIZE _collectionSize{};

	public:
		//Constructor
		CollectionAllocator(T* start,STACK_MAX_SIZE collectionSize);
		//Destructor
		~CollectionAllocator();
		//Returns a Pointer to the Closest available memory in a Collection
		T* Allocate();
		//Adds an element to the stack for future allocation
		void Deallocate(T* object);
		
	};

#include "../src/CollectionAllocator_src.h"
}

#endif

