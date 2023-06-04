#include "pyramid.h"

Pyramid::Pyramid(const std::vector<float> &args)
    : height(args[0]), slices(static_cast<std::uint32_t>(args[1])) {
  float step = std::numbers::pi_v<float> * 2 / static_cast<float>(slices);

  float beginTop = 1.0f / 4.0f;
  float radiusTex = 3.0f / 16.0f;
  float beginBase = 5.0f / 8.0f;
  float beginLateral = 3.0f / 8.0f;
  float lateralTexStep = 1.0f / static_cast<float>(slices);

  for (int i = 0; i < slices; ++i) {
    float angle = step * static_cast<float>(i);
    float next_angle = step * static_cast<float>(i + 1);
    float middle_height = height / 2;
    float currentTexLateral = static_cast<float>(i) * lateralTexStep;
    float nextTexLateral = static_cast<float>(i + 1) * lateralTexStep;

    // top
    this->vertices.emplace_back(0.0f, middle_height, 0.0f, 1.0f);
    this->normals.emplace_back(0.0f, 1.0f, 0.0f, 0.0f);
    this->texCoords.emplace_back(beginTop + radiusTex, radiusTex);

    this->vertices.emplace_back(std::sin(angle), middle_height, std::cos(angle),
                                1.0f);
    this->normals.emplace_back(std::sin(angle), 0, std::cos(angle), 0.0f);
    this->texCoords.emplace_back(beginTop + radiusTex +
                                     (std::cos(angle) * radiusTex),
                                 radiusTex + (radiusTex * std::sin(angle)));

    this->vertices.emplace_back(std::sin(next_angle), middle_height,
                                std::cos(next_angle), 1.0f);
    this->normals.emplace_back(std::sin(next_angle), 0, std::cos(next_angle),
                               0.0f);
    this->texCoords.emplace_back(
        beginTop + radiusTex + (std::cos(next_angle) * radiusTex),
        radiusTex + (radiusTex * std::sin(next_angle)));

    // lateral

    this->vertices.emplace_back(std::sin(angle), middle_height, std::cos(angle),
                                1.0f);
    this->normals.emplace_back(std::sin(angle), 0.0f, std::cos(angle), 0.0f);
    this->texCoords.emplace_back(currentTexLateral, 1.0f);

    this->vertices.emplace_back(std::sin(angle), -middle_height,
                                std::cos(angle), 1.0f);
    this->normals.emplace_back(std::sin(angle), 0.0f, std::cos(angle), 0.0f);
    this->texCoords.emplace_back(currentTexLateral, beginLateral);

    this->vertices.emplace_back(std::sin(next_angle), -middle_height,
                                std::cos(next_angle), 1.0f);
    this->normals.emplace_back(std::sin(next_angle), 0.0f, std::cos(next_angle),
                               0.0f);
    this->texCoords.emplace_back(nextTexLateral, beginLateral);

    this->vertices.emplace_back(std::sin(angle), middle_height, std::cos(angle),
                                1.0f);
    this->normals.emplace_back(std::sin(angle), 0.0f, std::cos(angle), 0.0f);
    this->texCoords.emplace_back(currentTexLateral, 1.0f);

    this->vertices.emplace_back(std::sin(next_angle), -middle_height,
                                std::cos(next_angle), 1.0f);
    this->normals.emplace_back(std::sin(next_angle), 0.0f, std::cos(next_angle),
                               0.0f);
    this->texCoords.emplace_back(nextTexLateral, beginLateral);

    this->vertices.emplace_back(std::sin(next_angle), middle_height,
                                std::cos(next_angle), 1.0f);
    this->normals.emplace_back(std::sin(next_angle), 0.0f, std::cos(next_angle),
                               0.0f);
    this->texCoords.emplace_back(nextTexLateral, 1.0f);

    //base
    this->vertices.emplace_back(0.0f, -middle_height, 0.0f, 1.0f);
    this->normals.emplace_back(0.0f, -1.0f, 0.0f, 1.0f);
    this->texCoords.emplace_back(beginBase + radiusTex, radiusTex);

    this->vertices.emplace_back(-std::sin(angle), -middle_height,
                                std::cos(angle), 1.0f);
    this->normals.emplace_back(-std::sin(angle), 0.0f, std::cos(angle), 0.0f);
    this->texCoords.emplace_back(beginBase + radiusTex +
                                     (std::cos(angle) * radiusTex),
                                 radiusTex + (std::sin(angle) * radiusTex));

    this->vertices.emplace_back(-std::sin(next_angle), -middle_height,
                                std::cos(next_angle), 1.0f);
    this->normals.emplace_back(-std::sin(next_angle), 0.0f,
                               std::cos(next_angle), 0.0f);
    this->texCoords.emplace_back(
        beginBase + radiusTex + (std::cos(next_angle) * radiusTex),
        radiusTex + (std::sin(next_angle) * radiusTex));
  }
}
