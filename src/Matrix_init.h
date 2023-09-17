#ifndef	ARSON_CLASS_MATRIX_INIT_H
#define ARSON_CLASS_MATRIX_INIT_H

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

#endif
