#ifndef	ARSON_CLASS_TENSOR_2D_SRC_H
#define ARSON_CLASS_TENSOR_2D_SRC_H

template <typename T>
T& Tensor2D<T>::operator[](const Vector2<size_t> indexes)
{
	// Calculation to find the index : x + max_x * y
	return _data[indexes.x + indexes.y * _dimensions.x];
}

template <typename T>
T& Tensor2D<T>::at(const Vector2<size_t> indexes)
{
	//Secure Checker
	assert("Outside the size of the Width" && indexes.x < _dimensions.x);
	assert("Outside the size of the Height" && indexes.y < _dimensions.y);

	// Calculation to find the index : x + max_x * y
	return _data[indexes.y * _dimensions.x + indexes.x];
}

template <typename T>
void Tensor2D<T>::resize(const Vector2<size_t> new_dimensions)
{
	if (FORCE_STATIC) { return; }
	if (new_dimensions.x * new_dimensions.y > _capacity)
	{
		reserve(new_dimensions.x * new_dimensions.y);
	}

	_dimensions = new_dimensions;
}

template <typename T>
T* Tensor2D<T>::data()
{
	return _data;
}

template <typename T>
void Tensor2D<T>::reserve(const size_t new_alloc)
{
	if (new_alloc > _capacity)
	{
		T* temp{new T[new_alloc]};
		std::copy(_data, _data + _capacity, temp);
		delete [] _data;
		_data = temp;
		_capacity = new_alloc;
	}
}

template <typename T>
void Tensor2D<T>::shrink_to_fit()
{
	if (_capacity > _dimensions.x * _dimensions.y)
	{
		T* temp{new T[_dimensions.x * _dimensions.y]};
		std::copy(_data, _data + _dimensions.x * _dimensions.y, temp);
		delete [] _data;
		_data = temp;
		_capacity = _dimensions.x * _dimensions.y;
	}
}

template <typename T>
Vector2<size_t> Tensor2D<T>::dimensions() const
{
	return _dimensions;
}

template <typename T>
size_t Tensor2D<T>::width() const
{
	return _dimensions.x;
}

template <typename T>
size_t Tensor2D<T>::height() const
{
	return _dimensions.y;
}

template <typename T>
size_t Tensor2D<T>::max_size() const
{
	return _dimensions.x * _dimensions.y;
}

template <typename T>
size_t Tensor2D<T>::capacity() const
{
	return _capacity;
}

template <typename T>
bool Tensor2D<T>::empty()
{
	return _data == _data + _capacity;
}

template <typename T>
T* Tensor2D<T>::begin()
{
	return _data;
}

template <typename T>
T* Tensor2D<T>::end()
{
	return _data + _capacity + 1;
}

template <typename T>
void Tensor2D<T>::fill(const T& value)
{
	std::fill(_data, _data + _dimensions.x * _dimensions.y, value);
}

#endif
