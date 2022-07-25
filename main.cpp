/*
Geometry lib c++ source code.


Date: 13/07/2022
Author: R. Tonneau (romain.tonneau@gmail.com)

Next to do:
    - implement cross-product
    - implement dot-product
    - implement vector only case
    - implement norm (which one? different possibility? at least the cartesian one!)
    - what about power operation?
    - implement transpose
*/

#include <iostream>
#include <vector>

// Local includes
#include "matrix.hpp"
#include "matrixUtils.hpp"
#include "matrixOperations.hpp"

int main()
{
    geometry::Matrix<int> x{3,4, {11,21,31,  12,22,32,  13,23,33,  14,24,34}};
    geometry::Matrix<int> y{3,4, {11,21,31,  12,22,32,  13,23,33,  14,24,34}};

    geometry::Matrix<int> z{2,2, {1,2, 3,4}};

    std::vector<int> other{51,52,53, 54,55,56, 57,58,59, 60,61,62};

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

    x = x * y;
    x.print();

    geometry::Matrix<int> a{x};
    x = x*x;
    a.print();

    x.print();
    x += 5.4;
    x.print();

    std::cout << "ok up to here\n";

    std::vector<int> data{};
    std::copy(std::begin(y), std::end(y), std::back_inserter(data));
    x.setValues(data);
    x.print();

    x = geometry::transpose(x);
    x.print();

    x = geometry::transpose(x);
    x.print();

    data.erase(std::next(data.begin(), 1), std::next(data.begin(), 3));
    x.setValues(data);
    x.print();


    /*
    geometry::Matrix<int> xx(geometry::utils::AdditionMCH<int>(50, &x.m_data, &x.m_size));
    geometry::Matrix<int> yy;

    xx.print();

    yy = xx * xx / 100;
    yy.print();

    geometry::Matrix<double> zz;
    zz = yy;
    zz += 0.1;
    zz.print();
    */
}