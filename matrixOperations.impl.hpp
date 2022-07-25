
/*
Geometry library file
Date: 19/07/2022
Author: R. Tonneau (romain.tonneau@gmail.com)
*/

#ifndef GEOMETRY__MATRIXOPERATION_IMPL__GUARD__2207
#define GEOMETRY__MATRIXOPERATION_IMPL__GUARD__2207

// STANDARD INCLUDES

// LOCAL INCLUDES
#include "matrixOperations.decl.hpp"
#include "matrix.decl.hpp"
#include "matrixUtils.hpp"


namespace geometry{

    template<typename T>
    Matrix<T> transpose(const Matrix<T>& obj){
        return Matrix<T>(utils::TransposeMCH<T>(&obj.getElements(), &obj.dimension()));
    }

}

#endif
