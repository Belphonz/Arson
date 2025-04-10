#ifndef ARSON_STYLE_H
#define ARSON_STYLE_H

namespace Arn
{
	// Primitive type Aliases
	using byte = unsigned char;
	using wideByte = unsigned short;
	using uint = unsigned int;

	//Type Cast
	template<class T, class U>
	constexpr T TCast(U var)
	{
		return static_cast<T>(var);
	}

	template<class T, class U>
	constexpr T* UpCast(U* ptr)
	{
		return dynamic_cast<T*>(ptr);
	}

	template<class T, class U>
	constexpr T* UnsafeCast(U* var)
	{
		return (T)var;
	}
}

// User defined literals
short operator ""_shrt(unsigned long long int);
size_t operator ""_sz(unsigned long long int);

#endif
