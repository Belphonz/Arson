#ifndef	ARSON_CLASS_COLLECTION_ALLOCATOR_SRC_H
#define ARSON_CLASS_COLLECTION_ALLOCATOR_SRC_H 

#include <cassert>
#include <iostream>
#include "Arson/Structure/CollectionAllocator.h"

template<typename T, typename STACK_MAX_SIZE>
Arn::CollectionAllocator<T, STACK_MAX_SIZE>::CollectionAllocator(T* start, STACK_MAX_SIZE collectionSize)
{
	_stack = new STACK_MAX_SIZE[collectionSize]{};
	_begin = start;
	_collectionSize = collectionSize;

	STACK_MAX_SIZE value{ collectionSize };
	for (STACK_MAX_SIZE* first{ _stack }; first != _stack + collectionSize; ++first)
		*first = --value;

	_head = collectionSize - 1;

}

template<typename T, typename STACK_MAX_SIZE>
Arn::CollectionAllocator<T, STACK_MAX_SIZE>::~CollectionAllocator()
{
	delete[] _stack;
}

template<typename T, typename STACK_MAX_SIZE>
T* Arn::CollectionAllocator<T, STACK_MAX_SIZE>::Allocate()
{
	//Secure Check
	assert("Can't Allocate Anymore" && pow(2, 8 * sizeof(STACK_MAX_SIZE)) - 2 != static_cast<Arn::wideByte>(_head - 1));
	return _begin + _stack[_head--];
}

template<typename T, typename STACK_MAX_SIZE>
void Arn::CollectionAllocator<T, STACK_MAX_SIZE>::Deallocate(T* object)
{
	//Secure Check
	assert("Can't Deallocate Anymore" && _head != _collectionSize); 
	_stack[++_head] = pow(2, 8 * sizeof(STACK_MAX_SIZE)) - 2;
	if (_head == 0 || _stack[_head] < object - _begin)
	{
		_stack[_head] = object - _begin;
	}
	else 
	{
		_stack[_head] = _stack[_head-1];
		_stack[_head-1]	= object - _begin;
	}
}

#endif