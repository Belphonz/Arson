#ifndef	ARSON_CLASS_TENSOR_2D_VECTOR_INIT_H
#define ARSON_CLASS_TENSOR_2D_VECTOR_INIT_H

#include "Arson/Structure/Tensor2DVector.h"

template <typename T>
Tensor2DVector<T>::Tensor2DVector(const Vector2<size_t> dimensions, const bool force_static)
{
	_data = new T[dimensions.x * dimensions.y];
	_dimensions = dimensions;
	_capacity = dimensions.x * dimensions.y;
	FORCE_STATIC = force_static;

	std::fill(_data, _data + dimensions.x * dimensions.y, 0);
}

template <typename T>
Tensor2DVector<T>::Tensor2DVector(const Vector2<size_t> dimensions, std::initializer_list<T> tensor, const bool force_static)
{
	assert("Too many elements given" && tensor.size() <= dimensions.x * dimensions.y);

	_data = new T[dimensions.x * dimensions.y];
	_dimensions = dimensions;
	_capacity = dimensions.x * dimensions.y;
	FORCE_STATIC = force_static;

	std::copy(tensor.begin(), tensor.end(), _data);
	std::fill(_data + tensor.size(), _data + dimensions.x * dimensions.y, 0);
}

template <typename T>
Tensor2DVector<T>::Tensor2DVector(const Tensor2DVector& delta_tensor)
{
	delete[] _data;

	_data = new T[delta_tensor._capacity];
	_dimensions = delta_tensor._dimensions;
	_capacity = delta_tensor._capacity;
	FORCE_STATIC = delta_tensor.FORCE_STATIC;

	std::copy(delta_tensor._data, delta_tensor._data + delta_tensor._capacity, _data);
}

template <typename T>
Tensor2DVector<T>::Tensor2DVector(Tensor2DVector&& delta_tensor) noexcept
{
	delete[] _data;

	_data = delta_tensor._data;
	_dimensions = delta_tensor._dimensions;
	FORCE_STATIC = delta_tensor.FORCE_STATIC;
	_capacity = delta_tensor._capacity;

	delta_tensor._data = nullptr;
}

template <typename T>
Tensor2DVector<T>::~Tensor2DVector()
{
	delete[] _data;
}

template <typename T>
Tensor2DVector<T>& Tensor2DVector<T>::operator=(const Tensor2DVector& delta_tensor)
{
	if (this != &delta_tensor)
	{
		delete[] _data;

		_data = new T[delta_tensor._capacity];
		_dimensions = delta_tensor._dimensions;
		_capacity = delta_tensor._capacity;
		FORCE_STATIC = delta_tensor.FORCE_STATIC;

		std::copy(delta_tensor._data, delta_tensor._data + delta_tensor._capacity, _data);
	}
	return *this;
}

template <typename T>
Tensor2DVector<T>& Tensor2DVector<T>::operator=(std::initializer_list<T> tensor)
{
	assert("Too many elements given" && tensor.size() <= _dimensions.x * _dimensions.y);
	std::copy(tensor.begin(), tensor.end(), _data);
	std::fill(_data + tensor.size(), _data + _dimensions.x * _dimensions.y, 0);
	return *this;
}

template <typename T>
Tensor2DVector<T>& Tensor2DVector<T>::operator=(Tensor2DVector&& delta_tensor) noexcept
{
	delete[] _data;

	_data = delta_tensor._data;
	_dimensions = delta_tensor._dimensions;
	_capacity = delta_tensor._capacity;
	FORCE_STATIC = delta_tensor.FORCE_STATIC;

	delta_tensor._data = nullptr;

	return *this;
}

#endif
