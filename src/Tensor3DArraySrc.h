#ifndef	ARSON_CLASS_TENSOR_3D_ARRAY_SRC_H
#define ARSON_CLASS_TENSOR_3D_ARRAY_SRC_H

#include "Arson/Structure/Tensor3DArray.h"

template<typename T, size_t SIZE_X, size_t SIZE_Y, size_t SIZE_Z>
T& Arn::Tensor3DArray<T, SIZE_X, SIZE_Y, SIZE_Z>::operator[](Vector3<size_t> indexes)
{
	// Calculation to find the index : x + (max_x * y) + (max_y * max_x * z)
	return Data[indexes.x + (indexes.y * SIZE_X) + (indexes.z * SIZE_X * SIZE_Y)];
}

template<typename T, size_t SIZE_X, size_t SIZE_Y, size_t SIZE_Z>
T& Arn::Tensor3DArray<T, SIZE_X, SIZE_Y, SIZE_Z>::At(Vector3<size_t> indexes)
{
	//Secure Checker
	assert("Outside the size of the Width" && indexes.x < SIZE_X);
	assert("Outside the size of the Height" && indexes.y < SIZE_Y);
	assert("Outside the size of the Depth" && indexes.z < SIZE_Z);

	// Calculation to find the index : x + (max_x * y) + (max_y * max_x * z)
	return Data[indexes.x + (indexes.y * SIZE_X) + (indexes.z * SIZE_X * SIZE_Y)];
}

template<typename T, size_t SIZE_X, size_t SIZE_Y, size_t SIZE_Z>
size_t Arn::Tensor3DArray<T, SIZE_X, SIZE_Y, SIZE_Z>::MaxSize() const
{
	return SIZE_X * SIZE_Y * SIZE_Z;
}

template<typename T, size_t SIZE_X, size_t SIZE_Y, size_t SIZE_Z>
bool Arn::Tensor3DArray<T, SIZE_X, SIZE_Y, SIZE_Z>::Empty()
{
	return Data == Data + (SIZE_X * SIZE_Y * SIZE_Z);
}

template<typename T, size_t SIZE_X, size_t SIZE_Y, size_t SIZE_Z>
T* Arn::Tensor3DArray<T, SIZE_X, SIZE_Y, SIZE_Z>::Begin()
{
	return Data;
}

template<typename T, size_t SIZE_X, size_t SIZE_Y, size_t SIZE_Z>
inline T* Arn::Tensor3DArray<T, SIZE_X, SIZE_Y, SIZE_Z>::End()
{
	return Data + (SIZE_X * SIZE_Y * SIZE_Z);
}

template<typename T, size_t SIZE_X, size_t SIZE_Y, size_t SIZE_Z>
void Arn::Tensor3DArray<T, SIZE_X, SIZE_Y, SIZE_Z>::Fill(const T& value)
{
	std::fill(Data, Data + (SIZE_X * SIZE_Y * SIZE_Z), value);
}

#endif