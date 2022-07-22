/*
Geometry library file
Date: 19/07/2022
Author: R. Tonneau (romain.tonneau@gmail.com)
*/

#ifndef GEOMETRY__MATRIX_IMPL__GUARD__2207
#define GEOMETRY__MATRIX_IMPL__GUARD__2207

// STANDARD INCLUDES
#include <vector>
#include <initializer_list> // for std::initializer_list
#include <algorithm>
#include <numeric>
#include <functional>
#include <stdexcept>
#include <iostream>
#include <iterator>
#include <cstring>

// LOCAL INCLUDES
//#include "matrix.decl.hpp"
//#include "matrixUtils.hpp"
#include "matrix.decl.hpp"
#include "exceptions.hpp"
#include "matrixUtils.hpp"

namespace geometry{

    // ============================ PUBLIC METHODS ============================
    // ----------------------------- CONSTRUCTORS -----------------------------
    template<class T>
    Matrix<T>::Matrix(const Matrix<T>& other)
        :Matrix<T>::Matrix(other.nLines(), other.nColumns())
    {
        this->setValues(other.getElements());
    }

    template<class T>
    Matrix<T>::Matrix(const utils::MatrixConstructorHelper<T>& ope)
        :Matrix<T>::Matrix(ope.nLines(), ope.nColumns())
    {
        for(std::size_t i=0; i<ope.nLines()*ope.nColumns(); i++)
            m_data.at(i) = ope.at(i);
    }

    template<class T> template<typename U>
    Matrix<T>::Matrix(const Matrix<U>& other)
        :Matrix<T>::Matrix(other.nLines(), other.nColumns())
    {
        for(std::size_t i=0; i<other.nLines()*other.nColumns(); i++)
            m_data.at(i) = static_cast<T>(other.at(i));
    }

    // ----------------------------- DESTRUCTORS ------------------------------

    // ------------------------ OPERATORS OVERLOADING -------------------------
    // -> Assignement
    template<class T> template<typename U>
    Matrix<T>& Matrix<T>::operator=(const Matrix<U>& mat)
    {
        this->reset();
        for(auto dim: mat.dimension())
            this->m_size.push_back(dim);
        for(auto elt: mat)
            this->m_data.push_back(static_cast<T>(elt));
        return *this;
    }

    template<class T>
    Matrix<T>& Matrix<T>::operator=(const Matrix<T>& mat)
    {
        this->reset();
        for(auto dim: mat.dimension())
            this->m_size.push_back(dim);
        for(auto elt: mat.getElements())
            this->m_data.push_back(elt);
        return *this;
    }

    template<class T>
    Matrix<T>& Matrix<T>::operator=(std::initializer_list<T> list)
    {
        // If the new list is a different size, reallocate it
        this->checkLength(static_cast<std::size_t>(list.size()));
        // Now initialize our array from the list
        std::copy(list.begin(), list.end(), m_data.begin());
        return *this;
    }

    // -> Math operations with single value
    template<class T>
    inline Matrix<T>& Matrix<T>::operator*=(T value)
    {
        for(int i=0; i<m_data.size(); i++)
            m_data.at(i) *= value;
        return *this;
    }

    template<class T>
    inline Matrix<T>& Matrix<T>::operator+=(T value)
    {
        for(int i=0; i<m_data.size(); i++)
            m_data.at(i) += value;
        return *this;
    }

    template<class T>
    inline Matrix<T>& Matrix<T>::operator-=(T value)
    {
        for(int i=0; i<m_data.size(); i++)
            m_data.at(i) -= value;
        return *this;
    }

    template<class T>
    inline Matrix<T>& Matrix<T>::operator/=(T value)
    {
        for(int i=0; i<m_data.size(); i++)
            m_data.at(i) /= value;
        return *this;
    }

    // -> Math operations with other Matrices

    template<class T>
    Matrix<T> Matrix<T>::operator*(const Matrix<T>& value)
    {
        this->checkSize(value);
        return Matrix<T>(utils::MultiplicationMCH<T>(&value.getElements(), &m_data, &m_size));
    }

    template<class T>
    Matrix<T> Matrix<T>::operator+(const Matrix<T>& value)
    {
        this->checkSize(value);
        return Matrix<T>(utils::AdditionMCH<T>(&value.getElements(), &m_data, &m_size));
    }

    template<class T>
    Matrix<T> Matrix<T>::operator-(const Matrix<T>& value)
    {
        this->checkSize(value);
        return Matrix<T>(utils::SoustractionMCH<T>(&value.getElements(), &m_data, &m_size));
    }

