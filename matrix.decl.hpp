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
#include "exceptions.hpp"

namespace geometry{

    using utils::Coord;

    template<class T=double>
    class Matrix
    {
    public: // attributes
        std::vector<T> m_data{};
        std::vector<std::size_t> m_size{0, 0};

    public: // METHODS
        // --------------------------- CONSTRUCTORS ---------------------------
        Matrix() {} // --> (0,0) size with no data in it.

        // Specify size but no data to populate with, still m_data is allocated
        // with correct size and sets to 0.
        Matrix(std::size_t line, std::size_t col):
            m_size{line, col},
            m_data(line*col, 0)
            {}

        // Specify size and give data from brace initialization.
        Matrix(std::size_t line, std::size_t col, std::initializer_list<T> list):
            Matrix(line, col)
        {
            std::copy(list.begin(), list.end(), m_data.begin());
        }

        // Copy constructor.
        Matrix(const Matrix<T>& other);

        // Advanced copy constructor to support creation with math operations.
        Matrix(const utils::MatrixConstructorHelper<T>& ope);

        // Type conversion from U to T.
        template<typename U>
        Matrix(const Matrix<U>& other);

        // --------------------------- DESTRUCTORS ----------------------------
        virtual ~Matrix() {}

        // ---------------------- OPERATORS OVERLOADING -----------------------
        // -> Assignement
        template<typename U>
        Matrix<T>& operator=(const Matrix<U>& mat);
        Matrix<T>& operator=(const Matrix<T>& mat);
        Matrix<T>& operator=(std::initializer_list<T> list);

        // -> Math operations with single value
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

        // -> Math operations with other Matrices
        Matrix<T> operator*(const Matrix<T>& value);
        Matrix<T> operator+(const Matrix<T>& value);
        Matrix<T> operator/(const Matrix<T>& value);
        Matrix<T> operator-(const Matrix<T>& value);
        Matrix<T>& operator*=(Matrix<T>& value);
        Matrix<T>& operator+=(Matrix<T>& value);
        Matrix<T>& operator/=(Matrix<T>& value);
        Matrix<T>& operator-=(Matrix<T>& value);

        // ------------------- ASK INFO MEMBERS (-> const) --------------------
        std::size_t nLines()   const {return m_size.at(0);}
        std::size_t nColumns() const {return m_size.at(1);}
        std::size_t length() const {
            return std::accumulate(std::begin(m_size),
                                   std::end(m_size),
                                   1,
                                   std::multiplies<>()
                                   );
        }
        const std::vector<std::size_t>& dimension() const {return m_size;}
        void print() const;
        bool isZero() const{
            return std::all_of(m_data.begin(),
                               m_data.end(),
                               [](auto i) { return i==0; });
        }
        T at(std::size_t index) const {return m_data.at(index);}
        std::vector<T> getLine (const std::size_t line) const;
        std::vector<T> getColumn (const std::size_t line) const;

        // ----------------------- DATA MODIFIER MEMBERS ----------------------
        void setValues(const std::vector<T> &values);
        void clear() {std::fill(m_data.begin(), m_data.end(), 0);}
        void reset() {m_data.clear(); m_size.clear();}

        //TO BE IMPLEMENTED
        void resize(const std::size_t line, const std::size_t column);

    // --------------------------- PROTECTED METHODS --------------------------
    protected:
        // ------------------- ASK INFO MEMBERS (-> const) --------------------
        bool isSameSize(const Matrix<T>& other) const {
            return (this->nLines()==other.nLines()) & (this->nColumns()==other.nColumns());
        }

        int flatCoord(const std::size_t line, const std::size_t col) const {
            return line + col * m_size.at(0);
        }

        int flatCoord(const Coord coord) const;
        Coord coord2D(const std::size_t flat) const;
        const std::vector<T>& getElements() const {return m_data;}

        // ---------------- SANITY CHECKS MEMBERS (-> const) ------------------
        // ---> all these methods can throws exceptions

        // -> Exceptions::SizeMismatch()
        void checkSize(const Matrix<T>& other) const{
            if(other.length() != this->length())
                throw Exeptions::SizeMismatch(this->length(), other.length());
        }

        void checkLength(const std::size_t length) const{
            if(length != this->length())
                throw Exeptions::SizeMismatch(this->length(), length);
        }

        // ----------------------- DATA MODIFIER MEMBERS ----------------------
        /*
        void setSize(std::initializer_list<std::size_t> list){
            if ()
            std::copy(list.begin(), list.end(), m_size.begin());
        }
        */
    };

}

#endif