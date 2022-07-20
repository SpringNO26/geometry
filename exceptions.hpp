/*
geometry Library source code.
Date: 13/07/2022
Author: R. Tonneau (romain.tonneau@gmail.com)
*/

#ifndef GEOMETRY_EXCEPTIONS_GUARD_2207
#define GEOMETRY_EXCEPTIONS_GUARD_2207

// STANDARD INCLUDES
#include <exception>
#include <string>


// MESHSUBSTRATE INCLUDES

namespace geometry{
    namespace Exeptions{
        class GeometryException: public std::exception
        {
        protected:
            std::string m_error{};

        public:
            GeometryException(std::string_view error)
                : m_error{error}
            {
                m_error = "Error: " + m_error;
            }
            const char *what() const noexcept override{
                return m_error.c_str();
            }
        };

        class SizeMismatch: public GeometryException
        {
        public:
            SizeMismatch(int size1, int size2):
                GeometryException("Size mismatch: ")
            {
                m_error += "size1: " + std::to_string(size1);
                m_error += " & size2: " + std::to_string(size2);
            }
        };

    }
}

#endif