    template<class T>
    Matrix<T> Matrix<T>::operator/(const Matrix<T>& value)
    {
        this->checkSize(value);
        return Matrix<T>(utils::DivisionMCH<T>(&value.getElements(), &m_data, &m_size));
    }

    template<class T>
    inline Matrix<T>& Matrix<T>::operator*=(Matrix<T>& value)
    {
        this->checkSize(value);
        for(std::size_t i=0; i<m_data.size(); i++)
            m_data.at(i) *= value.at(i);
        return *this;
    }

    template<class T>
    inline Matrix<T>& Matrix<T>::operator+=(Matrix<T>& value)
    {
        this->checkSize(value);
        for(std::size_t i=0; i<m_data.size(); i++)
            m_data.at(i) += value.at(i);
        return *this;
    }

    template<class T>
    inline Matrix<T>& Matrix<T>::operator-=(Matrix<T>& value)
    {
        this->checkSize(value);
        for(int i=0; i<m_data.size(); i++)
            m_data.at(i) -= value.at(i);
        return *this;
    }

    template<class T>
    inline Matrix<T>& Matrix<T>::operator/=(Matrix<T>& value)
    {
        this->checkSize(value);
        for(int i=0; i<m_data.size(); i++)
            m_data.at(i) /= value.at(i);
        return *this;
    }

    // --------------------- ASK INFO MEMBERS (-> const) ----------------------

    template<class T>
    void Matrix<T>::print() const
    {
        std::cout << m_size.at(0)
                  << " X "
                  << m_size.at(1)
                  << " matrix:\n";
        for(int i=0; i<m_size.at(0); i++) // Loop over lines
        {
            auto line = this->getLine(i);
            std::copy(line.begin(), line.end(), std::ostream_iterator<T>(std::cout, " "));
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    template<class T>
    std::vector<T> Matrix<T>::getLine(const std::size_t line) const
    {
        std::vector<T> out(m_size.at(1));
        for(int i=0; i<m_size.at(1); i++)
            out.at(i) = m_data.at(line+i*m_size.at(0));
        return out;
    }

    template<class T>
    std::vector<T> Matrix<T>::getColumn(const std::size_t col) const
    {
        std::vector<T> out{};
        out.reserve(m_size.at(1));

        auto index = this->flatCoord(0, col);

        typename std::vector<T>::iterator it_begin =
            std::next(m_data.begin(), index);

        typename std::vector<T>::iterator it_end =
            std::next(m_data.begin(), index+m_size.at(1));

        std::copy(it_begin, it_end, std::back_inserter(out));
        return out;
    }

    // ------------------------- DATA MODIFIER MEMBERS ------------------------
    template<class T>
    void Matrix<T>::setValues(const std::vector<T> &values)
    {
        this->checkLength(values.size());
        std::copy(std::begin(values), std::end(values), std::begin(*this));
    }

    //TO BE IMPLEMENTED
    /*
    template<class T>
    void Matrix<T>::resize(const std::size_t line, const std::size_t column)
    {
        //Total size must be equals
        if (line*column != this->length())
            throw Exeptions::SizeMismatch(this->size, line*column);
        m_size.at(0) = line;
        m_size.at(1) = column;
    }
    */

    // =========================== PROTECTED METHODS ==========================
    // --------------------- ASK INFO MEMBERS (-> const) ----------------------
    // (X,Y,Z) -> (X + Y * DX + Z * DY * DX)
    template<class T>
    int Matrix<T>::flatCoord(const Coord coord) const
    {
        int out{coord.front()};
        for (int i=1; i<m_size.size(); i++)
            out += (coord.at(i) * m_size.at(i));
        return out;
    }

    template<class T>
    Coord Matrix<T>::coord2D(const std::size_t flat) const
    {
        if (m_size.at(1)==0) return {flat, 0};
        return {flat%m_size.at(0), (flat/m_size.at(0))%m_size.at(1)};
    }

    // ------------------ SANITY CHECKS MEMBERS (-> const) --------------------

    // ----------------------- DATA MODIFIER MEMBERS ----------------------
    template<class T>
    void Matrix<T>::setSize(std::initializer_list<std::size_t> list){
            this->checkLength(utils::multiplyElements(std::vector<std::size_t>{list}));
            m_size.clear();
            std::copy(std::begin(list), std::end(list), std::back_inserter(m_size));
        }
    //TO BE IMPLEMENTED

}

#endif