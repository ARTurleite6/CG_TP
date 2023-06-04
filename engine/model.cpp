#include "model.h"

Model::Model(tinyxml2::XMLElement *element)
    : filename(element->Attribute("file")),
      color(element->FirstChildElement("color")) {

  auto texture = element->FirstChildElement("texture");
  if (texture) {
    auto texture_attr = texture->FindAttribute("file");
    if (!texture_attr)
      throw errors::XMLParseError("Expected element Texture on element file");
    this->texture_file = texture_attr->Value();
  }
}

void Model::draw(Renderer &renderer) const noexcept {
  this->setupMaterial();
  renderer.draw(this->filename, this->texture_file);
}
