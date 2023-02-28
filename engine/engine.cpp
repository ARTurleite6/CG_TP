#include "engine.h"
#include "camera.h"
#include "tinyxml2.h"
#include <iostream>
#include <memory>
#include <string_view>

Engine::Engine(std::string_view xml_file)
    : doc(), window_width(800), window_height(800), camera(nullptr) {

  this->doc.LoadFile(xml_file.data());

  if (doc.Error()) {
    std::cout << "Error: " << doc.ErrorStr() << '\n';
    return;
  }

  auto world = doc.FirstChildElement("world");
  if (world == nullptr) {
    std::cout << "Error: world element not found" << '\n';
    return;
  }

  auto window = world->FirstChildElement("window");
  if (window == nullptr) {
    std::cout << "Error: window element not found" << '\n';
    return;
  }
  window->QueryUnsignedAttribute("width", &this->window_width);
  window->QueryUnsignedAttribute("height", &this->window_height);

  std::cout << this->window_width << ' ' << this->window_height << '\n';

  auto camera = world->FirstChildElement("camera");

  if (camera == nullptr) {
    std::cout << "Error: camera element not found" << '\n';
    return;
  }

  this->loadCamera(camera);

  auto group = world->FirstChildElement("group");
  this->group = std::make_unique<Group>(group);
}

void Engine::loadCamera(tinyxml2::XMLElement *camera) {
  camera_engine::Coordinates position;
  camera->QueryUnsignedAttribute("x", &position.x);
  camera->QueryUnsignedAttribute("y", &position.y);
  camera->QueryUnsignedAttribute("z", &position.z);
  std::cout << position.x << ' ' << position.y << ' ' << position.z << '\n';

  auto lookAt = camera->FirstChildElement("lookAt");
  if (lookAt == nullptr) {
    std::cout << "Error: lookAt element not found" << '\n';
    return;
  }
  camera_engine::Coordinates lookAtCoordinates;
  lookAt->QueryUnsignedAttribute("x", &lookAtCoordinates.x);
  lookAt->QueryUnsignedAttribute("y", &lookAtCoordinates.y);
  lookAt->QueryUnsignedAttribute("z", &lookAtCoordinates.z);
  std::cout << lookAtCoordinates.x << ' ' << lookAtCoordinates.y << ' '
            << lookAtCoordinates.z << '\n';

  auto up = camera->FirstChildElement("up");
  if (up == nullptr) {
    std::cout << "Error: up element not found" << '\n';
    return;
  }
  camera_engine::Coordinates upCoordinates;
  up->QueryUnsignedAttribute("x", &upCoordinates.x);
  up->QueryUnsignedAttribute("y", &upCoordinates.y);
  up->QueryUnsignedAttribute("z", &upCoordinates.z);
  std::cout << upCoordinates.x << ' ' << upCoordinates.y << ' '
            << upCoordinates.z << '\n';

  auto projection = camera->FirstChildElement("projection");
  if (projection == nullptr) {
    std::cout << "Error: projection element not found" << '\n';
    return;
  }
  camera_engine::Pov pov;
  projection->QueryUnsignedAttribute("fov", &pov.fov);
  projection->QueryUnsignedAttribute("near", &pov.near);
  projection->QueryUnsignedAttribute("far", &pov.far);
  std::cout << pov.fov << ' ' << pov.near << ' ' << pov.far << '\n';

  this->camera = std::make_unique<camera_engine::Camera>(
      position, lookAtCoordinates, upCoordinates, pov);
}
