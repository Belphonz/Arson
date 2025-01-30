#ifndef	ARSON_CLASS_TENSOR_3D_VECTOR_H
#define ARSON_CLASS_TENSOR_3D_VECTOR_H

#include <initializer_list>
#include <Arson/Common/StructCommon.h>

namespace Arn
{
	//Specialized 3D array class of variable length, designed to optimize cache
	template <typename T>
	class Tensor3DVector
	{
	private:
		Vector3<size_t> _dimensions{ 1,1,1 };

		//Actual tensor
		T* _data{};
		size_t _capacity{};
		bool _forceStatic{};

	public:
		Tensor3DVector() = default;
		//Constructor
		Tensor3DVector(Vector3<size_t> dimensions, bool forceStatic = false);
		//Alternative Constructor
		Tensor3DVector(Vector3<size_t> dimensions, std::initializer_list<T> data, bool forceStatic = false);
		//Copy Constructor
		Tensor3DVector(const Tensor3DVector& other);
		//Move Constructor
		Tensor3DVector(Tensor3DVector&& other) noexcept;
		//Destructor
		~Tensor3DVector();
		//Late Constructor
		void Init(Vector3<size_t> dimensions, bool forceStatic = false);

		//Copy assignment
		Tensor3DVector& operator=(const Tensor3DVector& other);
		//Operator= List assignment
		Tensor3DVector& operator=(std::initializer_list<T> data);
		//Move assignment
		Tensor3DVector& operator=(Tensor3DVector&& other) noexcept;

		//Return the Element stored in the position given
		T& operator[](Vector3<size_t> indexes);

		//Return the Element stored in the position given
		//WARNING : Will throw an error if the index is outside dimension length
		T& At(Vector3<size_t> indexes);
		//Converts the position given into the Absolute Position in the Tensor
		[[nodiscard]] size_t PosConvert(Vector3<size_t> indexes) const;

		//Direct access to the underlying array making up the tensor
		T* Data();
		//Reallocates the capacity of the tensor if the new_alloc is greater than the Current Capacity
		void Reserve(size_t newAlloc);
		//Resizes the capacity of the tensor to the size of the tensor
		void ShrinkToFit();
		//Returns the dimensions of the tensor
		[[nodiscard]] Vector3<size_t> Dimensions() const;
		//Returns the Current Width of the Tensor
		[[nodiscard]] size_t Width() const;
		//Returns the Current Height of the Tensor
		[[nodiscard]] size_t Height() const;
		//Returns the Current Depth of the Tensor
		[[nodiscard]] size_t Depth() const;
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
		//Fill a part of the Tensor with specified value
		void FillSection(const T& value, Arn::Vector3<size_t> topLeft, Arn::Vector3<size_t> bottomRight);
	};
}
#include <Arson/../../src/Tensor3DVectorSrc.h>

#endif
