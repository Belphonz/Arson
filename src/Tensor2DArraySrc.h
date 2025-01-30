#ifndef	ARSON_CLASS_TENSOR_2D_ARRAY_SRC_H
#define ARSON_CLASS_TENSOR_2D_ARRAY_SRC_H

#include <Arson/Structure/Tensor2DArray.h>

template<typename T, size_t SIZE_X, size_t SIZE_Y>
T& Arn::Tensor2DArray<T, SIZE_X, SIZE_Y>::operator[](Vector2<size_t> indexes)
{
	// Calculation to find the index : x + max_x * y
	return Data[indexes.x + indexes.y * SIZE_X];
}

template<typename T, size_t SIZE_X, size_t SIZE_Y>
T& Arn::Tensor2DArray<T, SIZE_X, SIZE_Y>::At(Vector2<size_t> indexes)
{
	//Secure Checker
	assert("Outside the size of the Width" && indexes.x < SIZE_X);
	assert("Outside the size of the Height" && indexes.y < SIZE_Y);

	// Calculation to find the index : x + max_x * y
	return Data[indexes.x + indexes.y * SIZE_X];
}

template<typename T, size_t SIZE_X, size_t SIZE_Y>
size_t Arn::Tensor2DArray<T, SIZE_X, SIZE_Y>::MaxSize() const
{
	return SIZE_X * SIZE_Y;
}

template<typename T, size_t SIZE_X, size_t SIZE_Y>
bool Arn::Tensor2DArray<T, SIZE_X, SIZE_Y>::Empty()
{
	return Data == Data + (SIZE_X * SIZE_Y);
}

template<typename T, size_t SIZE_X, size_t SIZE_Y>
T* Arn::Tensor2DArray<T, SIZE_X, SIZE_Y>::Begin()
{
	return Data;
}

template<typename T, size_t SIZE_X, size_t SIZE_Y>
inline T* Arn::Tensor2DArray<T, SIZE_X, SIZE_Y>::End()
{
	return Data + (SIZE_X * SIZE_Y);
}

template<typename T, size_t SIZE_X, size_t SIZE_Y>
void Arn::Tensor2DArray<T, SIZE_X, SIZE_Y>::Fill(const T& value)
{
	std::fill(Data, Data + (SIZE_X * SIZE_Y), value);
}

#endif