#ifndef ARSON_STRUCT_COMMON_H
#define ARSON_STRUCT_COMMON_H

namespace Arn
{
	//General Vector2 struct
	template <typename T>
	struct Vector2
	{
		T x{};
		T y{};
	};

	//General Vector3 struct
	template <typename T>
	struct Vector3
	{
		T x{};
		T y{};
		T z{};
	};
}


#endif
