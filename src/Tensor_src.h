#ifndef	ARSON_CLASS_TENSOR_SRC_H
#define ARSON_CLASS_TENSOR_SRC_H

#include <cassert>
#include "Arson/Tensor.h"

template <typename T, size_t Init_Dimension, size_t ... Dimensions>
size_t Tensor<T, Init_Dimension, Dimensions...>::array_size()
{
	size_t total{1};
	for (size_t index{0}; index < DIMENSION_AMOUNT; ++index)
	{
		total *= _all_dimensions[index];
	}
	return total;
}

template <typename T, size_t Init_Dimension, size_t ... Dimensions>
T& Tensor<T, Init_Dimension, Dimensions...>::operator[](const std::initializer_list<size_t> indexes)
{
	assert("Incorrect ammount of elements given" && indexes.size() == DIMENSION_AMOUNT);

	size_t* all_indexes{new size_t[DIMENSION_AMOUNT]{}};
	std::copy(indexes.begin(), indexes.end(), all_indexes);
	size_t total{0};

	//Calculation : x + max_x * y + max_x * max_y * z ...

	for (size_t index{0}; index < DIMENSION_AMOUNT; ++index)
	{
		size_t current_index{all_indexes[index]};
		for (size_t dimension{1}; dimension < index + 1; ++dimension)
		{
			current_index *= _all_dimensions[dimension - 1];
		}
		total += current_index;
	}
	delete[] all_indexes; 
	return _data[total];
}

template <typename T, size_t Init_Dimension, size_t ... Dimensions>
T& Tensor<T, Init_Dimension, Dimensions...>::at(const std::initializer_list<size_t> indexes)
{
	assert("Incorrect ammount of elements given" && indexes.size() == DIMENSION_AMOUNT);


	size_t* all_indexes{new size_t[DIMENSION_AMOUNT]{}};
	std::copy(indexes.begin(), indexes.end(), all_indexes);
	size_t total{0};


	//Throws an error if the index is outside dimension length
	bool checker{true};
	for (size_t index{0}; index < DIMENSION_AMOUNT; ++index)
	{
		if (all_indexes[index] >= _all_dimensions[index])
		{
			checker = false;
			break;
		}
	}
	assert("Outside the length of a dimension" && checker);

	//Calculation : x + max_x * y + max_x * max_y * z ...

	for (size_t index{0}; index < DIMENSION_AMOUNT; ++index)
	{
		size_t current_index{all_indexes[index]};
		for (size_t dimension{1}; dimension < index + 1; ++dimension)
		{
			current_index *= _all_dimensions[dimension - 1];
		}
		total += current_index;
	}
	delete[] all_indexes; 
	return _data[total];
}

template <typename T, size_t Init_Dimension, size_t ... Dimensions>
template <size_t Dimension>
size_t Tensor<T, Init_Dimension, Dimensions...>::size()
{
	return _all_dimensions[Dimension - 1];
}

template <typename T, size_t Init_Dimension, size_t ... Dimensions>
T* Tensor<T, Init_Dimension, Dimensions...>::data()
{
	return _data;
}


template <typename T, size_t Init_Dimension, size_t ... Dimensions>
size_t Tensor<T, Init_Dimension, Dimensions...>::size(size_t dimension)
{
	return _all_dimensions[dimension - 1];
}

template <typename T, size_t Init_Dimension, size_t ... Dimensions>
size_t Tensor<T, Init_Dimension, Dimensions...>::max_size() const
{
	return _size;
}

template <typename T, size_t Init_Dimension, size_t ... Dimensions>
bool Tensor<T, Init_Dimension, Dimensions...>::empty()
{
	return _data == _data + _size;
}

template <typename T, size_t Init_Dimension, size_t ... Dimensions>
T* Tensor<T, Init_Dimension, Dimensions...>::begin()
{
	return _data;
}

template <typename T, size_t Init_Dimension, size_t ... Dimensions>
T* Tensor<T, Init_Dimension, Dimensions...>::end()
{
	return _data + _size + 1;
}

template <typename T, size_t Init_Dimension, size_t ... Dimensions>
void Tensor<T, Init_Dimension, Dimensions...>::fill(const T& value)
{
	std::fill(_data, _data + _size, value);
}


#endif
