#include "bezzier.h"
#include "io.h"
#include "my_math.h"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <initializer_list>

Bezzier::Bezzier(const std::string &filepath, float tesselation)
    : tesselation(tesselation) {
  std::ifstream file;
  file.open(filepath);

  if (!file.is_open()) {
    throw std::invalid_argument("File does not exist");
  }

  int number_patches = 0;
  file >> number_patches;
  file.ignore();

  std::string buffer;

  for (int i = 0; i < number_patches; ++i) {
    std::getline(file, buffer);
    std::array<std::string_view, 16> arr = split_N<16>(buffer, ", ");

    std::array<int, 16> res{};
    for (int j = 0; j < 16; j++) {
      res[j] = std::stoi(std::string(arr[j]));
    }

    this->patchesIndices.push_back(res);
  }

  int number_vertices = 0;
  file >> number_vertices;
  file.ignore();

  for (int i = 0; i < number_vertices; ++i) {
    std::getline(file, buffer);
    std::array<std::string_view, 3> arr = split_N<3>(buffer, ", ");

    maths::Vertex coords{std::stof(std::string(arr[0])),
                         std::stof(std::string(arr[1])),
                         std::stof(std::string(arr[2])), 0.1f};

    this->vertices.push_back(coords);
  }
}

std::pair<maths::Vertex, maths::Vertex>
Bezzier::getPoint(const maths::Matrix<maths::Vertex, 4, 4> &mA, float u,
                  float v) {
  using namespace maths;

  Matrix<float, 1, 4> uVertex{u * u * u, u * u, u, 1.0f};

  Matrix<float, 1, 4> uDVertex{3.0f * u * u, 2.0f * u, 1.0f, 0.0f};

  Matrix<float, 4, 1> vVertex{
      v * v * v,
      v * v,
      v,
      1.0f,
  };

  Matrix<float, 4, 1> vDVertex{
      3.0f * v * v,
      2.0f * v,
      1.0f,
      0.0f,
  };

  auto u_tangent = (uDVertex * mA * vVertex)[0][0];
  auto v_tangent = (uVertex * mA * vDVertex)[0][0];
  auto normal_vector = v_tangent.crossProduct(u_tangent);
  normal_vector.normalize();
  auto point = (uVertex * mA * vVertex)[0][0];

  return std::make_pair(point, normal_vector);
}

std::tuple<std::vector<maths::Vertex>, std::vector<maths::Vertex>,
           std::vector<maths::Vertex2D>>
Bezzier::calculatePoints() const noexcept {

  using namespace maths;

  std::vector<Vertex> vertex;
  std::vector<Vertex> normals;
  std::vector<Vertex2D> texCoords;
  vertex.reserve(this->patchesIndices.size() *
                 static_cast<unsigned long>(this->tesselation) *
                 static_cast<unsigned long>(this->tesselation));

  int iTesselation = static_cast<int>(this->tesselation);
  for (const auto &patch : this->patchesIndices) {

    auto pointsMatrix = Matrix<maths::Vertex, 4, 4>{
        this->vertices[patch[0]],  this->vertices[patch[1]],
        this->vertices[patch[2]],  this->vertices[patch[3]],
        this->vertices[patch[4]],  this->vertices[patch[5]],
        this->vertices[patch[6]],  this->vertices[patch[7]],
        this->vertices[patch[8]],  this->vertices[patch[9]],
        this->vertices[patch[10]], this->vertices[patch[11]],
        this->vertices[patch[12]], this->vertices[patch[13]],
        this->vertices[patch[14]], this->vertices[patch[15]],
    };

    auto mA = pointsMatrix.patchBezzier();

    for (int uI = 0; uI < iTesselation; ++uI) {

      float uValue = static_cast<float>(uI) / this->tesselation;
      float uNextValue = static_cast<float>(uI + 1) / this->tesselation;

      for (int vI = 0; vI < iTesselation; ++vI) {

        float vValue = static_cast<float>(vI) / this->tesselation;
        float vNextValue = static_cast<float>(vI + 1) / this->tesselation;

        auto [point, normal_vector] = Bezzier::getPoint(mA, uValue, vValue);
        vertex.push_back(point);
        normals.push_back(normal_vector);
        texCoords.emplace_back(uValue, vValue);

        auto [point2, normal_vector2] =
            Bezzier::getPoint(mA, uValue, vNextValue);
        vertex.push_back(point2);
        normals.push_back(normal_vector2);
        texCoords.emplace_back(uValue, vNextValue);

        auto [point3, normal_vector3] =
            Bezzier::getPoint(mA, uNextValue, vNextValue);
        vertex.push_back(point3);
        normals.push_back(normal_vector3);
        texCoords.emplace_back(uNextValue, vNextValue);

        auto [point4, normal_vector4] = Bezzier::getPoint(mA, uValue, vValue);
        vertex.push_back(point4);
        normals.push_back(normal_vector4);
        texCoords.emplace_back(uValue, vValue);

        auto [point5, normal_vector5] =
            Bezzier::getPoint(mA, uNextValue, vNextValue);
        vertex.push_back(point5);
        normals.push_back(normal_vector5);
        texCoords.emplace_back(uNextValue, vNextValue);

        auto [point6, normal_vector6] =
            Bezzier::getPoint(mA, uNextValue, vValue);
        vertex.push_back(point6);
        normals.push_back(normal_vector6);
        texCoords.emplace_back(uNextValue, vValue);
      }
    }
  }

  return std::make_tuple(vertex, normals, texCoords);
}

void Bezzier::storeVertices(std::string_view outFile) const noexcept {
  auto [vertex, normals, texCoords] = this->calculatePoints();

  std::ofstream file;
  file.open(outFile.data());
  if (!file.is_open()) {
    std::cerr << "Error creating file named: " << outFile << '\n';
    return;
  }

  int iPoint = 0;
  for (const auto point : vertex) {
    auto tex = texCoords[iPoint];
    auto normal = normals[iPoint++];
    file << point.x << ' ' << point.y << ' ' << point.z << ' ' << normal.x
         << ' ' << normal.y << ' ' << normal.z << ' ' << tex << '\n';
  }
}
