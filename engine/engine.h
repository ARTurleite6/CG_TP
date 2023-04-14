#ifndef ENGINE_H
#define ENGINE_H
#include "camera.h"
#include "group.h"
#include "model.h"
#include <tinyxml2.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

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

  inline void draw() const noexcept {
    for (const auto &group : this->groups) {
      group.draw();
    }
  }

  inline void moveCameraRight() noexcept {
    this->camera->moveHorizontally(0.1f);
  }

  inline void moveCameraLeft() noexcept {
    this->camera->moveHorizontally(-0.1f);
  }

  inline void moveCameraUp() noexcept { this->camera->moveVertically(0.1f); }

  inline void moveCameraDown() noexcept {
    this->camera->moveVertically(-0.1f);
  }

private:
  void loadCamera(tinyxml2::XMLElement *camera);

  tinyxml2::XMLDocument doc;

  std::uint32_t window_width{}, window_height{};
  std::unique_ptr<camera_engine::Camera> camera;
  std::vector<Group> groups;
  std::string xml_file;
};

void reshape(int width, int height);
void display();
void processInput(unsigned char key, int x, int y);

static Engine *engine = nullptr;

#endif
