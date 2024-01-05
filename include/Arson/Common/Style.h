#ifndef ARSON_STYLE_H
#define ARSON_STYLE_H

namespace Arn
{
	// Primitive type Aliases
	using Byte = unsigned char;
	using WideByte = wchar_t;
	using UInt = unsigned int;
}

// User defined literals
short operator ""_shrt(unsigned long long int);
size_t operator ""_sz(unsigned long long int);

#endif
