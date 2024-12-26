#ifndef	ARSON_CLASS_TENSOR_2D_VECTOR_INIT_H
#define ARSON_CLASS_TENSOR_2D_VECTOR_INIT_H

#include <cassert>
#include "Arson/Structure/Tensor2DVector.h"

template <typename T>
Arn::Tensor2DVector<T>::Tensor2DVector(const Vector2<size_t> dimensions, const bool forceStatic)
{
	_capacity = dimensions.x * dimensions.y;
	_data = new T[_capacity];
	_dimensions = dimensions;
	_forceStatic = forceStatic;

	std::fill(_data, _data + _capacity, 0);
}

template <typename T>
Arn::Tensor2DVector<T>::Tensor2DVector(const Vector2<size_t> dimensions, std::initializer_list<T> data, const bool forceStatic)
{
	assert("Too many elements given" && data.size() <= dimensions.x * dimensions.y);

	_capacity = dimensions.x * dimensions.y;
	_data = new T[_capacity];
	_dimensions = dimensions;
	_forceStatic = forceStatic;

	std::copy(data.begin(), data.end(), _data);
	std::fill(_data + data.size(), _data + _capacity, 0);
}

template <typename T>
Arn::Tensor2DVector<T>::Tensor2DVector(const Tensor2DVector& other)
{
	delete[] _data;

	_data = new T[other._capacity];
	_dimensions = other._dimensions;
	_capacity = other._capacity;
	_forceStatic = other._forceStatic;

	std::copy(other._data, other._data + other._capacity, _data);
}

template <typename T>
Arn::Tensor2DVector<T>::Tensor2DVector(Tensor2DVector&& other) noexcept
{
	delete[] _data;

	_data = other._data;
	_dimensions = other._dimensions;
	_forceStatic = other._forceStatic;
	_capacity = other._capacity;

	other._data = nullptr;
}

template <typename T>
Arn::Tensor2DVector<T>::~Tensor2DVector()
{
	delete[] _data;
}

template <typename T>
Arn::Tensor2DVector<T>& Arn::Tensor2DVector<T>::operator=(const Tensor2DVector& other)
{
	if (this != &other)
	{
		delete[] _data;

		_data = new T[other._capacity];
		_dimensions = other._dimensions;
		_capacity = other._capacity;
		_forceStatic = other._forceStatic;

		std::copy(other._data, other._data + other._capacity, _data);
	}
	return *this;
}

template <typename T>
Arn::Tensor2DVector<T>& Arn::Tensor2DVector<T>::operator=(std::initializer_list<T> data)
{
	assert("Too many elements given" && data.size() <= _dimensions.x * _dimensions.y);
	std::copy(data.begin(), data.end(), _data);
	std::fill(_data + data.size(), _data + _dimensions.x * _dimensions.y, 0);
	return *this;
}

template <typename T>
Arn::Tensor2DVector<T>& Arn::Tensor2DVector<T>::operator=(Tensor2DVector&& other) noexcept
{
	delete[] _data;

	_data = other._data;
	_dimensions = other._dimensions;
	_capacity = other._capacity;
	_forceStatic = other._forceStatic;

	other._data = nullptr;

	return *this;
}

#endif