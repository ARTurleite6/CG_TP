#include <stdexcept>
#ifndef MATRIX_H
#define MATRIX_H

template <class T, std::uint32_t C, std::uint32_t L> 
class Matrix {
    explicit Matrix(const T &value) {
        std::uint32_t column = 0;
        for(int i = 0; i < L; ++i) {
            this->m[column] = value;
            column += 1;
        }
    }

    const std::array<T, C> &operator[](int i) const {
        if(this->m.size() <= i) throw std::out_of_range("Matrix out of bounds");
        return this->m[i];
    }

    private:
        std::array<std::array<T, C>, L> m{};
};

#endif // MATRIX_HÇ_l0kjçhg5v3cf4xvw