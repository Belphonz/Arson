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

	const size_t shift_amount{new_dimensions.y <= _dimensions.y ? new_dimensions.y : _dimensions.y};
	//If the new width is smaller or equal to the old one
	if (_dimensions.x >= new_dimensions.x)
	{
		size_t left_current_pos{new_dimensions.x};
		//It squashes the values outside the new width by copying the next widths into their position 
		for (size_t index{0}; index < shift_amount; ++index)
		{
			size_t get_position{(index + 1) * _dimensions.x};
			std::copy(_data + get_position, _data + get_position + new_dimensions.x, _data + left_current_pos);
			left_current_pos += new_dimensions.x;
		}
	}
	//If the new width is bigger than the old one
	else if (_dimensions.x < new_dimensions.x)
	{																										
		size_t total_shift{0};
		const size_t shift{new_dimensions.x - _dimensions.x};

		//It moves the widths of the old array to make space for the new spaces which are opened up
		for (size_t index{0}; index < shift_amount; ++index)
		{
			size_t get_position{(index + 1) * _dimensions.x + total_shift};
			std::copy(_data + get_position, _data + _capacity, _data + get_position + shift);
			total_shift += shift;
		}

		//Sets the Values of the new opened up spaces to 0
		for (size_t delta_index{0}; delta_index < _dimensions.y; ++delta_index)
		{
			for (size_t index{0}; index < new_dimensions.x; ++index)
			{
				if (index >= _dimensions.x)
				{
					_data[index + delta_index * new_dimensions.x] = 0;
				}
			}
		}
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
		std::fill(_data + _capacity, _data + new_alloc, 0);
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
