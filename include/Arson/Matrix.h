#ifndef	ARSON_CLASS_MATRIX_H
#define ARSON_CLASS_MATRIX_H

#include <cstdarg>

namespace Arn
{
	//Multidimensional array class of variable dimension, designed to optimize cache 
	template <typename T, size_t Init_Dimension, size_t... Dimensions>
	class Matrix
	{
		const size_t _dimension_amount{sizeof...(Dimensions) + 1};
		//Stores all dimensions size_wise
		const size_t* _all_dimensions {new size_t[_dimension_amount]{Init_Dimension, Dimensions...}};

		//Find and Return the size of the array
		size_t array_size() const;
		const size_t _size{array_size()};

		//Actual matrix
		T* _data{new T[_size]};

	public:
		//Constructor 
		Matrix(std::initializer_list<T> matrix);

		//Return the Element stored in the position given
		//WARNING : Will throw an error if not the correct amount of indexes are given
		template <size_t Index, size_t... Sup_Index >
		T& at();

		//Return the Element stored in the position given
		//WARNING : Will throw an error if not the correct amount of indexes are given
		//WARNING : Will throw an error if the index is outside dimension length
		template <size_t Index, size_t... Sup_Index >
		T& secure_at();

		//Destructor
		~Matrix();
	};

#include "Matrix_src.h"
}


#endif
