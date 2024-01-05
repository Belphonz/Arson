#ifndef	ARSON_CLASS_TENSOR_2D_ARRAY_SRC_H
#define ARSON_CLASS_TENSOR_2D_ARRAY_SRC_H

#include "Arson/Structure/Tensor2DArray.h"

template<typename T, size_t SIZE_X, size_t SIZE_Y>
T& Arn::Tensor2DArray<T, SIZE_X, SIZE_Y>::operator[](Vector2<size_t> indexes)
{
	// Calculation to find the index : x + max_x * y
	return _data[indexes.x + indexes.y * SIZE_X];
}

template<typename T, size_t SIZE_X, size_t SIZE_Y>
T& Arn::Tensor2DArray<T, SIZE_X, SIZE_Y>::at(Vector2<size_t> indexes)
{
	//Secure Checker
	assert("Outside the size of the Width" && indexes.x < SIZE_X);
	assert("Outside the size of the Height" && indexes.y < SIZE_Y);

	// Calculation to find the index : x + max_x * y
	return _data[indexes.x + indexes.y * SIZE_X];
}

template<typename T, size_t SIZE_X, size_t SIZE_Y>
size_t Arn::Tensor2DArray<T, SIZE_X, SIZE_Y>::max_size() const
{
	return SIZE_X * SIZE_Y;
}

template<typename T, size_t SIZE_X, size_t SIZE_Y>
bool Arn::Tensor2DArray<T, SIZE_X, SIZE_Y>::empty()
{
	return _data == _data + _capacity;
}

template<typename T, size_t SIZE_X, size_t SIZE_Y>
T* Arn::Tensor2DArray<T, SIZE_X, SIZE_Y>::begin()
{
	return _data;
}

template<typename T, size_t SIZE_X, size_t SIZE_Y>
inline T* Arn::Tensor2DArray<T, SIZE_X, SIZE_Y>::end()
{
	return _data + (SIZE_X * SIZE_Y);
}

template<typename T, size_t SIZE_X, size_t SIZE_Y>
void Arn::Tensor2DArray<T, SIZE_X, SIZE_Y>::fill(const T& value)
{
	std::fill(_data, _data + (SIZE_X * SIZE_Y), value);
}

#endif