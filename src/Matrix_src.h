#ifndef	ARSON_CLASS_MATRIX_SRC_H
#define ARSON_CLASS_MATRIX_SRC_H

#include <cassert>

template <typename T, size_t Init_Dimension, size_t ... Dimensions>
size_t Matrix<T, Init_Dimension, Dimensions...>::array_size() const
{
	size_t total{1};
	for (size_t index{0}; index < _dimension_amount; ++index)
	{
		total *= _all_dimensions[index];
	}
	return total;
}

template <typename T, size_t Init_Dimension, size_t ... Dimensions>
Matrix<T, Init_Dimension, Dimensions...>::Matrix(std::initializer_list<T> matrix)
{
	assert("Too many elements given" && matrix.size() <= _size);
	std::copy(matrix.begin(), matrix.end(), _data);
}

template <typename T, size_t Init_Dimension, size_t ... Dimensions>
Matrix<T, Init_Dimension, Dimensions...>::Matrix(const Matrix& delta_matrix)
{
	delete [] _data;
	delete [] _all_dimensions;

	_data = new T[delta_matrix._size];
	_all_dimensions = new size_t[delta_matrix._dimension_amount];
	_dimension_amount = delta_matrix._dimension_amount;
	_size = delta_matrix._size;

	std::copy(delta_matrix._data, delta_matrix._data + _size, _data);
	std::copy(delta_matrix._all_dimensions, delta_matrix._all_dimensions + _dimension_amount, _all_dimensions);
}

template <typename T, size_t Init_Dimension, size_t ... Dimensions>
Matrix<T, Init_Dimension, Dimensions...>::Matrix(Matrix&& delta_matrix) noexcept
{
	delete [] _data;
	delete [] _all_dimensions;

	_data = delta_matrix._data;
	_all_dimensions = delta_matrix._all_dimensions;
	_dimension_amount = delta_matrix._dimension_amount;
	_size = delta_matrix._size;

	delta_matrix._data = nullptr;
	delta_matrix._all_dimensions = nullptr;
}

template <typename T, size_t Init_Dimension, size_t ... Dimensions>
Matrix<T, Init_Dimension, Dimensions...>& Matrix<T, Init_Dimension, Dimensions...>
::operator=(const Matrix& delta_matrix)
{
	if (this != &delta_matrix)
	{
		delete [] _data;
		delete [] _all_dimensions;

		_data = new T[delta_matrix._size];
		_all_dimensions = new size_t[delta_matrix._dimension_amount];
		_dimension_amount = delta_matrix._dimension_amount;
		_size = delta_matrix._size;

		std::copy(delta_matrix._data, delta_matrix._data + _size, _data);
		std::copy(delta_matrix._all_dimensions, delta_matrix._all_dimensions + _dimension_amount, _all_dimensions);
	}
	return *this;
}

template <typename T, size_t Init_Dimension, size_t ... Dimensions>
Matrix<T, Init_Dimension, Dimensions...>& Matrix<T, Init_Dimension, Dimensions...>::operator=(
	std::initializer_list<T> matrix)
{
	assert("Too many elements given" && matrix.size() <= _size);
	std::copy(matrix.begin(), matrix.end(), _data);
	return *this;
}

template <typename T, size_t Init_Dimension, size_t ... Dimensions>
Matrix<T, Init_Dimension, Dimensions...>& Matrix<T, Init_Dimension, Dimensions...>
::operator=(Matrix&& delta_matrix) noexcept
{
	
	delete [] _data;
	delete [] _all_dimensions;

	_data = delta_matrix._data;
	_all_dimensions = delta_matrix._all_dimensions;
	_dimension_amount = delta_matrix._dimension_amount;
	_size = delta_matrix._size;

	delta_matrix._data = nullptr;
	delta_matrix._all_dimensions = nullptr;

	return *this;
}

template <typename T, size_t Init_Dimension, size_t ... Dimensions>
Matrix<T, Init_Dimension, Dimensions...>::~Matrix()
{
	delete [] _all_dimensions;
	delete [] _data;
}

template <typename T, size_t Init_Dimension, size_t ... Dimensions>
template <size_t Index, size_t ... Sup_Index>
T& Matrix<T, Init_Dimension, Dimensions...>::at()
{
	assert("Incorrect ammount of elements given" && sizeof...(Sup_Index) + 1 == _dimension_amount);

	const size_t* all_indexes{new size_t[_dimension_amount]{Index, Sup_Index...}};
	size_t total{0};

	//Calculation : x + max_x * y + max_x * max_y * z ...

	for (size_t index{0}; index < _dimension_amount; ++index)
	{
		size_t current_index{all_indexes[index]};
		for (size_t dimension{1}; dimension < index + 1; ++dimension)
		{
			current_index *= _all_dimensions[dimension - 1];
		}
		total += current_index;
	}
	return _data[total];
}

template <typename T, size_t Init_Dimension, size_t ... Dimensions>
template <size_t Index, size_t ... Sup_Index>
T& Matrix<T, Init_Dimension, Dimensions...>::secure_at()
{
	assert("Incorrect ammount of elements given" && sizeof...(Sup_Index) + 1 == _dimension_amount);

	const size_t* all_indexes{new size_t[_dimension_amount]{Index, Sup_Index...}};

	//Throws an error if the index is outside dimension length
	bool checker{true};
	for (size_t index{0}; index < _dimension_amount; ++index)
	{
		if (all_indexes[index] <= _all_dimensions[index])
		{
			checker = false;
		}
	}
	assert("Outside the length of a dimension" && checker);

	size_t total{0};

	//Calculation : x + max_x * y + max_x * max_y * z ...

	for (size_t index{0}; index < _dimension_amount; ++index)
	{
		size_t current_index{all_indexes[index]};
		for (size_t dimension{1}; dimension < index + 1; ++dimension)
		{
			current_index *= _all_dimensions[dimension - 1];
		}
		total += current_index;
	}
	return _data[total];
}
#endif
