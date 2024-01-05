#ifndef	ARSON_CLASS_TENSOR_2D_VECTOR_H
#define ARSON_CLASS_TENSOR_2D_VECTOR_H

#include <initializer_list>
#include "Arson/Common/Struct_Common.h"

namespace Arn
{
	//Specialized 2D array class of variable length, designed to optimize cache
	template <typename T>
	class Tensor2DVector
	{
		Vector2<size_t> _dimensions{ 1,1 };

		//Actual tensor
		T* _data{};
		size_t _capacity{};
		bool FORCE_STATIC{};

	public:
		//Constructor
		explicit Tensor2DVector(Vector2<size_t> dimensions, bool force_static = false);
		//Alternative Constructor
		Tensor2DVector(Vector2<size_t> dimensions, std::initializer_list<T> tensor, bool force_static = false);
		//Copy Constructor
		Tensor2DVector(const Tensor2DVector& delta_tensor);
		//Move Constructor
		Tensor2DVector(Tensor2DVector&& delta_tensor) noexcept;
		//Destructor
		~Tensor2DVector();

		//Copy assignment
		Tensor2DVector& operator=(const Tensor2DVector& delta_tensor);
		//Operator= List assignment
		Tensor2DVector& operator=(std::initializer_list<T> tensor);
		//Move assignment
		Tensor2DVector& operator=(Tensor2DVector&& delta_tensor) noexcept;

		//Return the Element stored in the position given
		T& operator[](Vector2<size_t> indexes);

		//Return the Element stored in the position given
		//WARNING : Will throw an error if the index is outside dimension length
		T& at(Vector2<size_t> indexes);

		//Changes the size of the tensor with the new_dimensions
		//WARNING : If tensor is shrank, elements will be removed
		void resize(Vector2<size_t> new_dimensions);

		//Direct access to the underlying array making up the tensor
		T* data();
		//Reallocates the capacity of the tensor if the new_alloc is greater than the Current Capacity
		void reserve(size_t new_alloc);
		//Resizes the capacity of the tensor to the size of the tensor
		void shrink_to_fit();
		//Returns the dimensions of the tensor
		[[nodiscard]] Vector2<size_t> dimensions() const;
		//Returns the Current Width of the Tensor
		[[nodiscard]] size_t width() const;
		//Returns the Current Height of the Tensor
		[[nodiscard]] size_t height() const;
		//Returns the maximum possible number of elements in the tensor
		[[nodiscard]] size_t max_size() const;
		//Returns the amount of elements allocated for the tensor
		[[nodiscard]] size_t capacity() const;
		//Checks whether the container is empty
		bool empty();
		//Returns a pointer to the beginning
		T* begin();
		//Returns a pointer to the end (element following the last element of the tensor)
		T* end();
		//Fill the container with specified value
		void fill(const T& value);
	};
#include "Tensor2D/Vector/Tensor2DVector_src.h"
#include "Tensor2D/Vector/Tensor2DVector_init.h"
}

#endif
