/*
Geometry library file
Date: 19/07/2022
Author: R. Tonneau (romain.tonneau@gmail.com)
*/

#ifndef GEOMETRY__MATRIX_DECL__GUARD__2207
#define GEOMETRY__MATRIX_DECL__GUARD__2207

// STANDARD INCLUDES
#include <array>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>

// LOCAL INCLUDES
//#include "matrix.forward.hpp"
//#include "matrixUtils.forward.hpp"
#include "matrixUtils.hpp"

namespace geometry{

    using utils::Coord;

    //********************************* MATRIX ********************************
    template<class T=double>
    class Matrix
    {
    public: // attributes
        std::vector<T> m_data{};
        std::vector<std::size_t> m_size{0, 0};

    private: // Methods
        bool isSameSize(const Matrix<T>& other) const {
            return (this->nLines()==other.nLines()) & (this->nColumns()==other.nColumns());
        }

    public: //protected:
        int flatCoord(const std::size_t line, const std::size_t col) const {
            return line + col * m_size.at(0);
        }

        int flatCoord(const Coord coord) const;
        Coord coord2D(const std::size_t flat) const;
        std::vector<T> getLine(const std::size_t line); 
        std::vector<T> getColumn(const std::size_t line); 

    public:
        Matrix() {}
        Matrix(std::size_t line, std::size_t col): m_size{line, col}, m_data(line*col, 0) {}

        Matrix(std::size_t line, std::size_t col, std::initializer_list<T> list): Matrix(line, col)
        {
            std::copy(list.begin(), list.end(), m_data.begin());
        }

        Matrix(const Matrix<T>& other); // copy constructor
        Matrix(const utils::MatrixConstructorHelper<T>& ope); // advanced copy constructor

        virtual ~Matrix() {}

        Matrix<T>& operator=(const Matrix<T>& mat);
        Matrix<T>& operator=(std::initializer_list<T> list);

        Matrix<T> operator*(T value) {
            return Matrix<T>(utils::MultiplicationMCH<T>(value, &m_data, &m_size));
        }
        Matrix<T> operator+(T value) {
            return Matrix<T>(utils::AdditionMCH<T>(value, &m_data, &m_size));
        }
        Matrix<T> operator/(T value) {
            return Matrix<T>(utils::DivisionMCH<T>(value, &m_data, &m_size));
        }
        Matrix<T> operator-(T value) {
            return Matrix<T>(utils::SoustractionMCH<T>(value, &m_data, &m_size));
        }

        Matrix<T>& operator*=(T value);
        Matrix<T>& operator+=(T value);
        Matrix<T>& operator/=(T value);
        Matrix<T>& operator-=(T value);

        Matrix<T> operator*(const Matrix<T>& value);
        Matrix<T> operator+(const Matrix<T>& value);
        Matrix<T> operator/(const Matrix<T>& value);
        Matrix<T> operator-(const Matrix<T>& value);

        Matrix<T>& operator*=(Matrix<T>& value);
        Matrix<T>& operator+=(Matrix<T>& value);
        Matrix<T>& operator/=(Matrix<T>& value);
        Matrix<T>& operator-=(Matrix<T>& value);

        std::size_t nLines()   const {return m_size.at(0);}
        std::size_t nColumns() const {return m_size.at(1);}
        std::size_t size() const 
        {
            return std::accumulate(std::begin(m_size),
                                   std::end(m_size),
                                   1,
                                   std::multiplies<>()
                                   );
        }

        const std::vector<std::size_t>& dimension() const {return m_size;}
        void print();
        void setValues(const std::vector<T> &values);
        void clear() {std::fill(m_data.begin(), m_data.end(), 0);}
        void reset() {m_data.clear(); m_size.clear();}
        
        bool isZero() {
            return std::all_of(m_data.begin(),
                               m_data.end(),
                               [](auto i) { return i==0; });
        }

        const std::vector<T>& getElements() const {return m_data;}

        T at(std::size_t index) {return m_data.at(index);}

        //TO BE IMPLEMENTED
        void resize(const std::size_t line, const std::size_t column);
        void setValues(const Matrix &other);
    };

}

#endif