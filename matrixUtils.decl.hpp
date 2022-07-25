/*
Geometry library file
Date: 19/07/2022
Author: R. Tonneau (romain.tonneau@gmail.com)
*/

#ifndef GEOMETRY__MATRIXUTILS_DECL__GUARD__2207
#define GEOMETRY__MATRIXUTILS_DECL__GUARD__2207

// STANDARD INCLUDES
#include <vector>
#include <array>
#include <iostream>

// LOCAL INCLUDES


namespace geometry
{
    namespace utils{
        using Coord = std::array<std::size_t,2>;

        // (X,Y,Z) -> (X + Y * DX + Z * DY * DX)
        inline std::size_t flatCoord(std::size_t nLines, const Coord coord)
        {
            return coord.at(0) + coord.at(1)*nLines;
        }

        inline Coord coord2D(std::size_t nLines, std::size_t nCols, const std::size_t flat)
        {
            return (nCols==0)? Coord({flat, 0}) : Coord({flat%nLines, (flat/nLines)%nCols});
        }

        template<typename T>
        bool areAllElementsZero(const std::vector<T>& vec)
        {
            return std::all_of(std::begin(vec),
                               std::end(vec),
                               [](auto i) { return i==0; });
        }

        template<typename T>
        T multiplyElements(const std::vector<T>& vec) {
            return std::accumulate(std::begin(vec),
                                   std::end(vec),
                                   1,
                                   std::multiplies<>()
                                   );
        }

        template <class T>
        class MatrixConstructorHelper
        {
        protected:
            const std::vector<T>* mp_data{};
            const std::vector<T>* mp_values{};
            const std::vector<std::size_t>* mp_size{};

        public:
            MatrixConstructorHelper() = delete;
            MatrixConstructorHelper(T value, const std::vector<T>* data, const std::vector<std::size_t>* size):
                mp_values{new std::vector<T>{value}},
                mp_data{data},
                mp_size{size}
                {}

            MatrixConstructorHelper(const std::vector<T>* values, const std::vector<T>* data, const std::vector<std::size_t>* size):
                mp_values{values},
                mp_data{data},
                mp_size{size}
                {}

            virtual ~MatrixConstructorHelper() {}

            std::size_t nLines() const {return mp_size->at(0);}
            std::size_t nColumns() const {return mp_size->at(1);}

            virtual T at(std::size_t index) const {return this->operation(mp_data->at(index), (mp_values->size()>1)?index:0);}
            virtual T operation(T value, std::size_t index=0) const {return value;} // default = no operation on value

            T value(std::size_t index=0) const {return mp_values->at(index);}
        };

        template<class T>
        class AdditionMCH: public MatrixConstructorHelper<T>
        {
        public:

            AdditionMCH(T value, const std::vector<T>* data, const std::vector<std::size_t>* size):
                MatrixConstructorHelper<T>(value, data, size) {}

            AdditionMCH(const std::vector<T>* values, const std::vector<T>* data, const std::vector<std::size_t>* size):
                MatrixConstructorHelper<T>(values, data, size) {}

            ~AdditionMCH() {}

            T operation(T value, std::size_t index=0) const override {return value+this->mp_values->at(index);}
        };

        template<class T>
        class SoustractionMCH: public MatrixConstructorHelper<T>
        {
        public:
            SoustractionMCH(T value, const std::vector<T>* data, const std::vector<std::size_t>* size):
                MatrixConstructorHelper<T>(value, data, size) {}

            SoustractionMCH(const std::vector<T>* values, const std::vector<T>* data, const std::vector<std::size_t>* size):
                MatrixConstructorHelper<T>(values, data, size) {}

            ~SoustractionMCH() {}

            T operation(T value, std::size_t index=0) const override {return value-this->mp_values->at(index);}
        };

        template<class T>
        class MultiplicationMCH: public MatrixConstructorHelper<T>
        {
        public:
            MultiplicationMCH(T value, const std::vector<T>* data, const std::vector<std::size_t>* size):
                MatrixConstructorHelper<T>(value, data, size) {}

            MultiplicationMCH(const std::vector<T>* values, const std::vector<T>* data, const std::vector<std::size_t>* size):
                MatrixConstructorHelper<T>(values, data, size) {}

            ~MultiplicationMCH() {}

            T operation(T value, std::size_t index=0) const override {return value*this->mp_values->at(index);}
        };

        template<class T>
        class DivisionMCH: public MatrixConstructorHelper<T>
        {
        public:
            DivisionMCH(T value, const std::vector<T>* data, const std::vector<std::size_t>* size):
                MatrixConstructorHelper<T>(value, data, size) {}

            DivisionMCH(const std::vector<T>* values, const std::vector<T>* data, const std::vector<std::size_t>* size):
                MatrixConstructorHelper<T>(values, data, size) {}

            ~DivisionMCH() {}

            T operation(T value, std::size_t index=0) const override {return value/this->mp_values->at(index);}
        };

        template<class T>
        class TransposeMCH: public MatrixConstructorHelper<T>
        {
        public:
            //vector<int>n_v (v.rbegin(), v.rend());
            TransposeMCH(const std::vector<T>* data, const std::vector<std::size_t>* size):
                MatrixConstructorHelper<T>(
                    static_cast<T>(0),
                    data,
                    new std::vector<std::size_t>(size->rbegin(), size->rend())) {}

            TransposeMCH(T value, const std::vector<T>* data, const std::vector<std::size_t>* size):
                MatrixConstructorHelper<T>(
                    value,
                    data,
                    new std::vector<std::size_t>(size->rbegin(), size->rend())) {}

            TransposeMCH(const std::vector<T>* values, const std::vector<T>* data, const std::vector<std::size_t>* size):
                MatrixConstructorHelper<T>(
                    values,
                    data,
                    new std::vector<std::size_t>(size->rbegin(), size->rend())) {}

            ~TransposeMCH() {}

            T operation(T value, std::size_t index=0) const override {return value;}
            T at(std::size_t index) const override {
                if(index==0) return this->operation(this->mp_data->at(0));
                //Get corresponding coordinates in transposed matrix.
                Coord coord=coord2D(this->mp_size->at(0),
                                    this->mp_size->at(1),
                                    index);
                //Compute corresponding index in non-transposed matrix.
                index = flatCoord(this->mp_size->at(1), {coord.at(1), coord.at(0)});
                return this->operation( this->mp_data->at(index),
                                       (this->mp_values->size()>1)?index:0);
            }
        };

    }
}
#endif