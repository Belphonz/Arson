#ifndef	ARSON_CLASS_MATRIX_H
#define ARSON_CLASS_MATRIX_H

#include <cstdarg>

namespace Arn
{
	//Multidimensional array class of variable dimension, designed to optimize cache 
	template <typename T, size_t Init_Dimension, size_t... Dimensions>
	class Matrix
	{
		inline static const size_t DIMENSION_AMOUNT{sizeof...(Dimensions) + 1};
		//Stores all dimensions size_wise
		inline static const size_t* _all_dimensions{new size_t[DIMENSION_AMOUNT]{Init_Dimension, Dimensions...}};

		//Find and Return the size of the array
		[[nodiscard]] static size_t array_size() ;
		const size_t _size{array_size()};

		//Actual matrix
		T* _data{new T[_size]{}};

	public:
		//Default Constructor
		Matrix() = default;
		//Constructor 
		Matrix(std::initializer_list<T> matrix);
		//Copy Constructor
		Matrix(const Matrix& delta_matrix);
		//Move Constructor
		Matrix(Matrix&& delta_matrix) noexcept;
		//Destructor
		~Matrix();

		//Copy assignment 
		Matrix& operator=(const Matrix& delta_matrix);
		//Operator= List assignment   
		Matrix& operator=(std::initializer_list<T> matrix);
		//Move assignment
		Matrix& operator=(Matrix&& delta_matrix) noexcept;

		//Return the Element stored in the position given
		//WARNING : Will throw an error if not the correct amount of indexes are given
		T& at(std::initializer_list<size_t> indexes);

		//Return the Element stored in the position given
		//WARNING : Will throw an error if not the correct amount of indexes are given
		//WARNING : Will throw an error if the index is outside dimension length
		T& secure_at(std::initializer_list<size_t> indexes);

		//Direct access to the underlying array making up the Matrix
		T* data();
		//Returns the maximum possible number of elements in Dimension given
		template <size_t Dimension>
		[[nodiscard]] size_t size();
		//Returns the maximum possible number of elements in Dimension given
		size_t size(size_t dimension);
		//Returns the maximum possible number of elements in the Matrix
		[[nodiscard]] size_t max_size() const;
		//Checks whether the container is empty
		bool empty();
		//Returns a pointer to the beginning
		T* begin();
		//Returns a pointer to the end (element following the last element of the matrix)
		T* end();
		//Fill the container with specified value
		void fill(const T& value);
	};
	#include "Matrix_src.h"
	#include "Matrix_init.h"

}


#endif
