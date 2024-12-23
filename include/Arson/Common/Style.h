#ifndef ARSON_STYLE_H
#define ARSON_STYLE_H

namespace Arn
{
	// Primitive type Aliases
	using byte = unsigned char;
	using wideByte = unsigned short;
	using uint = unsigned int;
}

// User defined literals
short operator ""shrt(unsigned long long int);
size_t operator ""sz(unsigned long long int);

#endif
