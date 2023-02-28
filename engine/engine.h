#ifndef ENGINE_H
#define ENGINE_H
#include "camera.h"
#include <cstdint>
#include <memory>
#include <string_view>
#include "model.h"
#include <tinyxml2.h>
#include "group.h"

class Engine {
public:
  Engine() = default;
  explicit Engine(std::string_view xml_file);
  Engine(Engine &&) = delete;
  Engine(const Engine &) = delete;
  Engine &operator=(Engine &&) = delete;
  Engine &operator=(const Engine &) = delete;
  ~Engine() = default;

private:

  void loadCamera(tinyxml2::XMLElement *camera);
    
  tinyxml2::XMLDocument doc;

  std::uint32_t window_width{}, window_height{};
  std::unique_ptr<camera_engine::Camera> camera;
  std::unique_ptr<Group> group;
};

#endif
