
/*
Geometry library file
Date: 19/07/2022
Author: R. Tonneau (romain.tonneau@gmail.com)
*/

#ifndef GEOMETRY__MATRIXOPERATION_DECL__GUARD__2207
#define GEOMETRY__MATRIXOPERATION_DECL__GUARD__2207

// STANDARD INCLUDES
#include <iostream>

namespace geometry{

    template<typename T> class Matrix; // Need to forward declare matrix.

    template<typename T>
    Matrix<T> transpose(const Matrix<T>& obj);

}
#endif