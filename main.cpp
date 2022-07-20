/*
Geometry lib c++ source code.


Date: 13/07/2022
Author: R. Tonneau (romain.tonneau@gmail.com)
*/

#include <iostream>
#include <vector>

// Local includes
#include "matrix.hpp"
#include "matrixUtils.hpp"

int main()
{
    geometry::Matrix<int> x{3,3, {11,21,31,  12,22,32,  13,23,33}};
    geometry::Matrix<int> y{3,3, {11,21,31,  12,22,32,  13,23,33}};

    geometry::Matrix<int> z{2,2, {1,2, 3,4}};

    std::vector<int> other{51,52,53, 54,55,56, 57,58,59};

    x.print();

    std::cout << "Is zero? "
              << x.isZero()
              << "\n";

    std::cout << "Clearing... ";
    x.clear();
    x.print();

    std::cout << "Is zero? "
            << x.isZero()
            << "\n";

    x.setValues(other);
    x.print();

    std::cout << "Is zero? "
              << x.isZero()
              << "\n";

    /*
    x = x * y;
    x.print();

    geometry::Matrix<int> a{x};
    x = x*x;
    a.print();
    */

    x.print();
    x += 5.4;
    x.print();

    std::cout << "ok up to here\n";

    geometry::Matrix<int> xx(geometry::utils::AdditionMCH<int>(50, &x.m_data, &x.m_size));
    geometry::Matrix<int> yy;

    xx.print();

    yy = xx * xx / 100;
    yy.print();

    geometry::Matrix<float> zz;
    zz.print();
}