#include "model.h"
#include "io.h"
#include "my_math.h"
#include "tinyxml2.h"

Model::Model(tinyxml2::XMLElement *element): filename(element->Attribute("file")), color(element->FirstChildElement("color")) {
//  std::ifstream file;
//  file.open(filename.data());
//  if (!file.is_open()) {
//    std::cerr << "Couldn't open " << filename << " successfully\n";
//    return;
//  }
//
//  this->loadPoints(file);
}

void Model::loadPoints(std::ifstream &file) noexcept {
  std::string buffer;
  while (std::getline(file, buffer)) {
    std::array<std::string_view, 6> arr = split_N<6>(buffer, " ");

    this->vertices.emplace_back(std::stof(std::string(arr[0])),
                                std::stof(std::string(arr[1])),
                                std::stof(std::string(arr[2])), 1.0f);

    this->normals.emplace_back(std::stof(std::string(arr[3])),
                               std::stof(std::string(arr[4])),
                               std::stof(std::string(arr[5])), 1.0f);
  }
}

void Model::draw(Renderer &renderer) const noexcept {
  renderer.draw(this->filename);
}
