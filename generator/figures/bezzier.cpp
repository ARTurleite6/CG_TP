#include "bezzier.h"
#include "io.h"
#include "my_math.h"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <initializer_list>

Bezzier::Bezzier(const std::string &filepath, float tesselation): tesselation(tesselation) {
    std::ifstream file;
    file.open(filepath);

    if(!file.is_open()) {
        throw std::invalid_argument("File does not exist");
    }

    std::cout << "entrei aqui\n";

    int number_patches = 0;
    file >> number_patches;
    file.ignore();

    std::string buffer;

    for(int i = 0; i < number_patches; ++i) {
        std::getline(file, buffer);
        std::array<std::string_view, 16> arr = split_N<16>(buffer, ", ");

        std::array<int, 16> res{};
        for(int j = 0; j < 16; j++) {
            res[j] = std::stoi(std::string(arr[j]));
        }

        this->patchesIndices.push_back(res);
    }

    int number_vertices = 0;
    file >> number_vertices;
    file.ignore();

    for(int i = 0; i < number_vertices; ++i) {
        std::getline(file, buffer);
        std::array<std::string_view, 3> arr = split_N<3>(buffer, ", ");

        for(const auto value : arr) {
            std::cout << value << '\n';
        }

        maths::Vertex coords { 
            std::stof(std::string(arr[0])),
            std::stof(std::string(arr[1])),
            std::stof(std::string(arr[2])),
            0.1f };

        this->vertices.push_back(coords);
    }

}

maths::Vertex Bezzier::getPoint(const matrix::Matrix<maths::Vertex, 4, 4> &mA, float u, float v) {
    using namespace maths;

    matrix::Matrix<float, 1, 4> uVertex {
        u * u * u, u * u, u, 1.0f
    };

    matrix::Matrix<float, 4, 1> vVertex {
        v * v * v,
        v * v,
        v,
        1.0f,
    };
    return (uVertex * mA * vVertex)[0][0];
}

std::vector<maths::Vertex> Bezzier::calculatePoints() const noexcept {

    using namespace maths;

    std::vector<Vertex> vertex;
    vertex.reserve(this->patchesIndices.size() * static_cast<unsigned long>(this->tesselation) * static_cast<unsigned long>(this->tesselation));

    int iTesselation = static_cast<int>(this->tesselation);
    for(const auto &patch : this->patchesIndices) {

        auto pointsMatrix = matrix::Matrix<maths::Vertex, 4, 4>{
                this->vertices[patch[0]], this->vertices[patch[1]],
                this->vertices[patch[2]], this->vertices[patch[3]],
                this->vertices[patch[4]], this->vertices[patch[5]],
                this->vertices[patch[6]], this->vertices[patch[7]],
                this->vertices[patch[8]], this->vertices[patch[9]],
                this->vertices[patch[10]], this->vertices[patch[11]],
                this->vertices[patch[12]], this->vertices[patch[13]],
                this->vertices[patch[14]], this->vertices[patch[15]],
        };


        auto mA = pointsMatrix.patchBezzier();

        for(int uI = 0; uI < iTesselation; ++uI) {

            float uValue = static_cast<float>(uI) / this->tesselation;
            float uNextValue = static_cast<float>(uI + 1) / this->tesselation;

            for (int vI = 0; vI < iTesselation; ++vI) {
            
                float vValue = static_cast<float>(vI) / this->tesselation;
                float vNextValue =
                    static_cast<float>(vI + 1) / this->tesselation;


                vertex.push_back(Bezzier::getPoint(mA, uValue, vValue));
                vertex.push_back(Bezzier::getPoint(mA, uValue, vNextValue));
                vertex.push_back(Bezzier::getPoint(mA, uNextValue, vNextValue));

                vertex.push_back(Bezzier::getPoint(mA, uValue, vValue));
                vertex.push_back(Bezzier::getPoint(mA, uNextValue, vNextValue));
                vertex.push_back(Bezzier::getPoint(mA, uNextValue, vValue));
            }
        }
    }

    return vertex;
}

void Bezzier::storeVertices(std::string_view outFile) const noexcept {
    auto result = this->calculatePoints();

    std::ofstream file;
    file.open(outFile.data());
    if(!file.is_open()) {
        std::cerr << "Error creating file named: " << outFile << '\n';
        return;
    }


    for(const auto point : result) {
        file << point.x << " " << point.y << " " << point.z << '\n';
    }

}