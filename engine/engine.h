#ifndef ENGINE_H
#define ENGINE_H
#include "camera.h"
#include "group.h"
#include "model.h"
#include <tinyxml2.h>
#include "renderer.h"

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

  inline void draw() noexcept {
    for (const auto &group : this->groups) {
      group.draw(this->renderer);
    }
  }

  inline void handleMouseMotion(int x, int y) noexcept {
    this->camera->handleMouseMotion(x, y);
  }

  void registerKey(unsigned char key);
  void unregisterKey(unsigned char key);

  void handleInput();

  inline void setMousePosition(int x, int y) noexcept {
    this->camera->setMousePosition(x, y);
  }

  inline void setCameraTracking(int tracking) {
    this->camera->setTrackingMode(tracking);
  }

private:
  void loadCamera(tinyxml2::XMLElement *camera);

  tinyxml2::XMLDocument doc;

  std::uint32_t window_width{}, window_height{};
  std::unique_ptr<camera_engine::Camera> camera;
  std::vector<Group> groups;
  std::string xml_file;

  Renderer renderer;

  std::array<bool, std::numeric_limits<unsigned char>::max()> keyboard{};
};

void reshape(int width, int height);
void display();
void processKeyDown(unsigned char key, int x, int y);
void processKeyUp(unsigned char key, int x, int y);

void passiveMouseFunc(int x, int y);
void mouseFunc(int button, int state, int x, int y);
void motionFunc(int x, int y);

static Engine *engine = nullptr;

#endif
