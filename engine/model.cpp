#include "model.h"
#include "io.h"
#include "my_math.h"

Model::Model(std::string_view filename) : filename(filename) {
  std::ifstream file;
  file.open(filename.data());
  if (!file.is_open()) {
    std::cerr << "Couldn't open " << filename << " successfully\n";
    return;
  }

  this->loadPoints(file);
}

void Model::loadPoints(std::ifstream &file) noexcept {
  std::string buffer;
  while (std::getline(file, buffer)) {
    std::array<std::string_view, 3> arr = split_N<3>(buffer, " ");

    maths::Vertex v{std::stof(std::string(arr[0])),
                    std::stof(std::string(arr[1])),
                    std::stof(std::string(arr[2])), 1.0f};

    this->vertices.push_back(v);
  }
}

void Model::draw(Renderer &renderer) const noexcept {
  renderer.draw(this->filename);
}
