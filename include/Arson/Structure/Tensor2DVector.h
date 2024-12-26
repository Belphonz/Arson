#ifndef	ARSON_CLASS_TENSOR_2D_VECTOR_H
#define ARSON_CLASS_TENSOR_2D_VECTOR_H

#include <initializer_list>
#include "Arson/Structure/Vector2.h"

namespace Arn
{
	//Specialized 2D array class of variable length, designed to optimize cache
	template <typename T>
	class Tensor2DVector
	{
	private:
		Vector2<size_t> _dimensions{ 1,1 };

		//Actual tensor
		T* _data{};
		size_t _capacity{};
		bool _forceStatic{};

	public:
		//Constructor
		explicit Tensor2DVector(Vector2<size_t> dimensions, bool forceStatic = false);
		//Alternative Constructor
		Tensor2DVector(Vector2<size_t> dimensions, std::initializer_list<T> data, bool forceStatic = false);
		//Copy Constructor
		Tensor2DVector(const Tensor2DVector& other);
		//Move Constructor
		Tensor2DVector(Tensor2DVector&& other) noexcept;
		//Destructor
		~Tensor2DVector();

		//Copy assignment
		Tensor2DVector& operator=(const Tensor2DVector& other);
		//Operator= List assignment
		Tensor2DVector& operator=(std::initializer_list<T> data);
		//Move assignment
		Tensor2DVector& operator=(Tensor2DVector&& other) noexcept;

		//Return the Element stored in the position given
		T& operator[](Vector2<size_t> indexes);

		//Return the Element stored in the position given
		//WARNING : Will throw an error if the index is outside dimension length
		T& At(Vector2<size_t> indexes);

		//Changes the size of the tensor with the new_dimensions
		//WARNING : If tensor is shrank, elements will be removed
		//BUG:BREAKS ON SIZE UP
		void Resize(Vector2<size_t> newDimensions);

		//Direct access to the underlying array making up the tensor
		T* Data();
		//Reallocates the capacity of the tensor if the new_alloc is greater than the Current Capacity
		void Reserve(size_t newAlloc);
		//Resizes the capacity of the tensor to the size of the tensor
		void ShrinkToFit();
		//Returns the dimensions of the tensor
		[[nodiscard]] Vector2<size_t> Dimensions() const;
		//Returns the Current Width of the Tensor
		[[nodiscard]] size_t Width() const;
		//Returns the Current Height of the Tensor
		[[nodiscard]] size_t Height() const;
		//Returns the maximum possible number of elements in the tensor
		[[nodiscard]] size_t MaxSize() const;
		//Returns the amount of elements allocated for the tensor
		[[nodiscard]] size_t Capacity() const;
		//Checks whether the container is empty
		bool Empty();
		//Returns a pointer to the beginning
		T* Begin();
		//Returns a pointer to the end (element following the last element of the tensor)
		T* End();
		//Fill the container with specified value
		void Fill(const T& value);
	};
#include "../src/Tensor2D/Vector/Tensor2DVector_src.h"
#include "../src/Tensor2D/Vector/Tensor2DVector_init.h"
}

#endif
