#ifndef	ARSON_CLASS_TENSOR_3D_VECTOR_SRC_H
#define ARSON_CLASS_TENSOR_3D_VECTOR_SRC_H

#include <cassert>
#include <Arson/Structure/Tensor3DVector.h>

template <typename T>
Arn::Tensor3DVector<T>::Tensor3DVector(const Vector3<size_t> dimensions, const bool forceStatic)
{
	_capacity = dimensions.x * dimensions.y * dimensions.z;
	_data = new T[_capacity]{};
	_dimensions = dimensions;
	_forceStatic = forceStatic;
}

template <typename T>
Arn::Tensor3DVector<T>::Tensor3DVector(const Vector3<size_t> dimensions, std::initializer_list<T> data, const bool forceStatic)
{
	assert("Too many elements given" && data.size() <= dimensions.x * dimensions.y * dimensions.z);

	_capacity = dimensions.x * dimensions.y * dimensions.z;
	_data = new T[_capacity]{};
	_dimensions = dimensions;
	_forceStatic = forceStatic;

	std::copy(data.begin(), data.end(), _data);
}

template <typename T>
Arn::Tensor3DVector<T>::Tensor3DVector(const Tensor3DVector& other)
{
	delete[] _data;

	_data = new T[other._capacity];
	_dimensions = other._dimensions;
	_capacity = other._capacity;
	_forceStatic = other._forceStatic;

	std::copy(other._data, other._data + other._capacity, _data);
}

template <typename T>
Arn::Tensor3DVector<T>::Tensor3DVector(Tensor3DVector&& other) noexcept
{
	delete[] _data;

	_data = other._data;
	_dimensions = other._dimensions;
	_forceStatic = other._forceStatic;
	_capacity = other._capacity;

	other._data = nullptr;
}

template <typename T>
Arn::Tensor3DVector<T>::~Tensor3DVector()
{
	delete[] _data;
}

template<typename T>
void Arn::Tensor3DVector<T>::Init(Vector3<size_t> dimensions, bool forceStatic)
{
	if (!_data)
	{
		_capacity = dimensions.x * dimensions.y * dimensions.z;
		_data = new T[_capacity]{};
		_dimensions = dimensions;
		_forceStatic = forceStatic;
	}
}

template <typename T>
Arn::Tensor3DVector<T>& Arn::Tensor3DVector<T>::operator=(const Tensor3DVector& other)
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
Arn::Tensor3DVector<T>& Arn::Tensor3DVector<T>::operator=(std::initializer_list<T> data)
{
	assert("Too many elements given" && data.size() <= _dimensions.x * _dimensions.y * _dimensions.z);
	std::copy(data.begin(), data.end(), _data);
	std::fill(_data + data.size(), _data + _dimensions.x * _dimensions.y * _dimensions.z, 0);
	return *this;
}

template <typename T>
Arn::Tensor3DVector<T>& Arn::Tensor3DVector<T>::operator=(Tensor3DVector&& other) noexcept
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
T& Arn::Tensor3DVector<T>::operator[](const Vector3<size_t> indexes)
{
	// Calculation to find the index : x + (max_x * y) + (max_y * max_x * z)
	return _data[indexes.x + (indexes.y * _dimensions.x) + (indexes.z * _dimensions.x * _dimensions.y)];
}

template <typename T>
T& Arn::Tensor3DVector<T>::At(const Vector3<size_t> indexes)
{
	//Secure Checker
	assert("Outside the size of the Width" && indexes.x < _dimensions.x);
	assert("Outside the size of the Height" && indexes.y < _dimensions.y);

	// Calculation to find the index : x + (max_x * y) + (max_y * max_x * z)
	return _data[indexes.x + (indexes.y * _dimensions.x) + (indexes.z * _dimensions.x * _dimensions.y)];
}

template<typename T>
size_t Arn::Tensor3DVector<T>::PosConvert(Vector3<size_t> indexes) const
{
	return indexes.x + (indexes.y * _dimensions.x) + (indexes.z * _dimensions.x * _dimensions.y);
}

template <typename T>
T* Arn::Tensor3DVector<T>::Data()
{
	return _data;
}

template <typename T>
void Arn::Tensor3DVector<T>::Reserve(const size_t newAlloc)
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
void Arn::Tensor3DVector<T>::ShrinkToFit()
{
	if (_capacity < _dimensions.x * _dimensions.y) { return; }

	T* temp{ new T[_dimensions.x * _dimensions.y] };
	std::copy(_data, _data + _dimensions.x * _dimensions.y, temp);
	delete[] _data;
	_data = temp;
	_capacity = _dimensions.x * _dimensions.y;
}

template <typename T>
Arn::Vector3<size_t> Arn::Tensor3DVector<T>::Dimensions() const
{
	return _dimensions;
}

template <typename T>
size_t Arn::Tensor3DVector<T>::Width() const
{
	return _dimensions.x;
}

template <typename T>
size_t Arn::Tensor3DVector<T>::Height() const
{
	return _dimensions.y;
}

template<typename T>
size_t Arn::Tensor3DVector<T>::Depth() const
{
	return _dimensions.z;
}

template <typename T>
size_t Arn::Tensor3DVector<T>::MaxSize() const
{
	return _dimensions.x * _dimensions.y * _dimensions.z;
}

template <typename T>
size_t Arn::Tensor3DVector<T>::Capacity() const
{
	return _capacity;
}

template <typename T>
bool Arn::Tensor3DVector<T>::Empty()
{
	return _data == _data + _capacity;
}

template <typename T>
T* Arn::Tensor3DVector<T>::Begin()
{
	return _data;
}

template <typename T>
T* Arn::Tensor3DVector<T>::End()
{
	return _data + _capacity + 1;
}

template <typename T>
void Arn::Tensor3DVector<T>::Fill(const T& value)
{
	std::fill(_data, _data + _dimensions.x * _dimensions.y * *_dimensions.z, value);
}

template<typename T>
void Arn::Tensor3DVector<T>::FillSection(const T& value, Arn::Vector3<size_t> topLeft, Arn::Vector3<size_t> bottomRight)
{
	for (size_t x{ topLeft.x }; x < bottomRight.x; ++x)
	{
		for (size_t y{ topLeft.y }; y < bottomRight.y; ++y)
		{
			for (size_t z{ topLeft.z }; z < bottomRight.z; ++z)
			{
				this->operator[]({ x,y,z }) = value;
			}
		}
	}
}

#endif
