#ifndef ENGINE_H
#define ENGINE_H
#include "camera.h"
#include "group.h"
#include "model.h"
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <tinyxml2.h>

class Engine {
public:
  Engine() = default;
  explicit Engine(std::string_view xml_file);
  Engine(Engine &&) = delete;
  Engine(const Engine &) = delete;
  Engine &operator=(Engine &&) = delete;
  Engine &operator=(const Engine &) = delete;
  ~Engine() = default;

  void run(int argc, char *argv[]) const;

  inline const camera_engine::Camera &getCamera() const noexcept {
    return *this->camera;
  }

  inline void draw() const noexcept { this->group->draw(); }

private:
  void loadCamera(tinyxml2::XMLElement *camera);

  tinyxml2::XMLDocument doc;

  std::uint32_t window_width{}, window_height{};
  std::unique_ptr<camera_engine::Camera> camera;
  std::unique_ptr<Group> group;
  std::string xml_file;
};

void reshape(int width, int height);
void display();

static Engine *engine = nullptr;

#endif
