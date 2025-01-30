#ifndef	ARSON_CLASS_TENSOR_2D_VECTOR_SRC_H
#define ARSON_CLASS_TENSOR_2D_VECTOR_SRC_H

#include <cassert>
#include <Arson/Structure/Tensor2DVector.h>


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

template <typename T>
T& Arn::Tensor2DVector<T>::operator[](const Vector2<size_t> indexes)
{
	// Calculation to find the index : x + max_x * y
	return _data[indexes.x + indexes.y * _dimensions.x];
}

template <typename T>
T& Arn::Tensor2DVector<T>::At(const Vector2<size_t> indexes)
{
	//Secure Checker
	assert("Outside the size of the Width" && indexes.x < _dimensions.x);
	assert("Outside the size of the Height" && indexes.y < _dimensions.y);

	// Calculation to find the index : x + max_x * y
	return _data[indexes.y * _dimensions.x + indexes.x];
}

template <typename T>
void Arn::Tensor2DVector<T>::Resize(const Vector2<size_t> newDimensions)
{
	if (_forceStatic) { return; }

	Reserve(newDimensions.x * newDimensions.y);

	const size_t shiftAmount{ newDimensions.y <= _dimensions.y ? newDimensions.y : _dimensions.y };
	//If the new width is smaller or equal to the old one
	if (_dimensions.x >= newDimensions.x)
	{
		size_t leftCurrentPos{ newDimensions.x };
		//It squashes the values outside the new width by copying the next widths into their position
		for (size_t i{ 0 }; i < shiftAmount; ++i)
		{
			size_t getPos{ (i + 1) * _dimensions.x };
			std::copy(_data + getPos, _data + getPos + newDimensions.x, _data + leftCurrentPos);
			leftCurrentPos += newDimensions.x;
		}
	}
	//If the new width is bigger than the old one
	else
	{
		size_t totalShift{ 0 };
		const size_t shift{ newDimensions.x - _dimensions.x };

		//It moves the widths of the old array to make space for the new spaces which are opened up
		for (size_t i{ 0 }; i < shiftAmount; ++i)
		{
			size_t getPos{ (i + 1) * _dimensions.x + totalShift };
			std::copy(_data + getPos, _data + _capacity, _data + getPos + shift);
			totalShift += shift;
		}

		//Sets the Values of the new opened up spaces to 0
		for (size_t j{ 0 }; j < _dimensions.y; ++j)
		{
			for (size_t i{ 0 }; i < newDimensions.x; ++i)
			{
				if (i >= _dimensions.x) { _data[i + j * newDimensions.x] = T{}; }
			}
		}
	}

	_dimensions = newDimensions;
}

template <typename T>
T* Arn::Tensor2DVector<T>::Data()
{
	return _data;
}

template <typename T>
void Arn::Tensor2DVector<T>::Reserve(const size_t newAlloc)
{
	if (newAlloc < _capacity) { return; }

	T* temp{ new T[newAlloc] };
	std::copy(_data, _data + _capacity, temp);
	delete[] _data;
	_data = temp;
	std::fill(_data + _capacity, _data + newAlloc, T{});
	_capacity = newAlloc;
}

template <typename T>
void Arn::Tensor2DVector<T>::ShrinkToFit()
{
	if (_capacity < _dimensions.x * _dimensions.y) { return; }

	T* temp{ new T[_dimensions.x * _dimensions.y] };
	std::copy(_data, _data + _dimensions.x * _dimensions.y, temp);
	delete[] _data;
	_data = temp;
	_capacity = _dimensions.x * _dimensions.y;
}

template <typename T>
Arn::Vector2<size_t> Arn::Tensor2DVector<T>::Dimensions() const
{
	return _dimensions;
}

template <typename T>
size_t Arn::Tensor2DVector<T>::Width() const
{
	return _dimensions.x;
}

template <typename T>
size_t Arn::Tensor2DVector<T>::Height() const
{
	return _dimensions.y;
}

template <typename T>
size_t Arn::Tensor2DVector<T>::MaxSize() const
{
	return _dimensions.x * _dimensions.y;
}

template <typename T>
size_t Arn::Tensor2DVector<T>::Capacity() const
{
	return _capacity;
}

template <typename T>
bool Arn::Tensor2DVector<T>::Empty()
{
	return _data == _data + _capacity;
}

template <typename T>
T* Arn::Tensor2DVector<T>::Begin()
{
	return _data;
}

template <typename T>
T* Arn::Tensor2DVector<T>::End()
{
	return _data + _capacity + 1;
}

template <typename T>
void Arn::Tensor2DVector<T>::Fill(const T& value)
{
	std::fill(_data, _data + _dimensions.x * _dimensions.y, value);
}

#endif
