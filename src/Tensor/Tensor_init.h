#ifndef	ARSON_CLASS_TENSOR_INIT_H
#define ARSON_CLASS_TENSOR_INIT_H

#include "Arson/Tensor.h"

template <typename T, size_t Init_Dimension, size_t ... Dimensions>
Tensor<T, Init_Dimension, Dimensions...>::Tensor(std::initializer_list<T> tensor)
{
	assert("Too many elements given" && tensor.size() <= _size);
	std::copy(tensor.begin(), tensor.end(), _data);
}

template <typename T, size_t Init_Dimension, size_t ... Dimensions>
Tensor<T, Init_Dimension, Dimensions...>::Tensor(const Tensor& delta_tensor)
{
	delete[] _data;
	delete[] _all_dimensions;

	_data = new T[delta_tensor._size];
	_all_dimensions = new size_t[delta_tensor.DIMENSION_AMOUNT];
	DIMENSION_AMOUNT = delta_tensor.DIMENSION_AMOUNT;
	_size = delta_tensor._size;

	std::copy(delta_tensor._data, delta_tensor._data + _size, _data);
	std::copy(delta_tensor._all_dimensions, delta_tensor._all_dimensions + DIMENSION_AMOUNT, _all_dimensions);
}

template <typename T, size_t Init_Dimension, size_t ... Dimensions>
Tensor<T, Init_Dimension, Dimensions...>::Tensor(Tensor&& delta_tensor) noexcept
{
	delete[] _data;
	delete[] _all_dimensions;

	_data = delta_tensor._data;
	_all_dimensions = delta_tensor._all_dimensions;
	DIMENSION_AMOUNT = delta_tensor.DIMENSION_AMOUNT;
	_size = delta_tensor._size;

	delta_tensor._data = nullptr;
	delta_tensor._all_dimensions = nullptr;
}

template <typename T, size_t Init_Dimension, size_t ... Dimensions>
Tensor<T, Init_Dimension, Dimensions...>& Tensor<T, Init_Dimension, Dimensions...>
::operator=(const Tensor& delta_tensor)
{
	if (this != &delta_tensor)
	{
		delete[] _data;
		delete[] _all_dimensions;

		_data = new T[delta_tensor._size];
		_all_dimensions = new size_t[delta_tensor.DIMENSION_AMOUNT];
		DIMENSION_AMOUNT = delta_tensor.DIMENSION_AMOUNT;
		_size = delta_tensor._size;

		std::copy(delta_tensor._data, delta_tensor._data + _size, _data);
		std::copy(delta_tensor._all_dimensions, delta_tensor._all_dimensions + DIMENSION_AMOUNT, _all_dimensions);
	}
	return *this;
}

template <typename T, size_t Init_Dimension, size_t ... Dimensions>
Tensor<T, Init_Dimension, Dimensions...>& Tensor<T, Init_Dimension, Dimensions...>
::operator=(std::initializer_list<T> tensor)
{
	assert("Too many elements given" && tensor.size() <= _size);
	std::copy(tensor.begin(), tensor.end(), _data);
	return *this;
}

template <typename T, size_t Init_Dimension, size_t ... Dimensions>
Tensor<T, Init_Dimension, Dimensions...>& Tensor<T, Init_Dimension, Dimensions...>
::operator=(Tensor&& delta_tensor) noexcept
{
	delete[] _data;
	delete[] _all_dimensions;

	_data = delta_tensor._data;
	_all_dimensions = delta_tensor._all_dimensions;
	DIMENSION_AMOUNT = delta_tensor.DIMENSION_AMOUNT;
	_size = delta_tensor._size;

	delta_tensor._data = nullptr;
	delta_tensor._all_dimensions = nullptr;

	return *this;
}

template <typename T, size_t Init_Dimension, size_t ... Dimensions>
Tensor<T, Init_Dimension, Dimensions...>::~Tensor()
{
	delete[] _all_dimensions;
	delete[] _data;
}

#endif
