#ifndef PYRAMID_H
#define PYRAMID_H
#include "figure.h"

class Pyramid: public Figure {
    public:
        explicit Pyramid(const std::vector<float> &args);
        ~Pyramid() override = default;

    private:
        float height;
        std::uint32_t slices;
};

#endif // PYRAMID_H
