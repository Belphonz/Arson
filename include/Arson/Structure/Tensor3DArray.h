#ifndef	ARSON_CLASS_TENSOR_3D_ARRAY_H
#define ARSON_CLASS_TENSOR_3D_ARRAY_H

#include <Arson/Common/StructCommon.h>

namespace Arn
{
	//Specialized 3D Static array struct, designed to optimize cache
	template <typename T, size_t SIZE_X, size_t SIZE_Y, size_t SIZE_Z>
	struct Tensor3DArray
	{
		//Actual tensor
		T Data[SIZE_X * SIZE_Y * SIZE_Z]{};

		//Return the Element stored in the position given
		T& operator[](Vector3<size_t> indexes);

		//Return the Element stored in the position given
		//WARNING : Will throw an error if the index is outside dimension length
		T& At(Vector3<size_t> indexes);

		//Returns the maximum possible number of elements in the tensor
		[[nodiscard]] size_t MaxSize() const;
		//Checks whether the container is empty
		bool Empty();
		//Returns a pointer to the beginning
		T* Begin();
		//Returns a pointer to the end (element following the last element of the tensor)
		T* End();
		//Fill the container with specified value
		void Fill(const T& value);
	};
#include <Arson/../../src/Tensor3DArraySrc.h>
}

#endif