
#ifndef LINEAR_ALGEBRA_H
#define LINEAR_ALGEBRA_H

#include <string>
#include <iostream>

typedef double data_type;

#ifdef LINEAR_ALGEBRA_NO_CHECK
inline void verify(bool condition, std::string error) {}
#else
inline void verify(bool condition, std::string error)
{
	if(!condition)
	{
		std::cerr << error << std::endl;
		std::exit(-1);
	}
}
#endif /* LINEAR_ALGEBRA_NO_CHECK */

#include "Vector.h"
#include "Matrix.h"

#endif /* LINEAR_ALGEBRA_H */
